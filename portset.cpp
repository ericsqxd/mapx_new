// portset.cpp : implementation file
//

#include "stdafx.h"
#include "rescuekj2.h"
#include "portset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// portset dialog


portset::portset(CWnd* pParent /*=NULL*/)
	: CDialog(portset::IDD, pParent)
{
	//{{AFX_DATA_INIT(portset)
	m_Index = -1;
	m_BaudRate = -1;
	m_Date_Select = -1;
	m_StopBit = -1;
	m_ParityCheck = -1;
	//}}AFX_DATA_INIT
}


void portset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(portset)
	DDX_Control(pDX, IDC_COMBO_JIAOYAN, m_ParityCheck_M);
	DDX_Control(pDX, IDC_COMBO_STOP, m_StopBit_M);
	DDX_Control(pDX, IDC_COMBO_DATA, m_Date_Select_M);
	DDX_Control(pDX, IDC_COMBO_BOTE, m_BaudRate_M);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ComboBox);
	DDX_CBIndex(pDX, IDC_COMBO_PORT, m_Index);
	DDX_CBIndex(pDX, IDC_COMBO_BOTE, m_BaudRate);
	DDX_CBIndex(pDX, IDC_COMBO_DATA, m_Date_Select);
	DDX_CBIndex(pDX, IDC_COMBO_STOP, m_StopBit);
	DDX_CBIndex(pDX, IDC_COMBO_JIAOYAN, m_ParityCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(portset, CDialog)
	//{{AFX_MSG_MAP(portset)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_CBN_SELCHANGE(IDC_COMBO_BOTE, OnSelchangeComboBote)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_JIAOYAN, OnSelchangeComboJiaoyan)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT, OnSelchangeComboPort)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP, OnSelchangeComboStop)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// portset message handlers

void portset::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	CString str;
	if(m_Index<0)//串口的默认值没有改变	
		{	
			switch(spp->m_ctrlComm.GetPortOpen())//点击打开或关闭串口按键时，根据当前串口是否打开进行相应操作
			{
			case 1:	
					/**************************************************************/
					//当前串口是打开的则进行关串口操作
					spp->m_ctrlComm.SetPortOpen(FALSE);//关闭串口
					SetDlgItemText(IDC_BUTTON_OPEN,"打开串口");//更改按键指示
					UpdateData(FALSE);//更新按键状态
					break;
			case 0://当前串口是关闭的则进行开串口操作
					spp->m_ctrlComm.SetCommPort(7);//如果要打开串口则应先选择哪个串口
					spp->m_ctrlComm.SetPortOpen(TRUE);//打开串口
					SetDlgItemText(IDC_BUTTON_OPEN,"关闭串口");//更改按键指示
					UpdateData(FALSE);
					break;
			default : AfxMessageBox("cannot open or close serial port");	
			}
		}
	else//串口的默认值有改变
		{
		switch(spp->m_ctrlComm.GetPortOpen())//点击打开或关闭串口按键时，根据当前串口是否打开进行相应操作
			{
			case 0://当前串口是关闭的则进行开串口操作	
					

					spp->m_ctrlComm.SetCommPort(m_Index+1);//如果要打开串口则应先选择哪个串口

					spp->m_ctrlComm.SetPortOpen(TRUE);//打开串口

					SetDlgItemText(IDC_BUTTON_OPEN,"关闭串口");//更改按键指示					
					UpdateData(FALSE);//更新按键状态
					break;
			case 1: 
				
					//当前串口是打开的则进行关串口操作					
					spp->m_ctrlComm.SetPortOpen(FALSE);
					SetDlgItemText(IDC_BUTTON_OPEN,"打开串口");					
					UpdateData(FALSE);
					break;
			default : AfxMessageBox("cannot open serial port");
			}
		}
	if(m_Index<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(2);//如果没有另外进行串口选择则显示COM1
	if(m_BaudRate<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_BOTE))->SetCurSel(5);//如果没有另外进行波特率选择则显示9600
	if(m_Date_Select<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->SetCurSel(0);////如果没有另外进行数据位选择则显示8
	if(m_StopBit<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_STOP))->SetCurSel(0);//如果没有另外进行停止位选择则显示1
	if(m_ParityCheck<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_JIAOYAN))->SetCurSel(0);//如果没有另外进行校验位选择则显示没有校验位N	
}

void portset::OnSelchangeComboBote() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	m_BaudRate=((CComboBox*)GetDlgItem(IDC_COMBO_BOTE))->GetCurSel();//当前选中的行	
////***********************************************************/
///根据当前选中的值进行波特率设置
///************************************************************/
	switch(m_BaudRate)
	{	
	case 1: spp->m_ctrlComm.SetSettings("1200,,,");
	break;
	case 2: spp->m_ctrlComm.SetSettings("2400,,,");
	break;
	case 3: spp->m_ctrlComm.SetSettings("4800,,,");
	break;
	case 4: spp->m_ctrlComm.SetSettings("9600,,,");
	break;
	case 5: spp->m_ctrlComm.SetSettings("14400,,,");
	break;
	case 6: spp->m_ctrlComm.SetSettings("19200,,,");
	break;
	case 7: spp->m_ctrlComm.SetSettings("38400,,,");
	break;
	case 8: spp->m_ctrlComm.SetSettings("576000,,,");
	break;
	default:spp->m_ctrlComm.SetSettings("115200,,,");
	break;
	}
