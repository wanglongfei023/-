#include "MidFoePlane.h"
CMidFoePlane::CMidFoePlane(void)
{
	m_hBmpFoePlane = 0;    //  λͼ
	m_nBlood = 3;         //  Ѫ��
	m_nShowID = 2;         //  ��ʾ����һ��ͼƬ
	x = rand()%(380-70);        //  λ�� 
	y = -90;
}


CMidFoePlane::~CMidFoePlane(void)
{
}

bool CMidFoePlane::IsHitPlayerPlane(CPlayerPlane& plane)
{
	//  ѡȡ��ҷɻ���  3����   �͵��˷ɻ��ľ����ж�
	//  x+30,y
	if(plane.x+30 >= this->x && plane.x+30 <= this->x+70
		&& plane.y >= this->y && plane.y <= this->y+90)
	{
		return true;
	}
	//  x,y+50
	if(plane.x >= this->x && plane.x <= this->x+70
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+90)
	{
		return true;
	}
	//  x+60,y+50
	if(plane.x+60 >= this->x && plane.x+60 <= this->x+70
		&& plane.y+50 >= this->y && plane.y+50 <= this->y+90)
	{
		return true;
	}
	return false;
}
bool CMidFoePlane::IsGunnerHitFoePlane(CGunner* pGunner)
{
	//  ���ڵ�������  �ж�  �Ƿ��ڵ��˷ɻ��ľ��ο�ķ�Χ
	if(pGunner->x >= this->x && pGunner->x <= this->x+70 
		&& pGunner->y >= this->y && pGunner->y <= this->y+90 )
	{
		return true;
	}
	return false;
}

void CMidFoePlane::FoePlaneInit(HINSTANCE hIns)
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MID));
}

void CMidFoePlane::FoePlaneMove()
{
	y+=4;
}

void CMidFoePlane::FoePlaneShow(HDC hMemDC)
{
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempDC,m_hBmpFoePlane);
	::BitBlt(hMemDC,x,y,70,90,hTempDC,0,(2-m_nShowID)*90,SRCAND);
	::DeleteDC(hTempDC);
}