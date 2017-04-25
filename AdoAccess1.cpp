// AdoAccess1.cpp: implementation of the AdoAccess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "rescuekj2.h"
#include "AdoAccess1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void AdoAccess::OnInitADOConn()
{
::CoInitialize(NULL);
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		_bstr_t strConnect="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=MapX_access.mdb";//Home.mdb���ڹ���Ŀ¼��
		m_pConnection->Open(strConnect,"","",adModeUnknown);
		//AfxMessageBox("���ӳɹ�");
	}
	catch(_com_error e)
	{
		AfxMessageBox("����ʧ��");
	}
}

void AdoAccess::ExitConnect()
{
	CRescuekj2App *app = (CRescuekj2App *)AfxGetApp();
     if(app->m_pRecordset!=NULL)
    app->m_pRecordset->Close();
   m_pConnection->Close();
   ::CoUninitialize();
   AfxMessageBox("�ɹ��ر�");
}

void AdoAccess::Openace()
{
		CRescuekj2App *app = (CRescuekj2App *)AfxGetApp();
		app->m_pRecordset.CreateInstance("ADODB.Recordset");
		CString strTableName="MapX_ace1";
		app->m_pRecordset->Open(_variant_t(strTableName),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdTable);
}

bool AdoAccess::Chaxun(int id)
{
		_variant_t   var;
		CRescuekj2App *app = (CRescuekj2App *)AfxGetApp();
		CString strtmp;
		int cid;
		try
		 {
		  if(!app->m_pRecordset->BOF)
				app->m_pRecordset->MoveFirst();
		  else
		  {
				AfxMessageBox("��������Ϊ��");
				return false;
		  }
		  // ������и��ֶβ������б����
		  while(!app->m_pRecordset->adoEOF)
		  {
			var = app->m_pRecordset->GetCollect("ID");
			cid=_ttoi((LPCTSTR)(_bstr_t)var);
			if(cid!=id)
			{
				app->m_pRecordset->MoveNext();
				continue;
			}
			return true;
		  }
		if(app->m_pRecordset->adoEOF==NULL)
		{
			strtmp.Format("δ��ѯ��IDΪ%d���û�!",id);
			AfxMessageBox(strtmp);
			return false;
		}
		 }
		 catch(_com_error *e)
		 {
		  AfxMessageBox(e->ErrorMessage());
		  return false;
		 }
}
void AdoAccess::Write(int id,CString strst,double lgtd,double latd,int height,int bloodshou,int bloodzh,int beat,double temper)
{
		CString str;
		m_pRecordWrite.CreateInstance("ADODB.Recordset");
		CString strTableName="MapX_Receive";
		m_pRecordWrite->Open(_variant_t(strTableName),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdTable);
		m_pRecordWrite->AddNew();
		str.Format("%d",id);
		m_pRecordWrite->PutCollect(_variant_t("ID"),_variant_t(str));                  
		m_pRecordWrite->PutCollect(_variant_t("TIME"),_variant_t(strst));
		str.Format("%0.2lf",lgtd);
		m_pRecordWrite->PutCollect(_variant_t("LONGITUDE"),_variant_t(str));
		str.Format("%0.2lf",latd);
		m_pRecordWrite->PutCollect(_variant_t("LATITUDE"),_variant_t(str));
		str.Format("%d",height);
		m_pRecordWrite->PutCollect(_variant_t("HEIGHT"),_variant_t(str)); 
		str.Format("%d",bloodshou);
		m_pRecordWrite->PutCollect(_variant_t("BLOODSHOU"),_variant_t(str));
		str.Format("%d",bloodzh);
		m_pRecordWrite->PutCollect(_variant_t("BLOODSHU"),_variant_t(str));
		m_pRecordWrite->PutCollect(_variant_t("TEMPERATURE"),_variant_t(temper));
		str.Format("%d",beat);
		m_pRecordWrite->PutCollect(_variant_t("HEARTBEAT"),_variant_t(str));
		m_pRecordWrite->Update();//�������ݿ�-���¼�¼�������ݿ�
		m_pRecordWrite->Close();
		//AfxMessageBox("��ӳɹ�");		
}
AdoAccess::AdoAccess()
{

}

AdoAccess::~AdoAccess()
{

}


void AdoAccess::show_rescue(int id)
{
	_variant_t   var;
	CRescuekj2App *app = (CRescuekj2App *)AfxGetApp();
	CString strid,strunit,strposition,info,strtmp,strsex,strage;
	int cid;
	if(!app->m_pRecordset->BOF)
		app->m_pRecordset->MoveFirst();
	while(!app->m_pRecordset->adoEOF)
		{
			  var = app->m_pRecordset->GetCollect("ID");
			  cid=_ttoi((LPCTSTR)(_bstr_t)var);
			  if(cid!=id)
			  {
				app->m_pRecordset->MoveNext();
				continue;
			  }
			  break;
		}
		var = app->m_pRecordset->GetCollect("NAME");
		if(var.vt != VT_NULL)
			app->strname = (LPCSTR)_bstr_t(var);
		var = app->m_pRecordset->GetCollect("UNIT");
		if(var.vt != VT_NULL)
				strunit = (LPCSTR)_bstr_t(var);
			
		var = app->m_pRecordset->GetCollect("SEX");
		if(var.vt != VT_NULL)
				strsex = (LPCSTR)_bstr_t(var);
			
		var = app->m_pRecordset->GetCollect("AGE");
		if(var.vt != VT_NULL)
				strage = (LPCSTR)_bstr_t(var);
			
		var = app->m_pRecordset->GetCollect("PHONE1");
		if(var.vt != VT_NULL)
				app->str_phone1 = (LPCSTR)_bstr_t(var);
			
		var = app->m_pRecordset->GetCollect("PHONE4");
		if(var.vt != VT_NULL)
				app->str_phone2 = (LPCSTR)_bstr_t(var);
			
		var = app->m_pRecordset->GetCollect("POSITION");
		if(var.vt != VT_NULL)
				strposition = (LPCSTR)_bstr_t(var);
		info.Format(_T("ID: %d       ����:%s\n�Ա�:%s         ����:%s\n��λ:%s\nְ��:%s\n"),cid,app->strname,strsex,strage,strunit,strposition);
			//AfxMessageBox(info);
		MessageBox(NULL,info,"�����Ϣ",0);
}