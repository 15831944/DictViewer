#pragma once
#include <vector>
using namespace std;

class CChartView : public CFormView
{
	DECLARE_DYNCREATE(CChartView)

	typedef struct tagProductView
	{
		CStatic *m_pStatic;
		CTSLScope *m_pScope;

		tagProductView()
		{
			m_pStatic = NULL;
			m_pScope = NULL;
		}
	}ProductView,*PTR_ProductView;

protected:
	CChartView();           // 动态创建所使用的受保护的构造函数
	virtual ~CChartView();

public:
	enum { IDD = IDD_CHARTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	BOOL m_bLogarithmic;
	vector<PTR_ProductView> m_SubCharts;

protected:
	void AddProductView();
	//void DelProductView(int ch);
	void ReLayoutProductView();
	void AddProductView(int count);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileConvertascii();
	afx_msg void OnCurveLog();
	afx_msg void OnUpdateCurveLog(CCmdUI *pCmdUI);
};


