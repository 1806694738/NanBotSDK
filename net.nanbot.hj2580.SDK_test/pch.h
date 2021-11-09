#pragma once

//Ô¤±àÒëÍ·ÎÄ¼þÇëÎðÉ¾³ý







#ifndef PCH_H
#define PCH_H
#ifndef _M_IX86
#error NanBot is only win32
#endif
#ifdef _DEBUG
#error Please use Releas version
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
#include <cassert>
#include "CJsonObject.hpp"
#include <windows.h>
#include <cstdio> 
#include <TCHAR.H>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstring> 
#include <wininet.h>
#include <fstream>
#include <regex>

#pragma comment(lib, "Wininet.lib")
using namespace std;

using json = neb::CJsonObject;
typedef const char* text;
typedef char* _text;
typedef long long llong;

#endif //"PCH"
