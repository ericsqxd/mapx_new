// rescuekj2View.h : interface of the CRescuekj2View class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_RESCUEKJ2VIEW_H__4E656EE2_CAFA_4443_BA9E_DC2F7A72FBA4__INCLUDED_)
#define AFX_RESCUEKJ2VIEW_H__4E656EE2_CAFA_4443_BA9E_DC2F7A72FBA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MapX.h"
#include "add.h"
#include "stdafx.h"
#include "AdoAccess1.h"
#include <time.h>

class CRescuekj2View : public CFormView
{
protected: // create from serialization only
	CRescuekj2View();
	DECLARE_DYNCREATE(CRescuekj2View)
	void CRescuekj2View::guiji(double y, double x);
public:
	BOOL m_bFlash;
	//{{AFX_DATA(CRescuekj2View)
	enum { IDD = IDD_RESCUEKJ2_FORM };
	CComboBox	m_ParityCheck_M;
	CComboBox	m_StopBit_M;
	CComboBox	m_Date_Select_M;
	CComboBox	m_BaudRate_M;
	CComboBox	m_ComboBox;
	CMSComm	m_ctrlComm;
	CString	m_strRXData;
	int		m_Index;
	int		m_BaudRate;
	int		m_Date_Select;
	int		m_StopBit;
	int		m_ParityCheck;
	//}}AFX_DATA

// Attributes
public:
	CRescuekj2Doc* GetDocument();
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRescuekj2View)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRescuekj2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
		CMapX m_ctrlMapX;
		CList <CRect,CRect> listRect;
		CMapXFeature xt;
		double yg,xg;
		AdoAccess myAccess;
// Generated message map functions
protected:
	//{{AFX_MSG(CRescuekj2View)
	afx_msg void OnAdd();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnMovePan();
	afx_msg void OnCenter();
	afx_msg void OnTuCengSet();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCommMscomm1();
	afx_msg void OnSelchangeComboPort();
	afx_msg void OnSelchangeComboBote();
	afx_msg void OnSelchangeComboData();
	afx_msg void OnSelchangeComboStop();
	afx_msg void OnSelchangeComboJiaoyan();
	afx_msg void OnPortOpen();
	afx_msg void OnCeshi();
	afx_msg void OnJiantou();
	afx_msg void OnAppExit();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in rescuekj2View.cpp
inline CRescuekj2Doc* CRescuekj2View::GetDocument()
   { return (CRescuekj2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESCUEKJ2VIEW_H__4E656EE2_CAFA_4443_BA9E_DC2F7A72FBA4__INCLUDED_)
