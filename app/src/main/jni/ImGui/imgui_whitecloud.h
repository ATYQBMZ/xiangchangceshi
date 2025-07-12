#ifndef __IMGUI_WHITECLOUD_H
#define __IMGUI_WHITECLOUD_H
#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
#include <map>
#include <linux/input.h>
#include "imgui.h"
#include <sstream>

using std::string;



ImColor tsb_color, tsb_color_end, 鸡鸡鸡;
float speed = 1.5f;
string tsb_but = "待选择";
float 透明度 = 1000.0f;
bool 开关 = true;
bool window = true, windows = true;
bool 增加;
bool 减少;
int Tab, 调色板Tab = -1;
float window_x, window_y, aevrage_now, aevrage_all, 设置_Tab, 设置_调色板_size, 灵动岛左, 灵动岛右;
float tab0, tab1, tab2, tab3, tab4, tab_0, tab_1, tab_2, tab_3, tab_4;
float 灵动岛大小 = 1.0f;
float homepage, homepages, setup, setups;

struct wc {
    int Tab;
    float beg, end;
    float 动画, 动画目前, 动画目标, 动画增加速度, 动画减少速度, 动画最小值, 动画展开百分比;
    bool 动画开关, 显示内容;
    ImColor color;
};


map<string, wc> wh;
extern map<string, ImColor> Styles;
wc& 位置x = wh["位置_x"];
wc& 位置y = wh["位置_y"];
wc& 窗口x = wh["window_x"];
wc& 窗口y = wh["window_y"];
wc& 设置 = wh["设置"];
wc& 调色板 = wh["调色板"];
wc& 调色板页数 = wh["调色板页数"];

// 灵动岛的
wc& logo = wh["logo"];
wc& 字体大小 = wh["字体大小"];
wc& 字体位置 = wh["字体位置"];
wc& 人数位置 = wh["人数位置"];
wc& 灵动岛宽度 = wh["灵动岛宽度"];


ImVec2 operator+(const ImVec2& a, const ImVec2& b) {
    return ImVec2(a.x + b.x, a.y + b.y);
}
ImVec2 operator-(const ImVec2& a, const ImVec2& b) {
    return ImVec2(a.x - b.x, a.y - b.y);
}
ImVec2 operator*(const ImVec2& a, const float& b) {
    return ImVec2(a.x * b, a.y * b);
}
ImVec2 operator/(const ImVec2& a, const float& b) {
    return ImVec2(a.x / b, a.y / b);
}
ImVec4 operator+(const ImVec4& lhs, const ImVec4& rhs) {
    return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}
ImVec4 operator-(const ImVec4& lhs, const ImVec4& rhs) {
    return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}
ImVec4 operator*(const ImVec4& lhs, const ImVec4& rhs) {
    return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
}
ImVec4 operator/(const ImVec4& lhs, const ImVec4& rhs) {
    return ImVec4(rhs.x != 0 ? lhs.x / rhs.x : 0, rhs.y != 0 ? lhs.y / rhs.y : 0, rhs.z != 0 ? lhs.z / rhs.z : 0, rhs.w != 0 ? lhs.w / rhs.w : 0);
}
ImVec4 operator+=(ImVec4& lhs, const ImVec4& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    lhs.w += rhs.w;
    return lhs;
}
ImColor operator+(const ImColor& lhs, const ImColor& rhs) {
    ImVec4 result = lhs.Value + rhs.Value;
    return ImColor(result);
}
ImColor operator-(const ImColor& lhs, const ImColor& rhs) {
    ImVec4 result = lhs.Value - rhs.Value;
    return ImColor(result);
}
ImColor operator*(const ImColor& lhs, const ImColor& rhs) {
    ImVec4 result = lhs.Value * rhs.Value;
    return ImColor(result);
}
ImColor operator/(const ImColor& lhs, const ImColor& rhs) {
    ImVec4 result = lhs.Value / rhs.Value;
    return ImColor(result);
}



void Lerp(float& a, const float& b, float t) {
    a += (b - a) * (t * speed);
}



// 渐变色函数
ImVec4 set_color(float Frequency, float TimeOffset = 0.5f, float alpha = 1.0f) {
    float r = sinf(Frequency * ImGui::GetTime() + 0.0f + TimeOffset) * 127.0f + 128.0f;
    float g = sinf(Frequency * ImGui::GetTime() + 2.0f + TimeOffset) * 127.0f + 128.0f;
    float b = sinf(Frequency * ImGui::GetTime() + 4.0f + TimeOffset) * 127.0f + 128.0f;
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, alpha);
}


bool state(bool &state) {
    static ImVec2 png_pos; //需要一个静态变量存储位置，多次调用函数要传参
    if (ImGui::IsItemActive()) {
        if (!state) {
            state = true;
            png_pos = ImGui::GetWindowPos();
            return false;
        }
    } else if (state) {
        state = false;
        if (png_pos.x == ImGui::GetWindowPos().x && ImGui::GetWindowPos().y == png_pos.y) {
            return true;
        }
    }
    return false;
}

