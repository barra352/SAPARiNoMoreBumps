// SAPARiNoMoreBumpsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SAPARiNoMoreBumps.h"
#include "SAPARiNoMoreBumpsDlg.h"
#include "QuestionMark.h"
#include "Vscp.h"

#include <shlwapi.h>

#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAPARiNoMoreBumpsDlg dialog

CSAPARiNoMoreBumpsDlg::CSAPARiNoMoreBumpsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSAPARiNoMoreBumpsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSAPARiNoMoreBumpsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_PENG);
	m_Bumps = FALSE;
	m_KeyPress = FALSE;
	m_Kame = new CAnimateCtrl;
	m_Progress = new CProgressCtrl;
	m_CurrentProgress = new CStatic;
	m_pThread = NULL;
}

void CSAPARiNoMoreBumpsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSAPARiNoMoreBumpsDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSAPARiNoMoreBumpsDlg, CDialog)
	//{{AFX_MSG_MAP(CSAPARiNoMoreBumpsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_BOY, OnRadioBoy)
	ON_BN_CLICKED(IDC_RADIO_PENG, OnRadioPeng)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAPARiNoMoreBumpsDlg message handlers

BOOL CSAPARiNoMoreBumpsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Finding the CPlace directory
	CPBDir = Vscp::FindDirClient();
	CPBDir += "\\world";

	GetVRMLFiles(CPBDir);
	if (m_Files.size() == 0)
	{
		AfxMessageBox(IDS_NOVRML);
		ShowWindow(SW_HIDE);
		CDialog::OnCancel();
	}

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_Boy().SetWindowText(CSAPARiNoMoreBumpsApp::GetString(IDS_GIVETHEMBACK));
	m_Peng().SetWindowText(CSAPARiNoMoreBumpsApp::GetString(IDS_NOMORE));

	m_Peng().SetCheck(TRUE);
	m_Bumps = FALSE;

	CFont m_Font;
	m_Peng().SetFont(&m_Font);

	m_Kame->Create(WS_CHILD | WS_VISIBLE | ACS_TRANSPARENT | ACS_AUTOPLAY, CRect(570, 5, 70, 70), this, 0x1984);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void TerminateIt(CSAPARiNoMoreBumpsDlg * pWnd)
{
	CString result;
	result = CSAPARiNoMoreBumpsApp::GetString(IDS_DONE);
	if (Vscp::writtenFiles > 0)
		result.Format(CSAPARiNoMoreBumpsApp::GetString(IDS_DONEFILES), Vscp::writtenFiles);
	MessageBox(pWnd->GetSafeHwnd(), result, ::AfxGetAppName(), MB_OK|MB_ICONINFORMATION);
	pWnd->EndDialog(0);
}

