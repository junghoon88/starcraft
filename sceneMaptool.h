#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"

enum BTNCTRL
{
	BTNCTRL_SAVE,
	BTNCTRL_LOAD,

	BTNCTRL_MAX
};

class sceneMaptool : public gameNode
{
private:
	//Ÿ��
	tagTile _tiles[TILEX][TILEY];				//Ÿ��
	image*	_imgTiles[TILEX][TILEY];			//Ÿ�� �̹���
	BOOL	_isChangedTile[TILEX][TILEY];		//Ÿ�� ���� ���� ����

	//ISOŸ��
	//tagisoTile _isoTile[ISOTILEX][ISOTILEY];	//X : ���ʾƷ���, Y:�����ʾƷ���
	POINT _isoCursor;


	//��ư
	button* _btnCtrl[BTNCTRL_MAX];

public:
	sceneMaptool();
	~sceneMaptool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);


private:
	void initButtons(void);
	void initTiles(void);
	void initIsoTiles(void);

	void clickIsoTile(void);

	void updateTileImage(void);
	void setTileImageAll(void);


	void saveData(void);
	void loadData(void);

	void renderTiles(void);

private:
	//button callbackFunction
	static void cbButtonSave(void* obj);
	static void cbButtonLoad(void* obj);

};

