#pragma once
class nrGas
{
	RECT	_rcTile;
	RECT	_rcBody;

	UINT	_amount;

	image*	_img;

public:
	nrGas(int tilex, int tiley, UINT amount);
	~nrGas();

public:
	inline RECT	getRectTile(void) { return _rcTile; }
	inline RECT	getRectBody(void) { return _rcBody; }
	inline UINT	getAmount(void) { return _amount; }
	inline image* getImage(void) { return _img; }

};

