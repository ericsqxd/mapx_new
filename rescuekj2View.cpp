// rescuekj2View.cpp : implementation of the CRescuekj2View class
//

#include "stdafx.h"
#include "rescuekj2.h"

#include "rescuekj2Doc.h"
#include "rescuekj2View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2View

IMPLEMENT_DYNCREATE(CRescuekj2View, CFormView)

BEGIN_MESSAGE_MAP(CRescuekj2View, CFormView)
	//{{AFX_MSG_MAP(CRescuekj2View)
	ON_COMMAND(IDC_ADD, OnAdd)
	ON_COMMAND(Zoom_In, OnZoomIn)
	ON_COMMAND(Zoom_Out, OnZoomOut)
	ON_COMMAND(Move_Pan, OnMovePan)
	ON_COMMAND(Cen_ter, OnCenter)
	ON_COMMAND(IDC_SET, OnTuCengSet)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_PORT, OnSelchangeComboPort)
	ON_CBN_SELCHANGE(IDC_COMBO_BOTE, OnSelchangeComboBote)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP, OnSelchangeComboStop)
	ON_CBN_SELCHANGE(IDC_COMBO_JIAOYAN, OnSelchangeComboJiaoyan)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnPortOpen)
	ON_COMMAND(IDC_CESHI, OnCeshi)
	ON_COMMAND(IDC_JIANTOU, OnJiantou)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2View construction/destruction

CRescuekj2View::CRescuekj2View()
	: CFormView(CRescuekj2View::IDD)
{
	//{{AFX_DATA_INIT(CRescuekj2View)
	m_strRXData = _T("");
	m_Index = -1;
	m_BaudRate = -1;
	m_Date_Select = -1;
	m_StopBit = -1;
	m_ParityCheck = -1;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CRescuekj2View::~CRescuekj2View()
{

}

void CRescuekj2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_MAP1,m_ctrlMapX);
	//{{AFX_DATA_MAP(CRescuekj2View)
	DDX_Control(pDX, IDC_COMBO_JIAOYAN, m_ParityCheck_M);
	DDX_Control(pDX, IDC_COMBO_STOP, m_StopBit_M);
	DDX_Control(pDX, IDC_COMBO_DATA, m_Date_Select_M);
	DDX_Control(pDX, IDC_COMBO_BOTE, m_BaudRate_M);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ComboBox);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_HISTORYMEG, m_strRXData);
	DDX_CBIndex(pDX, IDC_COMBO_PORT, m_Index);
	DDX_CBIndex(pDX, IDC_COMBO_BOTE, m_BaudRate);
	DDX_CBIndex(pDX, IDC_COMBO_DATA, m_Date_Select);
	DDX_CBIndex(pDX, IDC_COMBO_STOP, m_StopBit);
	DDX_CBIndex(pDX, IDC_COMBO_JIAOYAN, m_ParityCheck);
	//}}AFX_DATA_MAP
}

BOOL CRescuekj2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CRescuekj2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_bFlash=FALSE;
	int cx=0,cy=0;

	/******������MapX�ĳ�ʼ��      **********/

	CRect rect;
	GetClientRect(&rect);
	cx=rect.Width();
	cy=rect.Height();
	m_ctrlMapX.MoveWindow(20,20,cx-400,cy-30,TRUE);//���õ�ͼ�Ĵ�С
	m_ctrlMapX.SetGeoSet("jiangsu/china2012.gst");
	m_ctrlMapX.SetTitleText("");
	m_ctrlMapX.SetCenterX(118.85);//�������ĵ㾭��γ��
	m_ctrlMapX.SetCenterY(32.06);
	m_ctrlMapX.SetZoom(500);//���ó�ʼ���Ŵ�С
	CWnd *pWnd;  
	pWnd = GetDlgItem(IDC_EDIT_HISTORYMEG);    //���ݿؼ�ID�Ż�ȡ�ؼ�ָ�룬�˴�Ϊ��ʷ��ʾ��
	pWnd->MoveWindow(cx-350,cy-350,320,338,TRUE);    //ǰ����Ϊ��ʼ�㣬������Ϊ��Ⱥ͸߶� 
	pWnd = GetDlgItem(IDC_STATIC_HISTORY);    //�˴�Ϊ��ʷ��Ϣ
	pWnd->MoveWindow(cx-350,cy-375,70,30,TRUE);    



	/*****      ��������ѡ���ʼֵ�ʹ򿪴���        ******/

	m_ComboBox.SetCurSel(0);//�����ʱ����ѡ���Ĭ����ʾCOM1	
	m_BaudRate_M.SetCurSel(3);//�����ʱ������ѡ���Ĭ����ʾ9600
	m_Date_Select_M.SetCurSel(0);//�����ʱ����λѡ���Ĭ����ʾ8
	m_StopBit_M.SetCurSel(0);//�����ʱֹͣλѡ���Ĭ����ʾ1
	m_ParityCheck_M.SetCurSel(0);//�����ʱ��żУ��ѡ���Ĭ����ʾ��У��N
	//����if������ڴ�Ĭ�ϴ���
