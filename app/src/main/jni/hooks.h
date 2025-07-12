#ifndef HOOKS_H
#define HOOKS_H
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "内存工具.h"
#include "obfuscate.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"
#include "imgui/fonts/Font.h"
#include "Unity/Vector3.h"
#include "Unity/Vector3.hpp"
#include "Unity/Vector2.hpp"
#include "Unity/Vector.h"
#include "Unity/Rect.h"
#include "Unity/Quaternion.h"
#include "Unity/Quaternion2.h"
#include "Unity/Color.h"

#include "Il2cpp/Il2cpp.h"       // for EnsureAttached, Init
#include "Il2cpp/il2cpp-class.h" // for Il2CppImage, Il2CppObject
#include "Utils.h"
#include "Dobby/dobby.h"
#include "wy.h"
#include "bools.h"
float px,py;
#include "骨骼.h"
#include "imgui_whitecloud.h"
#include <android/log.h>
#define LOG_TAG  "连接输出"
Vector Coord;
float AimX, AimX2, AimY, AimY2;

std::string 登陆文本 = "登陆界面";

bool g_Initialized;
bool bInitDone = false;

#define ALOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
ImFont *font;
#define libName "libil2cpp.so"
int kmint=0;
std::string filePath;
char *登陆验证;

bool 不再提示;
int 子追概率=100;
int rand_num;
bool 是否达成;
long 人机数组指针;
long 载具数组指针;
long 物资数组指针;
float matrix[16];
int 真人,人机;
//int 自瞄范围=100;
Vector3 左手坐标;
float 距离,X,Y,W,H;
Vector Predicted;
static pthread_t AimCalcuPth;

int 开镜, 开火, 部位选择 = 9;
int 最小屏幕距离, 最小世界距离, 自瞄范围 = 100, 瞄准距离;
float 子弹重力, 子弹速度;
static pthread_t 目标计算;
//static pthread_t 子追;
Vector 子追预料;
Vector 移动速度, 最近玩家坐标, 子弹坐标;	// 计算人物速度算法
unsigned long 最近玩家地址 = 0x00000000;
Vector Compare_Vector = { 0.0f, 0.0f, 0.0f };
float 飞行方向X, 飞行方向Y, 飞行方向2X ;
void AddText(ImFont *font, float font_size, ImVec2 pos, ImColor col, char *text_begin) {
    auto size = ImGui::CalcTextSize(text_begin);
    float x = size.x * (font_size / 39.0f);
    float y = size.y * (font_size / 39.0f);
    ImGui::GetForegroundDrawList()->AddText(font, font_size,ImVec2(pos.x -= ((int) x >> 1), pos.y -= ((int) y >> 1)), col,text_begin);
}


double Vector距离(Vector Enemy, Vector My)
{
	return sqrt(pow(Enemy.x - My.x, 2) + pow(Enemy.z - My.z, 2) + pow(Enemy.y - My.y, 2));	// 实际距离;
}
struct PlayerStruct
{
    int 状态;
    int 头盔等级;
    int 护甲等级;
    float W;
    float 敌人屏幕位置;
    float 距离;
    float 血量;
    Vector 我的坐标;
    Vector 我的自瞄用坐标;
    Vector 敌人受击点坐标;
    Vector 我的子追用坐标;
    unsigned long 结构体1;
    unsigned long 子弹结构体;
    char 名称[128];
    char 头盔名字[128];
    char 护甲名字[128];
    char 手持枪械名称[128];
    int 手持枪械子弹数量;
    unsigned long 玩家地址;
    unsigned long 结构体;
    unsigned long 载具结构体;
    unsigned long 物资结构体;
    Vector 敌人坐标;
    bool 掩体;
} Player, MinAt, Closest, My;

struct 颜色结构体
{
ImColor 随机颜色[1000] = {};
ImColor 信息背景 = {};
} 颜色;

long 结构体1;
struct {
//long int 准心地址;
    long 准心地址;
    int 人物数量;
    long 人物数组;
} My1;
long 我的坐标添加;
struct {
    int width;
    int height;
    int screenWidth;
    int screenHeight;
} egl;

Quaternion2 quaternion_from_euler_angles(double pitch, double roll, double yaw) {
    // 将角度转换为弧度
    pitch *= 0.5;
    roll *= 0.5;
    yaw *= 0.5;

    // 计算正弦和余弦值
    double sp = sin(pitch);
    double sr = sin(roll);
    double sy = sin(yaw);
    double cp = cos(pitch);
    double cr = cos(roll);
    double cy = cos(yaw);

    // 计算四元数的四个分量
    Quaternion2 q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}

void *预测(void *Param)
{
    while (自瞄.开启预判)
    {
        移动速度 = Closest.敌人坐标 - 最近玩家坐标;
        移动速度.x*=自瞄.预判系数;
        移动速度.y*=自瞄.预判系数;
        移动速度.z*=自瞄.预判系数;
        if (移动速度.x >= 10.0f || 移动速度.x <= -10.0f || 移动速度.z >= 10.0f || 移动速度.z <= -10.0f || 移动速度.y >= 10.0f || 移动速度.y <= -10.0f || 最近玩家地址 != Closest.结构体)	// 判断
        移动速度 = Compare_Vector;	// 自身坐标
        最近玩家坐标 = Closest.敌人坐标;
        最近玩家地址 = Closest.结构体;
        usleep(100000);
    }
}

void FindMinAt()
{
    if (W > 0)
    {
        float 屏幕距离 = abs(Player.敌人屏幕位置);
        float 世界距离 = Player.距离;
        if (屏幕距离 < 最小屏幕距离 && 屏幕距离 > 0)
        {
            最小屏幕距离 = 屏幕距离;
            最小世界距离 = 世界距离;
            memcpy(&MinAt, &Player, sizeof(struct PlayerStruct));
        }
    }
}

Vector2 WorldToScreenLibUnity(Vector3 obj) {//重要
    float ViewW = matrix[3] * obj.X + matrix[7] * obj.Y + matrix[11] * obj.Z + matrix[15];
    if (ViewW>0.01) {
        float x  = egl.width/2 + (matrix[0] * obj.X + matrix[4] * obj.Y + matrix[8] * obj.Z + matrix[12]) / ViewW * egl.width/2;
        float y  = egl.height/2 - (matrix[1] * obj.X + matrix[5] * obj.Y + matrix[9] * obj.Z + matrix[13]) / ViewW * egl.height/2;
        if(x==0||y==0)
            return Vector2(9999,9999);
        else
            return Vector2(x, y);

    } else
        return Vector2(9999,9999);
}

std::map<std::string, Il2CppImage*> Images;
std::map<std::string, Il2CppClass*> Classes;
std::map<std::string, Il2CppObject*> Objects;
std::map<std::string, uintptr_t> Fields;
std::map<std::string, uintptr_t> Methods;
std::map<std::string, uintptr_t> FieldsAddress;

Vector3 (*Getposition)(Transform*transform) = NULL;
Vector3 (*Camera_WorldToScreen)(void *camera, Vector3 position) = NULL;
Vector3 (*人物坐标获取)(void *结构体) = NULL;
bool (*射线掩体)(Vector3 坐标1,Vector3 坐标2) = NULL;

void PlottingAlgorithm(Vector3 Obj)
{
    float camear_z = matrix[3] * Obj.X + matrix[7] * Obj.Y + matrix[11] * Obj.Z + matrix[15];
    距离 = camear_z;
    float r_x =
        egl.width/2 + (matrix[0] * Obj.X + matrix[4] * Obj.Y + matrix[8] * Obj.Z +
                       matrix[12]) / camear_z * egl.width/2;
    float r_y =
        egl.height/2 - (matrix[1] * Obj.X + matrix[5] * (Obj.Y) + matrix[9] * Obj.Z  +
                        matrix[13]) / camear_z * egl.height/2;
    float r_w =
        egl.height/2 - (matrix[1] * Obj.X + matrix[5] * (Obj.Y + 1.8) + matrix[9] * Obj.Z +
                        matrix[13]) / camear_z * egl.height/2;

    X = r_x - (r_y - r_w) / 4;

    Y = r_y;
    W = (r_y - r_w) / 2;
    X=X+(W/2);
    H = (r_y - r_w);
}


void (*old_Input)(void *thiz, void *ex_ab, void *ex_ac);
void hook_Input(void *thiz, void *ex_ab, void *ex_ac) {
    old_Input(thiz, ex_ab, ex_ac);
    ImGui_ImplAndroid_HandleTouchEvent((AInputEvent *) thiz, {(float) egl.screenWidth / (float) egl.width, (float) egl.screenHeight / (float) egl.height});
    return;
}

