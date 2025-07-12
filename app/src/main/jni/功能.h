bool 广角;
bool 准心修改开关;
bool 飞高加速开关;
bool 全枪自动开关;
bool 全枪射速开关;
bool 全枪间隔开关;
int 准心样式=0;
float 广角大小=80;




float (*old_WeTestSDK_InitializeMTP)(void*检测) = nullptr;
float WeTestSDK_InitializeMTP(void*检测) {
    if(检测!=nullptr)
    {
        return -698416192;
    }
}

float (*old_Launch_InitializeMTP)(void*检测) = nullptr;
float Launch_InitializeMTP(void*检测) {
    if(检测!=nullptr)
    {
        return -698416192;
    }
}

float (*old_BaseCameraRatio)(void*广角修改) = nullptr;//旧函数
float BaseCameraRatio(void*广角修改){//新函数以及变量名
if(广角修改!=nullptr && 广角)
{
return 广角大小;
}else{
return old_BaseCameraRatio(广角修改);
}
}

float (*old_GetZhunXing)(void*准心) = nullptr;//旧函数
float GetZhunXing(void*准心){//新函数以及变量名
if(准心!=nullptr && 准心修改开关)
{
return 准心样式;
}else{
return old_GetZhunXing(准心);
}
}

float (*old_AutoFireDelayTime)(void*全枪射速) = nullptr;
float AutoFireDelayTime(void*全枪射速) {
    if(全枪射速 != nullptr && 全枪射速开关)
        return -999;
    else
        return old_AutoFireDelayTime(全枪射速);
}

float (*old_HasAutoFire)(void*全枪自动) = nullptr;
float HasAutoFire(void*全枪自动) {
    if(全枪自动 != nullptr && 全枪自动开关)
        return true;
    else
        return old_HasAutoFire(全枪自动);
}

float (*old_getFireDeployTime)(void*全枪间隔) = nullptr;
float getFireDeployTime(void*全枪间隔) {
    if(全枪间隔 != nullptr && 全枪间隔开关)
        return true;
    else
        return old_getFireDeployTime(全枪间隔);
}

float (*old_get_flyMaxSpeedForward)(void*飞高加速) = nullptr;
float get_flyMaxSpeedForward(void*飞高加速) {
    if(飞高加速 != nullptr && 飞高加速开关)
        return 200;
    else
        return old_get_flyMaxSpeedForward(飞高加速);
}

