#include "FoePlane.h"


CFoePlane::CFoePlane(void)
{
	m_hBmpFoePlane = 0;   //  λͼ
	m_nBlood = 0;    //  Ѫ��
	m_nShowID = 0;     //  ��ʾ����һ��ͼƬ
	x = 0;        //  λ�� 
	y = 0;
}


CFoePlane::~CFoePlane(void)
{
	::DeleteObject(m_hBmpFoePlane);
	 m_hBmpFoePlane = 0;
}
