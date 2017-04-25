// info.cpp : implementation file
//

#include "stdafx.h"
#include "rescuekj2.h"
#include "info.h"
#include "MapX.h"
//#include "rescuekj2View.h"

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
	DDX_Control(pDX, IDC_STATIC_TEMP, m_temper);
	DDX_Control(pDX, IDC_STATIC_SHU, m_bloodshu);
	DDX_Control(pDX, IDC_STATIC_SHOU, m_bloodshou);
	DDX_Control(pDX, IDC_STATIC_PINGGU, m_pinggu);
	DDX_Control(pDX, IDC_STATIC_BEAT, m_beat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(info, CDialog)
	//{{AFX_MSG_MAP(info)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// info message handlers
void info::Show_info(int id,CString name,int bloodshou,int bloodshu,int beat,double temper)
{

	CString str1,str2,str3,str4;
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	str1.Format("%d mmHg",bloodshou);
	m_bloodshou.SetWindowText(str1);
	str2.Format("%d mmHg",bloodshu);
	m_bloodshu.SetWindowText(str2);
	str3.Format("%d ��/min",beat);
	m_beat.SetWindowText(str3);
	str4.Format("%0.1lf ��",temper);
	m_temper.SetWindowText(str4);

	cid = id;

	m_showname.SetWindowText(name);
	if(bloodshou>=90&&bloodshou<=140&&bloodshu>=60&&bloodshu<=90&&beat>=60&&beat<=100&&temper>=36.5&&temper<=37.5)
		spp->str_status="����";
	else if(bloodshou>60&&bloodshou<90||bloodshu>30&&bloodshu<60||beat<60||temper<36.5||temper>37.5)
		spp->str_status="����";
	else if(bloodshou>0&&bloodshou<30||bloodshu>0&&bloodshu<30||beat<30||temper<35.5||temper>38.5)
		spp->str_status="����";
	else if(bloodshou==0||bloodshu==0||beat==0||temper<34.5)
		spp->str_status="����";
	else if(bloodshou==255&&bloodshu==255&&beat==255&&temper==17.3)
		spp->str_status="δ֪";
	m_pinggu.SetWindowText(spp->str_status);
}
void info::Initial()
{
	CString str1,str2,str3,str4,str5,str7;
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
	str3.Format("%d ��/min",beat);
	m_beat.SetWindowText(str3);
	str4.Format("%0.1lf ��",temper);
	m_temper.SetWindowText(str4);
	str7="";
	m_showname.SetWindowText(str7);

	str5="����";
	m_pinggu.SetWindowText(str5);

	/******   �ؼ���ȡ��ʼ    *******/
	CRect rectWnd;
    GetWindowRect(&rectWnd);//�õ���ǰ�Ի��������
    listRect.AddTail(&rectWnd);//��������ӵ�����listRect��ĩβ
    CWnd *pWndChild=GetWindow(GW_CHILD);
    while (pWndChild)//���εõ��Ի����Ͽؼ������꣬�������еĿؼ�����洢��������
	{
        pWndChild->GetWindowRect(&rectWnd);
        listRect.AddTail(&rectWnd);//�������ν��ؼ�������ӵ�����ĩβ�����Կ�ͷ�������ǶԻ��������
        pWndChild=pWndChild->GetNextWindow();
	}
	
	/******   �ؼ���ȡ���˽���    *******/
}



void info::OnButton1() 
{
	// TODO: Add your control notification handler code here

	::SendMessage(this->GetParent()->GetParent()->m_hWnd, WM_MY_MESSAGE ,cid, 0);
}

void info::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(listRect.GetCount()>0)//�������Ƿ�Ϊ��
	{
		CRect rectDlgNow;
		GetWindowRect(&rectDlgNow);//�õ���ǰ�Ի��������
		POSITION mp=listRect.GetHeadPosition();//ȡ�ô洢�������е�ͷԪ�أ���ʵ����ǰ�ߵĶԻ�������
		CRect rectDlgSaved;
		rectDlgSaved=listRect.GetNext(mp);
		ScreenToClient(rectDlgNow);
		float fRateScaleX=(float)(rectDlgNow.right-rectDlgNow.left)/(rectDlgSaved.right-rectDlgSaved.left);//������Ĵ��ڴ�С��ԭ�����ڴ�С�ı���
		float fRateScaleY=(float)(rectDlgNow.bottom-rectDlgNow.top)/(rectDlgSaved.bottom-rectDlgSaved.top);
		ClientToScreen(rectDlgNow);
		CRect rectChildSaved;
		CWnd *pWndChild=GetWindow(GW_CHILD);
		
		CRect rc;
		
		CString strtmp;
		//��ǰ�������ſؼ���TABֵ
		while (pWndChild)
		{
			rectChildSaved=listRect.GetNext(mp);
			rectChildSaved.left=rectDlgNow.left+(int)((rectChildSaved.left-rectDlgSaved.left)*fRateScaleX);
			rectChildSaved.top=rectDlgNow.top+(int)((rectChildSaved.top-rectDlgSaved.top)*fRateScaleY);
			rectChildSaved.right=rectDlgNow.right+(int)((rectChildSaved.right-rectDlgSaved.right)*fRateScaleX);
			rectChildSaved.bottom=rectDlgNow.bottom+(int)((rectChildSaved.bottom-rectDlgSaved.bottom)*fRateScaleY);
			ScreenToClient(rectChildSaved);
			pWndChild->MoveWindow(rectChildSaved);
			pWndChild = pWndChild->GetNextWindow();
		}
	}
        Invalidate(); //ǿ���ػ洰��	
}