/************************************************************/
	if(m_ctrlComm.GetPortOpen())
		{
			m_ctrlComm.SetPortOpen(FALSE);//�رմ���
		}		
	m_ctrlComm.SetCommPort(1);//�����ʱĬ��ʹ��COM1����
	if(!m_ctrlComm.GetPortOpen())
		{
		m_ctrlComm.SetPortOpen(TRUE);//�򿪴���
		}		
	else
		{
		AfxMessageBox("cannot open serial port");
		}
			//Ĭ�����ô�
	m_ctrlComm.SetSettings("9600,n,8,1");//�����ʱ�˿�����Ĭ��Ϊ������9600����У��λ��8λ���ݣ�1λֹͣλ
	m_ctrlComm.SetInputMode(1); //1����ʾ�Զ����Ʒ�ʽ��ȡ����
	m_ctrlComm.SetRThreshold(1); //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
	m_ctrlComm.SetInputLen(0); //���õ�ǰ���������ݳ���Ϊ0
	m_ctrlComm.GetInput();//��Ԥ���������������������

	SetDlgItemText(IDC_BUTTON_OPEN,"�رմ���");
	/********     �������õ��˽���      **********/


	/*****    ������пؼ�    ********/
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
	myAccess.OnInitADOConn();			//�������ݿ�
	myAccess.Openace();			//����Ӧ�ı�
}

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2View printing

BOOL CRescuekj2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRescuekj2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRescuekj2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRescuekj2View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2View diagnostics

#ifdef _DEBUG
void CRescuekj2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CRescuekj2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CRescuekj2Doc* CRescuekj2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRescuekj2Doc)));
	return (CRescuekj2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2View message handlers

void CRescuekj2View::OnAdd() 
{
	// TODO: Add your command handler code here
	add addinfor;
	addinfor.DoModal();
}


void CRescuekj2View::OnZoomIn() //�Ŵ󹤾�
{
	this->m_ctrlMapX.SetCurrentTool(miZoomInTool);	
}

void CRescuekj2View::OnZoomOut() //��С����
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.SetCurrentTool(miZoomOutTool);	
}

void CRescuekj2View::OnMovePan()	//ץ�ֹ���
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.SetCurrentTool(miPanTool);	
}

void CRescuekj2View::OnCenter() //���й���
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.SetCurrentTool(miCenterTool);	
}

void CRescuekj2View::OnJiantou() //��ͷ����
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.SetCurrentTool(miArrowTool);
}

void CRescuekj2View::OnTuCengSet() //ͼ������
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.GetLayers().LayersDlg();
}

void CRescuekj2View::OnTimer(UINT nIDEvent) //��ʱ������
{
	// TODO: Add your message handler code here and/or call default
	if(ID_TIMER_FLASH==nIDEvent)
	{
		m_bFlash=!m_bFlash;
		if(m_bFlash)
		{
			CMapXFeatures fts=m_ctrlMapX.GetLayers().Item(1).AllFeatures();//ͻ����ʾѡ�е�ͼԪ
			m_ctrlMapX.GetLayers().Item(1).GetSelection().Add(fts);
		}
		else
		{
			m_ctrlMapX.GetLayers().Item(1).GetSelection().ClearSelection();
		}
	}
		xt.GetParts().Item(1).AddXY(yg, xg);//���켣
		yg=yg-0.1;
		xg=xg-0.1;
		xt.Update();
	CFormView::OnTimer(nIDEvent);
}

