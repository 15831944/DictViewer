#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define WM_PROCESSMSG WM_USER+0x01
typedef struct tagThreadParam
{
	vector<CString>* files;
	HWND hWnd;
}ThreadParam;

UINT ProcessThread(LPVOID lpVoid);

class CConvertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConvertDlg)

public:
	CConvertDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConvertDlg();

// �Ի�������
	enum { IDD = IDD_CONVERTDLG };

protected:
	CListBox m_FileListBox;
	vector<CString> m_FileList;
	CProgressCtrl m_ProgressBar;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedProcess();
	afx_msg LRESULT OnProcessMsg(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedFileclear();
};
