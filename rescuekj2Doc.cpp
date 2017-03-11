// rescuekj2Doc.cpp : implementation of the CRescuekj2Doc class
//

#include "stdafx.h"
#include "rescuekj2.h"
#include "rescuekj2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2Doc

IMPLEMENT_DYNCREATE(CRescuekj2Doc, CDocument)

BEGIN_MESSAGE_MAP(CRescuekj2Doc, CDocument)
	//{{AFX_MSG_MAP(CRescuekj2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2Doc construction/destruction

CRescuekj2Doc::CRescuekj2Doc()
{
	// TODO: add one-time construction code here

}

CRescuekj2Doc::~CRescuekj2Doc()
{

}

BOOL CRescuekj2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle("Rescue");

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRescuekj2Doc serialization

void CRescuekj2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2Doc diagnostics

#ifdef _DEBUG
void CRescuekj2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRescuekj2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2Doc commands
