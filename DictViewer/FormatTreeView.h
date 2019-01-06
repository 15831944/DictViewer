#pragma once


// CFormatTreeView ��ͼ

class CFormatTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CFormatTreeView)

protected:
	CFormatTreeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFormatTreeView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	void UpdateProperty(StandardFile* pStandardFile);
	void UpdateFileProperty(FileProperty* pFileProperty);
	void UpdateStationProperty(StationProperty* pStationProperty);
	void UpdateRecordProperty(RecordProperty* pRecordProperty);
	void UpdateChannelProperty(vector<Channel*>* pChannels);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
};


