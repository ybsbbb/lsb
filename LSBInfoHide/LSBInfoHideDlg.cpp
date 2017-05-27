
// LSBInfoHideDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LSBInfoHide.h"
#include "LSBInfoHideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int calculateLenth(MyBMP* bmp);
extern BYTE* hide(MyBMP* bmp, const char* content);
extern const char* extract(MyBMP* bmp);
extern void save(const char* filename, const char* fileheader, const char* infoheader, const char* rgbquad, const char* data, int length);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLSBInfoHideDlg 对话框



CLSBInfoHideDlg::CLSBInfoHideDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LSBINFOHIDE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLSBInfoHideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ORI, m_Ori);
	DDX_Control(pDX, IDC_STATIC_INFO, m_Info);
}

BEGIN_MESSAGE_MAP(CLSBInfoHideDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, &CLSBInfoHideDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CLSBInfoHideDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_HIDE, &CLSBInfoHideDlg::OnBnClickedBtnHide)
	ON_BN_CLICKED(IDC_BTN_EXTRACT, &CLSBInfoHideDlg::OnBnClickedBtnExtract)
	ON_BN_CLICKED(IDOK, &CLSBInfoHideDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLSBInfoHideDlg 消息处理程序

BOOL CLSBInfoHideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLSBInfoHideDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLSBInfoHideDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLSBInfoHideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLSBInfoHideDlg::OnBnClickedBtnLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("BMP文件(*.bmp)|*.BMP||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, NULL, NULL, 0, szFilter, this);

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		delete[] oribmp;
		m_FilePath = fileDlg.GetPathName();
		m_FileTitle = fileDlg.GetFileName();
		HBITMAP hbmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
			m_FilePath,
			IMAGE_BITMAP,
			200,
			200,
			LR_LOADFROMFILE);
		m_Ori.SetBitmap(hbmp);
		CStringA tmp(m_FilePath);
		oribmp = new MyBMP(tmp);

		int length = calculateLenth(oribmp);
		CString lengthStr;
		lengthStr.Format(L"%d",length);
		GetDlgItem(IDC_STATIC_LENGTH)->SetWindowTextW(lengthStr);
	}
}


void CLSBInfoHideDlg::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("BMP文件(*.bmp)|*.BMP||");
	// 构造保存文件对话框   
	CFileDialog fileDlg(FALSE,NULL, _T("tmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString saveFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		saveFilePath = fileDlg.GetPathName();
		CStringA tmp(saveFilePath);
		BITMAPINFOHEADER infoheader = oribmp->getInfoheader();
		int length = 0;
		char* rgbquad;
		if (infoheader.biBitCount == 8) {
			length = infoheader.biHeight * infoheader.biWidth;
			rgbquad = (char*)(oribmp->getRGBQUAD());
		}
		else {
			length = infoheader.biHeight * infoheader.biWidth * 3;
			rgbquad = NULL;
		}
		save(tmp, (char*)(&(oribmp->getFileheader())), (char*)(&(oribmp->getInfoheader())),
			rgbquad, (char*)newData, length);

		delete[] rgbquad;
	}
}


void CLSBInfoHideDlg::OnBnClickedBtnHide()
{
	// TODO: 在此添加控件通知处理程序代码
	CString info;
	GetDlgItem(IDC_EDIT_MESSAGE)->GetWindowText(info);
	CStringA tmp(info);
	delete[] newData;
	newData = hide(oribmp, tmp);
	HBITMAP hbmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
		_T("tmp.BMP"),
		IMAGE_BITMAP,
		200,
		200,
		LR_LOADFROMFILE);
	m_Info.SetBitmap(hbmp);
}


void CLSBInfoHideDlg::OnBnClickedBtnExtract()
{
	// TODO: 在此添加控件通知处理程序代码
	const char* content = extract(oribmp);
	CString tmp(content);
	GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowTextW(tmp);
	delete[] content;
}

CLSBInfoHideDlg::~CLSBInfoHideDlg()
{
	delete[] oribmp;
	delete[] newData;
}


void CLSBInfoHideDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
