
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "DictViewer.h"

#include "ChildFrm.h"
#include "ChartView.h"
#include "FormatTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	m_bInitial = FALSE;
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	m_wndSplit.CreateStatic(this,1,2,WS_CHILD | WS_VISIBLE,AFX_IDW_PANE_FIRST);
	m_wndSplit.CreateView(0,0,RUNTIME_CLASS(CChartView),CSize(800,500),pContext);
	m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CFormatTreeView),CSize(100,100),pContext);
	m_bInitial = TRUE;
	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}


void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	if(!m_bInitial)
		return;

	m_wndSplit.SetColumnInfo(0,cx-400,200);
	m_wndSplit.SetColumnInfo(1,200,200);
	m_wndSplit.RecalcLayout();
}
