// PlayerToolTopBar.cpp : implementation file
//

#include "stdafx.h"
#include "mplayerc.h"
#include "PlayerToolTopBar.h"


// PlayerToolTopBar.cpp : implementation file
//

#include "stdafx.h"
#include "mplayerc.h"
#include "PlayerToolTopBar.h"
#include "MainFrm.h"

// CPlayerToolTopBar

IMPLEMENT_DYNAMIC(CPlayerToolTopBar, CWnd)

CPlayerToolTopBar::CPlayerToolTopBar():
m_hovering(0),
m_pbtnList(&m_btnList)
{

}

CPlayerToolTopBar::~CPlayerToolTopBar()
{
}


BEGIN_MESSAGE_MAP(CPlayerToolTopBar, CWnd)
	ON_WM_CREATE()
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCPAINT()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnTtnNeedText)
	ON_WM_ENABLE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()



// CPlayerToolTopBar message handlers

BOOL CPlayerToolTopBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message){

	CPoint pt;
	::GetCursorPos (&pt);
	ScreenToClient (&pt);

	if(m_nItemToTrack){	
		SetCursor(cursorHand );
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, 0, 0);
}

BOOL CPlayerToolTopBar::OnTtnNeedText(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	//AfxMessageBox(_T("x")); where is my tooltip!?!
	UNREFERENCED_PARAMETER(id);

	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT_PTR nID = pNMHDR->idFrom;
	BOOL bRet = FALSE;


	// idFrom is actually the HWND of the tool
	CString toolTip;
	switch(nID){
				case ID_VIEW_VF_FROMINSIDE:
					toolTip = _T("标准画面");
					break;
				case ID_VIEW_VF_FROMOUTSIDE:
					toolTip = _T("智能去黑边");
					break;
				
	}
	//AfxMessageBox(toolTip);

	if(!toolTip.IsEmpty()){
		pTTT->lpszText = toolTip.GetBuffer();
		pTTT->hinst = AfxGetResourceHandle();
		bRet = TRUE;
	}



	*pResult = 0;

	return bRet;
}
int CPlayerToolTopBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	cursorHand = ::LoadCursor(NULL, IDC_HAND);
	cursorArrow = ::LoadCursor(NULL, IDC_ARROW);

	GetSystemFontWithScale(&m_statft, 14.0);

	CDC ScreenDC;
	ScreenDC.CreateIC(_T("DISPLAY"), NULL, NULL, NULL);
	m_nLogDPIY = ScreenDC.GetDeviceCaps(LOGPIXELSY);


	
	m_btnList.AddTail( new CSUIButton(L"PINAIL.BMP" , ALIGN_TOPRIGHT, CRect(1 , 1, 1,1)  , 0, ID_ONTOP_ALWAYS, FALSE, 0, 0 ) );
	m_btnList.AddTail( new CSUIButton(L"PINAIL2.BMP" , ALIGN_TOPRIGHT, CRect(1 , 1, 1,1)  , 0, ID_ONTOP_NEVER, TRUE, 0, 0 ) );
	
/*
#define ID_VIEW_VF_STRETCH              838
#define ID_VIEW_VF_FROMINSIDE           839
#define ID_VIEW_VF_FROMOUTSIDE          840
#define ID_VIEW_VF_KEEPASPECTRATIO      841*/


	m_btnList.AddTail( new CSUIButton(L"TOP_1X.BMP" , ALIGN_TOPLEFT, CRect(1 , 1, 1,1)  , 0, ID_VIEW_ZOOM_100, FALSE, 0, 0 ) );
	m_btnList.AddTail( new CSUIButton(L"TOP_2X.BMP" , ALIGN_TOPLEFT, CRect(1 , 1, 1,1)  , 0, ID_VIEW_ZOOM_200, FALSE, ALIGN_LEFT, m_btnList.GetTail() , CRect(1,1,1,1)  ) );


	m_btnList.AddTail( new CSUIButton(L"TOP_NORMAL.BMP" , ALIGN_TOPLEFT, CRect(1 , 1, 1,1)  , 0, ID_VIEW_VF_FROMINSIDE, FALSE, ALIGN_LEFT, m_btnList.GetTail() , CRect(5,1,1,1)  ) );
	m_btnList.AddTail( new CSUIButton(L"TOP_LETTERBOX.BMP" , ALIGN_TOPLEFT, CRect(1 , 1, 1,1)  , 0, ID_VIEW_VF_FROMOUTSIDE, FALSE, ALIGN_LEFT, m_btnList.GetTail() , CRect(1,1,1,1)  ) );
	m_btnList.AddTail( new CSUIButton(L"TOP_FULLSCREEN.BMP" , ALIGN_TOPLEFT, CRect(1 , 1, 1,1)  , 0, ID_VIEW_FULLSCREEN, FALSE, ALIGN_LEFT, m_btnList.GetTail() , CRect(1,1,1,1)  ) );
	
	m_btnList.AddTail( new CSUIButton(L"TOP_AUDIO.BMP" , ALIGN_TOPLEFT, CRect(1 , 1, 1,1)  , 0, ID_MENU_AUDIO, FALSE, ALIGN_LEFT, m_btnList.GetTail() , CRect(5,1,1,1)  ) );
	m_btnList.AddTail( new CSUIButton(L"TOP_VIDEO.BMP" , ALIGN_TOPLEFT, CRect(1 , 1, 1,1)  , 0, ID_MENU_VIDEO, FALSE, ALIGN_LEFT, m_btnList.GetTail() , CRect(1,1,1,1)  ) );


	return 0;
}
void CPlayerToolTopBar::ReCalcBtnPos(){
	CRect rc;
	GetWindowRect(&rc);
	m_btnList.OnSize( rc);
}
void CPlayerToolTopBar::UpdateButtonStat(){
	CMainFrame* pFrame = ((CMainFrame*)GetParentFrame());
	BOOL ontop = !!AfxGetAppSettings().iOnTop ;
	m_btnList.SetHideStat( ID_ONTOP_NEVER , !ontop );
	m_btnList.SetHideStat( ID_ONTOP_ALWAYS , ontop );
}
void CPlayerToolTopBar::OnMove(int x, int y)
{
	__super::OnMove(x, y);

	ReCalcBtnPos();
	Invalidate();
}

void CPlayerToolTopBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemoryDC hdc(&dc, rcClient);

	CRect rc;
	GetWindowRect(&rc);

	CRect rcBottomSqu = rcClient;
	rcBottomSqu.top = rcBottomSqu.bottom - 1;
	//hdc.FillSolidRect(rcBottomSqu, NEWUI_COLOR_BG);

	CRect rcUpperSqu = rcClient;
	rcUpperSqu.bottom--;
	//rcUpperSqu.right--;
	hdc.FillSolidRect(rcUpperSqu, RGB(61,65,69));

	hdc.FillSolidRect(rcBottomSqu, RGB(89,89,89));

	//rcBottomSqu = rcClient;
	//rcBottomSqu.left = rcBottomSqu.right - 1;
	//hdc.FillSolidRect(rcBottomSqu, RGB(89,89,89));
	UpdateButtonStat();
	m_btnList.PaintAll(&hdc, rc);
}

void CPlayerToolTopBar::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	ReCalcBtnPos();
	Invalidate();
}


BOOL CPlayerToolTopBar::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return __super::OnEraseBkgnd(pDC);
}

void CPlayerToolTopBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFrame = ((CMainFrame*)GetParentFrame());
	
	ReleaseCapture();

	CRect rc;
	GetWindowRect(&rc);

	CPoint xpoint = point + rc.TopLeft() ;
	UINT ret = m_btnList.OnHitTest(xpoint,rc);
	if( m_btnList.HTRedrawRequired ){
		if(ret)
			pFrame->PostMessage( WM_COMMAND, ret);
		Invalidate();
	}
	m_nItemToTrack = ret;

	

	//	__super::OnLButtonUp(nFlags, point);
	
	return;
	//__super::OnLButtonUp(nFlags, point);
}

void CPlayerToolTopBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rc;
	GetWindowRect(&rc);

	point += rc.TopLeft() ;
	UINT ret = m_btnList.OnHitTest(point,rc);
	if( m_btnList.HTRedrawRequired ){
		if(ret)
			SetCapture();
		Invalidate();
	}
	m_nItemToTrack = ret;


	//__super::OnLButtonDown(nFlags, point);
}

void CPlayerToolTopBar::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CToolBar::OnNcPaint() for painting messages
}

void CPlayerToolTopBar::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	__super::OnTimer(nIDEvent);
}
static CPoint m_lastMouseMove;
void CPlayerToolTopBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CSize diff = m_lastMouseMove - point;
	BOOL bMouseMoved =  diff.cx || diff.cy ;
	if(bMouseMoved)
		m_lastMouseMove = point;

	CRect rc;
	//CMainFrame* pFrame = ((CMainFrame*)GetParentFrame());
	GetWindowRect(&rc);
	point += rc.TopLeft() ;
	

	if( bMouseMoved){

		UINT ret = m_btnList.OnHitTest(point,rc);
		m_nItemToTrack = ret;
		if(ret){
			SetCursor(cursorHand);
		}else{
			SetCursor(cursorArrow);
		}
		if( m_btnList.HTRedrawRequired ){
			Invalidate();
		}
	}

	__super::OnMouseMove(nFlags, point);
}

INT_PTR CPlayerToolTopBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: Add your specialized code here and/or call the base class
	//	AfxMessageBox(_T("1"));
	if(!pTI){
		return -1;
	}

	
	UINT ret = m_nItemToTrack;
	//AfxMessageBox(_T("2"));
	if(ret){

		
		pTI->hwnd = m_hWnd;
		pTI->uId = (UINT) (ret);
		//pTI->uFlags = TTF_IDISHWND;
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		RECT rcClient;
		GetClientRect(&rcClient);
		//AfxMessageBox(_T("f"));
		pTI->rect = rcClient;

		return pTI->uId;

	}
	return -1;
	
}

void CPlayerToolTopBar::OnEnable(BOOL bEnable)
{
	//CWnd::OnEnable(TRUE);

	return;
	// TODO: Add your message handler code here
}

void CPlayerToolTopBar::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{

//
	CWnd::OnActivate(WA_INACTIVE, pWndOther, bMinimized);


}

BOOL CPlayerToolTopBar::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	__super::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	EnableToolTips(TRUE);
	return TRUE;
}
