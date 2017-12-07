#include "stdafx.h"
#include "RenderManager.h"


RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

HRESULT RenderManager::init()
{

	return S_OK;
}
void RenderManager::release()
{
	for (int i = 0; i < ZORDER_MAX; i++)
	{
		_vRenderList[i].clear();
	}
}


void RenderManager::insertImg(ZORDER zorder, image* img, HDC hdc, int destX, int destY)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_NORMAL;
	info.img = img;
	info.hdc = hdc;
	info.destX = destX;
	info.destY = destY;

	_vRenderList[zorder].push_back(info);
}

void RenderManager::insertImg(ZORDER zorder, image* img, HDC hdc, int destX, int destY, int sourWidth, int sourHeight)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_RESIZE;
	info.img = img;
	info.hdc = hdc;
	info.destX = destX;
	info.destY = destY;
	info.sourWidth = sourWidth;
	info.sourHeight = sourHeight;

	_vRenderList[zorder].push_back(info);
}

void RenderManager::insertImgFrame(ZORDER zorder, image* img, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_FRAME;
	info.img = img;
	info.hdc = hdc;
	info.destX = destX;
	info.destY = destY;
	info.curFrameX = currentFrameX;
	info.curFrameY = currentFrameY;

	_vRenderList[zorder].push_back(info);
}

void RenderManager::insertImgLoop(ZORDER zorder, image* img, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_LOOP;
	info.img = img;
	info.hdc = hdc;
	info.drawArea = drawArea;
	info.offsetX = offsetX;
	info.offsetY = offsetY;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAlpha(ZORDER zorder, image* img, HDC hdc, int destX, int destY, BYTE alpha)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA;
	info.img = img;
	info.hdc = hdc;
	info.destX = destX;
	info.destY = destY;
	info.alpha = alpha;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAlpha(ZORDER zorder, image* img, HDC hdc, int destX, int destY, int sourWidth, int sourHeight, BYTE alpha)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA_RESIZE;
	info.img = img;
	info.hdc = hdc;
	info.destX = destX;
	info.destY = destY;
	info.sourWidth = sourWidth;
	info.sourHeight = sourHeight;
	info.alpha = alpha;

	_vRenderList[zorder].push_back(info);

}
void RenderManager::insertImgAlphaFrame(ZORDER zorder, image* img, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA_FRAME;
	info.img = img;
	info.hdc = hdc;
	info.destX = destX;
	info.destY = destY;
	info.curFrameX = currentFrameX;
	info.curFrameY = currentFrameY;
	info.alpha = alpha;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAni(ZORDER zorder, image* img, HDC hdc, int destX, int destY, animation* ani)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ANIMATION;
	info.img = img;
	info.hdc = hdc;
	info.destX = destX;
	info.destY = destY;
	info.ani = ani;

	_vRenderList[zorder].push_back(info);
}



#if 0
void RenderManager::insertImg(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_NORMAL;
	info.strKey = strKey;
	info.hdc = hdc;
	info.destX = destX;
	info.destY = destY;

	_vRenderList[zorder].push_back(info);
}

void RenderManager::insertImg(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{

}

void RenderManager::insertImgFrame(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{

}

void RenderManager::insertImgLoop(ZORDER zorder, wstring strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{

}

void RenderManager::insertImgAlpha(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, BYTE alpha)
{

}

void RenderManager::insertImgAlpha(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{

}

void RenderManager::insertImgAlphaFrame(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{

}

void RenderManager::insertImgAni(ZORDER zorder, wstring strKey, HDC hdc, int destX, int destY, animation* ani)
{

}
#endif




void RenderManager::render()
{
	for (int i = 0; i < ZORDER_MAX; i++)
	{
		for (int j = 0; j < _vRenderList[i].size(); j++)
		{
			tagRenderInfo* info = &_vRenderList[i][j];
			
			switch (info->renderType)
			{
			case RENDER_TYPE_RECT:
				//Rectangle(info->hdc, info->rcRect->left, info->rcRect->top, info->rcRect->right, info->rcRect->bottom);
				break;
			case RENDER_TYPE_TEXT:
				//TextOut(info->hdc, info);
				break;
			case RENDER_TYPE_IMAGE_NORMAL:
				if(info && info->img)	info->img->render(info->hdc, info->destX, info->destY);
				break;
			case RENDER_TYPE_IMAGE_RESIZE:
				if (info && info->img)	info->img->render(info->hdc, info->destX, info->destY, 0, 0, info->sourWidth, info->sourHeight);
				break;
			case RENDER_TYPE_IMAGE_FRAME:
				if (info && info->img)	info->img->frameRender(info->hdc, info->destX, info->destY, info->curFrameX, info->curFrameY);
				break;
			case RENDER_TYPE_IMAGE_LOOP:
				if (info && info->img)	info->img->loopRender(info->hdc, info->drawArea, info->offsetX, info->offsetY);
				break;
			case RENDER_TYPE_IMAGE_ALPHA:
				if (info && info->img)	info->img->alphaRender(info->hdc, info->destX, info->destY, info->alpha);
				break;
			case RENDER_TYPE_IMAGE_ALPHA_RESIZE:
				if (info && info->img)	info->img->alphaRender(info->hdc, info->destX, info->destY, 0, 0, info->sourWidth, info->sourHeight, info->alpha);
				break;
			case RENDER_TYPE_IMAGE_ALPHA_FRAME:
				if (info && info->img)	info->img->alphaFrameRender(info->hdc, info->destX, info->destY, info->alpha);
				break;
			case RENDER_TYPE_IMAGE_ANIMATION:
				if (info && info->img)	info->img->aniRender(info->hdc, info->destX, info->destY, info->ani);
				break;
			}

			info = NULL;
		}
		_vRenderList[i].clear();
	}
}
