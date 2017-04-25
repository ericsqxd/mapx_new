// rescuekj2.h : main header file for the RESCUEKJ2 application
//

#if !defined(AFX_RESCUEKJ2_H__C5E8F109_BC51_465C_8BFF_85683088F869__INCLUDED_)
#define AFX_RESCUEKJ2_H__C5E8F109_BC51_465C_8BFF_85683088F869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "mscomm.h"
/////////////////////////////////////////////////////////////////////////////
// CRescuekj2App:
// See rescuekj2.cpp for the implementation of this class
//

class CRescuekj2App : public CWinApp
{
public:
	CRescuekj2App();
	 _RecordsetPtr    m_pRecordset; // √¸¡Ó
	 CMSComm	m_ctrlComm;
	 CString strname,str_status,str_phone1,str_phone2;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRescuekj2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRescuekj2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESCUEKJ2_H__C5E8F109_BC51_465C_8BFF_85683088F869__INCLUDED_)
