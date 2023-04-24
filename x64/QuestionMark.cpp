// QuestionMark.cpp : implementation file
//

#include "stdafx.h"
#include "SAPARiNoMoreBumps.h"
#include "QuestionMark.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuestionMark dialog


CQuestionMark::CQuestionMark(CWnd* pParent /*=NULL*/)
	: CDialog(CQuestionMark::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuestionMark)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Q = new CAnimateCtrl;
}


void CQuestionMark::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuestionMark)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuestionMark, CDialog)
	//{{AFX_MSG_MAP(CQuestionMark)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuestionMark message handlers

BOOL CQuestionMark::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Q->Create(WS_CHILD | WS_VISIBLE | ACS_AUTOPLAY, CRect(0, 0, 387, 290), this, 0x2020);
	m_Q->Open(IDR_AVI_H);

	SetWindowText("??");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
