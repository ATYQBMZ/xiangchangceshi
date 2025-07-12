typedef unsigned long int u64; 
typedef unsigned long int u32;
   struct vec4{
    float x, y, z, w;
    vec4() { x = y = z = w = 0.0f; }
    vec4(float _x, float _y, float _z, float _w){
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
};
struct vec3{
    float x, y, z;
    constexpr vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
Vector2A WorldToScreenLibUnity(vec3 obj , float matrix[16]) {
	float ViewW = matrix[3] * obj.x + matrix[7] * obj.y + matrix[11] * obj.z + matrix[15];
	if (ViewW>0.01){
		float x  = px + (matrix[0] * obj.x + matrix[4] * obj.y + matrix[8] * obj.z + matrix[12]) / ViewW * px;
		float y  = py - (matrix[1] * obj.x + matrix[5] * obj.y + matrix[9] * obj.z + matrix[13]) / ViewW * py;
		return Vector2A(x, y);
	}else
		return Vector2A(0,0);
}  
 struct Bone_Conversion {
 Vector2A 头部;
 Vector2A 左锁骨;
 Vector2A 左肩膀;
 Vector2A 左肘关节;
 Vector2A 左手;
 Vector2A 右锁骨;
 Vector2A 右肩膀;
 Vector2A 右肘关节;
 Vector2A 右手;
 Vector2A 胸部;
 Vector2A 腹部;
 Vector2A 盆骨;
 Vector2A 左髋骨;
 Vector2A 左膝盖;
 Vector2A 左踝关节;
 Vector2A 左脚;
 Vector2A 右髋骨;
 Vector2A 右膝盖;
 Vector2A 右踝关节;
 Vector2A 右脚;
 vec3 头部_骨骼;
 vec3 胸部_骨骼;
 vec3 腹部_骨骼;
 vec3 盆骨_骨骼;
};
Bone_Conversion Bone; 
struct Transform{
    vec4 position;
    vec4 rotate;
    vec4 scale;
    Transform() : position({0, 0, 0, 0}), rotate({0, 0, 0, 0}), scale({ 0, 0, 0, 0}) {}
    Transform(vec4 _position, vec4 _rotate, vec4 _scale) : position(_position),rotate(_rotate),scale(_scale) {}
};
                                    
vec3 getBonePosition(u32 pMatricies, u32 pIndices, int Indices){
    vec4 outPos,  position;
    Transform transform, transform1;
    ReadBuffer(pMatricies + sizeof(Transform) * Indices, &transform1, sizeof(Transform));
    outPos = transform1.position;
    int out = 0;
    while (true){
        Indices = getDword(pIndices + Indices * 4);
        if (Indices < 0)
           break;
            
        ReadBuffer(pMatricies + sizeof(Transform) * Indices, &transform, sizeof(Transform));

        position.x = outPos.x * transform.scale.x;
        position.y = outPos.y * transform.scale.y;
        position.z = outPos.z * transform.scale.z;
        
        outPos.x = (transform.rotate.x * 2 * transform.rotate.z - transform.rotate.y * -2 * transform.rotate.w) * position.z + (transform.rotate.z * -2 * transform.rotate.w - transform.rotate.x * -2 * transform.rotate.y) * position.y + (transform.rotate.y * -2 * transform.rotate.y - transform.rotate.z * 2 * transform.rotate.z) * position.x + position.x + transform.position.x;
        outPos.y = (transform.rotate.x * -2 * transform.rotate.w - transform.rotate.y * -2 * transform.rotate.z) * position.z + (transform.rotate.z * -2 * transform.rotate.z - transform.rotate.x * 2 * transform.rotate.x) * position.y + (transform.rotate.y * 2 * transform.rotate.x - transform.rotate.z * -2 * transform.rotate.w) * position.x + position.y + transform.position.y;
        outPos.z = (transform.rotate.x * -2 * transform.rotate.x - transform.rotate.y * 2 * transform.rotate.y) * position.z + (transform.rotate.z * 2 * transform.rotate.y - transform.rotate.x * -2 * transform.rotate.w) * position.y + (transform.rotate.y * -2 * transform.rotate.w - transform.rotate.z * -2 * transform.rotate.x) * position.x + position.z + transform.position.z;
        
        if(outPos.x==0)  break;     
    }
    return vec3(outPos.x, outPos.y, outPos.z);
}

vec3 getTransformPos(u32 pTransform){
    u32 transform = Read_Pointers(pTransform + 0x10, 0);
    u32 accessReadOnly = Read_Pointers(transform + 0x38, 0);
    int Indices = getDword(transform + 0x40);
    u32 pMatricies = Read_Pointers(accessReadOnly + 0x18, 0);
    u32 pIndices = Read_Pointers(accessReadOnly + 0x20, 0);
    return getBonePosition(pMatricies, pIndices, Indices);
}

void Unity_Bone_Transform(long Bone_Transform, float Transform_Matrix[16], Bone_Conversion &Bone) {

    intptr_t 头部_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 59, 0);
    vec3 头部_骨骼 = getTransformPos(头部_骨骼点);
    头部_骨骼.y = 头部_骨骼.y + 0.2;
    Vector2A 头部 = WorldToScreenLibUnity(头部_骨骼, Transform_Matrix);
    	
	uintptr_t 左锁骨_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 34, 0);
    vec3 左锁骨_骨骼 = getTransformPos(左锁骨_骨骼点);
    Vector2A 左锁骨 = WorldToScreenLibUnity(左锁骨_骨骼, Transform_Matrix);
	
	uintptr_t 左肩膀_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 35, 0);
    vec3 左肩膀_骨骼 = getTransformPos(左肩膀_骨骼点);
    Vector2A 左肩膀 = WorldToScreenLibUnity(左肩膀_骨骼, Transform_Matrix);
	
	uintptr_t 左肘关节_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 36, 0);
    vec3 左肘关节_骨骼 = getTransformPos(左肘关节_骨骼点);
    Vector2A 左肘关节 = WorldToScreenLibUnity(左肘关节_骨骼, Transform_Matrix);
	
	uintptr_t 左手_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 37, 0);
    vec3 左手_骨骼 = getTransformPos(左手_骨骼点);
    Vector2A 左手 = WorldToScreenLibUnity(左手_骨骼, Transform_Matrix);
	
	uintptr_t 右锁骨_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 59, 0);
    vec3 右锁骨_骨骼 = getTransformPos(右锁骨_骨骼点);
    Vector2A 右锁骨 = WorldToScreenLibUnity(右锁骨_骨骼, Transform_Matrix);
	
	uintptr_t 右肩膀_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 60, 0);
    vec3 右肩膀_骨骼 = getTransformPos(右肩膀_骨骼点);
    Vector2A 右肩膀 = WorldToScreenLibUnity(右肩膀_骨骼, Transform_Matrix);
	
	uintptr_t 右肘关节_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 61, 0);
    vec3 右肘关节_骨骼 = getTransformPos(右肘关节_骨骼点);
    Vector2A 右肘关节 = WorldToScreenLibUnity(右肘关节_骨骼, Transform_Matrix);
	
	uintptr_t 右手_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 62, 0);
    vec3 右手_骨骼 = getTransformPos(右手_骨骼点);
    Vector2A 右手 = WorldToScreenLibUnity(右手_骨骼, Transform_Matrix);
	
	uintptr_t 胸部_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 5, 0);
    vec3 胸部_骨骼 = getTransformPos(胸部_骨骼点);
    Vector2A 胸部 = WorldToScreenLibUnity(胸部_骨骼, Transform_Matrix);
	
	uintptr_t 腹部_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 11, 0);
    vec3 腹部_骨骼 = getTransformPos(腹部_骨骼点);
    Vector2A 腹部 = WorldToScreenLibUnity(腹部_骨骼, Transform_Matrix);
	
	uintptr_t 盆骨_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 3, 0);
    vec3 盆骨_骨骼 = getTransformPos(盆骨_骨骼点);
    Vector2A 盆骨 = WorldToScreenLibUnity(盆骨_骨骼, Transform_Matrix);
	
	uintptr_t 左髋骨_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 24, 0);
    vec3 左髋骨_骨骼 = getTransformPos(左髋骨_骨骼点);
    Vector2A 左髋骨 = WorldToScreenLibUnity(左髋骨_骨骼, Transform_Matrix);
	
	uintptr_t 左膝盖_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 25, 0);
    vec3 左膝盖_骨骼 = getTransformPos(左膝盖_骨骼点);
    Vector2A 左膝盖 = WorldToScreenLibUnity(左膝盖_骨骼, Transform_Matrix);
	
	uintptr_t 左踝关节_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 26, 0);
    vec3 左踝关节_骨骼 = getTransformPos(左踝关节_骨骼点);
    Vector2A 左踝关节 = WorldToScreenLibUnity(左踝关节_骨骼, Transform_Matrix);
	
	uintptr_t 左脚_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 27, 0);
    vec3 左脚_骨骼 = getTransformPos(左脚_骨骼点);
    Vector2A 左脚 = WorldToScreenLibUnity(左脚_骨骼, Transform_Matrix);
	
	uintptr_t 右髋骨_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 28, 0);
    vec3 右髋骨_骨骼 = getTransformPos(右髋骨_骨骼点);
    Vector2A 右髋骨 = WorldToScreenLibUnity(右髋骨_骨骼, Transform_Matrix);
	
	uintptr_t 右膝盖_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 29, 0);
    vec3 右膝盖_骨骼 = getTransformPos(右膝盖_骨骼点);
    Vector2A 右膝盖 = WorldToScreenLibUnity(右膝盖_骨骼, Transform_Matrix);
	
	uintptr_t 右踝关节_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 30, 0);
    vec3 右踝关节_骨骼 = getTransformPos(右踝关节_骨骼点);
    Vector2A 右踝关节 = WorldToScreenLibUnity(右踝关节_骨骼, Transform_Matrix);
	
	uintptr_t 右脚_骨骼点 = Read_Pointers(Bone_Transform + 0x18 * 31, 0);
    vec3 右脚_骨骼 = getTransformPos(右脚_骨骼点);
    Vector2A 右脚 = WorldToScreenLibUnity(右脚_骨骼, Transform_Matrix);

    Bone.头部 = 头部;
    Bone.左锁骨 = 左锁骨;
    Bone.左肩膀 = 左肩膀;
    Bone.左肘关节 = 左肘关节;
    Bone.左手 = 左手;
    Bone.右锁骨 = 右锁骨;
    Bone.右肩膀 = 右肩膀;
    Bone.右肘关节 = 右肘关节;
    Bone.右手 = 右手;
    Bone.胸部 = 胸部;
    Bone.腹部 = 腹部;
    Bone.盆骨 = 盆骨;
    Bone.左髋骨 = 左髋骨;
    Bone.左膝盖 = 左膝盖;
    Bone.左踝关节 = 左踝关节;
    Bone.左脚 = 左脚;
    Bone.右髋骨 = 右髋骨;
    Bone.右膝盖 = 右膝盖;
    Bone.右踝关节 = 右踝关节;
    Bone.右脚 = 右脚;   
    Bone.头部_骨骼 = 头部_骨骼;
    Bone.胸部_骨骼 = 胸部_骨骼;
    Bone.腹部_骨骼 = 腹部_骨骼;
    Bone.盆骨_骨骼 = 盆骨_骨骼;
}
