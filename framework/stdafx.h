#pragma once

// 공용 헤더
// Windows 헤더 파일:
#include <windows.h>
//#include <iostream>
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
#include <tchar.h>
//#include <commdlg.h>	//OPENFILENAME

#include <assert.h>
#include <stdio.h>

#include <vector>
#include <string>
#include <map>

#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

#pragma warning( disable : 4996 )

using namespace std;


// 프로젝트 헤더
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "collision.h"
#include "textureManager.h"
#include "timeManager.h"
#include "sceneManager.h"
#include "database.h"
#include "camera.h"
#include "textManager.h"
#include "keyAniManager.h"
#include "rectManager.h"
#include "soundManager.h"


#include "globalMacroVariables.h"

using namespace IOTA_UTIL;

//#include "Keyboard.h"
//#include "PrintText.h"

//==================================
// ## 싱글톤 매니저
//==================================

#define DEVICE getDevice()
#define STAGE getStage()

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define TEXTUREMANAGER textureManager::getSingleton()
//#define TXTDATA txtData::getSingleton()
#define TIMEMANAGER timeManager::getSingleton() 
#define SOUNDMANAGER soundManager::getSingleton()
//#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
//#define INIDATA iniDataManager::getSingleton()
#define DATABASE database::getSingleton()
#define MAINCAMERA camera::getSingleton()
//#define RENDERMANAGER RenderManager::getSingleton()
#define TEXTMANAGER textManager::getSingleton()
#define RECTMANAGER rectManager::getSingleton()


//==================================
// ## 매크로 함수 ##
//==================================

#define WINSIZEX 960
#define WINSIZEY 540

//#define PI 3.14159265f

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = NULL; } }
#define SAFE_RELEASE2(p) { if ( (p) ) { (p)->release(); (p) = NULL; } }
#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define SAFE_DELETE_ARRAY(a) if( (a) != NULL ) delete [] (a); (a) = NULL;

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69

#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B

#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28

#define VK_PAGEUP 0x21 //PgUp
#define VK_PAGEDOWN 0x22 //PgDn

#define VK_MULTIPLY 0x6A
#define VK_ADD 0x6B
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_SUBTRACT 0x6D //- 
#define VK_DECIMAL 0x6E //. 
#define VK_DIVIDE 0x6F /// 

#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_RETURN 0x0D
#define VK_TAB 0x09
#define VK_BACK 0x08

#define VK_SELECT 0x29   
#define VK_PRINT 0x2A   
#define VK_EXECUTE 0x2B   
#define VK_SNAPSHOT 0x2C
#define VK_HELP 0x2F

#define VK_OEM4 0xDB //[
#define VK_OEM6 0xDD //]


//===================================
// ## 전역 변수 ## 17.08.07 ##
//===================================

extern POINT _ptMouse;
extern POINT _mainCamera;
extern HWND _hWnd;
extern HINSTANCE _hInstance;