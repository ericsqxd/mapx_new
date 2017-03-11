// rescuekj2Doc.h : interface of the CRescuekj2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESCUEKJ2DOC_H__B25E4B58_F1BB_4404_88A9_57C7D9979EB5__INCLUDED_)
#define AFX_RESCUEKJ2DOC_H__B25E4B58_F1BB_4404_88A9_57C7D9979EB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRescuekj2Doc : public CDocument
{
protected: // create from serialization only
	CRescuekj2Doc();
	DECLARE_DYNCREATE(CRescuekj2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRescuekj2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRescuekj2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRescuekj2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESCUEKJ2DOC_H__B25E4B58_F1BB_4404_88A9_57C7D9979EB5__INCLUDED_)
