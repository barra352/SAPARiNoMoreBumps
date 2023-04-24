// SAPARiNoMoreBumpsDlg.h : header file
//
#include <vector>

#if !defined(AFX_SAPARINOMOREBUMPSDLG_H__501FF333_689B_4983_A9C1_56CB8B050EE9__INCLUDED_)
#define AFX_SAPARINOMOREBUMPSDLG_H__501FF333_689B_4983_A9C1_56CB8B050EE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSAPARiNoMoreBumpsDlg dialog

class CSAPARiNoMoreBumpsDlg : public CDialog
{
// Construction
public:
	CSAPARiNoMoreBumpsDlg(CWnd* pParent = NULL);	// standard constructor
	CString CPBDir;
	BOOL m_Bumps;
	void GetVRMLFiles(LPCTSTR dir);
	struct structFiles
	{
		CString fileName;
		BOOL bumps;
	};
	CWinThread *m_pThread;
	~CSAPARiNoMoreBumpsDlg();
	friend UINT FileThread(LPVOID arg);

	// Dialog Data
	//{{AFX_DATA(CSAPARiNoMoreBumpsDlg)
	enum { IDD = IDD_SAPARINOMOREBUMPS_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAPARiNoMoreBumpsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BOOL m_KeyPress;
	CAnimateCtrl *m_Kame;
	CProgressCtrl *m_Progress;
	CStatic *m_CurrentProgress;
	std::vector<structFiles> m_Files;
	CButton& m_Boy() { return *(CButton*)GetDlgItem(IDC_RADIO_BOY); }
	CButton& m_Peng() { return *(CButton*)GetDlgItem(IDC_RADIO_PENG); }
	CButton& m_BtnOk() { return *(CButton*)GetDlgItem(IDOK); }
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Generated message map functions
	//{{AFX_MSG(CSAPARiNoMoreBumpsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnRadioBoy();
	afx_msg void OnRadioPeng();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAPARINOMOREBUMPSDLG_H__501FF333_689B_4983_A9C1_56CB8B050EE9__INCLUDED_)