void 渐变字(const string& text, ImColor colorStart, ImColor colorEnd, float size = 60, bool 居中 = true) {
    ImVec2 textsize = ImGui::GetFont()->CalcTextSizeA(size, FLT_MAX, -1.0f, text.c_str(), text.c_str() + text.length());
    size_t text_length = text.length();
    ImColor current_color;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    if (居中)
        ImGui::SetCursorPosX( (ImGui::GetWindowWidth() - textsize.x) * 0.5f );
    ImVec2 pos = ImGui::GetCursorScreenPos();

    float flow_speed = 0.3f;
    float flow_offset = fmod(ImGui::GetTime() * flow_speed, 1.0f);

    for (size_t i = 0; i < text_length; ++i) {
        float t = static_cast<float>(i) / (text_length - 1);
        t = fmod(t - flow_offset, 1.0f);

        if (t < 0) t += 1.0f;

        if (t < 0.5f) {
            float t_normalized = t * 2.0f;
            current_color = ImColor(
                                colorStart.Value.x + (colorEnd.Value.x - colorStart.Value.x) * t_normalized,
                                colorStart.Value.y + (colorEnd.Value.y - colorStart.Value.y) * t_normalized,
                                colorStart.Value.z + (colorEnd.Value.z - colorStart.Value.z) * t_normalized,
                                colorStart.Value.w + (colorEnd.Value.w - colorStart.Value.w) * t_normalized
                            );
        } else {
            float t_normalized = (t - 0.5f) * 2.0f;
            current_color = ImColor(
                                colorEnd.Value.x + (colorStart.Value.x - colorEnd.Value.x) * t_normalized,
                                colorEnd.Value.y + (colorStart.Value.y - colorEnd.Value.y) * t_normalized,
                                colorEnd.Value.z + (colorStart.Value.z - colorEnd.Value.z) * t_normalized,
                                colorEnd.Value.w + (colorStart.Value.w - colorEnd.Value.w) * t_normalized
                            );
        }

        size_t charLength = 0;
        unsigned char lead = text[i];

        if (lead < 0x80) {
            charLength = 1;
        } else if ((lead >> 5) == 0x6) {
            charLength = 2;
        } else if ((lead >> 4) == 0xE) {
            charLength = 3;
        } else if ((lead >> 3) == 0x1E) {
            charLength = 4;
        }

        ImVec2 next_pos = pos;
        next_pos.x += ImGui::GetFont()->CalcTextSizeA(size, FLT_MAX, -1.0f, &text[i], &text[i] + charLength).x;

        ImFont* my_custom_font = ImGui::GetIO().Fonts->Fonts.back(); // 获取最后一个添加的字体
        draw_list->AddText(my_custom_font, size, pos, current_color, &text[i], &text[i] + charLength);

        pos = next_pos;
    }
    ImGui::SameLine();
    ImGui::Text(" "); // 重置光标
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + textsize.y*0.4); // 设置光标位置
}

void 圆环(ImVec2 center, float radius, ImColor color, float thickness, float luping, float current_time) {
    float percentage = current_time / luping;
    percentage = ImClamp(percentage, 0.0f, 1.0f);
    float angle = percentage * IM_PI * 2.0f;
    ImGui::GetForegroundDrawList()->PathClear();
    ImGui::GetForegroundDrawList()->PathArcTo(center, radius, IM_PI * 1.5f, IM_PI * 1.5f + angle, 64);
    ImGui::GetForegroundDrawList()->PathStroke(color, false, thickness);
}


void RenderFlowingRectangle() {

//  ImVec4 a1 = set_color(2.0f, 0.2f);
//  ImVec4 a2 = set_color(2.5f, 0.4f);
//  ImVec4 a3 = set_color(3.0f, 0.6f);
//  ImVec4 a4 = set_color(3.5f, 0.8f);

//  //  将插值后的ImVec4颜色转换回ImU32颜色
//  ImU32 upr_left = ImGui::ColorConvertFloat4ToU32(a1);
//  ImU32 upr_right = ImGui::ColorConvertFloat4ToU32(a2);
//  ImU32 bot_right = ImGui::ColorConvertFloat4ToU32(a3);
//  ImU32 bot_left = ImGui::ColorConvertFloat4ToU32(a4);

//  //  获取当前窗口的绘制列表
//  ImDrawList* draw_list = ImGui::GetWindowDrawList();
//  //  获取当前窗口的大小和位置
//  ImVec2 window_size = ImGui::GetWindowSize();
//  ImVec2 window_pos = ImGui::GetWindowPos();

//  //  设置矩形的左上角和右下角坐标
//  ImVec2 p_min = window_pos;
//  ImVec2 p_max = ImVec2(window_pos.x + window_size.x, window_pos.y + window_size.y);

//  //  使用插值颜色绘制矩形
//  draw_list->AddRectFilledMultiColor(p_min, p_max,
    //  upr_left, upr_right,
    //  bot_right, bot_left);
}




// 整体基础参数设置
void window_set() {
    ImGuiStyle & style = ImGui::GetStyle();
    ImGui::StyleColorsLight(); // 设置菜单整体风格 必须要有
    style.ScaleAllSizes(2.0f); // 控件间隔，必须在最上面，不然会设置更改后的2.0倍
    ImGui::SetNextWindowBgAlpha(1.0f);

//  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));  // 控件边框颜色
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.0f); // 主窗口背景颜色
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);  // 主窗口标题居中
    style.WindowBorderSize = 3; // 主窗口边框粗细

    style.ChildRounding = 20.0f; // 子窗口圆角
    style.ChildBorderSize = 1.0f; // 子窗口边框粗细
