#include "PlaneApp.h"
IMPLEMENT(CPlaneApp)
CPlaneApp::CPlaneApp(void)
{
	dc = 0;
	hMemDC = 0;
	hBitmap = 0;
}

CPlaneApp::~CPlaneApp(void)
{
		::DeleteObject(hBitmap);
        ::DeleteDC(hMemDC);
		::ReleaseDC(m_hMainWnd,dc);

		//ɾ���ڵ�
		list<CGunner*>::iterator it = m_lstGunner.begin();
		while(it != m_lstGunner.end())
			{
				delete *it;
				it++;
		}
		//ɾ�����е��˷ɻ�
		list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
		while(ite != m_lstFoePlane.end())
		   {
				delete *ite;
				ite++;
		}

		list<CFoePlane*>::iterator iter = m_lstBlastFoePlane.begin();
		while(iter != m_lstBlastFoePlane.end())
		   {
				delete *iter;
				iter++;
		}
}

void CPlaneApp::OnCreateGame()   // WM_CREATE
	{

		//0.������Դ
		dc = ::GetDC(m_hMainWnd);//��ȡ����DC
		hMemDC = ::CreateCompatibleDC(dc);// ����һ��������DC
		hBitmap = ::CreateCompatibleBitmap(dc,380,550);//����λͼ
		::SelectObject(hMemDC,hBitmap); 

		//1.��ʼ������
		back.BackInit(m_hIns);

		//2.��ʼ����ҷɻ�
		plane.PlayerPlaneInit(m_hIns);

		//3.������ʱ��
		::SetTimer(m_hMainWnd,BACK_MOVE_TIME_ID,25,NULL);
		::SetTimer(m_hMainWnd,KEY_STATE_TIME_ID,1,NULL);//�����̵�״̬
		::SetTimer(m_hMainWnd,SEND_GUNNER_TIME_ID,100,NULL);
		::SetTimer(m_hMainWnd,GUNNER_MOVE_TIME_ID,20,NULL);
		::SetTimer(m_hMainWnd,FOEPLANE_MOVE_TIME_ID,30,NULL);
		::SetTimer(m_hMainWnd,FOEPLANE_CREATE_TIME_ID,400,NULL);
         ::SetTimer(m_hMainWnd,CHANGE_SHOWID_TIME_ID,150,NULL);
	}
void CPlaneApp::OnGameDraw()     // WM_PAINT
	{
		
		back.BackShow(hMemDC);
		plane.PlayerPlaneShow(hMemDC);
		this->AllGunnerShow(hMemDC); 
		this->AllFoePlaneShow(hMemDC);
		this->AllBlastFoePlaneShow(hMemDC);
		::BitBlt(dc,0,0,380,550,hMemDC,0,0,SRCCOPY);

}

void CPlaneApp::OnGameRun(WPARAM nTimerID)      // WM_TIMER
{
	if(nTimerID == KEY_STATE_TIME_ID)
	{
		if(::GetAsyncKeyState(VK_LEFT))
		plane.PlayerPlaneMove(VK_LEFT);
		if(::GetAsyncKeyState(VK_RIGHT))
		plane.PlayerPlaneMove(VK_RIGHT);
		if(::GetAsyncKeyState(VK_UP))
		plane.PlayerPlaneMove(VK_UP);		
		if(::GetAsyncKeyState(VK_DOWN))
		plane.PlayerPlaneMove(VK_DOWN);			
	}
	if(nTimerID == BACK_MOVE_TIME_ID)
	{
		back.BackMove();
	}

	if(nTimerID == SEND_GUNNER_TIME_ID)
	{
		plane.SendGunner(m_lstGunner,m_hIns);
	}

	if(nTimerID == GUNNER_MOVE_TIME_ID)
	{
		this->AllGunnerMove();
		this->GunnerHitFoePlane();
	}

	if(nTimerID == FOEPLANE_MOVE_TIME_ID)
	{
		this->AllFoePaneMove();
		if(this->IsGameOver() == true)
		{
	    ::KillTimer(m_hMainWnd,BACK_MOVE_TIME_ID);
		::KillTimer(m_hMainWnd,KEY_STATE_TIME_ID);//�����̵�״̬
		::KillTimer(m_hMainWnd,SEND_GUNNER_TIME_ID);
		::KillTimer(m_hMainWnd,GUNNER_MOVE_TIME_ID);
		::KillTimer(m_hMainWnd,FOEPLANE_MOVE_TIME_ID);
		::KillTimer(m_hMainWnd,FOEPLANE_CREATE_TIME_ID);
        ::KillTimer(m_hMainWnd,CHANGE_SHOWID_TIME_ID);
		MessageBox(NULL,"��Ϸ����","��ʾ",MB_OK);
		return;
		}
	}

	if(nTimerID == FOEPLANE_CREATE_TIME_ID)
	{
		this->CreateFoePlane();
	}
	if(nTimerID == CHANGE_SHOWID_TIME_ID)
	{
		this->ChangeFoePlaneShowID();
	}
	//�ػ�
	this->OnGameDraw();
  }

