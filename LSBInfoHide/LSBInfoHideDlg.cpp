
// LSBInfoHideDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLSBInfoHideDlg �Ի���



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


// CLSBInfoHideDlg ��Ϣ�������

BOOL CLSBInfoHideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLSBInfoHideDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLSBInfoHideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLSBInfoHideDlg::OnBnClickedBtnLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("BMP�ļ�(*.bmp)|*.BMP||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, NULL, NULL, 0, szFilter, this);

	// ��ʾ���ļ��Ի���   
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("BMP�ļ�(*.bmp)|*.BMP||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE,NULL, _T("tmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString saveFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
