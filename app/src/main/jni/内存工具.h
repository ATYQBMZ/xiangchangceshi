// syscall内存读写
#include <sys/syscall.h>
#include <dirent.h>
#include <thread>
#include <pthread.h>
#if defined(__arm__)
int process_vm_readv_syscall = 376;
int process_vm_writev_syscall = 377;
#elif defined(__aarch64__)
int process_vm_readv_syscall = 270;
int process_vm_writev_syscall = 271;
#elif defined(__i386__)
int process_vm_readv_syscall = 347;
int process_vm_writev_syscall = 348;
#else
int process_vm_readv_syscall = 310;
int process_vm_writev_syscall = 311;
#endif

typedef char PACKAGENAME;
int WriteBuffer(long address, void *buffer, int size)
{
	struct iovec iov_WriteBuffer, iov_WriteOffset;
	iov_WriteBuffer.iov_base = buffer;
	iov_WriteBuffer.iov_len = size;
	iov_WriteOffset.iov_base = (void *)address;
	iov_WriteOffset.iov_len = size;
	return syscall(SYS_process_vm_writev, getpid(), &iov_WriteBuffer, 1, &iov_WriteOffset, 1, 0);
}

ssize_t process_v(pid_t __pid, const struct iovec* __local_iov, unsigned long __local_iov_count,
                  const struct iovec* __remote_iov, unsigned long __remote_iov_count, unsigned long __flags, bool iswrite) {
    return syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

bool pvm(int target_pid , void* address, void* buffer, size_t size, bool iswrite) {
    struct iovec local[1];
    struct iovec remote[1];

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = address;
    remote[0].iov_len = size;

    if (target_pid < 0) {
        return false;
    }

    ssize_t bytes = process_v(target_pid, local, 1, remote, 1, 0, iswrite);
    return bytes == size;
}

bool vm_readv(long int address, void *buffer, size_t size) {
	return pvm(getpid(), reinterpret_cast<void *>(address), buffer, size, false);
}




bool pvm(void *address, void *buffer, size_t size, bool iswrite)
{
	struct iovec local[1];
	struct iovec remote[1];
	local[0].iov_base = buffer;
	local[0].iov_len = size;
	remote[0].iov_base = address;
	remote[0].iov_len = size;
	if (getpid() < 0)
	{
		return false;
	}
	ssize_t bytes = process_v(getpid(), local, 1, remote, 1, 0, iswrite);
	return bytes == size;
}





float getFloat(unsigned long addr)
{
	float var = 0;
	vm_readv(addr, &var, 4);
	return (var);
}

int getDword(unsigned long addr)
{
	int var = 0;
	vm_readv(addr, &var, 4);
	return (var);
}


template <class T> T WriteAddress(long int addr, T value)
    {
    char lj[128];
    sprintf(lj, "/proc/%d/mem", getpid());
    long int handle = open(lj, O_RDWR | O_SYNC);
    pwrite64(handle, &value, sizeof(T), addr);
    close(handle);
    return 0;
    }

    long int get64(long long addr) {
	long long var[1] = {0};
	vm_readv(addr, var, 8);    //  8就是64位      4就是32位
	return var[0];
}

    long GetModuleBase(const char *module_name, const char *modulefield)
{
	FILE *fp;
	long addr = 0;
	char *pch;
	char filename[64];
	char line[1024];
	snprintf(filename, sizeof(filename), "/proc/%d/maps", getpid());
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name) && strstr(line, modulefield))
			{
				pch = strtok(line, "-");
				addr = strtoul(pch, NULL, 16);
				if (addr == 0x8000)
					addr = 0;
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}
int ReadBuffer(long address, void *buffer, unsigned long size)
{
	struct iovec iov_ReadBuffer, iov_ReadOffset;
	iov_ReadBuffer.iov_base = buffer;
	iov_ReadBuffer.iov_len = size;
	iov_ReadOffset.iov_base = (void *)address;
	iov_ReadOffset.iov_len = size;
	return syscall(SYS_process_vm_readv, getpid(), &iov_ReadBuffer, 1, &iov_ReadOffset, 1, 0);
}
int readb(int &c, int num)
{
	++c;
	return num;
}
float WriteFloat(long address, float value, int mode)
{
	if (mode == 1)
	{
		WriteBuffer(address, &value, 4);
		return value;
	}
	else if (mode == 2)
	{
		char lj[64];
		sprintf(lj, "/proc/%d/mem", getpid());
		int Handle = open(lj, O_RDWR);
		pwrite64(Handle, &value, 4, address);
		close(Handle);
		return value;
	}
	else
	{
		printf("填1为syscall写入，填2为pwrite64(mem)写入");
	}
}
int WriteDword(long address, int value, int mode)
{
	if (mode == 1)
	{
		WriteBuffer(address, &value, 4);
		return value;
	}
	else if (mode == 2)
	{
		char lj[64];
		sprintf(lj, "/proc/%d/mem", getpid());
		int Handle = open(lj, O_RDWR);
		pwrite64(Handle, &value, 4, address);
		close(Handle);
	return 0;
	}
	else
	{
		printf("填1为syscall写入，填2为pwrite64(mem)写入");
	}
}
struct Vector2A
{
	float X;
	float Y;

