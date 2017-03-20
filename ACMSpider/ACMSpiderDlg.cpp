
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
		__edit.ShowBalloonTip(_T("提示"), _T("请填写此字段"), TTI_INFO);
		return false;
	}
	USES_CONVERSION;
	__str = W2A(tmp);
	return true;
}

CString CACMSpiderDlg::RandomLRC()
{
	char * lrc[13] = { // 薛之谦 - 演员
		"简单点说话的方式简单点 递进的情绪请省略",
		"你又不是个演员 别设计那些情节",
		"没意见我只想看看你怎么圆 你难过的太表面像没天赋的演员 观众一眼能看见",
		"该配合你演出的我演视而不见 在逼一个最爱你的人即兴表演",
		"什么时候我们开始收起了底线 顺应时代的改变看那些拙劣的表演",
		"可你曾经那么爱我干嘛演出细节 我该变成什么样子才能延缓厌倦",
		"原来当爱放下防备后的这些那些 才是考验",
		"没意见你想怎样我都随便 你演技也有限 又不用说感言 分开就平淡些",
		"其实台下的观众就我一个 其实我也看出你有点不舍",
		"越演到重场戏越哭不出了 是否还值得",
		"该配合你演出的我尽力在表演 像情感节目里的嘉宾任人挑选",
		"如果还能看出我有爱你的那面 请剪掉那些情节让我看上去体面"
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

// 开始查找代码
void CACMSpiderDlg::OnBnClickedBtnFindit()
{
	// 获取信息
	std::string strUsername;
	std::string strPwd;
	std::string strURL;
	if (!(
		GetStrFromEdit(m_editUsername, strUsername) &&
		GetStrFromEdit(m_editPassword, strPwd) &&
		GetStrFromEdit(m_editURL, strURL)
		))
		return;
	// 首先我要发送post请求登录
	if(!login_acm(strUsername, strPwd))
	{
		MessageBox(_T("登录ACM失败,请检查用户名密码,如果确认用户名密码正确,请联系软件开发者"), _T("登录失败"), MB_OK | MB_ICONERROR);
		return;
	}

	// 然后去爬题目页URL
	std::string strCode;
	int nPage{};
	if (!get_submit_code(strURL.c_str(), strCode, m_strLang, nPage))
	{
		MessageBox(_T("题目URL或题目语言设置有误,请重新确认,如果确认题目URL正确,请联系软件开发者"), _T("URL错误"), MB_OK | MB_ICONERROR);
		return;
	}
	CString text;
	text.Format(_T("辛苦的小爬虫在爬取了%d张页面后终于找到了你的代码"), nPage);
	MessageBox(text, _T("辛苦的小爬虫"), MB_OK | MB_ICONINFORMATION);
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
			MessageBox(_T("魂斗罗是我小时候最喜欢玩的游戏"), _T("恭喜你发现彩蛋之科乐美秘技"), MB_OK | MB_ICONINFORMATION);
		}
		if (m_strInput.find("76738573788384697378") != std::string::npos)
		{
			m_strInput.clear();
			MessageBox(_T("LiuinStein是作者的英文名哦"), _T("恭喜你发现彩蛋之LiuinStein"), MB_OK | MB_ICONINFORMATION);
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
	MessageBox(_T("代码已复制到剪切板"), _T("剪切板"), MB_OK | MB_ICONINFORMATION);
}
