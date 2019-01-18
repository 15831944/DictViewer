// FormatTreeView.cpp : ʵ���ļ�
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


// CFormatTreeView ���

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


// CFormatTreeView ��Ϣ�������


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

	HTREEITEM parentNode = treeCtrl.InsertItem(_T("�ļ�����"),TVI_ROOT);
	CString tempStr(IFormatProperty::FormatTypeCaption[pFileProperty->_FormatType]);
	treeCtrl.InsertItem(_T("�ļ�����:") + tempStr,parentNode);
	tempStr.Format(_T("%.2f"),(float)pFileProperty->_FormatVersion);
	treeCtrl.InsertItem(_T("��ʽ�汾:") + tempStr,parentNode);
	treeCtrl.Expand(parentNode,TVE_EXPAND);
}

void CFormatTreeView::UpdateStationProperty(StationProperty* pStationProperty)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	HTREEITEM parentNode = treeCtrl.InsertItem(_T("̨վ����"),TVI_ROOT);
	treeCtrl.InsertItem(_T("��վ��:") + pStationProperty->_ID,parentNode);
	CString tempStr;
	tempStr.Format(_T("%.6f"),pStationProperty->_Position._longitude);
	treeCtrl.InsertItem(_T("����:") + tempStr,parentNode);
	tempStr.Format(_T("%.6f"),pStationProperty->_Position._latitude);
	treeCtrl.InsertItem(_T("γ��:") + tempStr,parentNode);
	tempStr.Format(_T("%d"),pStationProperty->_Position._altitude);
	treeCtrl.InsertItem(_T("�߶�:") + tempStr,parentNode);
	CString tempStr1;
	int sum = pStationProperty->_LenOfWaves.size();
	for(int i=0;i<sum;i++)
	{
		tempStr.Format(_T("%dnm,"),pStationProperty->_LenOfWaves.at(0));
		tempStr1 += tempStr;
	}
	treeCtrl.InsertItem(_T("����:") + tempStr1,parentNode);
	tempStr.Format(_T("%d"),pStationProperty->_ChannelCount);
	treeCtrl.InsertItem(_T("ͨ����:") + tempStr,parentNode);

	treeCtrl.Expand(parentNode,TVE_EXPAND);
}

void CFormatTreeView::UpdateRecordProperty(RecordProperty* pRecordProperty)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	HTREEITEM parentNode = treeCtrl.InsertItem(_T("��¼����"),TVI_ROOT);
	CString tempStr(RecordProperty::ModeTypeCaption[pRecordProperty->_ModeType]);
	treeCtrl.InsertItem(_T("̽��ģʽ:") + tempStr,parentNode);
	tempStr = pRecordProperty->_TimeStart.Format(_T("%Y/%m/%d %H:%M:%S"));
	treeCtrl.InsertItem(_T("��ʼʱ��:") + tempStr,parentNode);
	tempStr = pRecordProperty->_TimeEnd.Format(_T("%Y/%m/%d %H:%M:%S"));
	treeCtrl.InsertItem(_T("����ʱ��:") + tempStr,parentNode);
	tempStr.Format(_T("%.2f"),pRecordProperty->_FyAngle);
	treeCtrl.InsertItem(_T("������:") + tempStr,parentNode);
	tempStr.Format(_T("%.2f"),pRecordProperty->_FwAngle);
	treeCtrl.InsertItem(_T("��λ��:") + tempStr,parentNode);

	treeCtrl.Expand(parentNode,TVE_EXPAND);
}

void CFormatTreeView::UpdateChannelProperty(vector<Channel*>* pChannels)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	int sum = pChannels->size();

	HTREEITEM parentNode = treeCtrl.InsertItem(_T("ͨ������"),TVI_ROOT);

	for(int i=0;i<sum;i++)
	{
		CString tempStr;
		tempStr.Format(_T("ͨ��#%d"),i+1);
		HTREEITEM chParentNode = treeCtrl.InsertItem(tempStr,parentNode);

		ChannelProperty* pChannelProperty = pChannels->at(i)->_pChannelProperty;
		CString tempStr1(ChannelProperty::AcqTypeString[pChannelProperty->_AcqType]);
		treeCtrl.InsertItem(_T("�ɼ�����:") + tempStr1,chParentNode);

		tempStr.Format(_T("%d"),pChannelProperty->_WaveLen);
		treeCtrl.InsertItem(_T("����:") + tempStr,chParentNode);

		CString tempStr2(ChannelProperty::WaveTypeString[pChannelProperty->_WaveType]);
		treeCtrl.InsertItem(_T("ƫ��̬:") + tempStr2,chParentNode);

		tempStr.Format(_T("%.2fm"),pChannelProperty->_DistResolution);
		treeCtrl.InsertItem(_T("����ֱ���:") + tempStr,chParentNode);

		tempStr.Format(_T("%.2fm"),pChannelProperty->_DeadZone);
		treeCtrl.InsertItem(_T("ä���߶�:") + tempStr,chParentNode);

		tempStr.Format(_T("%d"),pChannelProperty->_DistCount);
		treeCtrl.InsertItem(_T("�������:") + tempStr,chParentNode);

		tempStr.Format(_T("%d"),pChannelProperty->_DataPtr);
		treeCtrl.InsertItem(_T("����ƫ��ָ��:") + tempStr,chParentNode);

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