void CPlaneApp::OnKeyDown(WPARAM nKey)
	{
		/*plane.PlayerPlaneMove(nKey);
		this->OnGameDraw();*/
	}


void CPlaneApp::AllGunnerMove()
{
		list<CGunner*>::iterator it = m_lstGunner.begin();
		while(it != m_lstGunner.end())
			{ 
				if((*it)->y < 0)
				{
					delete *it;
					it = m_lstGunner.erase(it);
				}else{
				(*it)->GunnerMove();
				it++;
				}
		}
}

void CPlaneApp::AllGunnerShow(HDC hMemDC)
{
		list<CGunner*>::iterator it = m_lstGunner.begin();
		while(it != m_lstGunner.end())
			{
				(*it)->GunnerShow(hMemDC);
				it++;
		}
}

void CPlaneApp::CreateFoePlane()
{
	CFoePlane* foePlane = NULL;
	 int index = rand()%12;
	 if(index >= 0 && index <= 1)
		 foePlane = new CBigFoePlane;
	 if(index >= 2 && index <= 5)
		 foePlane = new CMidFoePlane;
	 if(index >= 6 && index <= 11)
		 foePlane = new CSmallFoePlane;
	 foePlane->FoePlaneInit(m_hIns);
	 m_lstFoePlane.push_back(foePlane);
}

void CPlaneApp::AllFoePaneMove()
{
		list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
		while(ite != m_lstFoePlane.end())
		   {
			   if((*ite)->y > 550)
			   {
				   delete (*ite);
				   ite = m_lstFoePlane.erase(ite);
			   }else{
			   (*ite)->FoePlaneMove();
				ite++;
			   }
		}
}

void CPlaneApp::AllFoePlaneShow(HDC hMemDC)
{
		list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
		while(ite != m_lstFoePlane.end())
		   {
			   (*ite)->FoePlaneShow(hMemDC);
				ite++;
		}
}

void CPlaneApp::GunnerHitFoePlane()
{
	bool bflag = false;    //  ��� �Ƿ�ɾ���ڵ�

	//  �������е��ڵ�
	list<CGunner*>::iterator iteGunner = m_lstGunner.begin();
	while(iteGunner != m_lstGunner.end())
	{
		//-------------------------------------------------------
		//  �������еĵ��˷ɻ�
		list<CFoePlane*>::iterator iteFoePlane = m_lstFoePlane.begin();
		while(iteFoePlane != m_lstFoePlane.end())
		{
			//-----------------------------------------------------------
			// ��iteGunner  ����ڵ�  �� iteFoePlane ������˷ɻ��Ƚ�
			if( (*iteFoePlane)->IsGunnerHitFoePlane(*iteGunner) == true )
			{
				bflag = true;
				//  ɾ���ڵ�������ڵ��ڵ�
				delete (*iteGunner);
				iteGunner = m_lstGunner.erase(iteGunner);
				//  ���˷ɵ�Ѫ
				(*iteFoePlane)->DownBlood();
				//  �жϵ��˷ɻ��Ƿ�ը
				if((*iteFoePlane)->IsBoom() == true)
				{
					// ��ը�� �ŵ���һ��������  �л���ը��Ч��
					m_lstBlastFoePlane.splice(m_lstBlastFoePlane.end(),m_lstFoePlane,iteFoePlane);
				}
				break;
			}
			//-----------------------------------------------------------
			++iteFoePlane;
		}
		//-------------------------------------------------------
		if(bflag == false)
			++iteGunner;
		else
			bflag = false;
	}
}

void CPlaneApp::AllBlastFoePlaneShow(HDC hMemDC)
{
		list<CFoePlane*>::iterator iter = m_lstBlastFoePlane.begin();
		while(iter != m_lstBlastFoePlane.end())
		   {
			   (*iter)->FoePlaneShow(hMemDC);
				iter++;
		}
}
void CPlaneApp::ChangeFoePlaneShowID()
{
	  list<CFoePlane*>::iterator iter = m_lstBlastFoePlane.begin();
		while(iter != m_lstBlastFoePlane.end())
		   {
			   if((*iter)->m_nShowID == 0)
			   {
				   delete (*iter);
				   iter = m_lstBlastFoePlane.erase(iter);
			   }else{
				 (*iter)->m_nShowID--;
				iter++;

			   }
		}
}

bool CPlaneApp::IsGameOver()
{
		list<CFoePlane*>::iterator ite = m_lstFoePlane.begin();
		while(ite != m_lstFoePlane.end())
		   {
			   if((*ite)->IsHitPlayerPlane(plane) == true)
				   return true;
			   ++ite;
		}
		return false;
}
