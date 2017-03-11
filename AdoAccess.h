#if !defined(AFX_ADOACCESS_H__5A4C4AF4_0DF9_41FF_93E8_ABABC30AAB6A__INCLUDED_)
#define AFX_ADOACCESS_H__5A4C4AF4_0DF9_41FF_93E8_ABABC30AAB6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdoAccess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AdoAccess recordset

class AdoAccess : public CRecordset
{
public:
	AdoAccess(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(AdoAccess)

// Field/Param Data
	//{{AFX_FIELD(AdoAccess, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AdoAccess)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADOACCESS_H__5A4C4AF4_0DF9_41FF_93E8_ABABC30AAB6A__INCLUDED_)
