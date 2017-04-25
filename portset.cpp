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
	if(m_Index<0)//���ڵ�Ĭ��ֵû�иı�	
		{	
			switch(spp->m_ctrlComm.GetPortOpen())//����򿪻�رմ��ڰ���ʱ�����ݵ�ǰ�����Ƿ�򿪽�����Ӧ����
			{
			case 1:	
					/**************************************************************/
					//��ǰ�����Ǵ򿪵�����йش��ڲ���
					spp->m_ctrlComm.SetPortOpen(FALSE);//�رմ���
					SetDlgItemText(IDC_BUTTON_OPEN,"�򿪴���");//���İ���ָʾ
					UpdateData(FALSE);//���°���״̬
					break;
			case 0://��ǰ�����ǹرյ�����п����ڲ���
					spp->m_ctrlComm.SetCommPort(7);//���Ҫ�򿪴�����Ӧ��ѡ���ĸ�����
					spp->m_ctrlComm.SetPortOpen(TRUE);//�򿪴���
					SetDlgItemText(IDC_BUTTON_OPEN,"�رմ���");//���İ���ָʾ
					UpdateData(FALSE);
					break;
			default : AfxMessageBox("cannot open or close serial port");	
			}
		}
	else//���ڵ�Ĭ��ֵ�иı�
		{
		switch(spp->m_ctrlComm.GetPortOpen())//����򿪻�رմ��ڰ���ʱ�����ݵ�ǰ�����Ƿ�򿪽�����Ӧ����
			{
			case 0://��ǰ�����ǹرյ�����п����ڲ���	
					

					spp->m_ctrlComm.SetCommPort(m_Index+1);//���Ҫ�򿪴�����Ӧ��ѡ���ĸ�����

					spp->m_ctrlComm.SetPortOpen(TRUE);//�򿪴���

					SetDlgItemText(IDC_BUTTON_OPEN,"�رմ���");//���İ���ָʾ					
					UpdateData(FALSE);//���°���״̬
					break;
			case 1: 
				
					//��ǰ�����Ǵ򿪵�����йش��ڲ���					
					spp->m_ctrlComm.SetPortOpen(FALSE);
					SetDlgItemText(IDC_BUTTON_OPEN,"�򿪴���");					
					UpdateData(FALSE);
					break;
			default : AfxMessageBox("cannot open serial port");
			}
		}
	if(m_Index<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(2);//���û��������д���ѡ������ʾCOM1
	if(m_BaudRate<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_BOTE))->SetCurSel(5);//���û��������в�����ѡ������ʾ9600
	if(m_Date_Select<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->SetCurSel(0);////���û�������������λѡ������ʾ8
	if(m_StopBit<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_STOP))->SetCurSel(0);//���û���������ֹͣλѡ������ʾ1
	if(m_ParityCheck<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_JIAOYAN))->SetCurSel(0);//���û���������У��λѡ������ʾû��У��λN	
}

void portset::OnSelchangeComboBote() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	m_BaudRate=((CComboBox*)GetDlgItem(IDC_COMBO_BOTE))->GetCurSel();//��ǰѡ�е���	
////***********************************************************/
///���ݵ�ǰѡ�е�ֵ���в���������
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
	m_Date_Select=((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetCurSel();//��ǰѡ�е���
	
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
	m_ParityCheck=((CComboBox*)GetDlgItem(IDC_COMBO_JIAOYAN))->GetCurSel();//��ǰѡ�е���
	
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
		m_Index=((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->GetCurSel();//��ǰѡ�е���
		CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();

	((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(m_Index);//���õ�ǰѡ�е��е�����Ϊ��ʾ������
	if(spp->m_ctrlComm.GetPortOpen())//��Ҫ�ı�ʱ��Ҫ�ȹرմ��ڲſ����ð������д򿪣��������жϵ�ǰ�����Ƿ��
		{//����Ǵ򿪵����ȹر�
		spp->m_ctrlComm.SetPortOpen(FALSE);//�رմ���
		}		
	SetDlgItemText(IDC_BUTTON_OPEN,"�򿪴���");//���򿪻�زŰ�ť��Ϊ"�򿪴���"��ʾ״̬
	UpdateData(false);	
}

void portset::OnSelchangeComboStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	m_StopBit=((CComboBox*)GetDlgItem(IDC_COMBO_STOP))->GetCurSel();//��ǰѡ�е���
	
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
	m_ComboBox.SetCurSel(6);//�����ʱ����ѡ���Ĭ����ʾCOM7	
	m_BaudRate_M.SetCurSel(7);//�����ʱ������ѡ���Ĭ����ʾ9600
	m_Date_Select_M.SetCurSel(0);//�����ʱ����λѡ���Ĭ����ʾ8
	m_StopBit_M.SetCurSel(0);//�����ʱֹͣλѡ���Ĭ����ʾ1
	m_ParityCheck_M.SetCurSel(0);//�����ʱ��żУ��ѡ���Ĭ����ʾ��У��N
	//����if������ڴ�Ĭ�ϴ���
/************************************************************/
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();	
	if(spp->m_ctrlComm.GetPortOpen())
		{
			spp->m_ctrlComm.SetPortOpen(FALSE);//�رմ���
		}		
	spp->m_ctrlComm.SetCommPort(7);//�����ʱĬ��ʹ��COM1����
	spp->m_ctrlComm.SetInBufferSize(1024); //���ջ�����
	if(!spp->m_ctrlComm.GetPortOpen())
		{
		spp->m_ctrlComm.SetPortOpen(TRUE);//�򿪴���
		}		
	else
		{
		AfxMessageBox("cannot open serial port");
		}
			//Ĭ�����ô�

	spp->m_ctrlComm.SetSettings("57600,n,8,1");//�����ʱ�˿�����Ĭ��Ϊ������9600����У��λ��8λ���ݣ�1λֹͣλ
	spp->m_ctrlComm.SetInputMode(1); //1����ʾ�Զ����Ʒ�ʽ��ȡ����
	spp->m_ctrlComm.SetRThreshold(21); //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
	spp->m_ctrlComm.SetInputLen(0); //���õ�ǰ���������ݳ���Ϊ0
	spp->m_ctrlComm.GetInput();//��Ԥ���������������������

	SetDlgItemText(IDC_BUTTON_OPEN,"�رմ���");

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

void portset::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	//AfxMessageBox("jjsjsj");
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
