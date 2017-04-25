// gonglv.cpp : implementation file
//

#include "stdafx.h"
#include "rescuekj2.h"
#include "gonglv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// gonglv dialog


gonglv::gonglv(CWnd* pParent /*=NULL*/)
	: CDialog(gonglv::IDD, pParent)
{
	//{{AFX_DATA_INIT(gonglv)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void gonglv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(gonglv)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(gonglv, CDialog)
	//{{AFX_MSG_MAP(gonglv)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// gonglv message handlers

void gonglv::Show_gonglv(int gl[]) 
{
	// TODO: Add your control notification handler code here
	CRect rcClient;
	GetClientRect(&rcClient);

	if (!m_chart.Create(CRect(20, 10, 
			rcClient.Width()-10, 
			rcClient.Height() - 10), this, 0 ))
	{
		if (!m_chart.GetSafeHwnd())
		{
			AfxMessageBox("Unable to create the chart control");
			return;
		}

		m_chart.Reset();
//		m_chart.SetAutoScale(FALSE);
	}

	//m_chart.SetTitle("���������ʼ��");
	m_chart.SetBKColor(RGB(255, 255, 240));
	m_chart.ShowTooltip(FALSE);

	m_chart.AddBar(gl[0],"    1", RGB(0,255,0));
	m_chart.AddBar(gl[1],"    2", RGB(0,255,0));
	m_chart.AddBar(gl[2],"    3", RGB(0,255,0));
	m_chart.AddBar(gl[3],"    4", RGB(0,255,0));
	m_chart.AddBar(gl[4],"    5", RGB(0,255,0));
	m_chart.AddBar(gl[5],"    6", RGB(0,255,0));
	m_chart.AddBar(gl[6],"    7", RGB(0,255,0));
	m_chart.AddBar(gl[7],"    8", RGB(0,255,0));
	m_chart.AddBar(gl[8],"    9", RGB(0,255,0));
	m_chart.AddBar(gl[9],"   10", RGB(0,255,0));

	m_chart.Refresh();


}
void gonglv::Initial_gonglv() 
{
	// TODO: Add your control notification handler code here
	CRect rcClient;
	GetClientRect(&rcClient);

	if (!m_chart.Create(CRect(20, 10, 
			rcClient.Width()-10, 
			rcClient.Height() - 10), this, 0 ))
	{
		if (!m_chart.GetSafeHwnd())
		{
			AfxMessageBox("Unable to create the chart control");
			return;
		}

		m_chart.Reset();
//		m_chart.SetAutoScale(FALSE);
	}

	m_chart.SetTitle("���������ʼ��");
	m_chart.SetBKColor(RGB(255, 255, 240));
	m_chart.ShowTooltip(FALSE);

	m_chart.AddBar(0,"    1", RGB(0,255,0));
	m_chart.AddBar(0,"    2", RGB(0,255,0));
	m_chart.AddBar(0,"    3", RGB(0,255,0));
	m_chart.AddBar(0,"    4", RGB(0,255,0));
	m_chart.AddBar(0,"    5", RGB(0,255,0));
	m_chart.AddBar(0,"    6", RGB(0,255,0));
	m_chart.AddBar(0,"    7", RGB(0,255,0));
	m_chart.AddBar(0,"    8", RGB(0,255,0));
	m_chart.AddBar(0,"    9", RGB(0,255,0));
	m_chart.AddBar(0,"   10", RGB(0,255,0));

	m_chart.Refresh();

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

void gonglv::OnSize(UINT nType, int cx, int cy) 
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
