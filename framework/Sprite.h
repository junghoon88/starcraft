#pragma once
#include "animation.h"

class Texture;
class Sprite
{
private:
	LPDIRECT3DDEVICE9 _device;
	LPD3DXSPRITE _sprite;
	Texture* _texture;

	D3DXVECTOR2 _coord;		  //��ǥ
	D3DXVECTOR2 _size;		  //���������� �� ������
	D3DXVECTOR2 _scale;		  //������(�⺻���� ���)
	D3DXVECTOR2 _center;	  //ȸ����
	float _angleDeg;		  //����(Degree)
	D3DXVECTOR2 _scaleOffset; //�������� -������ ������ �ɶ� �ɼ�����

	D3DXMATRIX _world;


	bool _bCameraOffset;

	bool AdjustTransform();

public:
	Sprite(LPDIRECT3DDEVICE9 device,
		D3DXVECTOR2 coord = D3DXVECTOR2(0, 0),
		D3DXVECTOR2 size = D3DXVECTOR2(0, 0),
		D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	~Sprite();

	void init(Texture* texture, bool bCameraOffset = true);
	void release();
	void update();
	void render(BYTE alpha = 255);
	void frameRender(int frameX, int frameY, BYTE alpha = 255);
	void aniRender(animation* ani, BYTE alpha = 255);


	void move(float moveX, float moveY);


	//getter, setter
	inline D3DXVECTOR2 getCoord(void) { return _coord; }
	inline D3DXVECTOR2 getSize(void) { return _size; }
	inline D3DXVECTOR2 getScale(void) { return _scale; }
	inline D3DXVECTOR2 getCenter(void) { return _center; }
	inline float getAngle(void) { return _angleDeg; }


	D3DXVECTOR2 getRealSize(void);

	void setCoord(D3DXVECTOR2 coord);
	void setScale(D3DXVECTOR2 scale);
	void setCenterPer(D3DXVECTOR2 centerPer); //size ���� ������
	void setCenterPos(D3DXVECTOR2 centerPos); //position
	void setScaleOffset(D3DXVECTOR2 scaleOffset);

	void setCoord(float coordX, float corrdY);
	void setScale(float scaleX, float scaleY);
	void setCenterPer(float centerPerX, float centerPerY); //size ���� ������
	void setCenterPos(float centerPosX, float centerPosY); //position
	void setRotate(float angleDeg);
	void setScaleOffset(float scaleOffsetX, float scaleOffsetY);

	int getCurFrameX(void);
	int getCurFrameY(void);
	void setCurFrameX(int frameX);
	void setCurFrameY(int frameY);
	int getMaxFrameX(void);
	int getMaxFrameY(void);



	inline Texture* getTexture(void) { return _texture; }


	//int Sprite::getCurFrameX(void) { if (_texture) return _texture->getCurFrameX(); }
	//int Sprite::getCurFrameY(void) { if (_texture) return _texture->getCurFrameY(); }
	//void Sprite::setCurFrameX(int frameX) { if (_texture) _texture->setCurFrameX(frameX); }
	//void Sprite::setCurFrameY(int frameY) { if (_texture) _texture->setCurFrameY(frameY); }
	//int Sprite::getMaxFrameX(void) { if (_texture) return _texture->getMaxFrameX(); }
	//int Sprite::getMaxFrameY(void) { if (_texture) return _texture->getMaxFrameY(); }

};

