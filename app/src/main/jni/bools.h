#include "功能.h"

ImColor 黑色 = ImColor(0, 0, 0, 0);
ImColor 艳青 = ImColor(0, 255, 255, 255);
ImColor 红色 = ImColor(255, 0, 0, 255);
ImColor 黄色 = ImColor(255, 255, 0, 255);
ImColor 蓝色 = ImColor(0, 0, 255, 255);
ImColor 橙色 = ImColor(255, 165, 0, 255);
ImColor 粉红 = ImColor(255, 192, 203, 255);
ImColor 白色 = ImColor(255, 255, 255, 255);
ImColor 绿色 = ImColor(0, 255, 0, 255);
ImColor 浅绿 = ImColor(100, 255,100, 255);
ImColor 紫色 = ImColor(128, 0, 128, 255);
ImColor 天蓝 = ImColor(135, 206, 235, 255);
ImColor 深天蓝 = ImColor(0, 191, 255, 255);

//大小

int 名字大小 = 25;

int 阵营大小 = 25;

int 距离大小 = 25;

//粗细

int 方框粗细 = 0.0;

int 射线粗细 = 0.0;

int 骨骼粗细 = 2.8;

//颜色

ImColor 圈圈颜色 = 白色;
ImColor 子追圈圈颜色 = 白色;
ImColor 自瞄射线颜色 = 红色;
ImColor 子追射线颜色 = 红色;
ImColor 方框颜色 = 绿色;

ImColor 阵营颜色 = 白色;
ImColor 距离颜色 = 白色;

ImColor 人机名称颜色 = 白色;
ImColor 真人名称颜色 = 白色;

ImColor 人物血量颜色 = 白色;
ImColor 倒地血量颜色 = 红色;

ImColor 掩体前射线颜色 = 白色;
ImColor 掩体后射线颜色 = 红色;

ImColor 掩体前骨骼颜色 = 艳青;
ImColor 掩体后骨骼颜色 = 红色;

struct 开启信息结构体 {
bool 进程;
bool 人物;
bool 物资;
bool 载具;
bool 自瞄;
bool 子追;
bool 过检;
}开启;

struct 绘制信息结构体 {
bool 方框;
bool 填充;
bool 射线;
bool 信息;
bool 距离;
bool 背敌;
bool 骨骼;
bool 电报;
bool 名字;
bool 背景;
bool 血量;
bool 阵营;
bool 人机;
int 方框类型选择=0;
int 人数左侧 = 1,人数右侧 = 0;
}绘制;

struct 绘制载具信息结构体 {
bool 耐久;
bool 油量;
bool 距离;
bool 名字;
}绘制载具;

struct 绘制物资信息结构体 {
bool 防重叠 = false;
bool 步枪 = false;
bool 射手步枪 = false;
bool 冲锋枪 = false;
bool 狙击枪 = false;
bool 散弹枪 = false;
bool 机枪 = false;
bool 枪炮= false;
bool 子弹 = false;
bool 药物 = false;
bool 枪械配件 = false;
bool 近战武器 = false;
bool 身份卡 = false;
bool 盔甲包 = false;
bool 投掷物 = false;
bool 手枪 = false;
bool 信号枪 = false;
}绘制物资;

struct 自瞄信息结构体{
bool 头部边缘;
bool 圈圈开关;
bool 作弊射线;
bool 忽略人机;
bool 忽略倒地;
bool 忽略掩体;
bool 开火持锁;
bool 开启预判;
float 预判系数 = 1;
float 力度系数 = 2;
float 平滑系数 = 1;
int 范围系数 = 350;
int 最小动态系数 = 350;
int 最大动态系数 = 350;
int 选择 = 2,部位 = 0;
}自瞄;

struct 子追信息结构体{
bool 伪装视角;
int 概率系数 = 100;
}子追;

struct 页面信息结构体 {
bool 绘制 = true;
bool 自瞄 = false;
bool 内存 = false;
bool 设置 = false;
}页面;

int 窗口 = 0;
static int 主题颜色 = 0;
float 窗口圆角 = 0.00f;
float 控件描边 = 0.00f;
float 控件边框 = 0.00f;
float 控件圆角 = 0.00f;










void 保存配置() {
    std::string filePath = "/sdcard/Android/data/com.sofunny.Sausage/files/棒棒糖注入配置.ini";
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile 
        << "开启人物=" << 开启.人物
        << "\n" << "开启载具=" << 开启.载具
        << "\n" << "开启物资=" << 开启.物资
        << "\n" << "开启自瞄=" << 开启.自瞄
        << "\n" << "开启子追=" << 开启.子追
        
        << "\n" << "绘制人物方框=" << 绘制.方框
        << "\n" << "绘制人物填充=" << 绘制.填充
        << "\n" << "绘制人物射线=" << 绘制.射线
        << "\n" << "绘制人物信息=" << 绘制.信息
        << "\n" << "绘制人物距离=" << 绘制.距离
        << "\n" << "绘制人物背敌=" << 绘制.背敌
        << "\n" << "绘制人物血量=" << 绘制.血量
        << "\n" << "绘制人物电报=" << 绘制.电报

        << "\n" << "自瞄圈圈=" << 自瞄.圈圈开关
        << "\n" << "自瞄射线=" << 自瞄.作弊射线
        << "\n" << "头部边缘=" << 自瞄.头部边缘
        << "\n" << "不瞄人机=" << 自瞄.忽略人机
        << "\n" << "不瞄倒地=" << 自瞄.忽略倒地
        << "\n" << "不瞄掩体=" << 自瞄.忽略掩体
        << "\n" << "开火持锁=" << 自瞄.开火持锁
        << "\n" << "开启预判=" << 自瞄.开启预判
        << "\n" << "自瞄选择=" << 自瞄.选择
        << "\n" << "自瞄部位=" << 自瞄.部位
        << "\n" << "自瞄范围系数=" << 自瞄.范围系数
        << "\n" << "自瞄最大动态系数=" << 自瞄.最大动态系数
        << "\n" << "自瞄预判系数=" << 自瞄.预判系数
        << "\n" << "自瞄平滑系数=" << 自瞄.平滑系数
        << "\n" << "自瞄力度系数=" << 自瞄.力度系数
        
        << "\n" << "子追伪装视角=" << 子追.伪装视角
        << "\n" << "子追概率系数=" << 子追.概率系数
        
        << "\n" << "广角大小=" << 广角大小
        
        << "\n" << "窗口圆角=" << 窗口圆角
        << "\n" << "控件描边=" << 控件描边
        << "\n" << "控件边框=" << 控件边框
        << "\n" << "控件圆角=" << 控件圆角
        << "\n" << "主题颜色=" << 主题颜色;
        outFile.close();
    }
}

