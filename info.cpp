// info.cpp : implementation file
//

#include "stdafx.h"
#include "rescuekj2.h"
#include "info.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// info dialog


info::info(CWnd* pParent /*=NULL*/)
	: CDialog(info::IDD, pParent)
{
	//{{AFX_DATA_INIT(info)
	//}}AFX_DATA_INIT
}


void info::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(info)
	DDX_Control(pDX, IDC_STATIC_NAME, m_showname);
	DDX_Control(pDX, IDC_STATIC_ID, m_showid);
	DDX_Control(pDX, IDC_STATIC_TEMP, m_temper);
	DDX_Control(pDX, IDC_STATIC_SHU, m_bloodshu);
	DDX_Control(pDX, IDC_STATIC_SHOU, m_bloodshou);
	DDX_Control(pDX, IDC_STATIC_PINGGU, m_pinggu);
	DDX_Control(pDX, IDC_STATIC_BEAT, m_beat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(info, CDialog)
	//{{AFX_MSG_MAP(info)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// info message handlers
void info::Show_info(int id,CString name,int bloodshou,int bloodshu,int beat,double temper)
{

	CString str1,str2,str3,str4,str5,str6;
	str1.Format("%d mmHg",bloodshou);
	m_bloodshou.SetWindowText(str1);
	str2.Format("%d mmHg",bloodshu);
	m_bloodshu.SetWindowText(str2);
	str3.Format("%d 跳/分钟",beat);
	m_beat.SetWindowText(str3);
	str4.Format("%0.1lf ℃",temper);
	m_temper.SetWindowText(str4);
	str6.Format("%d",id);
	m_showid.SetWindowText(str6);
	m_showname.SetWindowText(name);
	if(bloodshou>=90&&bloodshou<=140&&bloodshu>=60&&bloodshu<=90&&beat>=60&&beat<=100&&temper>=35&&temper<=38)
		str5="正常";
	else //if(bloodshou>=90&&bloodshou<=140&&bloodshu>=60&&bloodshu<=90&&beat>=60&&beat<=100&&temper>=35&&temper<=38)
		str5="轻伤";
	m_pinggu.SetWindowText(str5);
}
void info::Initial()
{
	CString str1,str2,str3,str4,str5,str6,str7;
	double temper;
	int bloodshou,bloodshu,beat;
	bloodshou=0;
	bloodshu=0;
	temper=0;
	beat=0;
	str1.Format("%d mmHg",bloodshou);
	m_bloodshou.SetWindowText(str1);
	str2.Format("%d mmHg",bloodshu);
	m_bloodshu.SetWindowText(str2);
	str3.Format("%d 跳/分钟",beat);
	m_beat.SetWindowText(str3);
	str4.Format("%0.1lf ℃",temper);
	m_temper.SetWindowText(str4);
	str6="0";
	str7="";
	m_showid.SetWindowText(str6);
	m_showname.SetWindowText(str7);

	str5="正常";
	m_pinggu.SetWindowText(str5);
}
