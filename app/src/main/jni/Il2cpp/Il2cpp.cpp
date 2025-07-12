//
// Created by Perfare on 2020/7/4.
//

#include "Il2cpp.h"
#include <chrono>
#include <dlfcn.h>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <jni.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <unordered_map>
#include <thread>
#include "dobby.h"
#include "il2cpp-tabledefs.h"
#include "il2cpp-class.h"

#include "xdl/include/xdl.h"

#define DO_API(r, n, p) r(*n) p

#include "il2cpp-api-functions.h"

#undef DO_API

static uint64_t il2cpp_base = 0;

void init_il2cpp_api(void *handle){
#define DO_API(r, n, p)                                                                                                \
    {                                                                                                                  \
        n = (r(*) p)xdl_sym(handle, #n, nullptr);                                                                      \
    }

#include "il2cpp-api-functions.h"

#undef DO_API
}

void il2cpp_api_init(void *handle)
{
    init_il2cpp_api(handle);
    if (il2cpp_domain_get_assemblies)
    {
        Dl_info dlInfo;
        if (dladdr((void *)il2cpp_domain_get_assemblies, &dlInfo))
        {
            il2cpp_base = reinterpret_cast<uint64_t>(dlInfo.dli_fbase);
        }
    }
    else
    {
        return;
    }
    while (!il2cpp_is_vm_thread(nullptr))
    {
        sleep(1);
    }
}

bool g_DoLog = true;
class PauseLog
{
  public:
    PauseLog()
    {
        g_DoLog = false;
    }
    ~PauseLog()
    {
        g_DoLog = true;
    }
};
#define PAUSE_LOG PauseLog _

namespace Il2cpp
{
    void Init()
    {
        auto handle = xdl_open("libil2cpp.so", 0);
        il2cpp_api_init(handle);
        xdl_close(handle);
    }

    

    bool EnsureAttached()
    {
        auto curr = il2cpp_thread_current();
        if (curr)
        {
            return true;
        }
        auto *thread = il2cpp_thread_attach(il2cpp_domain_get());
        while (!il2cpp_is_vm_thread(thread))
        {
            sleep(1);
        }
        if (!thread)
        {
            return false;
        }
        return true;
    }

    void Detach()
    {
        auto curr = il2cpp_thread_current();
        if (!curr)
        {
            return;
        }
        il2cpp_thread_detach(curr);
    }

    Il2CppDomain *GetDomain()
    {
        return il2cpp_domain_get();
    }

    Il2CppAssembly *GetAssembly(const char *name)
    {
        auto result = il2cpp_domain_assembly_open(il2cpp_domain_get(), name);
        return result;
    }

    Il2CppImage *GetImage(Il2CppAssembly *assembly)
    {
        auto result = il2cpp_assembly_get_image(assembly);
        return result;
    }

    Il2CppImage *GetCorlib()
    {
        return il2cpp_get_corlib();
    }

    Il2CppImage *GetImage(const char *assemblyName)
    {
        return GetImage(GetAssembly(assemblyName));
    }

    Il2CppClass *GetClass(Il2CppImage *image, const char *name)
    {
        std::string nameStr = name;
        size_t dotIndex = nameStr.find_last_of('.');
        std::string classNamespace = (dotIndex == std::string::npos) ? "" : nameStr.substr(0, dotIndex);
        const std::string className = nameStr.substr(dotIndex + 1);
        auto result = il2cpp_class_from_name(image, classNamespace.c_str(), className.c_str());
        if (!result)
        {
            auto size = il2cpp_image_get_class_count(image);
            for (size_t i{0}; i < size; i++)
            {
                auto klass = il2cpp_image_get_class(image, i);
                if (klass->getFullName().compare(name) == 0)
                {
                    result = klass;
                    break;
                }
            }
        }
        return result;
    }

    MethodInfo *GetClassMethod(Il2CppClass *klass, const char *methodName, int argsCount)
    {
        auto result = il2cpp_class_get_method_from_name(klass, methodName, argsCount);
        return result;
    }

    Il2CppImage *GetClassImage(Il2CppClass *klass)
    {
        return il2cpp_class_get_image(klass);
    }

    FieldInfo *GetClassField(Il2CppClass *klass, const char *fieldName)
    {
        auto result = il2cpp_class_get_field_from_name(klass, fieldName);
        return result;
    }

    void GetFieldValue(Il2CppObject *object, FieldInfo *field, void *outValue)
    {
        il2cpp_field_get_value(object, field, outValue);
    }

    void SetFieldValue(Il2CppObject *object, FieldInfo *field, void *newValue)
    {
        il2cpp_field_set_value(object, field, newValue);
    }

    FieldInfo *GetClassFields(Il2CppClass *klass, void **iter)
    {
        return il2cpp_class_get_fields(klass, iter);
    }

    void GetFieldStaticValue(FieldInfo *field, void *outValue)
    {
        il2cpp_field_static_get_value(field, outValue);
    }

    void SetFieldStaticValue(FieldInfo *field, void *outValue)
    {
        il2cpp_field_static_set_value(field, outValue);
    }

    Il2CppObject *GetFieldValueObject(Il2CppObject *object, FieldInfo *field)
    {
        return il2cpp_field_get_value_object(field, object);
    }

    MethodInfo *GetClassMethods(Il2CppClass *klass, void **iter)
    {
        return il2cpp_class_get_methods(klass, iter);
    }

    int32_t GetClassSize(Il2CppClass *klass)
    {
        return il2cpp_class_instance_size(klass);
    }

    uint32_t GetObjectSize(Il2CppObject *object)
    {
        return il2cpp_object_get_size(object);
    }
    Il2CppObject *NewObject(Il2CppClass *klass)
    {
        return il2cpp_object_new(klass);
    }

    uint32_t GetMethodParamCount(MethodInfo *method)
    {
        return il2cpp_method_get_param_count(method);
    }

    const char *GetMethodParamName(MethodInfo *method, uint32_t index)
    {
        return il2cpp_method_get_param_name(method, index);
    }

    std::vector<Il2CppClass *> GetClasses(Il2CppImage *image, const char *filter)
    {
        std::vector<Il2CppClass *> classes;
        auto size = il2cpp_image_get_class_count(image);
        for (size_t i{0}; i < size; i++)
        {
            auto klass = il2cpp_image_get_class(image, i);
            if (!filter || strstr(klass->getFullName().c_str(), filter))
                classes.push_back(klass);
        }
        return classes;
    }

    const char *GetMethodName(MethodInfo *method)
    {
        return il2cpp_method_get_name(method);
    }

    const char *GetClassName(Il2CppClass *klass)
    {
        return il2cpp_class_get_name(klass);
    }

    const char *GetClassNamespace(Il2CppClass *klass)
    {
        return il2cpp_class_get_namespace(klass);
    }

    uintptr_t GetFieldOffset(FieldInfo *field)
    {
        return il2cpp_field_get_offset(field);
    }

    void forEachClass(Il2CppClass *klass, void *classesPtr)
    {
        auto classes = *(std::vector<Il2CppClass *> *)classesPtr;
        classes.push_back(klass);
    }

    std::vector<Il2CppClass *> GetClasses()
    {
        std::vector<Il2CppClass *> classes;
        il2cpp_class_for_each(forEachClass, &classes);
        return classes;
    }

    std::unordered_map<Il2CppClass *, std::tuple<Il2CppClass **, size_t>> subClassesCache;
    const std::tuple<Il2CppClass **, size_t> &GetSubClasses(Il2CppClass *klass)
    {
        auto it = subClassesCache.find(klass);
        if (it != subClassesCache.end())
        {
            return it->second;
        }
        std::vector<Il2CppClass *> subClasses{};
        void *iter = nullptr;
        while (auto subKlass = il2cpp_class_get_nested_types(klass, &iter))
        {
            subClasses.push_back(subKlass);
        }
        subClassesCache.insert(std::make_pair(klass, std::make_tuple(subClasses.data(), subClasses.size())));
        return subClassesCache.at(klass);
    }

    Il2CppType *GetClassType(Il2CppClass *klass)
    {
        return il2cpp_class_get_type(klass);
    }

    bool GetClassIsGeneric(Il2CppClass *klass)
    {
        return il2cpp_class_is_generic(klass);
    }

    Il2CppClass *FindClass(const char *klassName)
    {
        PAUSE_LOG;
        auto &images = GetImages();
        for (auto image : images)
        {
            auto klass = image->getClass(klassName);
            if (klass)
                return klass;
        }
        return nullptr;
    }

    Il2CppClass *GetClassFromSystemType(Il2CppReflectionType *type)
    {
        return il2cpp_class_from_system_type(type);
    }

    Il2CppType *GetBaseType(Il2CppClass *klass)
    {
        return il2cpp_class_enum_basetype(klass);
    }

    bool GetClassIsValueType(Il2CppClass *klass)
    {
        return il2cpp_class_is_valuetype(klass);
    }

    bool GetClassIsEnum(Il2CppClass *klass)
    {
        return il2cpp_class_is_enum(klass);
    }

    Il2CppType *GetMethodReturnType(MethodInfo *method)
    {
        return il2cpp_method_get_return_type(method);
    }

    Il2CppType *GetMethodParam(MethodInfo *method, uint32_t index)
    {
        return il2cpp_method_get_param(method, index);
    }

    bool GetIsMethodGeneric(MethodInfo *method)
    {
        il2cpp_method_is_generic(method);
    }

    bool GetIsMethodInflated(MethodInfo *method)
    {
        return il2cpp_method_is_inflated(method);
    }

    Il2CppReflectionMethod *GetMethodObject(MethodInfo *method, Il2CppClass *refclass)
    {
        return il2cpp_method_get_object(method, refclass);
    }

    MethodInfo *GetMethodFromReflection(Il2CppReflectionMethod *method)
    {
        return il2cpp_method_get_from_reflection(method);
    }

    uint32_t GetMethodGenericCount(MethodInfo *method)
    {
        auto obj = method->getObject();
        auto args = obj->invoke_method<Il2CppArray<Il2CppObject *> *>("GetGenericArguments");
        return args->length();
    }

    MethodInfo *FindMethod(const char *klassName, const char *methodName, size_t argsCount)
    {
        PAUSE_LOG;
        auto &images = GetImages();
        for (auto image : images)
        {
            auto klass = image->getClass(klassName);
            if (klass)
            {
                return GetClassMethod(klass, methodName, argsCount);
            }
        }
        return nullptr;
    }

    Il2CppClass *GetMethodClass(MethodInfo *method)
    {
        return il2cpp_method_get_class(method);
    }

    Il2CppClass *GetClassFromType(Il2CppType *type)
    {
        return il2cpp_class_from_type(type);
    }

    Il2CppClass *GetTypeClass(Il2CppType *type)
    {
        return il2cpp_type_get_class_or_element_class(type);
    }

    bool GetTypeIsPointer(Il2CppType *type)
    {
        return il2cpp_type_is_pointer_type(type);
    }

    bool GetTypeIsStatic(Il2CppType *type)
    {
        return il2cpp_type_is_static(type);
    }

    Il2CppType *GetFieldType(FieldInfo *field)
    {
        return il2cpp_field_get_type(field);
    }

    const char *GetFieldName(FieldInfo *field)
    {
        return il2cpp_field_get_name(field);
    }

    int GetFieldFlags(FieldInfo *field)
    {
        return il2cpp_field_get_flags(field);
    }
    
    FieldInfo *FindField(const char *klassName, const char *fieldName)
    {
        PAUSE_LOG;
        auto &images = GetImages();
        for (auto image : images)
        {
            auto klass = image->getClass(klassName);
            if (klass)
            {
                return GetClassField(klass, fieldName);
            }
        }
        return nullptr;
    }

    const char *GetTypeName(Il2CppType *type)
    {
        return il2cpp_type_get_name(type);
    }

    Il2CppObject *GetTypeObject(Il2CppType *type)
    {
        return il2cpp_type_get_object(type);
    }

    const char *GetChars(Il2CppString *str)
    {
        return reinterpret_cast<const char *>(il2cpp_string_chars(str));
    }

    Il2CppString *NewString(const char *str)
    {
        return il2cpp_string_new(str);
    }

    const char *GetImageName(Il2CppImage *image)
    {
        return il2cpp_image_get_name(image);
    }

    uint32_t GetArrayLength(_Il2CppArray *array)
    {
        return il2cpp_array_length(array);
    }

    _Il2CppArray *ArrayNew(Il2CppClass *elementTypeInfo, il2cpp_array_size_t length)
    {
        return il2cpp_array_new(elementTypeInfo, length);
    }

    Il2CppObject *GetBoxedValue(Il2CppClass *klass, void *value)
    {
        return il2cpp_value_box(klass, value);
    }

    std::tuple<Il2CppAssembly **, size_t> assembliesCache{nullptr, 0};
    const std::tuple<Il2CppAssembly **, size_t> &GetAssemblies()
    {
        const auto &[ass, size2] = assembliesCache;
        if (size2 > 0)
        {
            return assembliesCache;
        }
        size_t size = 0;
        auto asss = il2cpp_domain_get_assemblies(GetDomain(), &size);
        assembliesCache = std::make_tuple(asss, size);
        return assembliesCache;
    }

    std::vector<Il2CppImage *> imagesCache;
    const std::vector<Il2CppImage *> &GetImages()
    {
        if (!imagesCache.empty())
            return imagesCache;
        const auto &[ass, size] = GetAssemblies();
        for (size_t i = 0; i < size; i++)
        {
            imagesCache.push_back(GetImage(ass[i]));
        }
        return imagesCache;
    }
} // namespace Il2cpp
