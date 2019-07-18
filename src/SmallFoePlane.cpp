#include "SmallFoePlane.h"

CSmallFoePlane::CSmallFoePlane(void)
{
	m_hBmpFoePlane = 0;    //  λͼ
	m_nBlood = 1;         //  Ѫ��
	m_nShowID = 1;         //  ��ʾ����һ��ͼƬ
	x = rand()%(380-34);        //  λ�� 
	y = -28;
}


CSmallFoePlane::~CSmallFoePlane(void)
{
}

bool CSmallFoePlane::IsHitPlayerPlane(CPlayerPlane& plane)
{
	//  ѡȡ��ҷɻ���  3����   �͵��˷ɻ��ľ����ж�
	//  x+30,y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+34
		&& plane.y >= this->y && plane.y <= this->y+28)
	{
		return true;
	}
	//  x,y+50
	if(plane.x >= this->x && plane.x <= this->x+34
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+28)
	{
		return true;
	}
	//  x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+34
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+28)
	{
		return true;
	}
	return false;
}
bool CSmallFoePlane::IsGunnerHitFoePlane(CGunner* pGunner)
{
	//  ���ڵ�������  �ж�  �Ƿ��ڵ��˷ɻ��ľ��ο�ķ�Χ
	if(pGunner->x >= this->x && pGunner->x <= this->x+34 
		&& pGunner->y >= this->y && pGunner->y <= this->y+28 )
	{
		return true;
	}
	return false;
}
void CSmallFoePlane::FoePlaneInit(HINSTANCE hIns)
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SMALL));
}
void CSmallFoePlane::FoePlaneMove()
{
	y+=6;
}
void CSmallFoePlane::FoePlaneShow(HDC hMemDC)
{
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempDC,m_hBmpFoePlane);
	::BitBlt(hMemDC,x,y,34,28,hTempDC,0,(1-m_nShowID)*28,SRCAND);
	::DeleteDC(hTempDC); 
} 