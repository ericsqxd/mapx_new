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
//	ON_BN_CLICKED(IDC_BUTTON1, OnButton_gonglv)
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

	m_chart.SetTitle("各波束通道功率检测");
	m_chart.SetBKColor(RGB(255, 255, 240));
	m_chart.ShowTooltip(FALSE);

	m_chart.AddBar(gl[0],"1", RGB(0,255,0));
	m_chart.AddBar(gl[1],"2", RGB(0,255,0));
	m_chart.AddBar(gl[2],"3", RGB(0,255,0));
	m_chart.AddBar(gl[3],"4", RGB(0,255,0));
	m_chart.AddBar(gl[4],"5", RGB(0,255,0));
	m_chart.AddBar(gl[5],"6", RGB(0,255,0));
	m_chart.AddBar(gl[6],"7", RGB(0,255,0));
	m_chart.AddBar(gl[7],"8", RGB(0,255,0));
	m_chart.AddBar(gl[8],"9", RGB(0,255,0));
	m_chart.AddBar(gl[9],"10", RGB(0,255,0));

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

	m_chart.SetTitle("各波束通道功率检测");
	m_chart.SetBKColor(RGB(255, 255, 240));
	m_chart.ShowTooltip(FALSE);

	m_chart.AddBar(0,"1", RGB(0,255,0));
	m_chart.AddBar(0,"2", RGB(0,255,0));
	m_chart.AddBar(0,"3", RGB(0,255,0));
	m_chart.AddBar(0,"4", RGB(0,255,0));
	m_chart.AddBar(0,"5", RGB(0,255,0));
	m_chart.AddBar(0,"6", RGB(0,255,0));
	m_chart.AddBar(0,"7", RGB(0,255,0));
	m_chart.AddBar(0,"8", RGB(0,255,0));
	m_chart.AddBar(0,"9", RGB(0,255,0));
	m_chart.AddBar(0,"10", RGB(0,255,0));

	m_chart.Refresh();
}