//  style.Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // 子窗口边框
    style.Colors[ImGuiCol_ChildBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // 子窗口背景

    style.FrameRounding = 20.0f; // 所有按钮的圆角
    style.FrameBorderSize = 2; // 所有控件的描边


    style.FramePadding = ImVec2(11, 11); // 设置复选框大小
    style.ScrollbarRounding = 15.0f; // 滚动条圆角
    style.ScrollbarSize = 25.0f; // 滚动条宽度

    style.GrabMinSize = 30.0f; // 滑块宽度
    style.GrabRounding = 999.0f; // 滑条背景圆角

}



// 主窗口参数设置
void zhu_set() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 25.0f); //  设置圆角大小为15像素
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));  // 主窗口边框颜色
}



// 子菜单标题设置
void title(const char* text, float size = 6.0f, ImVec4 color = ImVec4(50.0f/255.0f,150.0f/255.0f,255.0f/255.0f,255.0f/255.0f), ImVec4 textcolor = ImVec4(50.0f/255.0f,150.0f/255.0f,255.0f/255.0f,255.0f/255.0f)) {
    ImGui::TextColored(textcolor, "%s", text); // 文字
    ImVec2 cursor_pos = ImGui::GetCursorScreenPos(); // 绘制标题线↓
    ImVec2 start = ImVec2(cursor_pos.x, cursor_pos.y + ImGui::GetFrameHeight() / 2 - 30);
    ImVec2 end = ImVec2(start.x + ImGui::GetContentRegionAvail().x, start.y);
    ImGui::GetWindowDrawList()->AddLine(start, end, ImGui::GetColorU32(color), size); // 绘制标题线↑
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15); // 设置光标位置
}


// 绘制分割线
void Line(float longg = ImGui::GetContentRegionAvail().x, float size = 1.0f, ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 255.0f)) {
    ImVec2 cursor_pos = ImGui::GetCursorScreenPos(); // 绘制标题线↓
//  ImVec2 start = ImVec2(cursor_pos.x, cursor_pos.y + ImGui::GetFrameHeight() / 2 - 30);
    ImVec2 end = ImVec2(ImGui::GetCursorScreenPos().x + longg, ImGui::GetCursorScreenPos().y);
    ImGui::GetWindowDrawList()->AddLine(ImGui::GetCursorScreenPos(), end, ImGui::GetColorU32(color), size); // 绘制标题线↑
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5); // 设置光标位置
}



// 居中文本
void CenteredText(const char* text, float size = 1.5f, ImColor color = ImColor(30, 130, 255, 255)) {
    float oldFontScale = ImGui::GetFont()->Scale; //  保存当前字体大小
    ImGui::SetWindowFontScale(size); //  将字体大小放大1.5倍

    float windowWidth = ImGui::GetWindowWidth();
    float textWidth = ImGui::CalcTextSize(text).x;
    float textStartX = (windowWidth - textWidth) * 0.5f;
    ImGui::SetCursorPosX(textStartX); //  计算并设置文本的起始位置，使其居中

//  临时改变字体大小
    ImGui::TextColored(color, "%s", text);
    ImGui::SetWindowFontScale(oldFontScale);
}



// 复选框样式设置
void Checkbox(const char* label, bool* value) {
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 9999.0f); // 设置圆角
    ImGui::Checkbox(label, value); // 创建复选框
    ImGui::PopStyleVar(); // 恢复圆角
}



// 按钮函数，if控制
bool button(string name, ImVec2 size, float dingsize = 15.0f, ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f), ImVec4 color1 = ImVec4(0.0f, 0.0f, 0.0f, 0.0f), ImVec4 color2 = ImVec4(0.8f, 0.8f, 0.8f, 0.8f)) {
    ImGui::PushStyleColor(ImGuiCol_Button,          color); // 按钮默认颜色
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,  color); // 按钮正常颜色
    ImGui::PushStyleColor(ImGuiCol_Border,          color1); // 按钮边框颜色
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    color2); // 按钮按下颜色
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, dingsize); // 设置圆角
    bool clicked = ImGui::Button(name.c_str(), size);
    ImGui::PopStyleColor(4); // 恢复颜色
    ImGui::PopStyleVar();
    return clicked;
}




// Toggle开关
void Toggle(const string& names, bool& toggle, float x = 30, float size = 50, ImVec2 button_size = ImVec2(120, 60), float speed = 0.05f, ImColor 未激活 = ImColor(200, 200, 200), ImColor 已激活 = ImColor(75, 146, 255)) {
    wc& name = wh[names.c_str()];

    auto textSize = ImGui::GetFont()->CalcTextSizeA(size, FLT_MAX, -1, names.c_str(), NULL, NULL);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() /*+ textSize.x + x */); //设置光标位置
    if (ImGui::InvisibleButton(names.c_str(), button_size)) {
        toggle = !toggle;
    }
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();

    float radius = (max.y - min.y) / 2.0f;
    if (toggle) {
        name.end = max.x - radius;
    } else {
        name.end = min.x + radius;
    }

    ImColor color_end = ImColor(200, 200, 200);
    color_end = toggle ? 已激活 : 未激活; //  苹果绿色和灰色
    Lerp(name.color.Value.x, color_end.Value.x, speed);
    Lerp(name.color.Value.y, color_end.Value.y, speed);
    Lerp(name.color.Value.z, color_end.Value.z, speed);
    Lerp(name.color.Value.w, color_end.Value.w, speed);



    Lerp(name.beg, name.end, speed);
    ImVec2 circle_center(name.beg, min.y + radius); // 圆位置
    circle_center.x = ImClamp(circle_center.x, min.x + radius, max.x - radius); // 限制圆的位置

    ImClamp(name.beg, min.x + radius, max.x - radius);
    ImGui::GetWindowDrawList()->AddRectFilled(min, max, name.color, 9999.0f, 0); // 背景
    ImGui::GetWindowDrawList()->AddCircleFilled(circle_center, radius*0.85f, ImColor(255, 255, 255)); // 圆


    ImVec2 textPos = ImVec2(max.x + x, min.y + button_size.y/2 - textSize.y/2);
    ImGui::GetWindowDrawList()->AddText(NULL, size, textPos, ImColor(0, 0, 0, 255), names.c_str());
}




