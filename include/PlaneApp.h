#pragma once
#include "cgamectrl.h"
#include "Back.h"
#include "PlayerPlane.h"
#include "Gunner.h"
#include "FoePlane.h"
#include "SmallFoePlane.h"
#include "BigFoePlane.h"
#include "MidFoePlane.h" //�´�����ɾ�����нڵ�ɻ�
class CPlaneApp :
	public CGameCtrl
{
public:
	virtual void OnCreateGame();   // WM_CREATE
	virtual void OnGameDraw();     // WM_PAINT
	virtual void OnGameRun(WPARAM nTimerID);      // WM_TIMER
	virtual void OnKeyDown(WPARAM nKey);

public:
	CBack back;
	CPlayerPlane plane;
	list<CGunner*> m_lstGunner; //װ�ڵ�������
	list<CFoePlane*> m_lstFoePlane;
	list<CFoePlane*> m_lstBlastFoePlane;
public:
	void AllGunnerMove();
	void AllGunnerShow(HDC hMemDC);
	void CreateFoePlane();
	void AllFoePaneMove();
	void AllFoePlaneShow(HDC hMemDC);
	void GunnerHitFoePlane();
	void AllBlastFoePlaneShow(HDC hMemDC);
	void ChangeFoePlaneShowID();
	bool IsGameOver();

public:
	HDC dc;
	HDC hMemDC;
	HBITMAP hBitmap;
public:
	DECLARE()
public:
	CPlaneApp(void);
	~CPlaneApp(void);
};

