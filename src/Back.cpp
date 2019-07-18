#include "Back.h"


CBack::CBack(void)
{
	m_hBmpBackDown = 0;   //  ����ͼƬ
	m_hBmpBackUp = 0;
	x = 0;
	y = 0;
}


CBack::~CBack(void)
{
	::DeleteObject(m_hBmpBackDown);   // ɾ��ͼƬ
	::DeleteObject(m_hBmpBackUp);
	m_hBmpBackDown = 0;   //  ����ͼƬ
	m_hBmpBackUp = 0;
}
void CBack::BackInit(HINSTANCE hIns)
{
	//  ����λͼ
	m_hBmpBackUp = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACK));
	m_hBmpBackDown = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACK)); 
}
void CBack::BackMove()
{
	if(y == 550)
		y = 0;
	else
		y++;
}
void CBack::BackShow(HDC hMemDC)
{
	//  ����һ��������DC
	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	//  ѡ��һ��λͼ
	::SelectObject(hTempDC,m_hBmpBackUp);
	//  ����λͼ
	::BitBlt(hMemDC,x,y-550,380,550,hTempDC,0,0,SRCCOPY);
	//  ѡ��һ��λͼ
	::SelectObject(hTempDC,m_hBmpBackDown);
	//  ����λͼ
	::BitBlt(hMemDC,x,y,380,550,hTempDC,0,0,SRCCOPY);
	//  ɾ��DC
	::DeleteDC(hTempDC);
}