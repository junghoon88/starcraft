#pragma once
#include "gameNode.h"
#include "loading.h"

class sceneLoading : public gameNode
{
private:
	loading* _loading;

public:
	sceneLoading();
	~sceneLoading();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