void CRescuekj2View::OnCeshi() 
{
	// TODO: Add your command handler code here
	CMapXLayer lyr,m_traceLayer;
	//CMapXPoint pt;
	CMapXFeature ft,st;
	//CMapXFeatures ftr;
	CString lyrName;
	//CMapXFeatureFactory ffy;
	double x,y;
	x=32.32;
	y=119.52;
	yg=119.3;
	xg=32.3;
	m_ctrlMapX.GetLayers().CreateLayer("tmplayer",NULL,1);
	lyr = m_ctrlMapX.GetLayers().Item("tmplayer");
	m_ctrlMapX.GetLayers().SetAnimationLayer(lyr);
	//����Ŀ��켣��
	m_traceLayer = m_ctrlMapX.GetLayers().CreateLayer("guiji",NULL, 2);
	m_ctrlMapX.GetLayers().SetAnimationLayer(m_traceLayer);
	m_traceLayer.SetSelectable(FALSE);
	m_traceLayer.SetDrawLabelsAfter(TRUE);//Ӱ���עˢ�µĹؼ�
	/*����*/

try
{
	if (ft.CreateDispatch(ft.GetClsid()))
	{
		/*******    ��ָ����γ����ʾ      *****/
		ft.Attach(m_ctrlMapX.GetDispatch());
		ft = m_ctrlMapX.GetFeatureFactory().CreateSymbol();
		CMapXStyle s = ft.GetStyle();
		s.SetSymbolType(miSymbolTypeBitmap);
		s.SetSymbolBitmapSize(8);  
		s.SetSymbolBitmapTransparent(true);
		s.SetSymbolBitmapName("STOP1-32.bmp");
		ft.SetStyle(s);
		ft.GetPoint().Set(y,x);
		st=lyr.AddFeature(ft);
		//lyr.Refresh();
		st.Update();
		guiji(117,30);
		
		myAccess.Chaxun();		//��ʾ�켣
	/**********       ���켣       *******/

		CMapXFeature gt;
		gt.CreateDispatch(ft.GetClsid());
	    gt.Attach(m_ctrlMapX.GetDispatch(FALSE));
	    gt.SetType(miFeatureTypeLine);
	    gt.GetStyle().SetLineColor(miColorRed);
	    gt.GetStyle().SetLineStyle(3);//77-����(�ο�����)
	    gt.GetStyle().SetLineWidth(2);
	    CMapXPoints pts;
	    pts.CreateDispatch(pts.GetClsid());
	    //������������
	    pts.AddXY(119.5, 32.5);
	    pts.AddXY(119.4, 32.4);
	    gt.GetParts().Add(pts);
	    //���뵽Ŀ��ͼ��
	    xt=m_traceLayer.AddFeature((LPDISPATCH)gt); 
		xt.Update();
   /*************      ����     **************/
	//	SetTimer(ID_TIMER_FLASH,1000,NULL);//�򿪶�ʱ��

	}
	else
	{
	AfxThrowOleException(CO_E_CLASS_CREATE_FAILED);
	}
}

catch (COleDispatchException *e)
	{
	e->ReportError();
	e->Delete();
	}
catch (COleException *e)
	{
	e->ReportError();
	e->Delete();
	}	
}

void CRescuekj2View::guiji(double y, double x)
{
	CMapXLayer lyr;
	lyr = m_ctrlMapX.GetLayers().Item("tmplayer");
	CMapXFeature ft,fr,fs;
	ft=lyr.AllFeatures().Item(1);
	fr=ft.Clone();
	fr.GetPoint().Set(y,x);
	fs=lyr.AddFeature(fr);
	//lyr.Refresh();
	fs.Update();
}
void CRescuekj2View::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
 if (listRect.GetCount()>0)//�������Ƿ�Ϊ��
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

            int n=1;  //��ǰ�������ſؼ���TABֵ
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
	// TODO: Add your message handler code here
	//m_ControlPos.MoveControls();
}

