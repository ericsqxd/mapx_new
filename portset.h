#if !defined(AFX_PORTSET_H__EC94E641_F398_49FB_94CF_823E9A2002B8__INCLUDED_)
#define AFX_PORTSET_H__EC94E641_F398_49FB_94CF_823E9A2002B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// portset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// portset dialog

class portset : public CDialog
{
// Construction
public:
	portset(CWnd* pParent = NULL);   // standard constructor
	void Oninitial();
// Dialog Data
	//{{AFX_DATA(portset)
	enum { IDD = IDD_PORT };
	CComboBox	m_ParityCheck_M;
	CComboBox	m_StopBit_M;
	CComboBox	m_Date_Select_M;
	CComboBox	m_BaudRate_M;
	CComboBox	m_ComboBox;
	int		m_Index;
	int		m_BaudRate;
	int		m_Date_Select;
	int		m_StopBit;
	int		m_ParityCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(portset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(portset)
	afx_msg void OnButtonOpen();
	afx_msg void OnSelchangeComboBote();
	afx_msg void OnSelchangeComboData();
	afx_msg void OnSelchangeComboJiaoyan();
	afx_msg void OnSelchangeComboPort();
	afx_msg void OnSelchangeComboStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORTSET_H__EC94E641_F398_49FB_94CF_823E9A2002B8__INCLUDED_)
