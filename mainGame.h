#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	bool		_stop;
	POINT		_winsize;
	float		_FPS;

private:
	void initScene(void);
	void checkWindowSize(void);
	void controlFPS(void);


public:
	mainGame();
	~mainGame();

	virtual HRESULT init(void);				//초기화
	virtual void release(void);				//메모리 해제
	virtual void update(void);				//연산관련(타이머)
	virtual void render(void);				//그려주는 함수
	virtual void getChar(WPARAM wParam);	//키보드 입력

	void setWindowResize(POINT size);

public:
	inline bool getStop(void) { return _stop; }
	inline void setStop(bool stop) { _stop = stop; }
	inline POINT getWinSize(void) { return _winsize; }
	inline float getFPS(void) { return _FPS; }

};

