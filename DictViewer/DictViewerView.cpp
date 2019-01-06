
// DictViewerView.cpp : CDictViewerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DictViewer.h"
#endif

#include "DictViewerDoc.h"
#include "DictViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDictViewerView

IMPLEMENT_DYNCREATE(CDictViewerView, CView)

BEGIN_MESSAGE_MAP(CDictViewerView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDictViewerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDictViewerView ����/����

CDictViewerView::CDictViewerView()
{
	// TODO: �ڴ˴���ӹ������

}

CDictViewerView::~CDictViewerView()
{
}

BOOL CDictViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDictViewerView ����

void CDictViewerView::OnDraw(CDC* /*pDC*/)
{
	CDictViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDictViewerView ��ӡ


void CDictViewerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDictViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDictViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDictViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CDictViewerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDictViewerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDictViewerView ���

#ifdef _DEBUG
void CDictViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CDictViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDictViewerDoc* CDictViewerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDictViewerDoc)));
	return (CDictViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CDictViewerView ��Ϣ�������
