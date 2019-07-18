#include "Gunner.h"


CGunner::CGunner(void)
{
	m_hBmpGunner = 0;
	x = 0;
	y = 0;
}


CGunner::~CGunner(void)
{
	::DeleteObject(m_hBmpGunner);
	m_hBmpGunner = 0;
}

void CGunner::GunnerInit(HINSTANCE hIns, int x, int y)
{
	//  ��ʼ��λ��
	this->x = x;
	this->y = y;
	m_hBmpGunner = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GUNNER));
}
void CGunner::GunnerMove()
{
	y-=10;   //  �ڵ��ƶ�
}
void CGunner::GunnerShow(HDC hMemDC)
{
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempDC,m_hBmpGunner);
	::BitBlt(hMemDC,x,y,6,9,hTempDC,0,0,SRCAND);
	::DeleteDC(hTempDC);
}