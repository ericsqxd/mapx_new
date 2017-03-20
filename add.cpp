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
	m_edit_age = _T("");
	m_edit_sex = _T("");
	m_edit_xuexing = _T("");
	m_edit_phone1 = _T("");
	m_edit_phone2 = _T("");
	m_edit_phone3 = _T("");
	m_edit_phone4 = _T("");
	m_edit_phone5 = _T("");
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
	DDX_Text(pDX, IDC_EDIT_AGE, m_edit_age);
	DDX_Text(pDX, IDC_EDIT_SEX, m_edit_sex);
	DDX_Text(pDX, IDC_EDIT_XUEXING, m_edit_xuexing);
	DDX_Text(pDX, IDC_EDIT_PHONE1, m_edit_phone1);
	DDX_Text(pDX, IDC_EDIT_PHONE2, m_edit_phone2);
	DDX_Text(pDX, IDC_EDIT_PHONE3, m_edit_phone3);
	DDX_Text(pDX, IDC_EDIT_PHONE4, m_edit_phone4);
	DDX_Text(pDX, IDC_EDIT_PHONE5, m_edit_phone5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(add, CDialog)
	//{{AFX_MSG_MAP(add)
	ON_BN_CLICKED(IDOK, OnAddOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// add message handlers
//UpdateData(true);//���ڽ���Ļ�Ͽؼ��е����ݽ����������С�
//UpdateData(false);//���ڽ���������Ļ�ж�Ӧ�ؼ�����ʾ������

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
	app->m_pRecordset->PutCollect(_variant_t("SEX"),_variant_t(m_edit_sex));                  
	app->m_pRecordset->PutCollect(_variant_t("AGE"),_variant_t(m_edit_age));
	app->m_pRecordset->PutCollect(_variant_t("BLOODTYPE"),_variant_t(m_edit_xuexing));
	app->m_pRecordset->PutCollect(_variant_t("PHONE1"),_variant_t(m_edit_phone1));
	app->m_pRecordset->PutCollect(_variant_t("PHONE2"),_variant_t(m_edit_phone2));                  
	app->m_pRecordset->PutCollect(_variant_t("PHONE3"),_variant_t(m_edit_phone3));
	app->m_pRecordset->PutCollect(_variant_t("PHONE4"),_variant_t(m_edit_phone4));
	app->m_pRecordset->PutCollect(_variant_t("PHONE5"),_variant_t(m_edit_phone5));
	app->m_pRecordset->Update();//�������ݿ�-���¼�¼�������ݿ�
	AfxMessageBox("��ӳɹ�");

	CDialog::OnOK();
}
