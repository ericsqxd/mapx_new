// rescuekj2View.cpp : implementation of the CRescuekj2View class
//

#include "stdafx.h"
#include "rescuekj2.h"

#include "rescuekj2Doc.h"
#include "rescuekj2View.h"
#include <iostream>
#include <cstring>
using namespace std;

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
	//ON_COMMAND(IDC_CESHI, OnCeshi)
	ON_COMMAND(IDC_JIANTOU, OnJiantou)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab)
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
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	//{{AFX_DATA_MAP(CRescuekj2View)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_MSCOMM1, spp->m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_HISTORYMEG, m_strRXData);
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
	pWnd->MoveWindow(cx-350,cy-320,320,308,TRUE);    //ǰ����Ϊ��ʼ�㣬������Ϊ��Ⱥ͸߶� 
	pWnd = GetDlgItem(IDC_STATIC_HISTORY);    //�˴�Ϊ��ʷ��Ϣ
	pWnd->MoveWindow(cx-350,cy-345,70,30,TRUE);    

	m_ctrlMapX.GetLayers().CreateLayer("tmplayer",NULL,1);//����Ŀ����
	lyr = m_ctrlMapX.GetLayers().Item("tmplayer");
	m_ctrlMapX.GetLayers().SetAnimationLayer(lyr);
	
	m_traceLayer = m_ctrlMapX.GetLayers().CreateLayer("guiji",NULL, 2);//����Ŀ��켣��
	m_ctrlMapX.GetLayers().SetAnimationLayer(m_traceLayer);
	m_traceLayer.SetSelectable(FALSE);
	m_traceLayer.SetDrawLabelsAfter(TRUE);//Ӱ���עˢ�µĹؼ�

		m_tab.InsertItem(0, _T("��������"));
		m_tab.InsertItem(1, _T("���ʼ��"));
		m_tab.InsertItem(2, _T("����״��"));
		//�趨��Tab����ʾ�ķ�Χ
		CRect rc;
		m_tab.GetClientRect(rc);////���TAB�ؼ�������
		//��λѡ�ҳ��λ�ã�������Ը�������Լ�����ƫ����
		rc.top += 30;
		rc.bottom -= 0;
		rc.left += 0;
		rc.right -= 0;
		//���������Ի���
		m_page1.Create(IDD_PORT, &m_tab);//&m_tabҲ���Ըĳ�Tab��ID
		m_page2.Create(IDD_GONGLV, &m_tab);
		m_page3.Create(IDD_INFO, &m_tab);
		//����ҳ���ƶ���ָ����λ��
		m_page1.MoveWindow(&rc);
		m_page2.MoveWindow(&rc);
		m_page3.MoveWindow(&rc);
		//��ʾ��ҳ��
		//��ʾ��ʼҳ��
		m_page1.ShowWindow(SW_SHOW);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		//���浱ǰѡ��
		//m_CurSelTab = 0;
		m_tab.SetCurSel(0);

		for(int i=0;i<50;i++)
			book[i]=0;
			

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

	/*****      ��������ѡ���ʼֵ�ʹ򿪴���        ******/
	m_page1.Oninitial();	//����ŵ��ζԻ��򴴽���
	m_page2.Initial_gonglv();
	m_page3.Initial();
	/********     �������õ��˽���      **********/

	myAccess.OnInitADOConn();			//�������ݿ�
	myAccess.Openace();

	SetTimer(ID_TIMER_FLASH,1000,NULL);//�򿪶�ʱ��

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
	CFormView::OnTimer(nIDEvent);
}