	  Vector2A()
	{
		this->X = 0;
		this->Y = 0;
	}

	Vector2A(float x, float y)
	{
		this->X = x;
		this->Y = y;
	}
};
template < typename...s > long Read_Pointers(long addr, s ... args)
{
	int con = 0;
	addr = get64(addr);
	int arr[] = {
		(readb(con, args))...
	};
	for (int f = 0; f < con; f++)
	{
		if (f == con - 1)
		{
			addr += arr[f];
			return addr;
		}
		addr = get64(addr + arr[f]);
	}
}

char *Unicode64(unsigned long Name_pointer)
{
	int len = 0;
	ReadBuffer(Name_pointer + 0x10, &len, 4);
	if (len <= 0 || len > 40)
	{
		return "无";
	}
	char *retres;
	char str[12];
	retres = (char *)malloc(sizeof(short) * 40);
	memset(retres, '\0', sizeof(retres));
	unsigned short Namecode[len];
	ReadBuffer(Name_pointer + 0x14, Namecode, len * 2);
	for (int i = 0; i < len; i++)
	{
		wchar_t wstr[] = {
			Namecode[i], 0
		};
		setlocale(LC_ALL, "");
		wcstombs(str, wstr, sizeof(str) / sizeof(char));
		strcat(retres, str);
	}
	free(retres);

	return retres;
}

int isapkrunning(PACKAGENAME * bm)
{
	DIR *dir = NULL;
	struct dirent *ptr = NULL;
	FILE *fp = NULL;
	char filepath[64];
	char filetext[64];
	dir = opendir("/proc/");
	if (dir != NULL)
	{
		while ((ptr = readdir(dir)) != NULL)
		{
			if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
				continue;
			if (ptr->d_type != DT_DIR)
				continue;
			sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
			fp = fopen(filepath, "r");
			if (NULL != fp)
			{
				fgets(filetext, sizeof(filetext), fp);
				if (strcmp(filetext, bm) == 0)
				{
					closedir(dir);
					return 1;
				}
				fclose(fp);
			}
		}
	}
	closedir(dir);
	return 0;
}

bool 检测root() {
    // 方法一：检查 su 命令是否存在
    if (access("/system/bin/su", F_OK) == 0) {
        return true;
    }
    if (access("/system/xbin/su", F_OK) == 0) {
        return true;
    }
    // 方法二：尝试执行 su 命令
    FILE* fp = popen("su -c id", "r");
    if (fp != NULL) {
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            pclose(fp);
            return false;
        }
        pclose(fp);
    }
    return true;
}

typedef struct
{
    char *englishName;
    char *chineseName;
} CarTranslation;

char *CarNameReturn(char *SyncCarSign)
{
    static CarTranslation translations[] = {
        {"Jeep", "吉普车"},
        {"JetCar", "飞车"},
        {"Buggy", "蹦蹦车"},
        {"UFO", "小飞碟"},
        {"Peterosaur", "飘飘龙"},
        {"Triceratops", "憨憨龙"},
        {"Kayak", "快艇"},
        {"Raptors", "奔奔龙"},
        {"Dragon", "呆呆龙"},
        {"TRexKing", "凶凶龙王"},
        {"ArmoredBus", "装甲巴士"},
        {"PonyVehicle", "小马"},
        {"PoseidonShark", "鲨鱼"},
        {"Machine_Carrier", "机甲"},
        {"Gutswing", "胜利飞燕号"},
        {"HoverBoard", "悬浮滑板"},
        {"SwordTiger", "剑齿虎"},
        {"ShenLong", "神龙"},
        {"FlyingBroom", "飞行扫帚"},
        {"空", "未知车型"},
        {NULL, "未知车型"}
    };
    int i;
    for (i = 0; translations[i].englishName != NULL; i++)
    {
        if (strcmp(SyncCarSign, translations[i].englishName) == 0)
        {
            return translations[i].chineseName;
        }
    }
    if (translations[i].englishName == NULL or "空")
    {
        return "未知车型";  // 这个定义不能定义在for循环里的if，不然会产生逻辑错误，TM害老子修了好久!
    }
}
