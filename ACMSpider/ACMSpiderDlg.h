
// ACMSpiderDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <string>


// CACMSpiderDlg dialog
class CACMSpiderDlg : public CDialogEx
{
// Construction
public:
	CACMSpiderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACMSPIDER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editUsername;
	CEdit m_editPassword;
	CEdit m_editURL;
	CEdit m_editRetcode;
	std::string m_strLang;
	std::string m_strInput;
	std::string m_strEasterEgg;

	bool GetStrFromEdit(CEdit& __edit, std::string & __str);
	CString RandomLRC();

	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedBtnFindit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnCopyit();
};
