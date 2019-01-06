
// DictViewerDoc.cpp : CDictViewerDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CDictViewerDoc ����/����

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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDictViewerDoc ���л�

void CDictViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
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

// ����ͼ��֧��
void CDictViewerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CDictViewerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CDictViewerDoc ���

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


// CDictViewerDoc ����
