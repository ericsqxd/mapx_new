#if !defined(AFX_INFO_H__C13460A8_57FF_447B_876A_A7F0208407FF__INCLUDED_)
#define AFX_INFO_H__C13460A8_57FF_447B_876A_A7F0208407FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// info.h : header file

//#include "rescuekj2View.h"

/////////////////////////////////////////////////////////////////////////////
// info dialog

class info : public CDialog
{
// Construction
public:
	info(CWnd* pParent = NULL);   // standard constructor
	void Show_info(int id,CString name,int bloodshou,int bloodshu,int beat,double temper);
	void Initial();
// Dialog Data
	//{{AFX_DATA(info)
	enum { IDD = IDD_INFO };
	CStatic	m_showname;
	CStatic	m_temper;
	CStatic	m_bloodshu;
	CStatic	m_bloodshou;
	CStatic	m_pinggu;
	CStatic	m_beat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(info)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int cid;
	CList <CRect,CRect> listRect;
	// Generated message map functions
	//{{AFX_MSG(info)
	afx_msg void OnButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFO_H__C13460A8_57FF_447B_876A_A7F0208407FF__INCLUDED_)
