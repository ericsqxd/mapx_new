#if !defined(AFX_GONGLV_H__A1D1D808_F02E_48EB_AA17_4E1D1C2656AC__INCLUDED_)
#define AFX_GONGLV_H__A1D1D808_F02E_48EB_AA17_4E1D1C2656AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gonglv.h : header file
//
#include "BarChart.h "
/////////////////////////////////////////////////////////////////////////////
// gonglv dialog

class gonglv : public CDialog
{
// Construction
public:
	gonglv(CWnd* pParent = NULL);   // standard constructor
	void Show_gonglv(int gl[]);
	void Initial_gonglv();
// Dialog Data
	//{{AFX_DATA(gonglv)
	enum { IDD = IDD_GONGLV };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(gonglv)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBarChart	m_chart;
	CList <CRect,CRect> listRect;
	// Generated message map functions
	//{{AFX_MSG(gonglv)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GONGLV_H__A1D1D808_F02E_48EB_AA17_4E1D1C2656AC__INCLUDED_)
