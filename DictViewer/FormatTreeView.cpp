// FormatTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "DictViewer.h"
#include "FormatTreeView.h"
#include "DictViewerDoc.h"

// CFormatTreeView

IMPLEMENT_DYNCREATE(CFormatTreeView, CTreeView)

CFormatTreeView::CFormatTreeView()
{

}

CFormatTreeView::~CFormatTreeView()
{
}

BEGIN_MESSAGE_MAP(CFormatTreeView, CTreeView)
END_MESSAGE_MAP()


// CFormatTreeView 诊断

#ifdef _DEBUG
void CFormatTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormatTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormatTreeView 消息处理程序


void CFormatTreeView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CDictViewerDoc* pDoc = (CDictViewerDoc *)GetDocument();
	StandardFile* pStandardFile = pDoc->m_pStandardFile;
	if(pStandardFile == NULL)
		return;

	UpdateProperty(pStandardFile);
}

void CFormatTreeView::UpdateProperty(StandardFile* pStandardFile)
{
	if(pStandardFile->_pFileProperty != NULL)
		UpdateFileProperty(pStandardFile->_pFileProperty);
	if(pStandardFile->_pStationProperty != NULL)
		UpdateStationProperty(pStandardFile->_pStationProperty);
	if(pStandardFile->_pRecordProperty != 0)
		UpdateRecordProperty(pStandardFile->_pRecordProperty);

	UpdateChannelProperty(&(pStandardFile->_Channels));
}

void CFormatTreeView::UpdateFileProperty(FileProperty* pFileProperty)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	HTREEITEM parentNode = treeCtrl.InsertItem(_T("文件属性"),TVI_ROOT);
	CString tempStr(IFormatProperty::FormatTypeCaption[pFileProperty->_FormatType]);
	treeCtrl.InsertItem(_T("文件类型:") + tempStr,parentNode);
	tempStr.Format(_T("%.2f"),(float)pFileProperty->_FormatVersion);
	treeCtrl.InsertItem(_T("格式版本:") + tempStr,parentNode);
	treeCtrl.Expand(parentNode,TVE_EXPAND);
}

void CFormatTreeView::UpdateStationProperty(StationProperty* pStationProperty)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	HTREEITEM parentNode = treeCtrl.InsertItem(_T("台站属性"),TVI_ROOT);
	treeCtrl.InsertItem(_T("区站号:") + pStationProperty->_ID,parentNode);
	CString tempStr;
	tempStr.Format(_T("%.6f"),pStationProperty->_Position._longitude);
	treeCtrl.InsertItem(_T("经度:") + tempStr,parentNode);
	tempStr.Format(_T("%.6f"),pStationProperty->_Position._latitude);
	treeCtrl.InsertItem(_T("纬度:") + tempStr,parentNode);
	tempStr.Format(_T("%d"),pStationProperty->_Position._altitude);
	treeCtrl.InsertItem(_T("高度:") + tempStr,parentNode);
	CString tempStr1;
	int sum = pStationProperty->_LenOfWaves.size();
	for(int i=0;i<sum;i++)
	{
		tempStr.Format(_T("%dnm,"),pStationProperty->_LenOfWaves.at(0));
		tempStr1 += tempStr;
	}
	treeCtrl.InsertItem(_T("波长:") + tempStr1,parentNode);
	tempStr.Format(_T("%d"),pStationProperty->_ChannelCount);
	treeCtrl.InsertItem(_T("通道数:") + tempStr,parentNode);

	treeCtrl.Expand(parentNode,TVE_EXPAND);
}

void CFormatTreeView::UpdateRecordProperty(RecordProperty* pRecordProperty)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	HTREEITEM parentNode = treeCtrl.InsertItem(_T("记录属性"),TVI_ROOT);
	CString tempStr(RecordProperty::ModeTypeCaption[pRecordProperty->_ModeType]);
	treeCtrl.InsertItem(_T("探测模式:") + tempStr,parentNode);
	tempStr = pRecordProperty->_TimeStart.Format(_T("%Y/%m/%d %H:%M:%S"));
	treeCtrl.InsertItem(_T("开始时间:") + tempStr,parentNode);
	tempStr = pRecordProperty->_TimeEnd.Format(_T("%Y/%m/%d %H:%M:%S"));
	treeCtrl.InsertItem(_T("结束时间:") + tempStr,parentNode);
	tempStr.Format(_T("%.2f"),pRecordProperty->_FyAngle);
	treeCtrl.InsertItem(_T("俯仰角:") + tempStr,parentNode);
	tempStr.Format(_T("%.2f"),pRecordProperty->_FwAngle);
	treeCtrl.InsertItem(_T("方位角:") + tempStr,parentNode);

	treeCtrl.Expand(parentNode,TVE_EXPAND);
}

void CFormatTreeView::UpdateChannelProperty(vector<Channel*>* pChannels)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	int sum = pChannels->size();

	HTREEITEM parentNode = treeCtrl.InsertItem(_T("通道属性"),TVI_ROOT);

	for(int i=0;i<sum;i++)
	{
		CString tempStr;
		tempStr.Format(_T("通道#%d"),i+1);
		HTREEITEM chParentNode = treeCtrl.InsertItem(tempStr,parentNode);

		ChannelProperty* pChannelProperty = pChannels->at(i)->_pChannelProperty;
		CString tempStr1(ChannelProperty::AcqTypeString[pChannelProperty->_AcqType]);
		treeCtrl.InsertItem(_T("采集类型:") + tempStr1,chParentNode);

		tempStr.Format(_T("%d"),pChannelProperty->_WaveLen);
		treeCtrl.InsertItem(_T("波长:") + tempStr,chParentNode);

		CString tempStr2(ChannelProperty::WaveTypeString[pChannelProperty->_WaveType]);
		treeCtrl.InsertItem(_T("偏振态:") + tempStr2,chParentNode);

		tempStr.Format(_T("%.2fm"),pChannelProperty->_DistResolution);
		treeCtrl.InsertItem(_T("距离分辨率:") + tempStr,chParentNode);

		tempStr.Format(_T("%.2fm"),pChannelProperty->_DeadZone);
		treeCtrl.InsertItem(_T("盲区高度:") + tempStr,chParentNode);

		tempStr.Format(_T("%d"),pChannelProperty->_DistCount);
		treeCtrl.InsertItem(_T("距离库数:") + tempStr,chParentNode);

		tempStr.Format(_T("%d"),pChannelProperty->_DataPtr);
		treeCtrl.InsertItem(_T("数据偏移指针:") + tempStr,chParentNode);

		treeCtrl.Expand(chParentNode,TVE_EXPAND);
	}
	treeCtrl.Expand(parentNode,TVE_EXPAND);
}

void CFormatTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CTreeCtrl& treeCtrl = GetTreeCtrl();

	DWORD dwStyle = treeCtrl.GetStyle();
	dwStyle |= TVS_HASLINES;
	dwStyle |= TVS_LINESATROOT;
	dwStyle |= TVS_HASBUTTONS;
	dwStyle |= TVS_SHOWSELALWAYS;
	treeCtrl.ModifyStyle(0,dwStyle);
}