void CRescuekj2View::guiji(int id,double y,double x,double yg,double xg)
{
	CMapXFeature ft;
	ft=lyr.AllFeatures().Item(id);
	ft.Offset(y-yg,x-xg);
	
	xt.GetParts().Item(id).AddXY(y, x);//���켣

	ft.Update();
	xt.Update();
}
void CRescuekj2View::guiji_initial(int id,double y0,double x0,double y1,double x1) 
{
	// TODO: Add your command handler code here
	
	//CMapXFeatures ftr;
	//CString lyrName;
	//CMapXFeatureFactory ffy;
	/*x=32.32;
	y=119.52;
	yg=y;
	xg=x;
	m_ctrlMapX.GetLayers().CreateLayer("tmplayer",NULL,1);//����Ŀ����
	lyr = m_ctrlMapX.GetLayers().Item("tmplayer");
	m_ctrlMapX.GetLayers().SetAnimationLayer(lyr);
	
	m_traceLayer = m_ctrlMapX.GetLayers().CreateLayer("guiji",NULL, 2);//����Ŀ��켣��
	m_ctrlMapX.GetLayers().SetAnimationLayer(m_traceLayer);
	m_traceLayer.SetSelectable(FALSE);
	m_traceLayer.SetDrawLabelsAfter(TRUE);//Ӱ���עˢ�µĹؼ�



	CMapXFeature ft,st;
try
{
	if (ft.CreateDispatch(ft.GetClsid()))
	{
		ft.Attach(m_ctrlMapX.GetDispatch());
		ft = m_ctrlMapX.GetFeatureFactory().CreateSymbol();
		CMapXStyle s = ft.GetStyle();
		s.SetSymbolType(miSymbolTypeBitmap);
		s.SetSymbolBitmapSize(8);  //�ɻ���С
		s.SetSymbolBitmapTransparent(true);
		s.SetSymbolBitmapName("STOP1-32.bmp");
		ft.SetStyle(s);
		ft.GetPoint().Set(y,x);
		st=lyr.AddFeature(ft);
		st.Update();
	}
	else
	{
	AfxThrowOleException(CO_E_CLASS_CREATE_FAILED);
	}
	*/
	
		//guiji(117,30);

	/**********       ���켣       *******/
try
{
		CMapXFeature gt,ft;
		gt.CreateDispatch(gt.GetClsid());
	    gt.Attach(m_ctrlMapX.GetDispatch(FALSE));
	    gt.SetType(miFeatureTypeLine);
	    gt.GetStyle().SetLineColor(miColorRed);
	    gt.GetStyle().SetLineStyle(3);//77-����(�ο�����)
	    gt.GetStyle().SetLineWidth(2);
	    CMapXPoints pts;
	    pts.CreateDispatch(pts.GetClsid());
	    //������������
	    pts.AddXY(y0, x0);
	    pts.AddXY(y1, x1);
	    gt.GetParts().Add(pts);
	    //���뵽Ŀ��ͼ��
	    xt=m_traceLayer.AddFeature((LPDISPATCH)gt); 

		ft=lyr.AllFeatures().Item(id);
		ft.Offset(y1-y0,x1-x0);
		ft.Update();

		xt.Update();
   /*************      ����     **************/

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

void CRescuekj2View::biaodian(double y, double x)
{
	/*
	CMapXLayer lyr;
	lyr = m_ctrlMapX.GetLayers().Item("tmplayer");
	CMapXFeature ft,fr,fs;
	ft=lyr.AllFeatures().Item(1);
	fr=ft.Clone();
	fr.GetPoint().Set(y,x);
	fs=lyr.AddFeature(fr);
	fs.Update();
	*/
	CMapXFeature ft,st;
try
{
	if (ft.CreateDispatch(ft.GetClsid()))
	{
		ft.Attach(m_ctrlMapX.GetDispatch());
		ft = m_ctrlMapX.GetFeatureFactory().CreateSymbol();
		CMapXStyle s = ft.GetStyle();
		s.SetSymbolType(miSymbolTypeBitmap);
		s.SetSymbolBitmapSize(8);  //�ɻ���С
		s.SetSymbolBitmapTransparent(true);
		s.SetSymbolBitmapName("STOP1-32.bmp");
		ft.SetStyle(s);
		ft.GetPoint().Set(y,x);
		st=lyr.AddFeature(ft);
		st.Update();
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
void CRescuekj2View::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
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
	char buf[50];
	bool cha=false;
	CString strtemp;
	//��ʾʱ��
	time_t m_time;
	tm *t;
	int hour,min,sec;
	int year, mon, day;
	CString name,strst;//str_receive,
	time(&m_time); //��ȡ��ǰʱ��ֵ
	t=localtime(&m_time);  //ת��Ϊ tm �ṹ����
	hour=t->tm_hour;  //�õ�Сʱ
	min=t->tm_min; //�õ�����
	sec=t->tm_sec; //�õ���
	year=t->tm_year+1900;  //�õ����
	mon =t->tm_mon+1; //�õ��·�
	day =t->tm_mday;  //�õ�����

	//st.Format( "\n %4d ��%2d �� %2d ��  %02d:%02d:%02d  " , year,mon,day,hour, min, sec);
	strst.Format( "%4d/%2d/%2d  %02d:%02d:%02d ",year,mon,day,hour, min, sec);
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();
	if (spp->m_ctrlComm.GetCommEvent()==2)//�¼�ֵΪ2��ʾ���ջ�������������
	{
		////��������Ը����Լ���ͨ��Э����봦�����
		variant_inp=spp->m_ctrlComm.GetInput();//��������
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
				buf[k]=bt;
			//	strtemp.Format("%c",bt);//���ַ�������ʱ����strtemp���
			//	str_receive+=strtemp;//������ձ༭���Ӧ�ַ���
			}
	}
	//��Ϣ��ʾ��$GLJC
	char *p=strstr(buf,"$GLZK");
	char *q=strstr(buf,"$TXXX");
	if(p!=NULL)
	{
		if(buf[7]==0x03&&buf[8]==0x00&&buf[9]==0x14)//�ж��û�����ַ�Ƿ�Ϸ�	
		{
			int value[10];
			for(int i=0;i<10;i++)
				value[i]=buf[10+i];
			m_page2.Show_gonglv(value);
		}
		else
			AfxMessageBox("�Ƿ��û�!");
	}
	else 
		if(q!=NULL)
	{
		if(buf[7]==0x03&&buf[8]==0x00&&buf[9]==0x14)//�ж��û�����ַ�Ƿ�Ϸ�	
		{
			int id,bloodshou,bloodzh,beat,height;
			double lgtd,latd,temper;
			id=(unsigned char)buf[18]*256+(unsigned char)buf[19];
			cha=myAccess.Chaxun(id,book[id]);
		//	AfxMessageBox("����!");
			if(cha==true)
			{
			lgtd=((unsigned char)buf[22]/60.0+buf[21])/60+buf[20];
			latd=((unsigned char)buf[26]/60.0+buf[25])/60+buf[24];
			
			if(book[id]==0)
			{
				biaodian(lgtd,latd);//�ڵ�ͼ�ϱ��
				book[id]=1;
			}
			else if(book[id]==1)
			{
				guiji_initial(id,pre[id].y,pre[id].x,lgtd,latd);
				book[id]=2;
			}
			else
				guiji(id,lgtd,latd,pre[id].y,pre[id].x);

			pre[id].y=lgtd;
			pre[id].x=latd;

			height=(unsigned char)buf[28]*256+(unsigned char)buf[29];
			bloodshou=(unsigned char)buf[30];
			bloodzh=(unsigned char)buf[31];
			temper=30+0.1*buf[32];
			beat=(unsigned char)buf[33];

			name=spp->strname;
			m_page3.Show_info(id,name,bloodshou,bloodzh,beat,temper);
			myAccess.Write(id,strst,lgtd,latd,height,bloodshou,bloodzh,beat,temper);
			}

			strtemp.Format("ID: %d, ����: %s, λ��: %d��%d'%d \"E,  %d��%d'%d \"N",id,name,(unsigned char)buf[20],buf[21],buf[22],(unsigned char)buf[24],buf[25],buf[26]);
			m_strRXData+=strst+strtemp+"\r\n";
			UpdateData(FALSE);//���±༭������(��Ҫ�ǽ��ձ༭���е�)

		}	
	}
	else
	AfxMessageBox("�Ƿ��û�!");
}



void CRescuekj2View::OnAppExit() 
{
	// TODO: Add your command handler code here
		myAccess.ExitConnect();				//�ر����ݿ�
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

void CRescuekj2View::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
    switch (m_tab.GetCurSel())
    {
        case 0:
            m_page1.ShowWindow(SW_SHOW);
            m_page2.ShowWindow(SW_HIDE);
			m_page3.ShowWindow(SW_HIDE);
            break;
        case 1:
            m_page1.ShowWindow(SW_HIDE);
            m_page2.ShowWindow(SW_SHOW);
			m_page3.ShowWindow(SW_HIDE);

            break;
        case 2:
			m_page1.ShowWindow(SW_HIDE);
			m_page2.ShowWindow(SW_HIDE);
			m_page3.ShowWindow(SW_SHOW);
            break;
    }
}
