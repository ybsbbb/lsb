
// LSBInfoHideDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MyBMP.h"


// CLSBInfoHideDlg �Ի���
class CLSBInfoHideDlg : public CDialogEx
{
// ����
public:
	CLSBInfoHideDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LSBINFOHIDE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	CMenu m_Menu;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnHide();
	afx_msg void OnBnClickedBtnExtract();

	CLSBInfoHideDlg::~CLSBInfoHideDlg();
	// ԭʼͼƬ
	CStatic m_Ori;
	// ������Ϣ���ͼƬ
	CStatic m_Info;

	CString m_FilePath;
	CString m_FileTitle;

	MyBMP* oribmp;

	BYTE* newData;

	afx_msg void OnBnClickedOk();
};
