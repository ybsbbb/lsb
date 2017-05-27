
// LSBInfoHideDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyBMP.h"


// CLSBInfoHideDlg 对话框
class CLSBInfoHideDlg : public CDialogEx
{
// 构造
public:
	CLSBInfoHideDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LSBINFOHIDE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CMenu m_Menu;

	// 生成的消息映射函数
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
	// 原始图片
	CStatic m_Ori;
	// 隐藏信息后的图片
	CStatic m_Info;

	CString m_FilePath;
	CString m_FileTitle;

	MyBMP* oribmp;

	BYTE* newData;

	afx_msg void OnBnClickedOk();
};
