#pragma once
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional> //�Լ�
#include <filesystem>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

//����ũ�μ���Ʈ�� �⺻���� ����ִ� ���̺귯��
// transparentBlt�Լ� ȣ���ϱ����� ����
#pragma comment(lib, "Msimg32.lib")

#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64