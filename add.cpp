// add.cpp : implementation file
//

#include "stdafx.h"
#include "rescuekj2.h"
#include "add.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// add dialog


add::add(CWnd* pParent /*=NULL*/)
	: CDialog(add::IDD, pParent)
{
	//{{AFX_DATA_INIT(add)
	m_edit_id = _T("");
	m_edit_name = _T("");
	m_edit_group = _T("");
	m_edit_job = _T("");
	//}}AFX_DATA_INIT
}


void add::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(add)
	DDX_Text(pDX, IDC_EDIT1_ID, m_edit_id);
	DDX_Text(pDX, IDC_EDIT2_NAME, m_edit_name);
	DDX_Text(pDX, IDC_EDIT3_GROUP, m_edit_group);
	DDX_Text(pDX, IDC_EDIT4_JOB, m_edit_job);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(add, CDialog)
	//{{AFX_MSG_MAP(add)
	ON_BN_CLICKED(IDOK, OnAddOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// add message handlers
//UpdateData(true);//用于将屏幕上控件中的数据交换到变量中。
//UpdateData(false);//用于将数据在屏幕中对应控件中显示出来。

void add::OnAddOK() 
{
	// TODO: Add your control notification handler code here
	CString str;
	UpdateData(true);
	CRescuekj2App *app = (CRescuekj2App *)AfxGetApp();
	app->m_pRecordset->AddNew();                  
	app->m_pRecordset->PutCollect(_variant_t("ID"),_variant_t(m_edit_id));                  
	app->m_pRecordset->PutCollect(_variant_t("NAME"),_variant_t(m_edit_name));
	app->m_pRecordset->PutCollect(_variant_t("UNIT"),_variant_t(m_edit_group));
	app->m_pRecordset->PutCollect(_variant_t("POSITION"),_variant_t(m_edit_job));
	app->m_pRecordset->Update();//更新数据库-将新纪录存入数据库
	AfxMessageBox("添加成功");

	CDialog::OnOK();
}