// 滑条函数
void SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = NULL, ImGuiSliderFlags flags = 0, float 光标x = 0) {
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 10.0f); // 背景圆角
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f); // 滑块圆角
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.86f, 0.86f, 0.86f, 1.0f)); // 滑条背景
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.86f, 0.86f, 0.86f, 1.0f)); // 滑条激活背景
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
     // 滑条被点击背景颜色
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.196f, 0.588f, 1.0f, 1.0f)); // 滑块手柄默认颜色
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.196f, 0.588f, 1.0f, 1.0f)); // 滑块手柄激活颜色
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // 设置文本颜色
//  ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 10, ImGui::GetCursorPos().y));
    ImGui::Text("%s", label); // 文本
    ImGui::PopStyleColor(); // 释放文本颜色
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // 设置滑条文本颜色
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x, ImGui::GetCursorPos().y - 13.0f)); // 缩小上下间距
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 光标x); // 设置光标位置
    ImGui::SliderFloat(label, v, v_min, v_max, format, flags); // 创建滑条
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x, ImGui::GetCursorPos().y - 13.0f)); // 缩小上下间距
    ImGui::PopStyleColor(6); // 释放颜色
    ImGui::PopStyleVar(2); // 释放圆角
}




// 吹雪调色板
void 吹雪调色板() {
    static ImVec2 tsb_min, tsb_max, tsb_end;
    static string last_clicked_button = ""; //  记录最后被点击的按钮的名称

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f); //  设置按钮圆角大小
    ImGui::BeginGroup(); // 开始新的控件组
    for (int i = 0; i < Styles.size(); ++i) {
        auto it = next(Styles.begin(), i);
        string buttonText = "按钮 " + it->first;
        ImVec4 color = it->second.Value;

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // 设置文本颜色
        ImGui::PushStyleColor(ImGuiCol_Button,          color); // 按钮默认颜色
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,  color); // 按钮正常颜色
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,    color); // 按钮按下颜色
        ImGui::PushStyleColor(ImGuiCol_Border,          color); // 边框颜色


        int itemsPerLine = Styles.size() / 7; //  每行应该有的元素数量
        int remainder = Styles.size() % 7; //  计算不能整除7的余数

        if ((i > 0) && (i % itemsPerLine == 0)) ImGui::NewLine(); // 换行，一共十行
        if (Styles.size() - ((i + remainder) / 7 * 7) == remainder) { // 处理最后一行多余的
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
        }

        ImVec2 buttonPos = ImGui::GetCursorScreenPos();
        if (ImGui::Button(buttonText.c_str(), ImVec2(50, 50))) {
            last_clicked_button = it->first; //  更新最后被点击的按钮
            tsb_end = buttonPos; //  设置随后被点击的标识
            tsb_color_end = color; // 赋值颜色
        }
        if (last_clicked_button == it->first) {
            tsb_end = buttonPos; //  如果这个按钮是最后被点击的，更新坐标
        }

        ImGui::SameLine();// 同行
        ImGui::PopStyleColor(5); // 释放文本颜色
    }
    ImGui::EndGroup(); // 控件组结束
    ImGui::PopStyleVar(); // 恢复按钮圆角


    Lerp(tsb_min.x, tsb_end.x - 8, 0.05f);
    Lerp(tsb_min.y, tsb_end.y - 8, 0.04f);
    Lerp(tsb_max.x, tsb_end.x + 58, 0.05f);
    Lerp(tsb_max.y, tsb_end.y + 58, 0.04f);


    Lerp(tsb_color.Value.x, tsb_color_end.Value.x, 0.04f);
    Lerp(tsb_color.Value.y, tsb_color_end.Value.y, 0.04f);
    Lerp(tsb_color.Value.z, tsb_color_end.Value.z, 0.04f);
    Lerp(tsb_color.Value.w, tsb_color_end.Value.w, 0.04f);

    ImGui::GetWindowDrawList()->AddRectFilled( tsb_min, tsb_max, tsb_color, 12);

}