int (*old_getWidth)(ANativeWindow* window);
int hook_getWidth(ANativeWindow* window) {
    egl.screenWidth = old_getWidth(window);
    return old_getWidth(window);
}

//Vector3 (*Camera_WorldToScreen)(void *camera) = NULL;
int (*old_getHeight)(ANativeWindow* window);
int hook_getHeight(ANativeWindow* window) {
    egl.screenHeight = old_getHeight(window);
    return old_getHeight(window);
}

void (*old_获取准心)(void *Role5);
void 获取准心(void *Role5) {
    if(Role5) {
        My1.准心地址=(long)Role5;
        return old_获取准心(Role5);
    }
}
Vector3 获取坐标1;
Vector3 (*old_获取坐标)(void *Role7);
Vector3 获取坐标(void *Role7) {
    获取坐标1=old_获取坐标(Role7);
    return old_获取坐标(Role7);

}




Vector 飞行方向;
Vector 欧拉角;
Quaternion2 四元素p;
Vector 没有点;
EulerAngles 记录欧拉角;
//类型假设
typedef struct {
} StartGame;
typedef struct {
} FireType;
typedef struct {
} Int32;
typedef struct {
} quaternion;



bool 自瞄条件判断()
{
    if (自瞄.选择 == 0)	// 这里是开镜
    {
        if (开镜 != 0)
        {
            return true;
        } else
        {
            return false;
        }
    }
    if (自瞄.选择 == 1)	// 这里是开火
    {
        if (开火 != 0)
        {
            return true;
        } else
        {
            return false;
        }
    }
    if (自瞄.选择 == 2)	// 这里是开镜开火，自己判断
    {
        if (开火 != 0)
        {
            return true;
        } else if (开镜 != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
void (*old_轨迹检测)(StartGame *startGame, Int32 *autoItemId, FireType *fireType, Int32 *useRoleId, String *useTeamId, Int32 *uniteId, Vector startPoint, Quaternion2 startRota);//旧函数
void 轨迹检测(void *startGame2, void *autoItemId2, void *fireType2, void *useRoleId2, void *useTeamId2, void *uniteId2, Vector startPoint,Quaternion2 startRota) { //新函数以及变量名

    StartGame *startGame = (StartGame*)startGame2;
    Int32* autoItemId = (Int32*)autoItemId2;
    FireType* fireType = (FireType*)fireType2;
    Int32* useRoleId = (Int32*)useRoleId2;
    String* useTeamId = (String*)useTeamId2;
    Int32* uniteId = (Int32*)uniteId2;
    rand_num = rand() % 100 + 1; // 生成1到100之间的随机数
        if (rand_num <= 子追.概率系数) {
            是否达成=true;
        } else {
            是否达成=false;
        }

    My.我的子追用坐标.x = startPoint.x;
    My.我的子追用坐标.z = startPoint.z;
    My.我的子追用坐标.y = startPoint.y;
    Vector Predicted1 = Predicted - My.我的子追用坐标;
    if (子弹重力 != 0)
    {
        float 子弹与人物y轴差 = 0.5 * 子弹重力 * pow(((sqrt(pow(Predicted.x - My.我的子追用坐标.x, 2) + pow(Predicted.z - (My.我的子追用坐标.z), 2) + pow(Predicted.y - My.我的子追用坐标.y, 2))) / 子弹速度), 2);	// 如果有子弹重力计算子弹落点位置,双发来自梦梦子
        Predicted1.z = Predicted1.z + 子弹与人物y轴差;
    }

    欧拉角.x = atan2(Predicted1.x, -Predicted1.y);  //俯仰角
    欧拉角.z = 0;  //翻滚角
    欧拉角.y = -atan2(Predicted1.z, sqrt(Predicted1.x * Predicted1.x + Predicted1.y * Predicted1.y));  //偏航角

    if (开启.子追&&是否达成&&Closest.敌人受击点坐标.x !=0 && Closest.敌人受击点坐标.z !=0 && Closest.敌人受击点坐标.y !=0)
    {
        Quaternion2 p = quaternion_from_euler_angles(欧拉角.x, 0.0f, 欧拉角.y);
        四元素p = startRota;
        old_轨迹检测(startGame, autoItemId, fireType, useRoleId, useTeamId, uniteId, startPoint, p);
    } else {
        old_轨迹检测(startGame, autoItemId, fireType, useRoleId, useTeamId, uniteId, startPoint, startRota);
    }
}

void (*old_视角伪装)(Quaternion2 cameraRotationX, Quaternion2 cameraRotationY, quaternion *lookX, quaternion *lookY, String *cameraRatioLevel);//旧函数
void 视角伪装(Quaternion2 cameraRotationX, Quaternion2 cameraRotationY, void *lookX2, void *lookY2, void *cameraRatioLevel2) { //新函数以及变量名



    quaternion* lookX = (quaternion*)lookX2;
    quaternion* lookY = (quaternion*)lookY2;
    String* cameraRatioLevel = (String*)cameraRatioLevel2;
    if(子追.伪装视角&&自瞄条件判断()&&Closest.敌人受击点坐标.x !=0&&Closest.敌人受击点坐标.z !=0&&Closest.敌人受击点坐标.y !=0) {
        Vector 子弹差 = Predicted - My.我的自瞄用坐标;
        Quaternion2 方向X,方向Y;
        方向X.x = sin(atan2(子弹差.x,子弹差.y)/2);
        方向X.z = cos(atan2(子弹差.x,子弹差.y)/2);
        方向Y.w= -tan(atan2f(子弹差.z,sqrt(子弹差.x *子弹差.x+子弹差.y*子弹差.y))/2);
        方向Y.z=1.0f;

        old_视角伪装(方向X, 方向Y, lookX, lookY, cameraRatioLevel);
    } else {
        old_视角伪装(cameraRotationX, cameraRotationY, lookX, lookY, cameraRatioLevel);
    }


}





void (*old_游戏世界循环)(void *Role6);
void 游戏世界循环(void *Role6) {
    if(getDword(My1.准心地址+0x10)==0)
        DobbyHook((void*)((void *(*)(void *)) (uintptr_t)Il2cpp::FindMethod("CameraMove", "get_MyUserData")->methodPointer),(void*)获取准心,(void**)&old_获取准心);
    return old_游戏世界循环(Role6);
}

float 平滑;
void 获取数据() {

    My1.人物数组=get64(get64(get64(My1.准心地址+Fields["CameraMove::gameWorld"])+Fields["GameWorld::startGame"])+Fields["StartGame::RoleList"]);
    My1.人物数量=getDword(My1.人物数组+0x18);
    
    人机数组指针 = Read_Pointers(My1.准心地址 + Fields["CameraMove::gameWorld"],Fields["GameWorld::startGame"],Fields["StartGame::<MyRoleAIMgr>k__BackingField"],Fields["RoleAIManager::logicList"], 0);

    载具数组指针 = Read_Pointers(My1.准心地址 + Fields["CameraMove::gameWorld"],Fields["GameWorld::startGame"],Fields["StartGame::AllCar"], 0);
    
    物资数组指针 = Read_Pointers(My1.准心地址 + Fields["CameraMove::gameWorld"],Fields["GameWorld::ItemManager"],Fields["ItemManager::_screenItemData"],Fields["ItemManager::cacheInfos"], 0);

    memset(matrix, 0, 16);
    vm_readv((get64(get64(My1.准心地址 + 0x40)+ 0x10)+0x100), matrix, 16 * 4);
    
    结构体1 = Read_Pointers(My1.准心地址 + Fields["CameraMove::LockRole"], Fields["Role::roleLogic"], 0);
    ReadBuffer(My1.准心地址 + Fields["CameraMove::NowPoint"], &My.我的自瞄用坐标, sizeof(Vector));
    开镜 = getDword(My1.准心地址 + Fields["CameraMove::_isSetWeaponBox"]);	// 开镜
    开火 = getDword(Read_Pointers(My1.准心地址 + Fields["CameraMove::CameraShakePoint"], 0x60));	// 开火
    long 子弹 = Read_Pointers(My1.准心地址 + Fields["CameraMove::LockRole"], Fields["Role::UserWeapon"], 0x38, 0x160, 0x20, 0);
    子弹速度 = getFloat(子弹 + 0x14);	// 子弹速度
    子弹重力 = getFloat(子弹 + 0x10);	// 子弹重力
    if (子弹速度 <= 100) 子弹速度 = 400.0;
    int 自身状态 = getDword(结构体1 + Fields["RoleLogic::myStandbyState"]);	// 人物状态
    if (自身状态 == 1)
    {
        (My.我的自瞄用坐标.z) += 1.6;
    }
    else if (自身状态 == 2)
    {
        (My.我的自瞄用坐标.z) += 1.4;
    }
    else if (自身状态 == 3)
    {
        (My.我的自瞄用坐标.z) += 1.0;
    }

    int 自身探头状态 = getDword(结构体1 + Fields["RoleLogic::SideAim"]);	// 人物探头
    if (自身探头状态 != 0)
    {
        My.我的自瞄用坐标.z -= 0.25;
    }

    int 自身举枪状态 = getDword(结构体1 + Fields["RoleLogic::TopShoot"]);	// 人物举枪射击
    if (自身举枪状态 != 0)
    {
        My.我的自瞄用坐标.z += 0.35;
    }

    int 自身皮球状态 = getDword(结构体1 + Fields["RoleLogic::UserCircusBalllNet"]);	// 皮球
    if (自身皮球状态 != 0)
    {
        My.我的自瞄用坐标.z += 0.7;
    }

    if (1)
    {
        if (Closest.掩体)
        {
            if ((Closest.敌人受击点坐标.x && Closest.敌人受击点坐标.z && Closest.敌人受击点坐标.y) != 0)
            {
                if (自瞄.头部边缘)
                {
                if (Fields["RoleLogic::SideAim"]!=0)
			    {
				Closest.敌人受击点坐标.x+=(Closest.敌人受击点坐标.x-Closest.敌人坐标.x)/3;
				Closest.敌人受击点坐标.z+=(Closest.敌人受击点坐标.z-Closest.敌人坐标.z)/3;
			    }
                }
                
			    float 预判时间 = Closest.距离 / 子弹速度;

			    Predicted = Closest.敌人受击点坐标 + 移动速度 * 预判时间;
			    Predicted.y += 0.5 * 子弹重力 * 预判时间 * 预判时间;
			    
                Coord = Predicted - My.我的自瞄用坐标;
                
                float AngleX = getFloat(My1.准心地址 + 0x9c);
                float AngleX2 = getFloat(My1.准心地址 + 0xa4);
                float AngleY = getFloat(My1.准心地址 + 0xA8);
                float AngleY2 = getFloat(My1.准心地址 + 0xB4);
                float TargetX = atan2(Coord.x,Coord.y);
                float TargetY = -atan2(Coord.z, sqrt(pow(Coord.x, 2) + pow(Coord.y, 2)));
                Quaternion PresentX, PresentY;
                PresentX. y = sin(TargetX / 2);
                PresentX. w = cos(TargetX / 2);
                PresentY. x = sin(TargetY / 2);
                PresentY. w = cos(TargetY / 2);
                if (自瞄.平滑系数 == 0)
                {
                平滑 = 1.0f + (1.0 - 1.0) * (1.0 / 自瞄.力度系数);
                }else{
                平滑 = 1.0f + (自瞄.平滑系数 - 1.0) * (1.0 / 自瞄.力度系数);
                }
                
                AimY2 = AngleY2 + (PresentY. w - AngleY2) / 平滑;
                AimX = AngleX + (PresentX. y - AngleX) / 平滑;
                AimX2 = AngleX2 + (PresentX. w - AngleX2) / 平滑;
                AimY = AngleY + (PresentY. x - AngleY) / 平滑;
                
                if (自瞄.开火持锁)
                {
                int 持锁 = -1;
                if (持锁 = -1)
                {
                if (开火 != 0) 持锁 = 0;
                if (开火 != 0 && 开镜 != 0) 持锁 = -1;
                }
                
                if (持锁 != -1 && 持锁 != 100)
                {
                开火 = 10;
                持锁 += 2;
                }else{
                持锁 = -1;
                }
                }
                
                if (自瞄条件判断()&&开启.自瞄)
                {
                    WriteFloat(My1.准心地址 + 0x98, 0, 1);	// 写入y
                    WriteFloat(My1.准心地址 + 0x9C, AimX, 1);
                    WriteFloat(My1.准心地址 + 0xA4, AimX2, 1);
                    WriteFloat(My1.准心地址 + 0xA0, 0, 1);	// 写入y
                    WriteFloat(My1.准心地址 + 0xA8, AimY, 1);	// 写入y
                    WriteFloat(My1.准心地址 + 0xAC, 0, 1);	// 写入y
                    WriteFloat(My1.准心地址 + 0xB0, 0, 1);	// 写入y
                    WriteFloat(My1.准心地址 + 0xB4, AimY2, 1);	// 写入y2
                    WriteFloat(My1.准心地址 + Fields["CameraMove::EndPoint"], 0, 1);	// 拉正视角
                }


            }
        }
    }






}

void ShowMenu() {
ImGuiIO& io = ImGui::GetIO();
ImGuiStyle &style = ImGui::GetStyle();
io.ConfigWindowsMoveFromTitleBarOnly = false;
io.WantSaveIniSettings = true;
style.WindowRounding = 窗口圆角; // 窗口圆角
style.FrameBorderSize = 控件描边;// 设置控件描边宽度
style.WindowBorderSize = 控件边框; // 设置框架描边宽度
style.FrameRounding = 控件圆角;	// 控件圆角
switch (主题颜色)
{
case 0: ImGui::StyleColorsLight(); break;
case 1: ImGui::StyleColorsDark(); break;
case 2: ImGui::StyleColorsClassic(); break;      
case 3: ImGui::StyleColorsBlack(); break;
case 4: ImGui::StyleColorsPink(); break;
case 5: ImGui::StyleColorsGreen(); break;
}
        ImGui::Begin("Lollipop注入");
        ImGui::SetWindowSize({950, 650}, ImGuiCond_Once);
        if(ImGui::BeginChild("##mMenu",ImVec2(180,0),false));  
        {
                if (ImGui::Button("绘制",{-1,60}))   
                {
                    页面.绘制 = true;
                    页面.自瞄 = false;
					页面.内存 = false;
					页面.设置 = false;
                }
                ImGui::Spacing();
                if (ImGui::Button("自瞄",{-1,60}))   
                {
                    页面.绘制 = false;
                    页面.自瞄 = true;
					页面.内存 = false;
					页面.设置 = false;
                }
                ImGui::Spacing();
                if (ImGui::Button("内存",{-1,60}))   
                {
                    页面.绘制 = false;
                    页面.自瞄 = false;
					页面.内存 = true;
					页面.设置 = false;
                }
                ImGui::Spacing();
                if (ImGui::Button("设置",{-1,60}))   
                {
                    页面.绘制 = false;
                    页面.自瞄 = false;
					页面.内存 = false;
					页面.设置 = true;
				}
            ImGui::EndChild();
        }
        
        ImGui::SameLine();
        
        if (ImGui::BeginChild("##右侧",ImVec2(0,0),false,ImGuiWindowFlags_NavFlattened)){
        if (页面.绘制)
        {
            ImGui::Checkbox("绘制初始化", &开启.人物);
            ImGui::SameLine();
            ImGui::Checkbox("开启载具绘制", &开启.载具);
            
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            
            ImGui::Checkbox("方框", &绘制.方框);
            ImGui::SameLine();
            ImGui::Checkbox("射线", &绘制.射线);
            ImGui::SameLine();
            ImGui::Checkbox("信息", &绘制.信息);
            ImGui::SameLine();
            ImGui::Checkbox("填充", &绘制.填充);
            
            ImGui::Checkbox("血量", &绘制.血量);
            ImGui::SameLine();
            ImGui::Checkbox("距离", &绘制.距离);
            ImGui::SameLine();
            ImGui::Checkbox("背敌", &绘制.背敌); 
            ImGui::SameLine();
            ImGui::Checkbox("字幕", &绘制.电报);
            
            ImGui::RadioButton("人数左侧距离",&绘制.人数左侧,0);
            ImGui::SameLine();
            ImGui::RadioButton("人数左侧血量",&绘制.人数左侧,1);
            ImGui::SameLine();
            ImGui::RadioButton("人数左侧状态",&绘制.人数左侧,2);
            
            ImGui::RadioButton("人数右侧距离",&绘制.人数右侧,0);
            ImGui::SameLine();
            ImGui::RadioButton("人数右侧血量",&绘制.人数右侧,1);
            ImGui::SameLine();
            ImGui::RadioButton("人数右侧状态",&绘制.人数右侧,2);
            }
            if (页面.自瞄) {
                ImGui::Checkbox("启动自瞄", &开启.自瞄);
                
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                
                ImGui::Checkbox("显示射线", &自瞄.作弊射线);
                ImGui::SameLine();
                ImGui::Checkbox("显示圈圈", &自瞄.圈圈开关);
                ImGui::SameLine();
                ImGui::Checkbox("不瞄倒地", &自瞄.忽略倒地);
                ImGui::SameLine();
                ImGui::Checkbox("不瞄人机", &自瞄.忽略人机);
                
                ImGui::Checkbox("不瞄掩体", &自瞄.忽略掩体);
                ImGui::SameLine();
                ImGui::Checkbox("头部边缘", &自瞄.头部边缘);
                ImGui::SameLine();
                ImGui::Checkbox("开火持锁", &自瞄.开火持锁);
                ImGui::SameLine();
                ImGui::Checkbox("开启预判", &自瞄.开启预判);
                
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
               
                ImGui::Checkbox("启动子追", &开启.子追);
                ImGui::SameLine();
                ImGui::Checkbox("伪装视角", &子追.伪装视角);
                
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                
                ImGui::Combo("自瞄&子追部位", &自瞄.部位, "头部\0胸部\0裤裆\0自动化\0");
					
			    ImGui::Combo("自瞄&子追选择", &自瞄.选择, "开镜\0开火\0同时\0");
			    
                ImGui::SliderInt("自瞄&子追范围",&自瞄.范围系数,0,1000);
                ImGui::SliderFloat("预判系数", &自瞄.预判系数, 0.0f, 10.0f, "%.2f");
                ImGui::SliderFloat("平滑系数", &自瞄.平滑系数, 0.00f, 10.0f, "%.2f");
                ImGui::SliderFloat("力度系数", &自瞄.力度系数, 0.00f, 10.0f, "%.2f");
                
                ImGui::SliderInt("子追概率",&子追.概率系数,0,100);
            }
            if (页面.内存)
            {
            ImGui::Checkbox("广角", &广角);
            ImGui::SliderFloat("广角大小", &广角大小, 40.00f, 150.0f, "%.1f");
            }
            if (页面.设置)
            {
            if (ImGui::Button("保存配置")) 保存配置();
            ImGui::SameLine();
            if (ImGui::Button("读取配置")) 读取配置();
            
            ImGui::Combo("主题颜色", &主题颜色, "WHITE\0BLUE\0PURPLE\0BLACK\0PINK\0GREEN\0");
            ImGui::SliderFloat("控件描边", &控件描边, 0, 10);
            ImGui::SliderFloat("控件边框", &控件边框, 0, 10);
            ImGui::SliderFloat("控件圆角", &控件圆角, 0, 50);
            ImGui::SliderFloat("窗口圆角", &窗口圆角, 0, 50);
            }
        }
    ImGui::End();
}
float 自瞄范围系数;
void DrawESP() {
    真人 = 0;
    人机 = 0;
    py = egl.height / 2;
    px = egl.width / 2;
    float 屏幕Y = py * 2;
	float 屏幕X = px * 2;
    最小屏幕距离 = 自瞄.范围系数;
    最小世界距离 = 瞄准距离;
    int MyBall = getFloat(get64(结构体1 + Fields["RoleLogic::localSynAction"]) + 0x20);
    int myinjury = getFloat(get64(get64(结构体1 + Fields["RoleLogic::userWeapon"]) + 0xF8) + 0x80);
    memset(&Player, 0, sizeof(Player));
    memset(&MinAt, 0, sizeof(MinAt));
    for (int i = 0; i < My1.人物数量; i++) {
        Vector3 我的坐标;
        Player.结构体 = get64(get64(My1.人物数组 + 0x10)+0x20 + 8 * i);
        
        int Jump = getFloat(Player.结构体 + Fields["RoleLogic::jumpState"]);
		int FlyJump = getFloat(Player.结构体 + Fields["RoleLogic::flyJumpState"]);
		long firearms = get64(get64(Player.结构体 + Fields["RoleLogic::userWeapon"]) + 0xF8);
		float injury = getFloat(firearms + 0x80);
		long Voyeurism = get64(Player.结构体 + Fields["RoleLogic::HeadEquipPart"]);
		long Armor = get64(Player.结构体 + Fields["RoleLogic::BodyEquipPart"]);
		int IsJump = Jump != 0 and FlyJump == 0;
		int IsMove = getFloat(Player.结构体 + Fields["RoleLogic::_moveH"]) != 0 or getFloat(Player.结构体 + Fields["RoleLogic::_moveV"]) != 0;// private Single _moveH;  private Single _moveV;
		int NoJump = Jump == 0 and FlyJump == 0;

		if (Voyeurism == 209){
		Player.头盔等级 = 1;
	    }else if (Voyeurism == 210){
		Player.头盔等级 = 2;
	    }else if (Voyeurism == 211){
		Player.头盔等级 = 3;
	    }else if (Voyeurism == 590){
		Player.头盔等级 = 4;
	    }else{
		Player.头盔等级 = 0;
        }
        
	    if (Armor == 199){
		Player.护甲等级 = 1;
	    }else if (Armor == 200){
		Player.护甲等级 = 2;
	    }else if (Armor == 201){
		Player.护甲等级 = 3;
	    }else if (Armor == 591){
        Player.护甲等级 = 4;
	    }else{
        Player.护甲等级 = 0;
        }
        
        Player.状态 = getDword(Player.结构体 + Fields["RoleLogic::myStandbyState"]);
        Player.血量 = getFloat(Player.结构体 + Fields["RoleLogic::hp"]);
        float 最大血量 = getFloat(Player.结构体 + Fields["RoleLogic::hp"]+0x4);
        float 倒地血量 = getFloat(Player.结构体 + Fields["RoleLogic::hp"]-0x8);
        float 倒地最大血量 = getFloat(Player.结构体 + Fields["RoleLogic::hp"] +0x10);
        float 人物欧拉角 = getFloat(get64(get64(Player.结构体 + Fields["RoleLogic::OnSetPlayerIdCallBack"])+0x40)+ 0x60);
        int 阵营 = getDword(Player.结构体 + Fields["RoleLogic::TeamNum"]);
        int 我多人模式阵营 = getDword(结构体1 + Fields["RoleLogic::TeamNum"] -0x8);
        int 多人模式阵营 = getDword(Player.结构体 + Fields["RoleLogic::TeamNum"] -0x8);
        int 己方阵营 = getDword(结构体1 + Fields["RoleLogic::TeamNum"]);

        if(我多人模式阵营 > 0) {
            if(我多人模式阵营 == 多人模式阵营)
            {
                continue;
            }
        }

        int 过滤自身阵营 = getDword(Player.结构体 + Fields["RoleLogic::TeamNum"] -0x4);
        if (过滤自身阵营 != 0)  //过滤自身与队友
        {
            continue;
        }
        if (最大血量 == 0)
        {
            continue;
        }
        strcpy(Player.名称, Unicode64(Read_Pointers(Player.结构体 + Fields["RoleLogic::NickName"],0)));
        strcpy(Player.头盔名字, Unicode64(Read_Pointers(Player.结构体 + Fields["RoleLogic::HeadEquipPart"], 0xE8, 0x28, 0)));
        strcpy(Player.护甲名字, Unicode64(Read_Pointers(Player.结构体 + Fields["RoleLogic::BodyEquipPart"], 0xE8, 0x28, 0)));
        
        strcpy(Player.手持枪械名称, Unicode64(Read_Pointers(Player.结构体 + Fields["RoleLogic::userWeapon"], 0xE8, 0x28, 0)));
        Player.手持枪械子弹数量 = getDword(Read_Pointers(Player.结构体 + Fields["RoleLogic::userWeapon"], 0xBC, 0));
        
        float 头盔ID = getDword(Read_Pointers(Player.结构体 + Fields["RoleLogic::HeadEquipPart"],0));
        float 护甲ID = getDword(Read_Pointers(Player.结构体 + Fields["RoleLogic::BodyEquipPart"],0));


        我的坐标添加 = get64(get64(get64(get64(get64(get64(get64(get64(Player.结构体 + Fields["RoleLogic::OnSetPlayerIdCallBack"])+0x40)+0x10)+0x30)+0x30)+0x28)+0x48)+0x28)+0xA0;	// 坐标
        ReadBuffer(我的坐标添加, &我的坐标, sizeof(Vector3));

        if(我的坐标.X==0) continue;

        PlottingAlgorithm(我的坐标);
		
        if (自瞄.部位 == 0){
        部位选择 = 9;
        }else if (自瞄.部位 == 1){
        部位选择 = 3;
        }else if (自瞄.部位 == 2){
        部位选择 = 4;
        }else if (自瞄.部位 == 3){
                if (injury >= myinjury)
			        部位选择 = 9;
			    else if (Player.头盔等级 < Player.护甲等级)
			        部位选择 = 9;
			    else if (Player.头盔等级 and Player.护甲等级 >= 3)
			    {
				if (Player.血量 >= 80)
				{
				部位选择 = 9;
				}
			    }
			    else
		        部位选择 = 3;
		}
        long 头部受击点坐标 = Read_Pointers(Player.结构体 + Fields["RoleLogic::OnSetPlayerIdCallBack"], 0x20, 0x48,Fields["AnimatorControl::MyBodyParts"], 0x20 + 8 * 部位选择, 0x10, 0x30, 0x30, 0x28, 0x48, 0x28, 0xA0);	// 头部受击点坐标
        ReadBuffer(头部受击点坐标, &Player.敌人受击点坐标, sizeof(Vector));
        ReadBuffer(我的坐标添加, &Player.敌人坐标, sizeof(Vector));

        if (IsJump or (IsMove and NoJump) and Fields["RoleLogic::myStandbyState"] == 1 and Fields["RoleLogic::SideAim"]==0)
			{
				if (Player.敌人受击点坐标.y-getFloat(我的坐标添加+0x4)>0.4)
				{
					if (IsJump)
						ReadBuffer(我的坐标添加, &Player.敌人受击点坐标, sizeof(Vector));
					else
						Player.敌人受击点坐标.y=getFloat(我的坐标添加+0x4);						
					if (自瞄.部位 == 0)
						Player.敌人受击点坐标.y+=1.25;
					else if (自瞄.部位 == 1)
						Player.敌人受击点坐标.y+=0.8;
				}
			}

        Player.距离 = Vector距离(Player.敌人坐标,My.我的自瞄用坐标);
        if(Player.距离>400) continue;

        真人++;
        if (!自瞄.忽略倒地 && Player.血量==0)
        {
            Player.掩体 = true;  //掩体外
            Player.敌人受击点坐标 = Player.敌人坐标;
            Player.敌人坐标.z -= 0.5;
        }else if (getDword(头部受击点坐标)!= 0){
            Player.掩体 = true;
        }else{
            Player.掩体 = false;
        }

        if(Closest.结构体==Player.结构体&&Player.掩体&&自瞄.作弊射线)
        ImGui::GetForegroundDrawList()->AddLine({egl.width/2, egl.height/2}, {X,Y}, 自瞄射线颜色,1.5f);
/*
        if(W>0&&Player.掩体)
        {
        float AimDs = sqrt(pow(X - px, 2) + pow(Y - py, 2));
		if (AimDs <= 自瞄.最大动态系数)
		{
	    if(自瞄条件判断()&&开启.自瞄)
		    {
            自瞄范围系数 = AimDs;
            }else{
            自瞄范围系数 = 自瞄.范围系数;
        }
       }
       }
*/
        Player.敌人屏幕位置 = sqrt(pow(X - egl.width/2, 2) + pow(Y - egl.height/2, 2));
        颜色.信息背景= ImColor(ImVec4(颜色.随机颜色[阵营].Value.x, 颜色.随机颜色[阵营].Value.y, 颜色.随机颜色[阵营].Value.z,0.8f));
        PlottingAlgorithm(我的坐标);
        if (自瞄.忽略掩体)
        {
        if(W>0&&Player.掩体) FindMinAt();
        }else{
        if(W>0) FindMinAt();
        }
        if(W>0&&开启.人物) {
		      if (绘制.背敌)//背敌
            {
                std::string s;
                s += std::to_string((int)Player.距离);
                s += "m";
                if (W > 0)//屏幕前
                {
                  if (Y - W > 屏幕Y)//下方
                  {
                    ImGui::GetForegroundDrawList()->AddRect({X - 46, 屏幕Y + 1},{X + 46, 屏幕Y - 51},ImColor(255,255,255,255),0,0,3.0);
                    if (阵营 != 0)
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 屏幕Y},{X + 45, 屏幕Y - 50},红色,0,0);
                    }
                    else
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 屏幕Y},{X + 45, 屏幕Y - 50},ImColor(255,255,255,100),0,0);
                    }
                    ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(X - 20, 屏幕Y - 40),ImColor(255,255,255),s.c_str()); 
                  }
                  if (Y + W < 0)//上方
                  {
                    ImGui::GetForegroundDrawList()->AddRect({X - 46, -1},{X + 46, 51},ImColor(255,255,255,255),0,0,3.0);
                    if (阵营 != 0)
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 0},{X + 45, 50},红色,0,0);
                    }
                    else
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 0},{X + 45, 50},ImColor(255,255,255,100),0,0);
                    }
                    ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(X - 20, 10 ),ImColor(255,255,255),s.c_str()); 
                  }         
                  if  (X+(W/2)<0)//左侧
                  {  
                    ImGui::GetForegroundDrawList()->AddRect({-1.0, Y - 26},{91.0, Y + 26},ImColor(255,255,255,255),0,0,3.0);
                    if (阵营 != 0)
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({0.0, Y - 25},{90.0, Y + 25},红色,0,0);
                    }
                    else
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({0.0, Y - 25},{90.0, Y + 25},ImColor(255,255,255,100),0,0);
                    }
                    ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(30,Y - 15),ImColor(255,255,255),s.c_str());             
                  }
                  if (X-(W/2) > 屏幕X)//右侧
                  {  
                    ImGui::GetForegroundDrawList()->AddRect({屏幕X+1, Y - 26},{屏幕X-91, Y + 26},ImColor(255,255,255,255),0,0,3.0);
                    if (阵营 != 0)
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({屏幕X, Y - 25},{屏幕X-90, Y + 25},红色,0,0);
                    }
                    else
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({屏幕X, Y - 25},{屏幕X-90, Y + 25},ImColor(255,255,255,100),0,0);
                    }
                      ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(屏幕X-62,Y - 15),ImColor(255,255,255),s.c_str()); 
                    }  
                }
                else//屏幕后
                {
                      ImGui::GetForegroundDrawList()->AddRect({X - 46, 屏幕Y + 1},{X + 46, 屏幕Y - 51},ImColor(255,255,255,255),0,0,3.0);
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 屏幕Y},{X + 45, 屏幕Y - 50},ImColor(255,255,255,100),0,0);
                      ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(X - 20, 屏幕Y - 40),ImColor(255,255,255),s.c_str()); 
          
                }
             }
                 if (绘制.方框)
                  {
                    if (Player.掩体)//判断
                    {
                    ImGui::GetForegroundDrawList()->AddRect({X - (W / 2), Y - W},{X + (W / 2), Y + W},红色);
                    }else{
                    ImGui::GetForegroundDrawList()->AddRect({X - (W / 2), Y - W},{X + (W / 2), Y + W},绿色);
                    }
                  }
                  if (绘制.填充)//绘制背景
                  {
                   if (Player.掩体)//判断
                    {
                    ImGui::GetForegroundDrawList()->AddRectFilled({(X - W / 2), Y - W}, {X + (W / 2), Y + W},ImColor(255,0,0,50));
                    }else{
                    ImGui::GetForegroundDrawList()->AddRectFilled({(X - W / 2), Y - W}, {X + (W / 2), Y + W},ImColor(50,255,0,50));
                    }
                   }
                  if (绘制.血量)
                    {
                    float Health;
                    if (Player.血量 <= 0)
                    {
                    Health = 倒地血量 / 倒地最大血量;
                    }else{
                    Health = Player.血量 / 最大血量;
                    }
                    ImGui::GetForegroundDrawList()->AddRectFilled({X + (W / 2) + 4, Y+W-((Y+W)-(Y-W)) * Health},{X+W/2 + 10, Y + W},绿色,{6});
                    }
                    if (绘制.射线)
                    {
                    if (Player.掩体)//判断掩体
                    {
                    ImGui::GetForegroundDrawList()->AddLine({px,0}, {X, Y - W},绿色);
                    }else{
                    ImGui::GetForegroundDrawList()->AddLine({px,0}, {X, Y - W},红色);
                    }
                    }
                    if (绘制.信息)
                    {
                    char extra[100];
                    sprintf(extra, "[%d] %s ",阵营,Player.名称);
                    AddText(font, 20, ImVec2(X,Y - W - 10),ImColor(255, 255, 255, 255), extra);
                    }
                if (绘制.距离)
                {
                char extras[128];
                sprintf(extras,"%.2fM",Player.距离);
                AddText(font,距离大小, {X, (Y + W) + 10},距离颜色,extras);
                
                sprintf(extras,"%s - %d",Player.手持枪械名称,Player.手持枪械子弹数量);
                AddText(font,距离大小,{X, (Y + W) + 30},距离颜色,extras);
                }
                }
        }
    
    int 人机数量 = getDword(人机数组指针 + 0x18);

    for(int i=0; i<人机数量; i++)
    {
        Player.结构体 = Read_Pointers(人机数组指针 + 0x10,0x20+0x8 * i, 0);

        Player.血量 = getFloat(Player.结构体 + Fields["RoleAILogic::<Hp>k__BackingField"]);

        float 倒地血量 = getFloat(Player.结构体 + Fields["RoleAILogic::<WeakValue>k__BackingField"]);

        if (倒地血量==0) continue;

        Vector3 绘制碰撞,绘制坐标t;
        
        if (Player.血量!=0) {
            ReadBuffer(Read_Pointers(Player.结构体 + Fields["RoleAILogic::<ClientLogic>k__BackingField"],Fields["ClientRoleAILogic::roleAIHits"],0x10,0x50,0x10,0x30,0x30,0x18,0x48,0x28,0xA0), &Player.敌人坐标, sizeof(Vector));
            ReadBuffer(Read_Pointers(Player.结构体 + Fields["RoleAILogic::<ClientLogic>k__BackingField"],Fields["ClientRoleAILogic::roleAIHits"],0x10,0x50,0x10,0x30,0x30,0x18,0x48,0x28,0xA0), &Player.敌人受击点坐标, sizeof(Vector));
            ReadBuffer(Read_Pointers(Player.结构体 + Fields["RoleAILogic::<ClientLogic>k__BackingField"],Fields["ClientRoleAILogic::roleAIHits"],0x10,0x50,0x10,0x30,0x30,0x18,0x48,0x28,0xA0), &绘制碰撞, sizeof(Vector3));
            PlottingAlgorithm(绘制碰撞);
            PlottingAlgorithm(绘制碰撞);
        }else{
            ReadBuffer(Player.结构体 + Fields["RoleAILogic::<Position>k__BackingField"], &Player.敌人坐标, sizeof(Vector));
            ReadBuffer(Player.结构体 + Fields["RoleAILogic::<Position>k__BackingField"], &Player.敌人受击点坐标, sizeof(Vector));
            ReadBuffer(Player.结构体 + Fields["RoleAILogic::<Position>k__BackingField"], &绘制坐标t, sizeof(Vector3));
            PlottingAlgorithm(绘制坐标t);
            Player.敌人受击点坐标.z=Player.敌人受击点坐标.z+1;
        }
        
        if ((Player.敌人受击点坐标.x && Player.敌人受击点坐标.z && Player.敌人受击点坐标.y) != 0)
        {
            Player.掩体 = true;
        }

        float 人物欧拉角 = getFloat(get64(get64(Player.结构体 + Fields["RoleLogic::OnSetPlayerIdCallBack"])+0x40)+ 0x60);
        int 阵营 = getDword(Player.结构体 + Fields["RoleAILogic::<TeamId>k__BackingField"]);
        
        char 手持枪械名称[128];
        strcpy(Player.名称, Unicode64(Read_Pointers(Player.结构体 + Fields["RoleAILogic::<Name>k__BackingField"],0)));
        strcpy(手持枪械名称, Unicode64(Read_Pointers(Player.结构体 + Fields["RoleAILogic::<CurrentWeapon>k__BackingField"], 0xE8, 0x28, 0)));
        Player.手持枪械子弹数量 = getDword(Read_Pointers(Player.结构体 + Fields["RoleAILogic::<CurrentWeapon>k__BackingField"], 0xB8));
        
        
        

        if(Closest.结构体==Player.结构体&&Player.掩体&&自瞄.作弊射线) ImGui::GetForegroundDrawList()->AddLine({egl.width/2, egl.height/2}, {X,Y}, 自瞄射线颜色,1.5f);

        Player.距离 = Vector距离(Player.敌人坐标, My.我的自瞄用坐标);
        if(Player.距离>400) continue;

        人机++;
        Player.敌人屏幕位置 = sqrt(pow(X - egl.width/2, 2) + pow(Y - egl.height/2, 2));	// 屏幕距离
        Player.W = W;
        Player.距离 = 距离;
        
        if (!自瞄.忽略人机 && (!自瞄.忽略倒地 || Player.血量 != 0)) FindMinAt();
        if(W > 0 && 开启.人物)
                {
        if (绘制.背敌)//背敌
            {
                std::string s;
                s += std::to_string((int)Player.距离);
                s += "m";
                if (W > 0)//屏幕前
                {
                  if (Y - W > 屏幕Y)//下方
                  {
                    ImGui::GetForegroundDrawList()->AddRect({X - 46, 屏幕Y + 1},{X + 46, 屏幕Y - 51},ImColor(255,255,255,255),0,0,3.0);
                    if (阵营 != 0)
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 屏幕Y},{X + 45, 屏幕Y - 50},红色,0,0);
                    }
                    else
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 屏幕Y},{X + 45, 屏幕Y - 50},ImColor(255,255,255,100),0,0);
                    }
                    ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(X - 20, 屏幕Y - 40),ImColor(255,255,255),s.c_str()); 
                  }
                  if (Y + W < 0)//上方
                  {
                    ImGui::GetForegroundDrawList()->AddRect({X - 46, -1},{X + 46, 51},ImColor(255,255,255,255),0,0,3.0);
                    if (阵营 != 0)
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 0},{X + 45, 50},红色,0,0);
                    }
                    else
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 0},{X + 45, 50},ImColor(255,255,255,100),0,0);
                    }
                    ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(X - 20, 10 ),ImColor(255,255,255),s.c_str()); 
                  }         
                  if  (X+(W/2)<0)//左侧
                  {  
                    ImGui::GetForegroundDrawList()->AddRect({-1.0, Y - 26},{91.0, Y + 26},ImColor(255,255,255,255),0,0,3.0);
                    if (阵营 != 0)
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({0.0, Y - 25},{90.0, Y + 25},红色,0,0);
                    }
                    else
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({0.0, Y - 25},{90.0, Y + 25},ImColor(255,255,255,100),0,0);
                    }
                    ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(30,Y - 15),ImColor(255,255,255),s.c_str());             
                  }
                  if (X-(W/2) > 屏幕X)//右侧
                  {  
                    ImGui::GetForegroundDrawList()->AddRect({屏幕X+1, Y - 26},{屏幕X-91, Y + 26},ImColor(255,255,255,255),0,0,3.0);
                    if (阵营 != 0)
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({屏幕X, Y - 25},{屏幕X-90, Y + 25},红色,0,0);
                    }
                    else
                    {
                      ImGui::GetForegroundDrawList()->AddRectFilled({屏幕X, Y - 25},{屏幕X-90, Y + 25},ImColor(255,255,255,100),0,0);
                    }
                      ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(屏幕X-62,Y - 15),ImColor(255,255,255),s.c_str()); 
                    }  
                }
                else//屏幕后
                {
                      ImGui::GetForegroundDrawList()->AddRect({X - 46, 屏幕Y + 1},{X + 46, 屏幕Y - 51},ImColor(255,255,255,255),0,0,3.0);
                      ImGui::GetForegroundDrawList()->AddRectFilled({X - 45, 屏幕Y},{X + 45, 屏幕Y - 50},ImColor(255,255,255,100),0,0);
                      ImGui::GetForegroundDrawList()->AddText(font,30,ImVec2(X - 20, 屏幕Y - 40),ImColor(255,255,255),s.c_str()); 
          
                }
             }
                 if (绘制.方框)
                  {
                    if (Player.掩体)//判断
                    {
                    ImGui::GetForegroundDrawList()->AddRect({X - (W / 2), Y - W},{X + (W / 2), Y + W},红色);
                    }else{
                    ImGui::GetForegroundDrawList()->AddRect({X - (W / 2), Y - W},{X + (W / 2), Y + W},绿色);
                    }
                  }
                  if (绘制.填充)//绘制背景
                  {
                   if (Player.掩体)//判断
                    {
                    ImGui::GetForegroundDrawList()->AddRectFilled({(X - W / 2), Y - W}, {X + (W / 2), Y + W},ImColor(255,0,0,50));
                    }else{
                    ImGui::GetForegroundDrawList()->AddRectFilled({(X - W / 2), Y - W}, {X + (W / 2), Y + W},ImColor(50,255,0,50));
                    }
                   }
                  if (绘制.血量)
                    {
                    float Health;
                    if (Player.血量 <= 0)
                    {
                    Health = 倒地血量 / 100;
                    }else{
                    Health = Player.血量 / 100;
                    }
                    ImGui::GetForegroundDrawList()->AddRectFilled({X + (W / 2) + 4, Y+W-((Y+W)-(Y-W)) * Health},{X+W/2 + 10, Y + W},绿色,{6});
                    }
                    if (绘制.射线)
                    {
                    if (Player.掩体)//判断掩体
                    {
                    ImGui::GetForegroundDrawList()->AddLine({px, 0}, {X, Y - W},绿色);
                    }else{
                    ImGui::GetForegroundDrawList()->AddLine({px, 0}, {X, Y - W},红色);
                    }
                    }
                    if (绘制.信息)
                    {
                    char extra[100];
                    sprintf(extra, "[0] %s ",Player.名称);
                    AddText(font, 20, ImVec2(X,Y - W - 10),ImColor(255, 255, 255, 255), extra);
                    }
                if (绘制.距离)
                {
                char extras[128];
                sprintf(extras,"%.2fM",Player.距离);
                AddText(font,距离大小, {X, (Y + W) + 10},距离颜色,extras);
                }
                }
                }
    
    for (int i = 0; i <100; i++)
    {
        Vector3 载具坐标;
        Player.载具结构体 = Read_Pointers(get64(载具数组指针 + 0x10) + 0x20 + 8 * i,0);  // 遍历数量次数
        ReadBuffer(Player.载具结构体 + 0x68, &载具坐标, sizeof(Vector)); // 对象坐标
        if (载具坐标.X == 0&&载具坐标.Z == 0&&载具坐标.Y == 0) continue;
        
        PlottingAlgorithm(载具坐标);
        
        if (距离 < 10) continue;
        if (距离 > 400) continue;
        
		char 载具名字[128];
        strcpy(载具名字, CarNameReturn(Unicode64(Read_Pointers(Player.载具结构体 + 0xA0, 0x20, 0))));
        float 最大耐久 = getFloat(Read_Pointers(Player.载具结构体 + 0x28, 0xB0));
        float 耐久 = getFloat(Read_Pointers(Player.载具结构体 + 0x28, 0xB4));
		float 最大油量 = getFloat(Read_Pointers(Player.载具结构体 + 0x28, 0xAC));
        float 油量 = getFloat(Read_Pointers(Player.载具结构体 + 0x28, 0xA8));
        
        if (耐久 <= 0) continue;
        if (油量 <= 0) continue;
        
        if (W > 0&&开启.载具)
        {
       char extras[128];
       sprintf(extras,"%s",载具名字);
       AddText(font,20,ImVec2(X, Y + W),ImColor(255,255,0,255),extras);
   }
  }
    /*
    char extra[100];
    
    ImGui::GetForegroundDrawList()->AddRectFilled({px - 90, 55},{px + 90,120},ImColor(250,250,250,255),{80});
    ImGui::GetForegroundDrawList()->AddRect({px - 90, 55},{px + 90,120},天蓝,{80},0,3.0);
    
    sprintf(extra,"%d"),真人);
    AddText(font,35,ImVec2(px - 55, 80),红色,extra);

    sprintf(extra,"%d"),人机);
    AddText(font,35,ImVec2(px + 55, 80),绿色,extra);
    */
    char *状态;
    string LeftDraw,RightDraw;
    int 血量 = Closest.血量,距离 = Closest.距离;
    
    if (Closest.状态 == 1){状态 = "站着";
    }else if (Closest.状态 == 2){状态 = "蹲着";
    }else if (Closest.状态 == 3){状态 = "趴着";}
    
    if (绘制.人数左侧 == 0){
    LeftDraw = to_string(距离) + "M";
    }else if (绘制.人数左侧 == 1){
    LeftDraw = to_string(血量) + "hp";
    }else if (绘制.人数左侧 == 2){
    LeftDraw = 状态;
    }
    
    if (绘制.人数右侧 == 0){
    RightDraw = to_string(距离) + "M";
    }else if (绘制.人数右侧 == 1){
    RightDraw = to_string(血量) + "hp";
    }else if (绘制.人数右侧 == 2){
    RightDraw = 状态;
    }
    
    string bot = to_string(人机);
    string play = to_string(真人);
    wc& 灵动鸟宽度 = wh["灵动鸟宽度"];

    Lerp(logo.beg, logo.end, 0.1f);
    Lerp(人数位置.beg, 人数位置.end, 0.1f);
    Lerp(字体大小.beg, 字体大小.end, 0.125f);
    Lerp(字体位置.beg, 字体位置.end, 0.125f);
    Lerp(灵动鸟宽度.beg, 灵动鸟宽度.end, 0.125f);


    if ((Closest.敌人受击点坐标.x && Closest.敌人受击点坐标.z && Closest.敌人受击点坐标.y) == 0){
    logo.end = 0;
    灵动鸟宽度.end = 0;
    字体大小.end = 0;
    字体位置.end = 15;
    }else{
    logo.end = 70;
    灵动鸟宽度.end = 70;
    字体大小.end = 41;
    字体位置.end = 110;
    }
    
    float 灵动岛 = 灵动鸟宽度.beg;
    ImGui::GetForegroundDrawList()->AddRectFilled({px - (95) - 灵动岛 , 35},{px + (95) + 灵动岛 , 110},白色,200, 0); // 白色背景
    ImGui::GetForegroundDrawList()->AddRect({px - (95) - 灵动岛 , 35 },{px + (95) + 灵动岛 , 110},天蓝,200, 0, 3.3f); // 白色边框
    
    // 玩家
    auto textSize_play = ImGui::GetFont()->CalcTextSizeA((50), FLT_MAX, -1, play.c_str(), NULL, NULL);
    ImGui::GetForegroundDrawList()->AddText(NULL, (50), ImVec2(px - (textSize_play.x / 2) - (45), (73.5f) - (textSize_play.y / 2)), 红色, play.c_str());
    // 人机
    auto textSize_bot = ImGui::GetFont()->CalcTextSizeA((50), FLT_MAX, -1, bot.c_str(), NULL, NULL);
    ImGui::GetForegroundDrawList()->AddText(NULL, (50), ImVec2(px - (textSize_bot.x / 2) + (45), (73.5f) - (textSize_bot.y / 2)), 绿色, bot.c_str());
    
    if ((Closest.敌人受击点坐标.x && Closest.敌人受击点坐标.z && Closest.敌人受击点坐标.y) != 0){
    ImColor 数值颜色 = 天蓝;
    if (Closest.血量 <= 50 && Closest.距离 <= 100){
    数值颜色 = 红色;
    }else{
    数值颜色 = 天蓝;
    }
    auto textSize_left = ImGui::GetFont()->CalcTextSizeA((45), FLT_MAX, -1, LeftDraw.c_str(), NULL, NULL);
    ImGui::GetForegroundDrawList()->AddText(NULL, (45), ImVec2(px - (textSize_left.x / 2) - (110), (74) - (textSize_left.y / 2)), 数值颜色, LeftDraw.c_str());

    auto textSize_right = ImGui::GetFont()->CalcTextSizeA((45), FLT_MAX, -1, RightDraw.c_str(), NULL, NULL);
    ImGui::GetForegroundDrawList()->AddText(NULL, (45), ImVec2(px - (textSize_right.x / 2) + (110), (74) - (textSize_right.y / 2)), 数值颜色, RightDraw.c_str());
    }
    
    if (绘制.电报)
    {
    AddText(font,50,ImVec2(px - 40, 135),红色,"女朋友英文名LY8270");
    }
    memcpy(&Closest, &MinAt, sizeof(struct PlayerStruct));
    if(自瞄.圈圈开关)
    {
    ImGui::GetForegroundDrawList()->AddCircle({egl.width/2, egl.height/2}, {自瞄.范围系数}, 圈圈颜色);
    }
}

EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {

    eglQuerySurface(dpy, surface, EGL_WIDTH, &egl.width);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &egl.height);

    if (!g_Initialized) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        io.DisplaySize = ImVec2((float)egl.width, (float)egl.height);
        io.Fonts->AddFontFromMemoryTTF((void *)OPPOSans_H, OPPOSans_H_size, 26.5f, NULL, io.Fonts->GetGlyphRangesChineseFull());
        ImGui::StyleColorsLight();
        ImGui_ImplOpenGL3_Init("#version 100");
        ImGui::GetStyle().ScaleAllSizes(2.8f);
        for (auto & sgu : 颜色.随机颜色)
        {
        sgu = ImColor(ImVec4((rand() % 205 + 50) / 255.f, rand() % 255 / 255.f, rand() % 225 / 225.f, 225 / 225.f));
        }
        g_Initialized = true;
    }
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(egl.width, egl.height);
    ImGui::NewFrame();
    
    获取数据();
    DrawESP();
    ShowMenu();
    
    ImGui::EndFrame();
    ImGui::Render();

    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return old_eglSwapBuffers(dpy, surface);
}

void *hack_thread(void *) {
    do {
        sleep(1);
    } while (!isLibraryLoaded(libName));
    
    //sleep(5);

    Il2cpp::Init();
    Il2cpp::EnsureAttached();
   
    auto p_eglSwapBuffers = (uintptr_t)dlsym(RTLD_NEXT, "eglSwapBuffers");
    DobbyHook((void *)p_eglSwapBuffers, (void *)hook_eglSwapBuffers, (void **)&old_eglSwapBuffers);

    DobbyHook((void*)((void *(*)(void *)) (uintptr_t)Il2cpp::FindMethod("Role", "UpdateDynamicBone")->methodPointer),(void*)游戏世界循环,(void**)&old_游戏世界循环);
    
    DobbyHook((void*)((void *(*)(void *)) (uintptr_t)Il2cpp::FindMethod("SOCameraUserData", "get_BaseCameraRatio")->methodPointer),(void*)BaseCameraRatio,(void**)&old_BaseCameraRatio); // 平板视角
    
    Fields["CameraMove::gameWorld"] = Il2cpp::FindField("CameraMove", "gameWorld")->getOffset();
    Fields["GameWorld::startGame"] = Il2cpp::FindField("GameWorld", "startGame")->getOffset();
    Fields["StartGame::RoleList"] = Il2cpp::FindField("StartGame", "RoleList")->getOffset();
    Fields["RoleLogic::OnSetPlayerIdCallBack"] = Il2cpp::FindField("RoleLogic", "OnSetPlayerIdCallBack")->getOffset();
    Fields["RoleControl::animatorControl"] = Il2cpp::FindField("RoleControl", "animatorControl")->getOffset();
    Fields["AnimatorControl::animator"] = Il2cpp::FindField("AnimatorControl", "animator")->getOffset();
    Fields["AnimatorControl::baseSkinManager"] = Il2cpp::FindField("AnimatorControl", "baseSkinManager")->getOffset();
    Fields["RoleLogic::hp"] = Il2cpp::FindField("RoleLogic", "hp")->getOffset();
    Fields["RoleLogic::TeamNum"] = Il2cpp::FindField("RoleLogic", "TeamNum")->getOffset();
    Fields["AnimatorControl::MyBodyParts"] = Il2cpp::FindField("AnimatorControl", "MyBodyParts")->getOffset();
    Fields["CameraMove::_isSetWeaponBox"] = Il2cpp::FindField("CameraMove", "_isSetWeaponBox")->getOffset();
    Fields["CameraMove::CameraShakePoint"] = Il2cpp::FindField("CameraMove", "CameraShakePoint")->getOffset();
    Fields["CameraMove::LockRole"] = Il2cpp::FindField("CameraMove", "LockRole")->getOffset();
    Fields["CameraMove::EndPoint"] = Il2cpp::FindField("CameraMove", "EndPoint")->getOffset();
    Fields["Role::roleLogic"] = Il2cpp::FindField("Role", "roleLogic")->getOffset();
    
    Fields["RoleLogic::myStandbyState"] = Il2cpp::FindField("RoleLogic", "myStandbyState")->getOffset();
    Fields["RoleLogic::SideAim"] = Il2cpp::FindField("RoleLogic", "SideAim")->getOffset();
    Fields["RoleLogic::TopShoot"] = Il2cpp::FindField("RoleLogic", "TopShoot")->getOffset();
    Fields["RoleLogic::UserCircusBalllNet"] = Il2cpp::FindField("RoleLogic", "UserCircusBalllNet")->getOffset();
    Fields["RoleLogic::NickName"] = Il2cpp::FindField("RoleLogic", "NickName")->getOffset();
    
    Fields["RoleLogic::userWeapon"] = Il2cpp::FindField("RoleLogic", "userWeapon")->getOffset();
    Fields["RoleLogic::localSynAction"] = Il2cpp::FindField("RoleLogic", "localSynAction")->getOffset();
    Fields["RoleLogic::jumpState"] = Il2cpp::FindField("RoleLogic", "jumpState")->getOffset();
    Fields["RoleLogic::flyJumpState"] = Il2cpp::FindField("RoleLogic", "flyJumpState")->getOffset();
    Fields["RoleLogic::HeadEquipPart"] = Il2cpp::FindField("RoleLogic", "HeadEquipPart")->getOffset();
    Fields["RoleLogic::BodyEquipPart"] = Il2cpp::FindField("RoleLogic", "BodyEquipPart")->getOffset();
    Fields["RoleLogic::_moveH"] = Il2cpp::FindField("RoleLogic", "_moveH")->getOffset();
    Fields["RoleLogic::_moveV"] = Il2cpp::FindField("RoleLogic", "_moveV")->getOffset();
    
    Fields["RoleAILogic::<TeamId>k__BackingField"] = Il2cpp::FindField("RoleAILogic", "<TeamId>k__BackingField")->getOffset();
    Fields["RoleAILogic::<Name>k__BackingField"] = Il2cpp::FindField("RoleAILogic", "<Name>k__BackingField")->getOffset();
    Fields["RoleAILogic::<CurrentWeapon>k__BackingField"] = Il2cpp::FindField("RoleAILogic", "<CurrentWeapon>k__BackingField")->getOffset();
    
    Fields["CameraMove::gameWorld"] = Il2cpp::FindField("CameraMove", "gameWorld")->getOffset();
    Fields["GameWorld::startGame"] = Il2cpp::FindField("GameWorld", "startGame")->getOffset();
    Fields["StartGame::<MyRoleAIMgr>k__BackingField"] = Il2cpp::FindField("StartGame", "<MyRoleAIMgr>k__BackingField")->getOffset();
    Fields["StartGame::AllCar"] = Il2cpp::FindField("StartGame", "AllCar")->getOffset();
    Fields["GameWorld::ItemManager"] = Il2cpp::FindField("GameWorld", "ItemManager")->getOffset();
    Fields["ItemManager::_screenItemData"] = Il2cpp::FindField("ItemManager", "_screenItemData")->getOffset();
    Fields["ItemManager::cacheInfos"] = Il2cpp::FindField("ItemManager", "cacheInfos")->getOffset();
    Fields["RoleAIManager::logicList"] = Il2cpp::FindField("RoleAIManager", "logicList")->getOffset();
    Fields["RoleAILogic::<Hp>k__BackingField"] = Il2cpp::FindField("RoleAILogic", "<Hp>k__BackingField")->getOffset();
    Fields["RoleAILogic::<WeakValue>k__BackingField"] = Il2cpp::FindField("RoleAILogic", "<WeakValue>k__BackingField")->getOffset();
    Fields["RoleAILogic::<ClientLogic>k__BackingField"] = Il2cpp::FindField("RoleAILogic", "<ClientLogic>k__BackingField")->getOffset();
    Fields["ClientRoleAILogic::roleAIHits"] = Il2cpp::FindField("ClientRoleAILogic", "roleAIHits")->getOffset();
    Fields["RoleAILogic::<Position>k__BackingField"] = Il2cpp::FindField("RoleAILogic", "<Position>k__BackingField")->getOffset();
    Fields["ClientRoleAILogic::animator"] = Il2cpp::FindField("ClientRoleAILogic", "animator")->getOffset();
    Fields["ClientRoleAIAnimator::anim"] = Il2cpp::FindField("ClientRoleAIAnimator", "anim")->getOffset();
    Fields["CameraMove::NowPoint"] = Il2cpp::FindField("CameraMove", "NowPoint")->getOffset();
    Fields["CameraMove::gameWorld"] = Il2cpp::FindField("CameraMove", "gameWorld")->getOffset();

    DobbyHook((void*)((void *(*)(void *)) (uintptr_t)Il2cpp::FindMethod("BulletControl", "LocalRoleWeaponInit")->methodPointer),(void*)轨迹检测,(void**)&old_轨迹检测);
    DobbyHook((void*)((void *(*)(void *)) (uintptr_t)Il2cpp::FindMethod("Role", "SetCameraSendData")->methodPointer),(void*)视角伪装,(void**)&old_视角伪装);
    Camera_WorldToScreen = (Vector3 (*)(void *, Vector3)) (uintptr_t)Il2cpp::FindMethod("UnityEngine.Camera", "WorldToScreenPoint",1)->methodPointer;
    人物坐标获取 = (Vector3 (*)(void *)) (uintptr_t)Il2cpp::FindMethod("RoleLogic", "get_NowPoint")->methodPointer;
    射线掩体 = (bool (*)(Vector3,Vector3)) (uintptr_t)Il2cpp::FindMethod("RaycastManager", "IsPartition")->methodPointer;
    //Camera_WorldToScreen = (Vector3 (*)(void *)) (uintptr_t)Il2cpp::FindMethod("RoleLogic", "get_NowPointnPoint",1)->methodPointer;
    bInitDone = true;
    void *sym_input = DobbySymbolResolver("/system/lib/libinput.so", "_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE");
    if (NULL != sym_input) {
        DobbyHook((void *)sym_input, (void *) hook_Input, (void **)&old_Input);
    }
    DobbyHook((void *) dlsym(dlopen("libandroid.so", 4), "ANativeWindow_getWidth"), (void *) hook_getWidth, (void **) &old_getWidth);
    DobbyHook((void *) dlsym(dlopen("libandroid.so", 4), "ANativeWindow_getHeight"), (void *) hook_getHeight, (void **) &old_getHeight);
    
    pthread_create(&AimCalcuPth, NULL, 预测, NULL);

    return NULL;
}

#endif
