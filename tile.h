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
	// F == 총 비용 
	// G == 시작점으로부터 현재 노드(타일) 까지의 경로비용
	// H == 현재 노드(타일)부터 도착점까지의 경로비용

	float _totalCost;		//F
	float _costFromStart;	//G
	float _costToGoal;		//H

	bool _isOpen;

	tile* _parentNode;


	DWORD _attribute;



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

	void setAttribute(DWORD attr) { _attribute = attr; }
	DWORD getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }
};

typedef vector<tile*> vTile;
typedef vector<tile*>::iterator vTileIter;
