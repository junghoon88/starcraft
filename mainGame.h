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

	virtual HRESULT init(void);				//�ʱ�ȭ
	virtual void release(void);				//�޸� ����
	virtual void update(void);				//�������(Ÿ�̸�)
	virtual void render(void);				//�׷��ִ� �Լ�
	virtual void getChar(WPARAM wParam);	//Ű���� �Է�

	void setWindowResize(POINT size);

public:
	inline bool getStop(void) { return _stop; }
	inline void setStop(bool stop) { _stop = stop; }
	inline POINT getWinSize(void) { return _winsize; }
	inline float getFPS(void) { return _FPS; }

};

