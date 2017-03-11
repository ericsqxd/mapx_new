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
		_bstr_t strConnect="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=MapX_access.mdb";//Home.mdb放在工程目录下
		m_pConnection->Open(strConnect,"","",adModeUnknown);
		AfxMessageBox("连接成功");
	}
	catch(_com_error e)
	{
		AfxMessageBox("连接失败");
	}
}

void AdoAccess::ExitConnect()
{
	CRescuekj2App *app = (CRescuekj2App *)AfxGetApp();
     if(app->m_pRecordset!=NULL)
    app->m_pRecordset->Close();
   m_pConnection->Close();
   ::CoUninitialize();
   AfxMessageBox("成功关闭");
}

void AdoAccess::Openace()
{
		CRescuekj2App *app = (CRescuekj2App *)AfxGetApp();
		app->m_pRecordset.CreateInstance("ADODB.Recordset");
		CString strTableName="MapX_ace1";
		app->m_pRecordset->Open(_variant_t(strTableName),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdTable);
}

void AdoAccess::Chaxun()
{
		_variant_t   var;
		CRescuekj2App *app = (CRescuekj2App *)AfxGetApp();
		CString strid,strname,strunit,strposition,info;
		try
		 {
		  if(!app->m_pRecordset->BOF)
				app->m_pRecordset->MoveFirst();
		  else
		  {
				AfxMessageBox("表内数据为空");
				return;
		  }
		  // 读入库中各字段并加入列表框中
		  while(!app->m_pRecordset->adoEOF)
		  {
			var = app->m_pRecordset->GetCollect("ID");
			if(var.vt != VT_NULL)
				strid = (LPCSTR)_bstr_t(var);
			var = app->m_pRecordset->GetCollect("NAME");
			if(var.vt != VT_NULL)
				strname = (LPCSTR)_bstr_t(var);
			var = app->m_pRecordset->GetCollect("UNIT");
			if(var.vt != VT_NULL)
				strunit = (LPCSTR)_bstr_t(var);
			var = app->m_pRecordset->GetCollect("POSITION");
			if(var.vt != VT_NULL)
				strposition = (LPCSTR)_bstr_t(var);
			app->m_pRecordset->MoveNext();
			info=strid+strname+strunit+strposition;
			AfxMessageBox(info);
		  }
		 }
		 catch(_com_error *e)
		 {
		  AfxMessageBox(e->ErrorMessage());
		 }
}
AdoAccess::AdoAccess()
{

}

AdoAccess::~AdoAccess()
{

}
