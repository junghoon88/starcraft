#pragma once
//-------------------------------------------------------
//2017.09.20. jhkim
//Magenta Background Manager
//��濡 ����Ÿ�� �߰��� �Է��� �� �ֵ��� �� (��Ʈ�������� ���)
//-------------------------------------------------------

#include "gameNode.h"

enum EXPLOSION_TYPE
{
	EXPOLISION_TYPE_ELLIPSE,		//��
	EXPOLISION_TYPE_RECTANGLE,		//�簢��


};

struct tagExplosion
{
	EXPLOSION_TYPE type;	// ���� ����
	POINT pt;				// ���� ��ġ
	float width;			// ���� �ݰ�(����)
	float height;			// ���� �ݰ�(����)
	float angleDeg;			// ���� ���� ����(�����϶� ���)
	float speed;			// ���� ���� ���ǵ�(�����϶� ���)

	int explosionCnt;		// ���� ȸ��
	int explosionCntMax;	// �ִ� ���� ȸ��
	int explosionTime;		// ���� ���� �ð�(ms)
	int explosionTimeCnt;	// ���� ���� �ð� ���� ī����
	int explosionDamping;	// ���� �����ϸ鼭 ���� �ݰ� �پ��� ���� (%)
	bool isExplosioned;		// ���� �ߴ��� 
};

struct tagTrace
{
	EXPLOSION_TYPE type;
	RECT rc;
};

class MBGManager : public gameNode
{
private:
	image* _imgBG;			//��׶��� �̹���
	HDC _hdcImg;			//��׶��� �̹��� DC
	
	vector<tagExplosion> _vExplosion;
	vector<tagExplosion>::iterator _viExplosion;

	vector<tagTrace> _vRCTrace;	// �����ϰ� ���� ����(����Ÿ �׸� �κ�)
	vector<tagTrace>::iterator _viRCTrace;


	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

private:
	void PlayExplosion(tagExplosion* ex);

public:
	virtual HRESULT init(wstring strImgName);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setExplosion(tagExplosion ex);
	
	bool getisExplosion(void);


	MBGManager();
	~MBGManager();
};