//*************************************************////
UpdateData(false);	
}

void portset::OnSelchangeComboData() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	m_Date_Select=((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetCurSel();//当前选中的行
	
///*******************************************************************************/

///********************************************************************************/
switch(m_Date_Select)
	{
	case 1: spp->m_ctrlComm.SetSettings(",,8,");
	break;
	case 2: spp->m_ctrlComm.SetSettings(",,7,");
	break;
	case 3: spp->m_ctrlComm.SetSettings(",,6,");
	break;
	case 4: spp->m_ctrlComm.SetSettings(",,5,");
	break;
	default:spp->m_ctrlComm.SetSettings(",,4,");
	break;
	
	}
//*********************************************************************************//
	UpdateData(false);	
}

void portset::OnSelchangeComboJiaoyan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	m_ParityCheck=((CComboBox*)GetDlgItem(IDC_COMBO_JIAOYAN))->GetCurSel();//当前选中的行
	
///*******************************************************************************/

///********************************************************************************/
switch(m_ParityCheck)
	{
	case 1: spp->m_ctrlComm.SetSettings(",J,,");
	break;
	case 2: spp->m_ctrlComm.SetSettings(",O,,");
	break;
	default:spp->m_ctrlComm.SetSettings(",N,,");
	break;
	
	}
//*********************************************************************************//
	UpdateData(false);	
}

void portset::OnSelchangeComboPort() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
		m_Index=((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->GetCurSel();//当前选中的行
		CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();

	((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(m_Index);//设置当前选中的行的内容为显示的内容
	if(spp->m_ctrlComm.GetPortOpen())//当要改变时则要先关闭串口才可以用按键进行打开，所以先判断当前串口是否打开
		{//如果是打开的则先关闭
		spp->m_ctrlComm.SetPortOpen(FALSE);//关闭串口
		}		
	SetDlgItemText(IDC_BUTTON_OPEN,"打开串口");//将打开或关才按钮改为"打开串口"显示状态
	UpdateData(false);	
}

void portset::OnSelchangeComboStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	m_StopBit=((CComboBox*)GetDlgItem(IDC_COMBO_STOP))->GetCurSel();//当前选中的行
	
///*******************************************************************************/

///********************************************************************************/
switch(m_StopBit)
	{
	case 1: spp->m_ctrlComm.SetSettings(",,,1");
	break;
	default:spp->m_ctrlComm.SetSettings(",,,2");
	break;
	}
//*********************************************************************************//
UpdateData(false);	
}

void portset::Oninitial()
{
	m_ComboBox.SetCurSel(6);//打开软件时串口选择框默认显示COM7	
	m_BaudRate_M.SetCurSel(7);//打开软件时波特率选择框默认显示9600
	m_Date_Select_M.SetCurSel(0);//打开软件时数据位选择框默认显示8
	m_StopBit_M.SetCurSel(0);//打开软件时停止位选择框默认显示1
	m_ParityCheck_M.SetCurSel(0);//打开软件时奇偶校验选择框默认显示无校验N
	//下面if语句用于打开默认串口
/************************************************************/
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();	
	if(spp->m_ctrlComm.GetPortOpen())
		{
			spp->m_ctrlComm.SetPortOpen(FALSE);//关闭串口
		}		
	spp->m_ctrlComm.SetCommPort(7);//打开软件时默认使用COM1串口
	spp->m_ctrlComm.SetInBufferSize(1024); //接收缓冲区
	if(!spp->m_ctrlComm.GetPortOpen())
		{
		spp->m_ctrlComm.SetPortOpen(TRUE);//打开串口
		}		
	else
		{
		AfxMessageBox("cannot open serial port");
		}
			//默认设置打开

	spp->m_ctrlComm.SetSettings("57600,n,8,1");//打开软件时端口设置默认为波特率9600，无校验位，8位数据，1位停止位
	spp->m_ctrlComm.SetInputMode(1); //1：表示以二进制方式检取数据
	spp->m_ctrlComm.SetRThreshold(21); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
	spp->m_ctrlComm.SetInputLen(0); //设置当前接收区数据长度为0
	spp->m_ctrlComm.GetInput();//先预读缓冲区以清除残留数据

	SetDlgItemText(IDC_BUTTON_OPEN,"关闭串口");

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

void portset::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	//AfxMessageBox("jjsjsj");
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