UINT FileThread(LPVOID arg)
{
	CSAPARiNoMoreBumpsDlg * pWnd;
	pWnd = (CSAPARiNoMoreBumpsDlg *)arg;
	CString curProgress, titleProgress, shortFilePath, errBump;
	shortFilePath = pWnd->m_Files[0].fileName;
	shortFilePath.Replace(Vscp::FindDirClient(), "...");
	titleProgress = "NoMoreBumps - " + shortFilePath;
	pWnd->SetWindowText(titleProgress);
	curProgress.Format(CSAPARiNoMoreBumpsApp::GetString(IDS_WRITTINGFILES), 1, pWnd->m_Files.size());
	pWnd->m_CurrentProgress->SetWindowText(curProgress);
	int bumpResult;
	for (int i = 0; i < pWnd->m_Files.size(); i++)
	{
		bumpResult = Vscp::SetBumps(pWnd->m_Files[i].fileName, pWnd->m_Bumps);
		switch (bumpResult)
		{
		case 1:
			break;
		case -1:
			errBump = CSAPARiNoMoreBumpsApp::GetString(IDS_CANNOT_FIND_FILE);
			errBump.Replace("%d", pWnd->m_Files[i].fileName);
			AfxMessageBox(errBump, MB_OK|MB_ICONEXCLAMATION);
			break;
		case -2:
			errBump = CSAPARiNoMoreBumpsApp::GetString(IDS_CANNOT_OPEN_FILE);
			errBump.Replace("%d", pWnd->m_Files[i].fileName);
			AfxMessageBox(errBump, MB_OK|MB_ICONEXCLAMATION);
			break;
		case -3:
			errBump = CSAPARiNoMoreBumpsApp::GetString(IDS_CANNOT_WRITE_FILE);
			errBump.Replace("%d", pWnd->m_Files[i].fileName);
			AfxMessageBox(errBump, MB_OK|MB_ICONEXCLAMATION);
			break;
		case -4:
			errBump = CSAPARiNoMoreBumpsApp::GetString(IDS_UNABLE_WRITE_FILE);
			errBump.Replace("%d", pWnd->m_Files[i].fileName);
			AfxMessageBox(errBump, MB_OK|MB_ICONERROR);
			pWnd->EndDialog(-0x4);
			break;
		case -5:
			errBump = CSAPARiNoMoreBumpsApp::GetString(IDS_ACCESS_DENIED);
			errBump.Replace("%d", pWnd->m_Files[i].fileName);
			AfxMessageBox(errBump, MB_OK|MB_ICONEXCLAMATION);
			break;
		}
		int percent = (i+1) * 100 / pWnd->m_Files.size();
		curProgress.Format(CSAPARiNoMoreBumpsApp::GetString(IDS_WRITTINGFILES), i+1, pWnd->m_Files.size());
		shortFilePath = pWnd->m_Files[i].fileName;
		shortFilePath.Replace(Vscp::FindDirClient(), "...");
		titleProgress = "NoMoreBumps - " + shortFilePath;
		pWnd->SetWindowText(titleProgress);
		pWnd->m_CurrentProgress->SetWindowText(curProgress);
		pWnd->m_Progress->SetPos(percent);
	}
	TerminateIt(pWnd);
	return 0;
}

void CSAPARiNoMoreBumpsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		if (m_KeyPress == FALSE)
		{
			CAboutDlg dlgAbout;
			dlgAbout.DoModal();
		}
		else
		{
			m_KeyPress = FALSE;
			CMenu* pSysMenu = GetSystemMenu(FALSE);
			if (pSysMenu != NULL)
			{
				CString strAboutMenu;
				strAboutMenu.LoadString(IDS_ABOUTBOX);
				if (!strAboutMenu.IsEmpty())
					pSysMenu->ModifyMenu(IDM_ABOUTBOX, MF_BYCOMMAND | MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			}
			CQuestionMark dlgQ;
			dlgQ.DoModal();
		}
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSAPARiNoMoreBumpsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSAPARiNoMoreBumpsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSAPARiNoMoreBumpsDlg::OnCancel() 
{	
	CDialog::OnCancel();
}

void CSAPARiNoMoreBumpsDlg::OnRadioBoy() 
{
	m_Bumps = TRUE;
}

void CSAPARiNoMoreBumpsDlg::OnRadioPeng() 
{
	m_Bumps = FALSE;
}

void CSAPARiNoMoreBumpsDlg::OnOK() 
{
	m_BtnOk().EnableWindow(FALSE);
	m_Boy().EnableWindow(FALSE);
	m_Peng().EnableWindow(FALSE);
	m_Kame->Open(IDR_AVI_KAME);
	m_Progress->Create(WS_CHILD | WS_VISIBLE, CRect(5, 90, 390, 110), this, 0x16);
	m_Progress->SetRange32(1, 100);
	m_CurrentProgress->Create("", WS_CHILD | WS_VISIBLE, CRect(395, 90, 550, 110), this);
	EnableWindow(FALSE);
	m_pThread = AfxBeginThread(FileThread, this);
}

CSAPARiNoMoreBumpsDlg::~CSAPARiNoMoreBumpsDlg()
{
	if(m_pThread != NULL) 
	{
		::WaitForSingleObject(m_pThread->m_hThread, INFINITE);
		m_pThread = NULL;
	}
}

//https://learn.microsoft.com/en-us/cpp/mfc/reference/cfilefind-class?view=msvc-170#example-15
void CSAPARiNoMoreBumpsDlg::GetVRMLFiles(LPCTSTR dir)
{
	CFileFind finder;
	CFileStatus status;

	CString wrlpath;
	CString wrlname;
	CString wrlext;

	// build a string with wildcards
	CString strWildcard(dir);
	strWildcard += _T("\\*.*");

	BOOL noFolder = FALSE;
	CString dirFolder = CString(dir);
	dirFolder.MakeLower();
	if (dirFolder.Right(5) == "ko-en")
		noFolder = TRUE;
	if (dirFolder.Right(6) == "avtwrl")
		noFolder = TRUE;
	if (dirFolder.Right(6) == "mirror")
		noFolder = TRUE;
	if (dirFolder.Right(6) == "models")
		noFolder = TRUE;
	if (dirFolder.Right(6) == "object")
		noFolder = TRUE;
	if (dirFolder.Right(7) == "ukisima")
		noFolder = TRUE;
	if (dirFolder.Right(7) == "inlines")
		noFolder = TRUE;
	if (dirFolder.Right(8) == "base-spa")
		noFolder = TRUE;
	if (dirFolder.Right(9) == "component")
		noFolder = TRUE;
	if (dirFolder.Right(9) == "base-park")
		noFolder = TRUE;
	if (dirFolder.Right(10) == "base-coast")
		noFolder = TRUE;
	if (dirFolder.Right(10) == "base-hills")
		noFolder = TRUE;
	if (dirFolder.Right(10) == "base-honjo")
		noFolder = TRUE;
	if (dirFolder.Right(11) == "base-garden")
		noFolder = TRUE;
	if (dirFolder.Right(13) == "baseComponent")
		noFolder = TRUE;

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		  // skip . and .. files; otherwise, we'd
		  // recur infinitely!
		
		if (finder.IsDots())
			 continue;

		wrlext = finder.GetFilePath().Right(4);
		if (noFolder == FALSE)
		{
			if(wrlext == ".wrl")
			{
				if(CFile::GetStatus(finder.GetFilePath(), status))
				{
					wrlpath = finder.GetFilePath();
					wrlname = finder.GetFileName();
					wrlpath.Delete(wrlpath.GetLength() - wrlname.GetLength(), wrlname.GetLength());
				}
			}
			if (!wrlpath.IsEmpty())
			{
				if(CFile::GetStatus(wrlpath+wrlname, status))
				{
					if (m_Files.size() > 0)
					{
						int lastFileInd = CSAPARiNoMoreBumpsApp::LastIndexOfVector(m_Files);
						CString lastFile = m_Files[lastFileInd].fileName;
						if (lastFile != wrlpath+wrlname)
						{
							m_Files.push_back(structFiles());
							lastFileInd = CSAPARiNoMoreBumpsApp::LastIndexOfVector(m_Files);
							m_Files[lastFileInd].fileName = wrlpath+wrlname;
							m_Files[lastFileInd].bumps = Vscp::GetBumps(wrlpath+wrlname);
						}
					}
					else
					{
						m_Files.push_back(structFiles());
						int lastFileInd = CSAPARiNoMoreBumpsApp::LastIndexOfVector(m_Files);
						m_Files[lastFileInd].fileName = wrlpath+wrlname;
						m_Files[lastFileInd].bumps = Vscp::GetBumps(wrlpath+wrlname);
					}
				}
			}
		}

		// if it's a directory, recursively search it

		if (finder.IsDirectory())
			GetVRMLFiles(finder.GetFilePath());
	}

	finder.Close();
};

BOOL CSAPARiNoMoreBumpsDlg::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN && IsWindowVisible())
    {
        if(pMsg->wParam == VK_SHIFT)
		{
			m_KeyPress = TRUE;
			CMenu* pSysMenu = GetSystemMenu(FALSE);
			if (pSysMenu != NULL)
				pSysMenu->ModifyMenu(IDM_ABOUTBOX, MF_BYCOMMAND | MF_STRING, IDM_ABOUTBOX, "??");
		}

    }
	if(pMsg->message == WM_KEYUP)
    {
        if(pMsg->wParam == VK_SHIFT)
		{
			m_KeyPress = FALSE;
			CMenu* pSysMenu = GetSystemMenu(FALSE);
			if (pSysMenu != NULL)
			{
				CString strAboutMenu;
				strAboutMenu.LoadString(IDS_ABOUTBOX);
				if (!strAboutMenu.IsEmpty())
					pSysMenu->ModifyMenu(IDM_ABOUTBOX, MF_BYCOMMAND | MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			}
		}
    }
    return CDialog::PreTranslateMessage(pMsg);
}
