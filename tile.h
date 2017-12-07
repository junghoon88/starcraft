#pragma once
#include "gameNode.h"

class tile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//F = G + H
	// F == �� ��� 
	// G == ���������κ��� ���� ���(Ÿ��) ������ ��κ��
	// H == ���� ���(Ÿ��)���� ������������ ��κ��

	int _totalCost;		//F

	bool _isOpen;
	bool _isFind;


	wstring _attribute;



public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	HRESULT init(int idX, int idY, RECT rc);
	void release();
	void update();
	void render();

	int getIdX(void) { return _idX; }
	int getIdY(void) { return _idY; }

	RECT getRect() { return _rc; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(wstring str) { _attribute = str; }
	wstring getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }

	inline void setIsFind(bool isFind) { _isFind = isFind; }
	inline bool getIsFind(void) { return _isFind; }
};

