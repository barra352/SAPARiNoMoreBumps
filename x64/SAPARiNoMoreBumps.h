// SAPARiNoMoreBumps.h : main header file for the SAPARINOMOREBUMPS application
//

#if !defined(AFX_SAPARINOMOREBUMPS_H__C5642F30_6516_431D_B14B_F56643F126F0__INCLUDED_)
#define AFX_SAPARINOMOREBUMPS_H__C5642F30_6516_431D_B14B_F56643F126F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SAPARiNoMoreBumpsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSAPARiNoMoreBumpsApp:
// See SAPARiNoMoreBumps.cpp for the implementation of this class
//

class CSAPARiNoMoreBumpsApp : public CWinApp
{
public:
	CSAPARiNoMoreBumpsApp();
	static CString GetString(UINT uID); //Gets String from resources.
	static int LastIndexOfVector(std::vector<CSAPARiNoMoreBumpsDlg::structFiles> vector);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAPARiNoMoreBumpsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSAPARiNoMoreBumpsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAPARINOMOREBUMPS_H__C5642F30_6516_431D_B14B_F56643F126F0__INCLUDED_)
