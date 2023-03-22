#pragma once
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional> //함수
#include <filesystem>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

//마이크로소프트에 기본으로 깔려있는 라이브러리
// transparentBlt함수 호출하기위해 넣음
#pragma comment(lib, "Msimg32.lib")

#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64