BEGIN_EVENTSINK_MAP(CRescuekj2View, CFormView)
    //{{AFX_EVENTSINK_MAP(CRescuekj2View)
	ON_EVENT(CRescuekj2View, IDC_MSCOMM1, 1 /* OnComm */, OnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRescuekj2View::OnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;//����һ��VARIANT�����
	COleSafeArray safearray_inp;//����һ��COleSafeArray����
	LONG len,k;
	BYTE rxdata[2048];//����BYTE���� AN 8��intterthat is not signed.
	CString strtemp;
//��ʾʱ��
	time_t m_time;
	tm *t;
	int hour,min,sec;
	int year, mon, day;
	CString st;
	time(&m_time); //��ȡ��ǰʱ��ֵ
	t=localtime(&m_time);  //ת��Ϊ tm �ṹ����
	hour=t->tm_hour;  //�õ�Сʱ
	min=t->tm_min; //�õ�����
	sec=t->tm_sec; //�õ���
	year=t->tm_year+1900;  //�õ����
	mon =t->tm_mon+1; //�õ��·�
	day =t->tm_mday;  //�õ�����

	st.Format( " \n %4d ��%2d �� %2d ��  %02d:%02d:%02d  " , year,mon,day,hour, min, sec);
	m_strRXData=st;



	if (m_ctrlComm.GetCommEvent()==2)//�¼�ֵΪ2��ʾ���ջ�������������
	{
		////��������Ը����Լ���ͨ��Э����봦�����
		variant_inp=m_ctrlComm.GetInput();//��������
		safearray_inp=variant_inp;//VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
		len=safearray_inp.GetOneDimSize();
		for(k=0;k<len;k++)
			{
				safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������
			}
		for(k=0;k<len;k++)//������ת��ΪCstring�ͱ���
			{
				BYTE bt=*(char*)(rxdata+k);
			//if(m_ctrlHexSend.GetCheck())//�����HEX��ʾ��תΪ16����
			//	strtemp.Format("%02x ",bt);	//��16������������ʱ����strtemp���
			//	else
				strtemp.Format("%c",bt);//���ַ�������ʱ����strtemp���
				m_strRXData+=strtemp;//������ձ༭���Ӧ�ַ���
				}
	}
	UpdateData(FALSE);//���±༭�����ݣ���Ҫ�ǽ��ձ༭���еģ�
	//��Ϣ��ʾ��
		int num;
		CString str,name,unit,position;
		num=1005;
		name="eric";
		unit="university";
		position="cadet";
		str.Format(_T("�յ�����ź����ԣ�ID %d,����%s,��λ%s��ְ��%s"),num,name,unit,position);
		AfxMessageBox(str);
}