void 调色板按钮(string names, ImColor& Color, int Tab, float 按钮x = 335, float 按钮y = 105, int 矩形位置 = 0, float 矩形圆角 = 17) {
    ImVec2 min, max, textPos, textMin, textMax;

    ImGui::PushStyleColor(ImGuiCol_Button,          ImVec4(0, 0, 0, 0)); // 按钮默认颜色
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,  ImVec4(0, 0, 0, 0)); // 按钮正常颜色
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    ImVec4(0, 0, 0, 0)); // 按钮按下颜色
    ImGui::PushStyleColor(ImGuiCol_Border,          ImVec4(0, 0, 0, 1)); // 按钮边框颜色
    ImGui::PushStyleColor(ImGuiCol_Text,            ImVec4(0, 0, 0, 0)); //  设置文本颜色为透明
    if (ImGui::Button(names.c_str(), ImVec2(按钮x, 按钮y))) {
        调色板Tab = Tab;
        tsb_but = names;
    }
    ImGui::PopStyleColor(); // 释放文本颜色

    if (调色板Tab == Tab) {
        Lerp(Color.Value.x, tsb_color.Value.x, 0.04f);
        Lerp(Color.Value.y, tsb_color.Value.y, 0.04f);
        Lerp(Color.Value.z, tsb_color.Value.z, 0.04f);
        Lerp(Color.Value.w, 透明度 / 1000, 0.04f);
// 用函数要修改，懒得改了
    }
    if (!矩形位置) {
        min = ImVec2(ImGui::GetItemRectMin().x + 按钮x*0.5f, ImGui::GetItemRectMin().y + 20);
        max = ImVec2(ImGui::GetItemRectMax().x - 20, ImGui::GetItemRectMax().y - 20);
        ImGui::GetWindowDrawList()->AddRectFilled( min, max, Color, 12);
    } else {
        min = ImVec2(ImGui::GetItemRectMin().x + 按钮x*0.62f, ImGui::GetItemRectMin().y + 15);
        max = ImVec2(ImGui::GetItemRectMax().x - 15, ImGui::GetItemRectMax().y - 15);
        ImGui::GetWindowDrawList()->AddRectFilled( min, max, tsb_color, 12);
    }


// 走个路文字占一半矩形占一半，文字要居中两次
    textMin = ImGui::GetItemRectMin();
    textMax = ImVec2(ImGui::GetItemRectMin().x + (ImGui::GetItemRectMax().x - ImGui::GetItemRectMin().x) / 2, ImGui::GetItemRectMin().y + (ImGui::GetItemRectMax().y - ImGui::GetItemRectMin().y) / 2);
    auto textSize = ImGui::GetFont()->CalcTextSizeA(38, FLT_MAX, -1, names.c_str(), NULL, NULL);
    textPos = ImVec2( textMax.x - (textMax.x - textMin.x) / 2 - (textSize.x / 2), textMax.y - (textSize.y / 2));
    if (!矩形位置) {
        textPos = ImVec2( textMax.x - (textMax.x - textMin.x) / 2 - (textSize.x / 2), textMax.y - (textSize.y / 2));
        ImGui::GetWindowDrawList()->AddText(NULL, 38, textPos, ImColor(0, 0, 0), names.c_str());
    } else {
        textPos = ImVec2( textMax.x - (textMax.x - textMin.x) / 2 - (textSize.x / 2) - 8, textMax.y - (textSize.y / 2));
        ImGui::GetWindowDrawList()->AddText(NULL, 35, textPos, ImColor(0, 0, 0), ("修改: " + tsb_but).c_str());
    }

    ImGui::PopStyleColor(4); // 释放按钮颜色
}




// 滑动选择条
void whitecloud(const vector<string>& names, int& 参数, float 居中 = 0, float 按钮x = 120, float 按钮y = 70, float 矩形圆角 = 17) {
    ImVec2 按钮 = ImVec2(按钮x, 按钮y);
    ImVec2 矩形 = ImVec2(按钮.x * 0.97f, 按钮.y * 0.95f);
    ImVec2 差距 = ImVec2(按钮.x - 矩形.x, 按钮.y - 矩形.y);
    ImVec2 窗口(按钮.x*names.size(), 按钮.y);
    ImVec2 min, max;
    wc& name = wh[names[0].c_str()];

    if (居中)
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetWindowSize().x - 窗口.x)/2, ImGui::GetWindowPos().y + ImGui::GetCursorPos().y)); // 窗口居中
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.86f, 0.86f, 0.86f, 0.0f)); // 子窗口边框
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.86f, 0.86f, 0.86f, 1.0f)); // 子窗口背景
    ImGui::PushStyleColor(ImGuiCol_Button,          ImVec4(0.86f, 0.86f, 0.86f, 0.0f)); // 按钮默认颜色
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,  ImVec4(0.86f, 0.86f, 0.86f, 0.0f)); // 按钮正常颜色
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,    ImVec4(0.86f, 0.86f, 0.86f, 0.0f)); // 按钮按下颜色
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // 设置按钮与窗口的间距
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, ImGui::GetStyle().ItemSpacing.y)); // 设置同行按钮间距
    ImGui::BeginChild(names[0].c_str(), 窗口, true); //  ...绘制第二页内容...
// 按钮1位置为 min.x   按钮2位置为  min.x + 按钮.x     按钮3位置为  min.x + 按钮.x*2
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 0)); //  设置文本颜色为透明
    if (ImGui::Button(names[0].c_str(), ImVec2(按钮.x, 按钮.y))) {
        name.Tab = 0;
        参数 = 0;
    }
    ImGui::PopStyleColor(); // 释放颜色
    ImGui::SameLine();// 同行
    min = ImVec2(ImGui::GetItemRectMin().x + 差距.x, ImGui::GetItemRectMin().y + 差距.y);
    max = ImVec2(ImGui::GetItemRectMax().x - 差距.x, ImGui::GetItemRectMax().y - 差距.y);

// 动画最主要的部分，点击按钮后end给他赋值，再进行线性插值
    Lerp(name.beg, name.end, 0.06f);

// 绘制滑块矩形
    ImGui::GetWindowDrawList()->AddRectFilled(
        ImVec2(min.x + name.beg, min.y),
        ImVec2(max.x + name.beg, max.y),
        ImColor(255, 255, 255, 255),
        矩形圆角
    );
