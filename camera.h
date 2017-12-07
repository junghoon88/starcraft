#pragma once
#include "singletonBase.h"
#include "globalMacroVariables.h"

class camera : public singletonBase<camera>
{
private:
	int _cameraX;
	int _cameraY;

	int _targetX;
	int _targetY;

	int _minX;
	int _minY;
	int _maxX;
	int _maxY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void moveCamera(DIRECTION dir);
	void earthquake(float power);

	//getter, setter
	inline int getCameraX(void) { return _cameraX; }
	inline int getCameraY(void) { return _cameraY; }
	inline void setCameraPos(int x, int y) { _cameraX = x; _cameraY = y; }
	inline void setCameraX(int x) { _cameraX = x; }
	inline void setCameraY(int y) { _cameraY = y; }
	inline void setTargetPos(int x, int y) { _targetX = x; _targetY = y; }
	inline void setTargetX(int x) { _targetX = x; }
	inline void setTargetY(int y) { _targetY = y; }

	inline void setMinMax(int minX, int minY, int maxX, int maxY) { _minX = minX; _minY = minY; _maxX = maxX; _maxY = maxY; }
	inline void setMin(int x, int y) { _minX = x; _minY = y; }
	inline void setMax(int x, int y) { _maxX = x; _maxY = y; }
	inline int getMinX(void) { return _minX; }
	inline int getMinY(void) { return _minY; }
	inline int getMaxX(void) { return _maxX; }
	inline int getMaxY(void) { return _maxY; }



	camera();
	~camera();
};

