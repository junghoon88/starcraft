#pragma once
#include "gameNode.h"

class hotkeys : public gameNode
{
private:
	TCHAR		_hotkey[COMMAND_NUM];

public:
	hotkeys();
	~hotkeys();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	inline TCHAR getHotkey(COMMAND cmd) { return _hotkey[cmd]; }

};