// 循环生成按钮和按钮名称
    for (int i = 0; i < names.size(); i++) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 0)); //  设置文本颜色为透明
// 生成按钮，第二个按钮开始
        if (i + 1 < names.size()) {
            if (ImGui::Button(names[i + 1].c_str(), ImVec2(按钮.x, 按钮.y))) {
                name.Tab = i + 1;
                参数 = i + 1;
            }
            ImGui::SameLine();// 同行
        }
        ImGui::PopStyleColor(); // 释放颜色
// 设置按钮被点击后end的值，end是目标位置
        if (name.Tab == i) {
            name.end = 按钮.x * i;
        }
// 生成按钮文字，以防按钮名字被矩形遮挡
        string bynh = names[i];
        ImVec2 居中(min.x, min.y);
        if (i > 0) {
            居中.x += 按钮.x * i;
        }
        float px = 居中.x + (max.x - min.x) / 2;
        float py = 居中.y + (max.y - min.y) / 2;
        auto textSize_bynh = ImGui::GetFont()->CalcTextSizeA(35, FLT_MAX, -1, bynh.c_str(), NULL, NULL);
//  ImVec2 textSize = ImGui::CalcTextSize(bynh.c_str());
        ImVec2 textPos = ImVec2(px - (textSize_bynh.x / 2), py - (textSize_bynh.y / 2));

        ImGui::GetWindowDrawList()->AddText(NULL, 35, textPos, ImColor(0, 0, 0, 255), bynh.c_str());
    }

    ImGui::EndChild();
    ImGui::PopStyleColor(5); // 释放颜色
    ImGui::PopStyleVar(2); // 释放按钮间距
}





// 没啥卵用的线条
void DrawFlowingGradientLine(ImDrawList* draw_list, ImVec2 start, ImVec2 end, ImVec4 start_color, ImVec4 end_color, float flow_speed) {
    const int num_segments = 100;
    ImVec2 direction = end - start;
    ImVec2 segment = direction / (float)num_segments;

    float flow_offset = fmod(ImGui::GetTime() * flow_speed, 1.0f);

    ImVec2 current_position = start;
    for (int i = 0; i < num_segments; ++i) {
        float t = (float)i / (float)(num_segments - 1) + flow_offset;
        t = fmod(t, 1.0f);

        ImVec4 color = ImVec4(
                           start_color.x + (end_color.x - start_color.x) * t,
                           start_color.y + (end_color.y - start_color.y) * t,
                           start_color.z + (end_color.z - start_color.z) * t,
                           start_color.w + (end_color.w - start_color.w) * t
                       );
        ImU32 im_color = ImGui::ColorConvertFloat4ToU32(color);
        ImVec2 next_position = current_position + segment;

        draw_list->AddLine(current_position, next_position, im_color, 10.0f);

        current_position = next_position;
    }
}
void DrawFlowingGradientLine2(ImDrawList* draw_list, ImVec2 start, ImVec2 end, ImVec4 start_color, ImVec4 end_color, float flow_speed) {
    const int num_segments = 100;
    ImVec2 direction = end - start;
    ImVec2 segment = direction / (float)num_segments;

    float flow_offset = fmod(ImGui::GetTime() * flow_speed, 1.0f);

    ImVec2 current_position = start;
    for (int i = 0; i < num_segments; ++i) {
//  Calculate normalized position along the line
        float t = (float)i / (float)(num_segments - 1);
//  Apply flow offset with wrapping around to create a seamless effect
        t = fmod(t + flow_offset, 1.0f);

//  Calculate color at the current position
        ImVec4 color;
        if (t < 0.5f) {
//  First half of the line: transition from start_color to end_color
            float t_normalized = t * 2.0f; //  Normalize t to [0, 1] for this half
            color = ImVec4(
                        start_color.x + (end_color.x - start_color.x) * t_normalized,
                        start_color.y + (end_color.y - start_color.y) * t_normalized,
                        start_color.z + (end_color.z - start_color.z) * t_normalized,
                        start_color.w + (end_color.w - start_color.w) * t_normalized
                    );
        } else {
//  Second half of the line: transition from end_color back to start_color
            float t_normalized = (t - 0.5f) * 2.0f; //  Normalize t to [0, 1] for this half
            color = ImVec4(
                        end_color.x + (start_color.x - end_color.x) * t_normalized,
                        end_color.y + (start_color.y - end_color.y) * t_normalized,
                        end_color.z + (start_color.z - end_color.z) * t_normalized,
                        end_color.w + (start_color.w - end_color.w) * t_normalized
                    );
        }

        ImU32 im_color = ImGui::ColorConvertFloat4ToU32(color);
        ImVec2 next_position = current_position + segment;

        draw_list->AddLine(current_position, next_position, im_color, 10.0f);

        current_position = next_position;
    }
}




// 北京时间函数
string getBeijingTimeString() {
// 获取当前时间
    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::gmtime(&now); // 获取UTC时间

// 北京时间比UTC时间快8个小时
    now_tm->tm_hour += 8;
    now_tm->tm_isdst = 0; // 清除夏令时标志

// 如果超出范围，需要调整日期
    if (now_tm->tm_hour >= 24) {
        now_tm->tm_hour -= 24;
        now_tm->tm_mday += 1;
// 这里没有处理月份和年份的变化，可能需要根据实际情况进行调整
    }

    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", now_tm); // 格式化时间
    return std::string(buffer);
}

