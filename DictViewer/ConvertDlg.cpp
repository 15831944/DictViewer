// ConvertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DictViewer.h"
#include "ConvertDlg.h"
#include "afxdialogex.h"
#include "afxmt.h"

#include <fstream>
using namespace std;

IMPLEMENT_DYNAMIC(CConvertDlg, CDialogEx)

CConvertDlg::CConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConvertDlg::IDD, pParent)
{

}

CConvertDlg::~CConvertDlg()
{
}

void CConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_FileListBox);
	DDX_Control(pDX, IDC_PROGRESS, m_ProgressBar);
}


BEGIN_MESSAGE_MAP(CConvertDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADDFILE, &CConvertDlg::OnBnClickedAdd)
	ON_BN_CLICKED(ID_PROCESS, &CConvertDlg::OnBnClickedProcess)
	ON_MESSAGE(WM_PROCESSMSG,&CConvertDlg::OnProcessMsg)
	ON_BN_CLICKED(IDC_CLEARFILE, &CConvertDlg::OnBnClickedFileclear)
END_MESSAGE_MAP()


// CConvertDlg 消息处理程序


void CConvertDlg::OnBnClickedAdd()
{
	 CFileDialog Dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT); 
	 TCHAR *pBuffer = new TCHAR[MAX_PATH * 5000];
	 Dlg.m_ofn.lpstrFile = pBuffer; 
	 Dlg.m_ofn.nMaxFile = MAX_PATH * 5000; 
	 Dlg.m_ofn.lpstrFile[0] = '\0'; 
	 if(Dlg.DoModal()!=IDOK)
		return;
	 POSITION pos = Dlg.GetStartPosition(); 
	 CString szFileName; 
	 while(pos != NULL) 
	 { 
		szFileName=Dlg.GetNextPathName(pos); 
		m_FileListBox.AddString(szFileName);
	 } 

	 delete[] pBuffer;
}

void CConvertDlg::OnBnClickedProcess()
{
	m_FileList.clear();
	int sum = m_FileListBox.GetCount();
	for(int i=0;i<sum;i++)
	{
		CString temp;
		m_FileListBox.GetText(i,temp);
		m_FileList.push_back(temp);
	}

	m_ProgressBar.SetRange(1,m_FileList.size());
	m_ProgressBar.SetStep(1);
	m_ProgressBar.SetPos(1);

	ThreadParam* threadParam = new ThreadParam;
	threadParam->files = &m_FileList;
	threadParam->hWnd = this->GetSafeHwnd();

	AfxBeginThread(ProcessThread,(LPVOID)threadParam,THREAD_PRIORITY_NORMAL,0,0,NULL);
}

LRESULT CConvertDlg::OnProcessMsg(WPARAM wParam,LPARAM lParam)
{
	m_ProgressBar.SetPos((int)lParam);
	return 0;
}

UINT ProcessThread(LPVOID lpVoid)
{
	ThreadParam* pThreadParam = (ThreadParam*)lpVoid;
	int sum = pThreadParam->files->size();
	for(int i=0;i<sum;i++)
	{
		::PostMessage(pThreadParam->hWnd,WM_PROCESSMSG,0,i+1);

		CString path = pThreadParam->files->at(i);
		int pos = path.ReverseFind('.');
		CString temp = path;
		temp.Delete(pos,temp.GetLength() - pos);
		temp += (_T(".txt"));

		CFile binFile;
		if(!binFile.Open(path,CFile::modeRead | CFile::typeBinary))
			continue;
		binFile.SeekToBegin();
		int size = binFile.SeekToEnd();
		binFile.SeekToBegin();

		unsigned char* pBuf = new unsigned char[size];
		binFile.Read(pBuf,size);

		StandardFile* standardFile = new StandardFile();
		if(standardFile->Restore(pBuf) != 0)
		{
			delete[] pBuf;
			binFile.Close();
			continue;
		}

		ofstream ofp;
		ofp.open(temp);
		standardFile->ConvertToAscii(ofp);
		ofp.close();

		delete[] pBuf;
		binFile.Close();
	}

	delete pThreadParam;
	return 0;
}

void CConvertDlg::OnBnClickedFileclear()
{
	m_FileListBox.ResetContent();
}
