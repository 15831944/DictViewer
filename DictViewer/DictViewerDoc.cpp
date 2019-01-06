
// DictViewerDoc.cpp : CDictViewerDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DictViewer.h"
#endif

#include "DictViewerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDictViewerDoc

IMPLEMENT_DYNCREATE(CDictViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDictViewerDoc, CDocument)
END_MESSAGE_MAP()


// CDictViewerDoc 构造/析构

CDictViewerDoc::CDictViewerDoc()
{
	m_pStandardFile = NULL;
}

CDictViewerDoc::~CDictViewerDoc()
{
}

BOOL CDictViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDictViewerDoc 序列化

void CDictViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		CFile* pFile = ar.GetFile();
		pFile->SeekToBegin();
		int size = pFile->SeekToEnd();
		pFile->SeekToBegin();

		unsigned char* pBuf = new unsigned char[size];
		pFile->Read(pBuf,size);

		if(m_pStandardFile != NULL)
			delete m_pStandardFile;
		m_pStandardFile = new StandardFile();
		m_pStandardFile->Restore(pBuf);

		//UpdateAllViews(NULL);

		delete[] pBuf;
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDictViewerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CDictViewerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CDictViewerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDictViewerDoc 诊断

#ifdef _DEBUG
void CDictViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDictViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDictViewerDoc 命令
