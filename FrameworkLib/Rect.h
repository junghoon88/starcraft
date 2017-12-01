#pragma once

class Rect
{
private:
	LPDIRECT3DDEVICE9 _device;
	LPD3DXLINE _line;
	DWORD _lineColor;
	D3DXVECTOR3 _lineVector[5];

	D3DXVECTOR2 _coord;
	D3DXVECTOR2 _size;
	D3DXVECTOR2 _scale;
	float _angleDeg;
	D3DXVECTOR2 _center;

	D3DXMATRIX _world;

	void AdjustTransform();


public:
	Rect(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, D3DXVECTOR2 size, DWORD color = 0xFF000000);
	~Rect();

	void init();
	void release();
	void update();
	void render(bool cameraOffset = true);

	//getter, setter
	RECT getRect();
	inline D3DXVECTOR2 getCoord() { return _coord; }
	inline DWORD getcolor() { return _lineColor; }
	inline D3DXVECTOR2 getCenter(void) { return _center; }
	inline float getAngle(void) { return _angleDeg; }

	void setCoord(D3DXVECTOR2 coord);
	void setSize(D3DXVECTOR2 size);
	void setScale(const D3DXVECTOR2* scale);
	void setRotate(float angleDeg);
	void setCenterPer(D3DXVECTOR2 centerPer); //size 기준 배율로
	void setCenterPos(D3DXVECTOR2 centerPos); //position
	inline void setColor(DWORD color) { _lineColor = color; }
	void move(float moveX, float moveY);
	

};