void 读取配置() {
    std::string filePath = "/sdcard/Android/data/com.sofunny.Sausage/files/棒棒糖注入配置.ini";
    std::ifstream inFile(filePath);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
        if (line.find("开启人物=") != std::string::npos) 开启.人物 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("开启载具=") != std::string::npos) 开启.载具 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("开启物资=") != std::string::npos) 开启.物资 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("开启自瞄=") != std::string::npos) 开启.自瞄 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("开启子追=") != std::string::npos) 开启.子追 = std::stof(line.substr(line.find("=") + 1));
        
        if (line.find("绘制人物方框=") != std::string::npos) 绘制.方框 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("绘制人物填充=") != std::string::npos) 绘制.填充 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("绘制人物射线=") != std::string::npos) 绘制.射线 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("绘制人物信息=") != std::string::npos) 绘制.信息 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("绘制人物距离=") != std::string::npos) 绘制.距离 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("绘制人物背敌=") != std::string::npos) 绘制.背敌 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("绘制人物血量=") != std::string::npos) 绘制.血量 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("绘制人物电报=") != std::string::npos) 绘制.电报 = std::stof(line.substr(line.find("=") + 1));
        
        if (line.find("自瞄圈圈=") != std::string::npos) 自瞄.圈圈开关 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("自瞄射线=") != std::string::npos) 自瞄.作弊射线 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("头部边缘=") != std::string::npos) 自瞄.头部边缘 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("不瞄人机=") != std::string::npos) 自瞄.忽略人机 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("不瞄倒地=") != std::string::npos) 自瞄.忽略倒地 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("不瞄掩体=") != std::string::npos) 自瞄.忽略掩体 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("开火持锁=") != std::string::npos) 自瞄.开火持锁 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("开启预判=") != std::string::npos) 自瞄.开启预判 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("自瞄选择=") != std::string::npos) 自瞄.选择 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("自瞄部位=") != std::string::npos) 自瞄.部位 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("自瞄范围系数=") != std::string::npos) 自瞄.范围系数 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("自瞄最大动态系数=") != std::string::npos) 自瞄.最大动态系数 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("自瞄预判系数=") != std::string::npos) 自瞄.预判系数 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("自瞄平滑系数=") != std::string::npos) 自瞄.平滑系数 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("自瞄力度系数=") != std::string::npos) 自瞄.力度系数 = std::stof(line.substr(line.find("=") + 1));
        
        if (line.find("子追伪装视角=") != std::string::npos) 子追.伪装视角 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("子追概率系数=") != std::string::npos) 子追.概率系数 = std::stof(line.substr(line.find("=") + 1));
        
        if (line.find("广角大小=") != std::string::npos) 广角大小 = std::stof(line.substr(line.find("=") + 1));
        
        if (line.find("窗口圆角=") != std::string::npos) 窗口圆角 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("控件描边=") != std::string::npos) 控件描边 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("控件边框=") != std::string::npos) 控件边框 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("控件圆角=") != std::string::npos) 控件圆角 = std::stof(line.substr(line.find("=") + 1));
        if (line.find("主题颜色=") != std::string::npos) 主题颜色 = std::stof(line.substr(line.find("=") + 1));
        }
        inFile.close();
    }
}









#include <iostream>
#include <vector>
#include <cmath>
//共用一个结构体
struct NE5 {
    float x;
    float y;
    float m;
};

bool matchPoint2D(const std::vector<NE5>& points, float x, float y) {
    for (const auto& point : points) {
        if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 20) {
            return true;
        }
    }
    return false;
}

void addToEnd2D(std::vector<NE5>& points, float x, float y ) {
    if (matchPoint2D(points, x, y )) {
        for (auto& point : points) {
            if (std::abs(point.x - x) <= 25 && std::abs(point.y - y) <= 20) {
                x = point.x;
                y = point.y - 25;
                addToEnd2D(points, x, y );
                return;
            }
        }
    }

    points.push_back({x, y });
}

void addToEnd(std::vector<NE5>& points, float x, float y, float m)
{
         addToEnd2D(points, x, y);
}


void readLastPoint(const std::vector<NE5>& points, float& a, float& b)
{
    if (!points.empty())
    {
        const NE5& lastPoint = points.back();
        a = lastPoint.x;
        b = lastPoint.y;
    }
}