map<string, ImColor>Styles= {{"初始化白色",ImColor(1,1,1)},{"象牙黑",ImColor(41,36,33)},{"泠灰",ImColor(128,138,135)},{"灰色",ImColor(192,192,192)},{"石板灰",ImColor(112,128,144)},{"暖灰色",ImColor(128,128,105)},{"牛马蓝色",ImColor(140,5,255)},{"桔黄色",ImColor(255,228,196)},{"cornsilk",ImColor(255,248,220)},{"蜜露橙",ImColor(240,255,240)},{"象牙色",ImColor(225,25,240)},{"亚麻色",ImColor(250,240,230)},{"navajo",ImColor(255,22,173)},{"old",ImColor(253,245,20)},{"海贝壳色",ImColor(55,195,28)},{"淡黄色",ImColor(229,222,179)},{"砖红",ImColor(156,102,31)},{"镉红",ImColor(227,23,13)},{"珊瑚色",ImColor(255,127,80)},{"耐火砖色",ImColor(178,34,34)},{"印度红",ImColor(176,23,31)},{"栗色",ImColor(176,48,96)},{"粉红",ImColor(255,192,203)},{"木莓色",ImColor(135,38,87)},{"红",ImColor(255,0,0)},{"橙红色",ImColor(250,128,114)},{"蕃茄红",ImColor(255,99,71)},{"镉橙",ImColor(255,97,3)},{"胡萝卜色",ImColor(237,145,33)},{"桔黄",ImColor(255,128,0)},{"桔红",ImColor(255,69,0)},{"香蕉色",ImColor(227,207,87)},{"镉黄",ImColor(255,153,18)},{"dougello",ImColor(235,142,85)},{"forum",ImColor(255,227,132)},{"金黄色",ImColor(255,215,0)},{"黄花色",ImColor(218,165,32)},{"瓜色",ImColor(227,168,105)},{"黄色",ImColor(255,255,0)},{"米色",ImColor(163,148,128)},{"棕色",ImColor(128,42,42)},{"锻浓黄土色",ImColor(138,54,15)},{"锻棕土色",ImColor(138,51,36)},{"巧克力色",ImColor(210,105,30)},{"肉色",ImColor(255,125,64)},{"黄褐色",ImColor(240,230,140)},{"玫瑰红",ImColor(188,143,143)},{"肖贡土色",ImColor(199,97,20)},{"标土棕",ImColor(115,74,18)},{"乌贼墨棕",ImColor(94,38,18)},{"赭色",ImColor(160,82,45)},{"马",ImColor(139,69,19)},{"沙棕色",ImColor(244,164,96)},{"棕褐色",ImColor(210,180,140)},{"蓝色",ImColor(0,0,255)},{"钴色",ImColor(61,89,171)},{"dodger",ImColor(30,144,255)},{"靛青",ImColor(8,46,84)},{"jackie",ImColor(11,23,70)},{"锰蓝",ImColor(3,168,158)},{"深蓝色",ImColor(25,25,112)},{"藏青色",ImColor(0,0,128)},{"孔雀篮色",ImColor(51,161,201)},{"浅灰蓝色",ImColor(176,224,230)},{"品蓝",ImColor(65,105,225)},{"石板蓝",ImColor(106,90,205)},{"天蓝",ImColor(135,206,235)},{"钢青色",ImColor(70,130,180)},{"土耳其玉色",ImColor(0,199,140)},{"深蓝色",ImColor(18,10,143)},{"碧绿色",ImColor(127,255,212)},{"青色",ImColor(0,255,255)},{"青绿色",ImColor(64,224,208)},{"黄绿色",ImColor(127,255,0)},{"钴绿色",ImColor(61,145,64)},{"翠绿色",ImColor(0,201,87)},{"森林绿",ImColor(34,139,34)},{"绿色",ImColor(0,255,0)},{"草地绿",ImColor(124,252,0)},{"酸橙绿",ImColor(50,205,50)},{"薄菏色",ImColor(189,252,201)},{"草绿色",ImColor(107,142,35)},{"暗绿色",ImColor(48,128,20)},{"海绿色",ImColor(46,139,87)},{"嫩绿色",ImColor(0,255,127)},{"绿土",ImColor(56,94,15)},{"紫罗蓝色",ImColor(138,43,226)},{"jasoa",ImColor(160,102,211)},{"湖紫色",ImColor(153,51,250)},{"红色",ImColor(255,0,255)},{"淡紫色",ImColor(218,112,214)},{"梅红色",ImColor(221,160,221)},{"紫色",ImColor(160,32,240)},{"艳青2",ImColor(0,255,255,255)},{"黄色2",ImColor(200,255,0,255)},{"蓝色2",ImColor(0,0,255,255)},{"橙色2",ImColor(255,165,0,255)},{"粉红2",ImColor(255,192,203,255)},{"白色2",ImColor(255,255,255,255)},{"紫色2",ImColor(15,67,255,255)},{"天蓝2",ImColor(135,206,235,255)},{"深天蓝",ImColor(0,191,255,255)},{"棕色2",ImColor(144,144,144,255)},{"空白2",ImColor(144,144,144,255)},{"粉色2",ImColor(226,145,163,255)},{"灰色2",ImColor(130,132,142,255)}};


