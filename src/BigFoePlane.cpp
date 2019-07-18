#include "BigFoePlane.h"


CBigFoePlane::CBigFoePlane(void)
{
	m_hBmpFoePlane = 0;    //  λͼ
	m_nBlood = 5;         //  Ѫ��
	m_nShowID = 3;         //  ��ʾ����һ��ͼƬ
	x = rand()%(380-108);        //  λ�� 
	y = -128;
}


CBigFoePlane::~CBigFoePlane(void)
{
}

bool CBigFoePlane::IsHitPlayerPlane(CPlayerPlane& plane)
{
	//  ѡȡ��ҷɻ���  3����   �͵��˷ɻ��ľ����ж�
	//  x+30,y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+108
		&& plane.y >= this->y && plane.y <= this->y+128)
	{
		return true;
	}
	//  x,y+50
	if(plane.x >= this->x && plane.x <= this->x+108
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+128)
	{
		return true;
	}
	//  x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+108
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+128)
	{
		return true;
	}
	return false;
}
bool CBigFoePlane::IsGunnerHitFoePlane(CGunner* pGunner)
{
	//  ���ڵ�������  �ж�  �Ƿ��ڵ��˷ɻ��ľ��ο�ķ�Χ
	if(pGunner->x >= this->x && pGunner->x <= this->x+108 
		&& pGunner->y >= this->y && pGunner->y <= this->y+128 )
	{
		return true;
	}
	return false;
}
void CBigFoePlane::FoePlaneInit(HINSTANCE hIns)
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BIG));
}
void CBigFoePlane::FoePlaneMove()
{
	y+=2;
}
void CBigFoePlane::FoePlaneShow(HDC hMemDC)
{
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempDC,m_hBmpFoePlane);
	::BitBlt(hMemDC,x,y,108,128,hTempDC,0,(3-m_nShowID)*128,SRCAND);
	::DeleteDC(hTempDC);
}