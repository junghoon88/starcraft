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

#define DEVICE getDevice()
#define STAGE getStage()


//==================================
// ## 매크로 함수 ##
//==================================

#define WINSIZEX 960
#define WINSIZEY 540

//#define PI 3.14159265f

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

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = NULL; } }
#define SAFE_RELEASE2(p) { if ( (p) ) { (p)->release(); (p) = NULL; } }
#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define SAFE_DELETE_ARRAY(a) if( (a) != NULL ) delete [] (a); (a) = NULL;


//===================================
// ## 전역 변수 ## 17.08.07 ##
//===================================

extern POINT _ptMouse;
extern HWND _hWnd;
extern HINSTANCE _hInstance;
