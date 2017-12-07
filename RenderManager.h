#pragma once
#include "singletonBase.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//17. 09. 29. jhkim
//Z-Order 변수를 추가해서 벡터에 추가한 후에, mainGame 에서 한번에 랜더를 뿌려줌 
////////////////////////////////////////////////////////////////////////////////////////////////
enum RENDER_TYPE
{
	RENDER_TYPE_RECT,
	RENDER_TYPE_TEXT,

	RENDER_TYPE_IMAGE_NORMAL,
	RENDER_TYPE_IMAGE_RESIZE,
	RENDER_TYPE_IMAGE_FRAME,
	RENDER_TYPE_IMAGE_LOOP,
	RENDER_TYPE_IMAGE_ALPHA,
	RENDER_TYPE_IMAGE_ALPHA_RESIZE,
	RENDER_TYPE_IMAGE_ALPHA_FRAME,
	RENDER_TYPE_IMAGE_ANIMATION,
	//RENDER_TYPE_IMAGE_EFFECT,


};


enum ZORDER
{
	ZORDER_BACKGROUND,
	ZORDER_ENEMY,
	ZORDER_BOSS,
	ZORDER_PLAYER,
	ZORDER_BACKGROUND2,
	ZORDER_INTERFACE,

	ZORDER_MAX
};



struct tagRenderInfo
{
	RENDER_TYPE renderType;
	HDC hdc;					//HDC
	image* img;					//Image
	wstring strKey;				//Image이름
	int destX;					//DC 좌표 Left
	int destY;					//DC 좌표 Top
	int sourWidth;				//resize width
	int sourHeight;				//resize height
	
	int curFrameX;				//frameX
	int curFrameY;				//frameY

	LPRECT drawArea;			//LoopRender
	int offsetX;				//LoopRender
	int offsetY;				//LoopRender

	BYTE alpha;					//alpha
	
	animation* ani;				//animation
	effect* effect;				//effect

	LPRECT rcRect;				//Rect
	TCHAR* strText;				//Text
};


class RenderManager : public singletonBase<RenderManager>
{
private:
	typedef vector<tagRenderInfo> vRenderList;
	typedef vector<tagRenderInfo>::iterator viRenderList;

	vRenderList _vRenderList[ZORDER_MAX];


public:
	RenderManager();
	~RenderManager();

	HRESULT init();
	void release();


	//image
	void insertImg(ZORDER zorder, image* img, HDC hdc, int destX, int destY);
	void insertImg(ZORDER zorder, image* img, HDC hdc, int destX, int destY, int sourWidth, int sourHeight);
	void insertImgFrame(ZORDER zorder, image* img, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void insertImgLoop(ZORDER zorder, image* img, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void insertImgAlpha(ZORDER zorder, image* img, HDC hdc, int destX, int destY, BYTE alpha);
	void insertImgAlpha(ZORDER zorder, image* img, HDC hdc, int destX, int destY, int sourWidth, int sourHeight, BYTE alpha);
	void insertImgAlphaFrame(ZORDER zorder, image* img, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void insertImgAni(ZORDER zorder, image* img, HDC hdc, int destX, int destY, animation* ani);


	//image strkey
	//void insertImg(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY);
	//void insertImg(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//void insertImgFrame(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	//void insertImgLoop(ZORDER zorder, wstring strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	//void insertImgAlpha(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, BYTE alpha);
	//void insertImgAlpha(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	//void insertImgAlphaFrame(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	//void insertImgAni(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, animation* ani);



	void render(void); //실제로 뿌려주는 함수

};

