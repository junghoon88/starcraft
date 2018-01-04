#pragma once
#include "singletonBase.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//17. 09. 29. jhkim
//Z-Order 변수를 추가해서 벡터에 추가한 후에, mainGame 에서 한번에 랜더를 뿌려줌 
////////////////////////////////////////////////////////////////////////////////////////////////
enum RENDER_TYPE
{
	RENDER_TYPE_RECT,
	RENDER_TYPE_LINERECT,
	RENDER_TYPE_ELLIPSE,
	RENDER_TYPE_TEXT,
	RENDER_TYPE_TEXTCENTER,

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
	ZORDER_TILES,
	ZORDER_GAMEOBJECT,
	ZORDER_GAMEOBJECTAIR,
	ZORDER_GAMEMOUSEDRAG,

	ZORDER_GAMEDEBUG1,

	ZORDER_INTERFACE,
	ZORDER_INTERFACE2,
	ZORDER_MOUSECURSOR,

	ZORDER_MAX
};



struct tagRenderInfo
{
	RENDER_TYPE renderType;
//	HDC hdc;					//HDC
	image* img;					//Image
//	wstring strKey;				//Image이름
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

	//Z-Order 에 처리할 Rect 추가(실제보여주는 이미지와 trans되서 안보이는 영역의 차이가 있을 수 있기 때문에 만든다)
	RECT	rcShow;
	PENVERSION penVersion;
};

struct tagTextRenderInfo
{
	RENDER_TYPE renderType;

	TCHAR strText[128];				//Text
	COLORREF colorText;			//TextColor
	FONTVERSION fontVersion;

	//Z-Order 에 처리할 Rect 추가(실제보여주는 이미지와 trans되서 안보이는 영역의 차이가 있을 수 있기 때문에 만든다)
	RECT	rcShow;
};


class RenderManager : public singletonBase<RenderManager>
{
private:
	typedef vector<tagRenderInfo> vRenderList;
	typedef vector<tagRenderInfo>::iterator viRenderList;
	typedef vector<tagTextRenderInfo> vTextRenderList;
	typedef vector<tagTextRenderInfo>::iterator viTextRenderList;

	vRenderList _vRenderList[ZORDER_MAX];
	vTextRenderList _vTextRenderList[ZORDER_MAX];


public:
	RenderManager();
	~RenderManager();

	HRESULT init();
	void release();

	//rectangle, ellipse, text etc..
	void insertRectangle(ZORDER zorder, RECT rc, PENVERSION penVersion);
	void insertLineRectangle(ZORDER zorder, RECT rc, PENVERSION penVersion);
	void insertEllipse(ZORDER zorder, RECT rc, PENVERSION penVersion);
	void insertText(ZORDER zorder, RECT rc, TCHAR* text, COLORREF color = RGB(0, 0, 0));
	void insertTextCenter(ZORDER zorder, RECT rc, TCHAR* text, COLORREF color = RGB(0, 0, 0));
	//void insertTextCenter(ZORDER zorder, RECT rc, TCHAR* text, FONTVERSION fontVersion, COLORREF color = RGB(0, 0, 0));

	//image
	void insertImg(ZORDER zorder, image* img, int destX, int destY);
	void insertImg(ZORDER zorder, image* img, int destX, int destY, int sourWidth, int sourHeight);
	void insertImgCT(ZORDER zorder, image* img, int cx, int cy);

	void insertImgFrame(ZORDER zorder, image* img, int destX, int destY, int currentFrameX, int currentFrameY);
	void insertImgFrameLC(ZORDER zorder, image* img, int left,  int cy,		int currentFrameX, int currentFrameY);
	void insertImgFrameLB(ZORDER zorder, image* img, int left,  int bottom, int currentFrameX, int currentFrameY);

	void insertImgFrameCT(ZORDER zorder, image* img, int cx,    int top,	int currentFrameX, int currentFrameY);
	void insertImgFrameCC(ZORDER zorder, image* img, int cx,    int cy,     int currentFrameX, int currentFrameY);
	void insertImgFrameCB(ZORDER zorder, image* img, int cx,    int bottom, int currentFrameX, int currentFrameY);

	void insertImgFrameRT(ZORDER zorder, image* img, int right, int top,    int currentFrameX, int currentFrameY);
	void insertImgFrameRC(ZORDER zorder, image* img, int right, int cy,     int currentFrameX, int currentFrameY);
	void insertImgFrameRB(ZORDER zorder, image* img, int right, int bottom, int currentFrameX, int currentFrameY);

	void insertImgLoop(ZORDER zorder, image* img, const LPRECT drawArea, int offsetX, int offsetY);
	void insertImgAlpha(ZORDER zorder, image* img, int destX, int destY, BYTE alpha);
	void insertImgAlpha(ZORDER zorder, image* img, int destX, int destY, int sourWidth, int sourHeight, BYTE alpha);
	void insertImgAlphaFrame(ZORDER zorder, image* img, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void insertImgAni(ZORDER zorder, image* img, int destX, int destY, animation* ani);


	//image strkey
	void insertImg(ZORDER zorder, image* img, int destX, int destY, RECT rcShow);
	void insertImg(ZORDER zorder, image* img, int destX, int destY, int sourWidth, int sourHeight, RECT rcShow);
	void insertImgFrame(ZORDER zorder, image* img, int destX, int destY, int currentFrameX, int currentFrameY, RECT rcShow);
	void insertImgLoop(ZORDER zorder, image* img, const LPRECT drawArea, int offsetX, int offsetY, RECT rcShow);
	void insertImgAlpha(ZORDER zorder, image* img, int destX, int destY, BYTE alpha, RECT rcShow);
	void insertImgAlpha(ZORDER zorder, image* img, int destX, int destY, int sourWidth, int sourHeight, BYTE alpha, RECT rcShow);
	void insertImgAlphaFrame(ZORDER zorder, image* img, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha, RECT rcShow);
	void insertImgAni(ZORDER zorder, image* img, int destX, int destY, animation* ani, RECT rcShow);

	static int funcCompare(const void* first, const void* second);
	void sort(void);

	void render(HDC hdc); //실제로 뿌려주는 함수


};

