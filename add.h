#if !defined(AFX_ADD_H__0229900E_286C_4565_B8F5_1CF644234874__INCLUDED_)
#define AFX_ADD_H__0229900E_286C_4565_B8F5_1CF644234874__INCLUDED_

#include "AdoAccess1.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// add.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// add dialog

class add : public CDialog
{
// Construction
public:
	add(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(add)
	enum { IDD = IDD_DIALOG1 };
	CString	m_edit_id;
	CString	m_edit_name;
	CString	m_edit_group;
	CString	m_edit_job;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(add)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(add)
	afx_msg void OnAddOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADD_H__0229900E_286C_4565_B8F5_1CF644234874__INCLUDED_)
