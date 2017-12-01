// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

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


//==================================
// ## 싱글톤 매니저
//==================================


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
