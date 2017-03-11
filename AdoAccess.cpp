// AdoAccess.cpp : implementation file
//

#include "stdafx.h"
#include "rescuekj2.h"
#include "AdoAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AdoAccess

IMPLEMENT_DYNAMIC(AdoAccess, CRecordset)

AdoAccess::AdoAccess(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(AdoAccess)
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString AdoAccess::GetDefaultConnect()
{
	return _T("ODBC;DSN=");
}

CString AdoAccess::GetDefaultSQL()
{
	return _T("");
}

void AdoAccess::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(AdoAccess)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// AdoAccess diagnostics

#ifdef _DEBUG
void AdoAccess::AssertValid() const
{
	CRecordset::AssertValid();
}

void AdoAccess::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
