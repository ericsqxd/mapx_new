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

	//m_chart.SetTitle("各波束功率检测");
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

	m_chart.SetTitle("各波束功率检测");
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

	/******   控件获取开始    *******/
	CRect rectWnd;
    GetWindowRect(&rectWnd);//得到当前对话框的坐标
    listRect.AddTail(&rectWnd);//将坐标添加到链表listRect的末尾
    CWnd *pWndChild=GetWindow(GW_CHILD);
    while (pWndChild)//依次得到对话框上控件的坐标，并将所有的控件坐标存储在链表中
	{
        pWndChild->GetWindowRect(&rectWnd);
        listRect.AddTail(&rectWnd);//由于依次将控件坐标添加到链表末尾，所以开头的坐标是对话框的坐标
        pWndChild=pWndChild->GetNextWindow();
	}
	
	/******   控件获取到此结束    *******/
}

void gonglv::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(listRect.GetCount()>0)//看链表是否为空
	{
		CRect rectDlgNow;
		GetWindowRect(&rectDlgNow);//得到当前对话框的坐标
		POSITION mp=listRect.GetHeadPosition();//取得存储在链表中的头元素，其实就是前边的对话框坐标
		CRect rectDlgSaved;
		rectDlgSaved=listRect.GetNext(mp);
		ScreenToClient(rectDlgNow);
		float fRateScaleX=(float)(rectDlgNow.right-rectDlgNow.left)/(rectDlgSaved.right-rectDlgSaved.left);//拖拉后的窗口大小与原来窗口大小的比例
		float fRateScaleY=(float)(rectDlgNow.bottom-rectDlgNow.top)/(rectDlgSaved.bottom-rectDlgSaved.top);
		ClientToScreen(rectDlgNow);
		CRect rectChildSaved;
		CWnd *pWndChild=GetWindow(GW_CHILD);
		
		CRect rc;
		
		CString strtmp;
		//当前处理缩放控件的TAB值
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
        Invalidate(); //强制重绘窗口	
}