// 颜色数组
float tm = 255/255.f;
ImVec4 arr[] = {
    {135/255.f,206/255.f,255/255.f,tm},    //淡蓝    1
    {255/255.f,0/255.f,0/255.f,tm},         //红色   2
    {0/255.f,255/255.f,127/255.f,tm},       //鲜绿   3
    {123/255.f,200/255.f,0/255.f,tm},       //草绿   4
    {255/255.f,182/255.f,193/255.f,tm},     //粉红   5
    {218/255.f,112/255.f,214/255.f,tm},      //紫色   6
    {255/255.f,165/255.f,0/255.f,tm},       //橙色   9
    {153/255.f,204/255.f,255/255.f,tm},     //淡蓝   10
    {204/255.f,255/255.f,153/255.f,tm},     //浅绿   11
    {255/255.f,200/255.f,153/255.f,tm},     //淡黄   12
    {255/255.f,153/255.f,153/255.f,tm},     //淡粉   13
    {153/255.f,153/255.f,204/255.f,tm},     //淡紫   14
    {102/255.f,204/255.f,153/255.f,tm},     //浅绿   16
    {255/255.f,102/255.f,0/255.f,tm},       //深橙   17
    {102/255.f,204/255.f,204/255.f,tm},     //淡青   18
    {153/255.f,204/255.f,255/255.f,tm},     //淡蓝   19
    {128/255.f,0/255.f,128/255.f,tm},      //淡紫     22
    {0/255.f,128/255.f,128/255.f,tm},      //青色     23
    {255/255.f,128/255.f,128/255.f,tm},    //不知道   24
    {255/255.f,215/255.f,0/255.f,tm},      //琥珀色   26
    {255/255.f,69/255.f,0/255.f,tm},      //深橙色    27
    {153/255.f,50/255.f,204/255.f,tm},    //紫罗兰   29
    {139/255.f,69/255.f,19/255.f,tm},      //棕色     30
    {0/255.f,139/255.f,139/255.f,tm},      //深青色   32
    {184/255.f,134/255.f,11/255.f,tm},      //橄榄褐   33
    {169/255.f,169/255.f,169/255.f,tm},    //深灰色   34
    {189/255.f,183/255.f,107/255.f,tm},    //浅棕色   36
    {233/255.f,150/255.f,122/255.f,tm},    //浅橙色   37
    {143/255.f,188/255.f,143/255.f,tm},   //浅橄榄绿  38
    {255/255.f,0/255.f,255/255.f,tm}      //紫色      41
};
int length = sizeof(arr)/16;


// 封装的绘图辅助类，用于绘制一些描边字体啊等等
class DrawIo {
public:
    inline void 绘制加粗文本(float size, float x, float y, ImColor color, ImColor color1, const char* str) {
        ImGui::GetBackgroundDrawList()->AddText(NULL, size, {(float)(x-0.1), (float)(y-0.1)}, color1, str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, size, {(float)(x+0.1), (float)(y+0.1)}, color1, str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, size, {x, y}, color, str);
    }

    inline void 绘制字体描边(float size,int x, int y, ImVec4 color, const char* str) {
        ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x - 0.1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(color), str);
    }

    inline void CenterText(float X,float Y,const char* content,float fontSize, ImVec4 color) {
        auto textSize = ImGui::CalcTextSize(content, 0, fontSize);
        textSize.x *= fontSize / 25.0f;
        textSize.y *= fontSize / 25.0f;
        ImGui::GetBackgroundDrawList()->AddText(NULL, fontSize,ImVec2(X - textSize.x / 2, Y), ImGui::ColorConvertFloat4ToU32(color), content);
    }

    inline void DrawRectFilledCorner(int x, int y, int w, int h, ImColor color, int rounding) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), (color), rounding, ImDrawCornerFlags_All);
    }

    inline void DrawCircleFilled(int x, int y, int radius, ImVec4 color, int segments) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(color), segments);
    }

    inline void DrawLine(int x1, int y1, int x2, int y2, ImVec4 color, int size) {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(color), size);
    }

    inline void DrawRect(int x, int y, int w, int h, ImVec4 color,int size) {  //rounding 方框边缘曲率  //rounding_corners_flags 方框边缘弯曲类型  1.ImDrawCornerFlags_All 2.ImDrawCornerFlags_Top 3. ImDrawCornerFlags_Bot 4. ImDrawCornerFlags_Left 5. ImDrawCornerFlags_Right
        // ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x+w, y+h), ImGui::ColorConvertFloat4ToU32(color), 10, 0, size);
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x+w, y+h), ImGui::ColorConvertFloat4ToU32(color), 10, ImDrawCornerFlags_All, size);
    }


    inline void DrawRectFilled(int x, int y, int w, int h, ImVec4 color) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x+w, y+h), ImGui::ColorConvertFloat4ToU32(color), 0, 0);
    }

    inline void DrawCircle(float X, float Y, float radius, float a, float r, float g, float b, float thickness) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(X, Y), radius, ImColor(r, g, b, a), 0, thickness);
    }

    inline void DrawStrokeText(int x, int y, ImVec4 color, const char* str) {
        ImGui::GetBackgroundDrawList()->AddText(NULL, 25, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, 25, ImVec2(x - 0.1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, 25, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, 25, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetBackgroundDrawList()->AddText(NULL, 25, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(color), str);
    }

    inline void DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, ImVec4 Color, int T) {
        ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(Color));
    }

    inline void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, ImVec4 Color, int T) {
        ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(Color));
    }
} DrawTf;

#endif