void CRescuekj2View::OnSelchangeComboPort() 
{
	// TODO: Add your control notification handler code here

	m_Index=((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->GetCurSel();//��ǰѡ�е���
	/*
	CString str;
	str.Format(_T("%d"), m_Index);
	AfxMessageBox(str);*/

	((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(m_Index);//���õ�ǰѡ�е��е�����Ϊ��ʾ������
	if(m_ctrlComm.GetPortOpen())//��Ҫ�ı�ʱ��Ҫ�ȹرմ��ڲſ����ð������д򿪣��������жϵ�ǰ�����Ƿ��
		{//����Ǵ򿪵����ȹر�
		m_ctrlComm.SetPortOpen(FALSE);//�رմ���
		}		
	SetDlgItemText(IDC_BUTTON_OPEN,"�򿪴���");//���򿪻�زŰ�ť��Ϊ"�򿪴���"��ʾ״̬	
}

void CRescuekj2View::OnSelchangeComboBote() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_BaudRate=((CComboBox*)GetDlgItem(IDC_COMBO_BOTE))->GetCurSel();//��ǰѡ�е���	
////***********************************************************/
///���ݵ�ǰѡ�е�ֵ���в���������
///************************************************************/
	switch(m_BaudRate)
	{	
	case 1: m_ctrlComm.SetSettings("1200,,,");
	break;
	case 2: m_ctrlComm.SetSettings("2400,,,");
	break;
	case 3: m_ctrlComm.SetSettings("4800,,,");
	break;
	case 4: m_ctrlComm.SetSettings("9600,,,");
	break;
	case 5: m_ctrlComm.SetSettings("14400,,,");
	break;
	case 6: m_ctrlComm.SetSettings("19200,,,");
	break;
	case 7: m_ctrlComm.SetSettings("38400,,,");
	break;
	case 8: m_ctrlComm.SetSettings("576000,,,");
	break;
	default:m_ctrlComm.SetSettings("115200,,,");
	break;
	}
//*************************************************////
UpdateData(false);
	
}

void CRescuekj2View::OnSelchangeComboData() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_Date_Select=((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetCurSel();//��ǰѡ�е���
	
///*******************************************************************************/

///********************************************************************************/
switch(m_Date_Select)
	{
	case 1: m_ctrlComm.SetSettings(",,8,");
	break;
	case 2: m_ctrlComm.SetSettings(",,7,");
	break;
	case 3: m_ctrlComm.SetSettings(",,6,");
	break;
	case 4: m_ctrlComm.SetSettings(",,5,");
	break;
	default:m_ctrlComm.SetSettings(",,4,");
	break;
	
	}
//*********************************************************************************//
	UpdateData(false);
	
}

void CRescuekj2View::OnSelchangeComboStop() 
{
	// TODO: Add your control notification handler code here
UpdateData(true);
	m_StopBit=((CComboBox*)GetDlgItem(IDC_COMBO_STOP))->GetCurSel();//��ǰѡ�е���
	
///*******************************************************************************/

///********************************************************************************/
switch(m_StopBit)
	{
	case 1: m_ctrlComm.SetSettings(",,,1");
	break;
	default:m_ctrlComm.SetSettings(",,,2");
	break;
	}
//*********************************************************************************//
UpdateData(false);
	
}

void CRescuekj2View::OnSelchangeComboJiaoyan() 
{
	// TODO: Add your control notification handler code here
UpdateData(true);
	m_ParityCheck=((CComboBox*)GetDlgItem(IDC_COMBO_JIAOYAN))->GetCurSel();//��ǰѡ�е���
	
///*******************************************************************************/

///********************************************************************************/
switch(m_ParityCheck)
	{
	case 1: m_ctrlComm.SetSettings(",J,,");
	break;
	case 2: m_ctrlComm.SetSettings(",O,,");
	break;
	default:m_ctrlComm.SetSettings(",N,,");
	break;
	
	}
//*********************************************************************************//
	UpdateData(false);
	
}

void CRescuekj2View::OnPortOpen() 
{
	// TODO: Add your control notification handler code here
//����Ƿ�ı�Ĭ�ϵĴ���ֵ��û�иı�m_Index��ֵ��0�ģ�������Ϊ0
	if(m_Index<0)//���ڵ�Ĭ��ֵû�иı�	
		{	
			switch(m_ctrlComm.GetPortOpen())//����򿪻�رմ��ڰ���ʱ�����ݵ�ǰ�����Ƿ�򿪽�����Ӧ����
			{
			case 1:	

					/**************************************************************/
				
					//��ǰ�����Ǵ򿪵�����йش��ڲ���
					m_ctrlComm.SetPortOpen(FALSE);//�رմ���
					SetDlgItemText(IDC_BUTTON_OPEN,"�򿪴���");//���İ���ָʾ
					UpdateData(FALSE);//���°���״̬
					break;
			case 0://��ǰ�����ǹرյ�����п����ڲ���
					m_ctrlComm.SetCommPort(1);//���Ҫ�򿪴�����Ӧ��ѡ���ĸ�����
					m_ctrlComm.SetPortOpen(TRUE);//�򿪴���
					SetDlgItemText(IDC_BUTTON_OPEN,"�رմ���");//���İ���ָʾ
					UpdateData(FALSE);
					break;
			default : AfxMessageBox("cannot open or close serial port");	
			}
		}
	else//���ڵ�Ĭ��ֵ�иı�
		{
		switch(m_ctrlComm.GetPortOpen())//����򿪻�رմ��ڰ���ʱ�����ݵ�ǰ�����Ƿ�򿪽�����Ӧ����
			{
			case 0://��ǰ�����ǹرյ�����п����ڲ���	
					m_ctrlComm.SetCommPort(m_Index+1);//���Ҫ�򿪴�����Ӧ��ѡ���ĸ�����
					m_ctrlComm.SetPortOpen(TRUE);//�򿪴���
					SetDlgItemText(IDC_BUTTON_OPEN,"�رմ���");//���İ���ָʾ					
					UpdateData(FALSE);//���°���״̬
					break;
			case 1: 
				
					//��ǰ�����Ǵ򿪵�����йش��ڲ���					
					m_ctrlComm.SetPortOpen(FALSE);
					SetDlgItemText(IDC_BUTTON_OPEN,"�򿪴���");					
					UpdateData(FALSE);
					break;
			default : AfxMessageBox("cannot open serial port");
			}
		}
	if(m_Index<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(0);//���û��������д���ѡ������ʾCOM1
	if(m_BaudRate<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_BOTE))->SetCurSel(3);//���û��������в�����ѡ������ʾ9600
	if(m_Date_Select<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->SetCurSel(0);////���û�������������λѡ������ʾ8
	if(m_StopBit<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_STOP))->SetCurSel(0);//���û���������ֹͣλѡ������ʾ1
	if(m_ParityCheck<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_JIAOYAN))->SetCurSel(0);//���û���������У��λѡ������ʾû��У��λN
}


void CRescuekj2View::OnAppExit() 
{
	// TODO: Add your command handler code here
		myAccess.ExitConnect();				//�ر����ݿ�
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
