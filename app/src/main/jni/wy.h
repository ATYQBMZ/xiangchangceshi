//微验网络验证//
//如果是AIDE编译jni，请将原main.cpp删除，将此注入好的文件改成main.cpp
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include "res/weiyan.h"
#include "res/cJSON.h"
#include "res/cJSON.c"
#include "res/Encrypt.h"
#include<iostream>
#include<ctime>
using namespace std;

bool 卡密隐藏;
char *_appgg;
char _Imei[40];
char _Kami[40];
char _buffer[80];
char _ggUrl[100];
char *登录内容;
std::string 输入法;
bool 大小写,大小写1;
const static char *_wyHost = "wy.llua.cn";
const static char *_wyAppid = "46971";	
const static char *_wyAppkey = "D06QEtQQuv26vtZ3";
const static char *_wyRc4key = "kJh70BRu170bRHkk";
const static char *_kmPath = "/sdcard/棒棒糖注入卡密";
const static char *_imeiPath = "/sdcard/棒棒糖注入设备码";

void 输入密码(char*a){
输入法+=a;
strcpy(_Kami,输入法.c_str());
}

