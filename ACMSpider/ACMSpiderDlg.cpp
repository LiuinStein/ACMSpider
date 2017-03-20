
// ACMSpiderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ACMSpider.h"
#include "ACMSpiderDlg.h"
#include "afxdialogex.h"
#include "Spider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CACMSpiderDlg dialog



CACMSpiderDlg::CACMSpiderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ACMSPIDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CACMSpiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editUsername);
	DDX_Control(pDX, IDC_EDIT2, m_editPassword);
	DDX_Control(pDX, IDC_EDIT3, m_editURL);
	DDX_Control(pDX, IDC_EDIT4, m_editRetcode);
}

BEGIN_MESSAGE_MAP(CACMSpiderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CACMSpiderDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CACMSpiderDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CACMSpiderDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CACMSpiderDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CACMSpiderDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BTN_FINDIT, &CACMSpiderDlg::OnBnClickedBtnFindit)
	ON_BN_CLICKED(IDC_BTN_COPYIT, &CACMSpiderDlg::OnBnClickedBtnCopyit)
END_MESSAGE_MAP()


// CACMSpiderDlg message handlers

BOOL CACMSpiderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	srand(time(nullptr));
	if (rand() % 2)
		m_editRetcode.SetWindowTextW(RandomLRC());
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
	m_strLang = "java";

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CACMSpiderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CACMSpiderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool CACMSpiderDlg::GetStrFromEdit(CEdit& __edit, std::string & __str)
{
	CString tmp;
	__edit.GetWindowText(tmp);
	if (tmp == _T(""))
	{
		__edit.ShowBalloonTip(_T("��ʾ"), _T("����д���ֶ�"), TTI_INFO);
		return false;
	}
	USES_CONVERSION;
	__str = W2A(tmp);
	return true;
}

CString CACMSpiderDlg::RandomLRC()
{
	char * lrc[13] = { // Ѧ֮ǫ - ��Ա
		"�򵥵�˵���ķ�ʽ�򵥵� �ݽ���������ʡ��",
		"���ֲ��Ǹ���Ա �������Щ���",
		"û�����ֻ�뿴������ôԲ ���ѹ���̫������û�츳����Ա ����һ���ܿ���",
		"��������ݳ��������Ӷ����� �ڱ�һ�������˼��˱���",
		"ʲôʱ�����ǿ�ʼ�����˵��� ˳Ӧʱ���ĸı俴��Щ׾�ӵı���",
		"����������ô���Ҹ����ݳ�ϸ�� �Ҹñ��ʲô���Ӳ����ӻ����",
		"ԭ���������·��������Щ��Щ ���ǿ���",
		"û������������Ҷ���� ���ݼ�Ҳ���� �ֲ���˵���� �ֿ���ƽ��Щ",
		"��ʵ̨�µĹ��ھ���һ�� ��ʵ��Ҳ�������е㲻��",
		"Խ�ݵ��س�ϷԽ�޲����� �Ƿ�ֵ��",
		"��������ݳ����Ҿ����ڱ��� ����н�Ŀ��ļα�������ѡ",
		"������ܿ������а�������� �������Щ������ҿ���ȥ����"
	};
	srand(time(nullptr));
	return CString{ lrc[rand() % 13] };
}

void CACMSpiderDlg::OnBnClickedRadio1()
{
	m_strLang = "gcc";
}


void CACMSpiderDlg::OnBnClickedRadio2()
{
	m_strLang = "g\\+\\+";
}


void CACMSpiderDlg::OnBnClickedRadio3()
{
	m_strLang = "java";
}


void CACMSpiderDlg::OnBnClickedRadio4()
{
	m_strLang = "python2";
}


void CACMSpiderDlg::OnBnClickedRadio5()
{
	m_strLang = "python3";
}

// ��ʼ���Ҵ���
void CACMSpiderDlg::OnBnClickedBtnFindit()
{
	// ��ȡ��Ϣ
	std::string strUsername;
	std::string strPwd;
	std::string strURL;
	if (!(
		GetStrFromEdit(m_editUsername, strUsername) &&
		GetStrFromEdit(m_editPassword, strPwd) &&
		GetStrFromEdit(m_editURL, strURL)
		))
		return;
	// ������Ҫ����post�����¼
	if(!login_acm(strUsername, strPwd))
	{
		MessageBox(_T("��¼ACMʧ��,�����û�������,���ȷ���û���������ȷ,����ϵ���������"), _T("��¼ʧ��"), MB_OK | MB_ICONERROR);
		return;
	}

	// Ȼ��ȥ����ĿҳURL
	std::string strCode;
	int nPage{};
	if (!get_submit_code(strURL.c_str(), strCode, m_strLang, nPage))
	{
		MessageBox(_T("��ĿURL����Ŀ������������,������ȷ��,���ȷ����ĿURL��ȷ,����ϵ���������"), _T("URL����"), MB_OK | MB_ICONERROR);
		return;
	}
	CString text;
	text.Format(_T("�����С��������ȡ��%d��ҳ��������ҵ�����Ĵ���"), nPage);
	MessageBox(text, _T("�����С����"), MB_OK | MB_ICONINFORMATION);
	m_editRetcode.SetWindowTextW(CString{ strCode.c_str() });
}


BOOL CACMSpiderDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONUP && m_editURL.m_hWnd == pMsg->hwnd)
	{
		m_editURL.SetSel(0, -1);
	}
	if (pMsg->message == WM_LBUTTONUP && m_editRetcode.m_hWnd == pMsg->hwnd)
	{
		m_editRetcode.SetSel(0, -1);
	}
	if (pMsg->message == WM_KEYDOWN && (/*pMsg->wParam == VK_RETURN ||*/ pMsg->wParam == VK_ESCAPE))
		return TRUE;
	if(pMsg->message == WM_KEYDOWN)
	{
		m_strInput.append(std::to_string(pMsg->wParam));
		if (m_strInput.find("383840403739373966656665") != std::string::npos)
		{
			m_strInput.clear();
			MessageBox(_T("�궷������Сʱ����ϲ�������Ϸ"), _T("��ϲ�㷢�ֲʵ�֮�������ؼ�"), MB_OK | MB_ICONINFORMATION);
		}
		if (m_strInput.find("76738573788384697378") != std::string::npos)
		{
			m_strInput.clear();
			MessageBox(_T("LiuinStein�����ߵ�Ӣ����Ŷ"), _T("��ϲ�㷢�ֲʵ�֮LiuinStein"), MB_OK | MB_ICONINFORMATION);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CACMSpiderDlg::OnBnClickedBtnCopyit()
{
	OpenClipboard();
	CString str;
	m_editRetcode.GetWindowTextW(str);
	HGLOBAL hClip;
	hClip = ::GlobalAlloc(GMEM_MOVEABLE, str.GetLength() * 2 + 2);
	TCHAR * pBuf = (TCHAR*)::GlobalLock(hClip);
	lstrcpy(pBuf, str);
	GlobalUnlock(hClip);
	SetClipboardData(CF_UNICODETEXT, hClip);
	CloseClipboard();
	MessageBox(_T("�����Ѹ��Ƶ����а�"), _T("���а�"), MB_OK | MB_ICONINFORMATION);
}
