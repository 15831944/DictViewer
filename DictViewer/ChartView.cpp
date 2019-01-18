// ChartView.cpp : 实现文件
//

#include "stdafx.h"
#include "DictViewer.h"
#include "ChartView.h"
#include "DictViewerDoc.h"

#include <fstream>
using namespace std;

IMPLEMENT_DYNCREATE(CChartView, CFormView)

CChartView::CChartView()
	: CFormView(CChartView::IDD)
{
	m_bLogarithmic = TRUE;
}

CChartView::~CChartView()
{
}

void CChartView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChartView, CFormView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_CONVERTASCII, &CChartView::OnFileConvertascii)
	ON_COMMAND(ID_CURVE_LOG, &CChartView::OnCurveLog)
	ON_UPDATE_COMMAND_UI(ID_CURVE_LOG, &CChartView::OnUpdateCurveLog)
END_MESSAGE_MAP()


// CChartView 诊断

#ifdef _DEBUG
void CChartView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChartView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChartView 消息处理程序


void CChartView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CDictViewerDoc* pDoc = (CDictViewerDoc *)GetDocument();
	StandardFile* pStandardFile = pDoc->m_pStandardFile;
	if(pStandardFile == NULL)
		return;

	if(pStandardFile->_Channels.size() == 0)
		return;

	AddProductView(pStandardFile->_Channels.size());

	float* range;
	for(int i=0;i<pStandardFile->_Channels.size();i++)
	{
		ChannelProperty* pChannelProperty = pStandardFile->_Channels.at(i)->_pChannelProperty;
		range = new float[pChannelProperty->_DistCount];
		for(int j=0;j<pChannelProperty->_DistCount;j++)
			range[j] = (j+1) * pChannelProperty->_DistResolution;

		CTSLScope* pScope = m_SubCharts.at(i)->m_pScope;
		pScope->Channels[0].Data.SetXYData(pStandardFile->_Channels.at(i)->_pDatas,
																	range,
																	pChannelProperty->_DistCount);
	}
}

//void CChartView::DelProductView(int ch)
//{
//	if(m_SubCharts.size() < ch)
//		return;
//
//	delete m_SubCharts[ch - 1]->m_pScope;
//
//	if(m_SubCharts[ch - 1]->m_pStatic != NULL)
//	{
//		m_SubCharts[ch - 1]->m_pStatic->DestroyWindow();
//		delete m_SubCharts[ch - 1]->m_pStatic;
//	}
//
//	//delete m_SubCharts[ch - 1];
//
//	ReLayoutProductView();
//}

void CChartView::ReLayoutProductView()
{
	CRect rt;
	GetClientRect(&rt);

	int cx = rt.Width();
	int cy = rt.Height();

	int nDx = cx / m_SubCharts.size();
	int x = 0;
	for(unsigned int i=0;i<m_SubCharts.size();i++)
	{
		m_SubCharts[i]->m_pStatic->MoveWindow(x,0,nDx,cy);
		m_SubCharts[i]->m_pScope->Width = nDx;
		m_SubCharts[i]->m_pScope->Height = cy;
		x += nDx;
	}
}

void CChartView::AddProductView(int count)
{
	for(int i=0;i<count;i++)
	{
		PTR_ProductView pProductView = new ProductView();
		pProductView->m_pStatic = new CStatic();
		pProductView->m_pStatic->Create(_T(""),WS_CHILD|WS_VISIBLE,CRect(0,0,300,300),this,0);
		
		pProductView->m_pScope = new CTSLScope();
		pProductView->m_pScope->Open(pProductView->m_pStatic->m_hWnd);
		pProductView->m_pScope->Align = CTAlign::alClient;
		pProductView->m_pScope->ToolBar.Visible = FALSE;
		pProductView->m_pScope->Title.Visible = TRUE;
		pProductView->m_pScope->Title.Font.Charset = GB2312_CHARSET;
		pProductView->m_pScope->Title.Font.Size = 11;
		CString title;
		title.Format(_T("通道-%d"),i+1);
		pProductView->m_pScope->Title.Text = title;
		pProductView->m_pScope->Title.Align = vaLeft;

		pProductView->m_pScope->XAxis.Min.AutoScale = TRUE;
		pProductView->m_pScope->XAxis.Max.AutoScale = TRUE;
		pProductView->m_pScope->XAxis.ScaleMode = m_bLogarithmic ? smLogarithmic : smLinear;
		pProductView->m_pScope->XAxis.AxisLabel.Font.Charset = GB2312_CHARSET;
		pProductView->m_pScope->XAxis.DataView.Lines.Visible = FALSE;
		pProductView->m_pScope->XAxis.DataView.ZeroLine.Visible = FALSE;
		pProductView->m_pScope->XAxis.AxisLabel.Visible = TRUE;
		pProductView->m_pScope->XAxis.AxisLabel.Text = _T("回波强度");

		pProductView->m_pScope->YAxis.Min.AutoScale = TRUE;
		pProductView->m_pScope->YAxis.Max.AutoScale = TRUE;
		pProductView->m_pScope->YAxis.AxisLabel.Font.Charset = GB2312_CHARSET;
		pProductView->m_pScope->YAxis.DataView.Lines.Visible = FALSE;
		pProductView->m_pScope->YAxis.DataView.ZeroLine.Visible = FALSE;
		pProductView->m_pScope->YAxis.AxisLabel.Visible = TRUE;
		pProductView->m_pScope->YAxis.AxisLabel.Text = _T("高度");
	
		pProductView->m_pScope->Legend.Visible = FALSE;
		pProductView->m_pScope->Channels.Add();

		m_SubCharts.push_back(pProductView);
	}
	
	VCL_Loaded();
	ReLayoutProductView();
}

void CChartView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if(m_SubCharts.size() == 0)
		return;

	ReLayoutProductView();
}

void CChartView::OnFileConvertascii()
{
	CFileDialog fDlg(FALSE);
	if(fDlg.DoModal() != IDOK)
		return;

	CString path = fDlg.GetPathName();

	CDictViewerDoc* pDoc = (CDictViewerDoc *)GetDocument();
	StandardFile* pStandardFile = pDoc->m_pStandardFile;
	if(pStandardFile == NULL)
		return;

	ofstream ofp;
	ofp.open(path);
	if(!ofp.is_open())
	{
		MessageBox(_T("无法创建文件！"),_T("错误"),MB_ICONERROR);
		return;
	}

	pStandardFile->ConvertToAscii(ofp);
	ofp.close();
}

void CChartView::OnCurveLog()
{
	if(m_bLogarithmic)
		m_bLogarithmic = FALSE;
	else m_bLogarithmic = TRUE;

	int sum = m_SubCharts.size();
	for(int i=0;i<sum;i++)
	{
		CTSLScope* pScope = m_SubCharts.at(i)->m_pScope;
		pScope->XAxis.ScaleMode = m_bLogarithmic ? smLogarithmic : smLinear;
	}
}

void CChartView::OnUpdateCurveLog(CCmdUI *pCmdUI)
{
	if(m_bLogarithmic)
		pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}
