// rescuekj2View.cpp : implementation of the CRescuekj2View class
//

#include "stdafx.h"
#include "rescuekj2.h"
#include <MMSystem.h>

#pragma comment(lib,"winmm.lib")

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
	ON_COMMAND(IDC_JIANTOU, OnJiantou)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_MESSAGE(WM_MY_MESSAGE, OnMyMessage) 
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab)
	ON_COMMAND(IDC_CESHI, OnCeshi)
	ON_COMMAND(ID_XIUGAI, OnXiugai)
	ON_COMMAND(IDC_DELETE, OnDelete)
	ON_COMMAND(IDC_VIEW, OnView)
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
	DDX_Control(pDX,IDC_MSCOMM1,spp->m_ctrlComm);
	//{{AFX_DATA_MAP(CRescuekj2View)
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Control(pDX, IDC_TAB1, m_tab);
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
	pWnd = GetDlgItem(IDC_LIST1);    //���ݿؼ�ID�Ż�ȡ�ؼ�ָ�룬�˴�Ϊ��ʷ��ʾ��
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

		all = lyr.AllFeatures();
		alltr = m_traceLayer.AllFeatures();

		m_tab.InsertItem(0, _T("��������"));
		m_tab.InsertItem(1, _T("���ʼ��"));
		m_tab.InsertItem(2, _T("����״��"));
		//�趨��Tab����ʾ�ķ�Χ
		CRect rc;
		m_tab.GetClientRect(rc);////���TAB�ؼ�������

		/*CString strtmp;
		strtmp.Format("%d %d %d %d",rc.top,rc.bottom,rc.left,rc.right);
		AfxMessageBox(strtmp);*/

		//��λѡ�ҳ��λ�ã�������Ը�������Լ�����ƫ����
		rc.top += 20;
		rc.bottom -= 0;
		rc.left += 0;
		rc.right -= 0;
		//���������Ի���
		m_page1.Create(IDD_PORT, &m_tab);//&m_tabҲ���Ըĳ�Tab��ID
		m_page2.Create(IDD_GONGLV, &m_tab);
		m_page3.Create(IDD_INFO, &m_tab);
		//����ҳ���ƶ���ָ����λ��
		//m_page1.MoveWindow(&rc);

	/*rc.top = 20;	//��λѡ�ҳ��λ�ã�������Ը�������Լ�����ƫ����
	rc.bottom = 272;
	rc.left = 0;
	rc.right = 293;*/

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

	List_Initial();


	num=0;
	/*****      ��������ѡ���ʼֵ�ʹ򿪴���        ******/
	m_page1.Oninitial();	//����ŵ��ζԻ��򴴽���
	m_page2.Initial_gonglv();
	m_page3.Initial();
	/********     �������õ��˽���      **********/

	myAccess.OnInitADOConn();			//�������ݿ�
	myAccess.Openace();

	//cishu=0;
		

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


	SetTimer(ID_TIMER_FLASH,1000,NULL);//�򿪶�ʱ��

}

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2View printing

void CRescuekj2View::List_Initial()
{
	m_List1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List1.InsertColumn(0, "���",LVCFMT_CENTER, 40, 0);
	m_List1.InsertColumn(1, "��Ϣ���",LVCFMT_CENTER, 80, 0);
	m_List1.InsertColumn(2, "����",LVCFMT_CENTER, 50, 0);
	m_List1.InsertColumn(3, "����״��",LVCFMT_CENTER, 100, 0);	
	m_List1.InsertColumn(4, "����",LVCFMT_CENTER, 100, 0);
	m_List1.InsertColumn(5, "γ��",LVCFMT_CENTER, 100, 0);
	m_List1.InsertColumn(6, "�߶�",LVCFMT_CENTER, 50, 0);
	m_List1.InsertColumn(7, "������ϵ�绰1",LVCFMT_CENTER, 100, 0);
	m_List1.InsertColumn(8, "������ϵ�绰2",LVCFMT_CENTER, 100, 0);
	m_List1.InsertColumn(9, "ʱ��",LVCFMT_CENTER, 150, 0);
	m_List1.InsertColumn(10, "ID",LVCFMT_CENTER, 30, 0);
}
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
			CMapXFeatures fts=lyr.AllFeatures();//ͻ����ʾѡ�е�ͼԪ
			lyr.GetSelection().Add(fts);
		}
		else
		{
			lyr.GetSelection().ClearSelection();
		}
	}
	CFormView::OnTimer(nIDEvent);
}

void CRescuekj2View::guiji(int id,double y,double x,double yg,double xg)
{
	CMapXFeature ft,ht;
	//CMapXPoints gt;
	CString strtmp1,strtmp2;
	strtmp1.Format("%d",id);
	int i;
	for(i=1;i<=all.GetCount();i++)
	{
		ft = all.Item(i);
		strtmp2 = ft.GetKeyValue();
		if(strtmp1==strtmp2)
			break;
	}
	ft.Offset(y-yg,x-xg);
	

	for(i=1;i<=alltr.GetCount();i++)
	{
		ht = alltr.Item(i);
		strtmp2 = ht.GetKeyValue();
		if(strtmp1==strtmp2)
			break;
	}
	//xt.GetParts().Item(i).AddXY(y, x);//���켣
	//AfxMessageBox("ok");
	//gt.AddXY(y,x);
	ht.GetParts().Item(1).AddXY(y,x);

	ft.Update();
	ht.Update();
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

		CString strtmp,strtmp1;
		strtmp.Format("%d",id);

		gt.CreateDispatch(gt.GetClsid());
	    gt.Attach(m_ctrlMapX.GetDispatch(FALSE));
	    gt.SetType(miFeatureTypeLine);
	    gt.GetStyle().SetLineColor(miColorRed);
	    gt.GetStyle().SetLineStyle(3);//77-����(�ο�����)
	    gt.GetStyle().SetLineWidth(3);
	    CMapXPoints pts;
	    pts.CreateDispatch(pts.GetClsid());
	    //������������
	    pts.AddXY(y0, x0);
	    pts.AddXY(y1, x1);
	    gt.GetParts().Add(pts);//���뵽Ŀ��ͼ��

	    xt=m_traceLayer.AddFeature((LPDISPATCH)gt); 
		xt.SetKeyValue(strtmp);
		alltr.Add(xt);

		//xt.SetKeyValue()		
		//ft=lyr.AllFeatures().Item(id);
		//ft = lyr.GetFeatureByKey(strtmp);

		int i;
		for(i=1;i<=all.GetCount();i++)
		{
			ft = all.Item(i);
			strtmp1 = ft.GetKeyValue();
			if(strtmp1==strtmp)
				break;
		}
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

void CRescuekj2View::biaodian(int id,double y, double x)
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
	CString str;
try
{
	if (ft.CreateDispatch(ft.GetClsid()))
	{
		ft.Attach(m_ctrlMapX.GetDispatch());
		ft = m_ctrlMapX.GetFeatureFactory().CreateSymbol();
		CMapXStyle s = ft.GetStyle();
		s.SetSymbolType(miSymbolTypeBitmap);
		s.SetSymbolBitmapSize(15);  //�ɻ���С
		s.SetSymbolBitmapTransparent(true);
		s.SetSymbolBitmapName("STOP1-32.bmp");
		ft.SetStyle(s);
		ft.GetPoint().Set(y,x);

		str.Format("%d",id);
		ft.SetKeyValue(str);

		st=lyr.AddFeature(ft);
		//str = st.GetFeatureKey();

		all.Add(st);

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
			CRect rc;
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
				if(*pWndChild==m_tab)
				{
					/*CString strtmp;
					strtmp.Format("%d %d %d %d",rectChildSaved.top,rectChildSaved.bottom,rectChildSaved.left,rectChildSaved.right);
					AfxMessageBox(strtmp);*/
					rc.top = 20;	
					rc.bottom = (int)(272*fRateScaleY);
					rc.left = 0;
					rc.right = (int)(293*fRateScaleX);
					m_page1.MoveWindow(&rc);
					m_page2.MoveWindow(&rc);
					m_page3.MoveWindow(&rc);
				}
                pWndChild = pWndChild->GetNextWindow();
            }
        }
        Invalidate(); //ǿ���ػ洰��
	// TODO: Add your message handler code here
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
	CString strtemp,strst,str_id,str_lgtd,str_latd,str_height,str_num,str_leibie;
	strtemp="";
	//��ʾʱ��
	time_t m_time;
	tm *t;
	int hour,min,sec;
	int year, mon, day;
	CString name;//str_receive,
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


	//strtemp.Format("data %d",cishu);//���ַ�������ʱ����strtemp���
	//cishu++;
	Sleep(50);  
	//

	if (spp->m_ctrlComm.GetCommEvent()==2)//�¼�ֵΪ2��ʾ���ջ�������������
	{
		////��������Ը����Լ���ͨ��Э����봦�����

		//AfxMessageBox("data");
		variant_inp=spp->m_ctrlComm.GetInput();//��������
		safearray_inp=variant_inp;//VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
		len=safearray_inp.GetOneDimSize();
		//if(len==0)return;
				//strtemp.Format("length:%d",len);//���ַ�������ʱ����strtemp���
				//AfxMessageBox(strtemp);

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
				//strtemp.Format("%d",bt);//���ַ�������ʱ����strtemp���
				//AfxMessageBox(strtemp);
			//	str_receive+=strtemp;//������ձ༭���Ӧ�ַ���
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
			id=(unsigned char)buf[19]*256+(unsigned char)buf[20];

			str_num.Format("%d",num);
			str_id.Format("%d",id);

			if(buf[18]==0)
			{
				cha=myAccess.Chaxun(id);
			//	AfxMessageBox("����!");
				if(cha==true)
				{
					lgtd=((unsigned char)buf[23]/60.0+buf[22])/60+buf[21];
					latd=((unsigned char)buf[27]/60.0+buf[26])/60+buf[25];
					
					this->m_ctrlMapX.SetCenterX(lgtd);//�Ըõ�Ϊ����
					this->m_ctrlMapX.SetCenterY(latd);
					this->m_ctrlMapX.SetZoom(5);

					if(book[id]==0)
					{
						PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
						biaodian(id,lgtd,latd);//�ڵ�ͼ�ϱ��
						myAccess.show_rescue(id);
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

					height=(unsigned char)buf[29]*256+(unsigned char)buf[30];
					bloodshou=(unsigned char)buf[31];
					bloodzh=(unsigned char)buf[32];
					temper=30+0.1*buf[33];
					beat=(unsigned char)buf[34];

					name=spp->strname;
					m_page3.Show_info(id,name,bloodshou,bloodzh,beat,temper);
					myAccess.Write(id,strst,lgtd,latd,height,bloodshou,bloodzh,beat,temper);
					
					
					str_lgtd.Format("%lf",lgtd);
					str_latd.Format("%lf",latd);
					str_height.Format("%d",height);
					str_leibie = "���";
					
				}
			}
			else
			{	
				strtemp.Format("�յ�IDΪ%d���Լ��ź�!",id);
				str_leibie = "�Լ�";
				MessageBox(strtemp,"�Լ��ź�",0);
			}

			m_List1.InsertItem(num, _T("")); 
			m_List1.SetItemText(num, 0, str_num);
			m_List1.SetItemText(num, 1, str_leibie);
			m_List1.SetItemText(num, 2, name);
			m_List1.SetItemText(num, 3, spp->str_status);
			m_List1.SetItemText(num, 4, str_lgtd);
			m_List1.SetItemText(num, 5, str_latd);
			m_List1.SetItemText(num, 6, str_height);
			m_List1.SetItemText(num, 7, spp->str_phone1);
			m_List1.SetItemText(num, 8, spp->str_phone2);
			m_List1.SetItemText(num, 9, strst);
			m_List1.SetItemText(num, 10, str_id);
			num++;	
			/*strtemp.Format("ID: %d, ����: %s, λ��: %d��%d'%d \"E,  %d��%d'%d \"N",id,name,(unsigned char)buf[20],buf[21],buf[22],(unsigned char)buf[24],buf[25],buf[26]);
			m_List1.InsertItem(0, _T("C")); 
			m_List1.SetItemText(0, 0, _T("1"));
			m_List1.SetItemText(0, 1, _T("1"));
			m_List1.SetItemText(0, 2, _T("1"));
			m_List1.SetItemText(0, 3, _T("1"));
			m_List1.SetItemText(0, 4, _T("1"));
			m_List1.SetItemText(0, 5, _T("1"));
			m_List1.SetItemText(0, 6, _T("1"));
			m_List1.SetItemText(0, 7, _T("1"));			
			m_strRXData+=strst+strtemp+"\r\n";
			UpdateData(FALSE);//���±༭������(��Ҫ�ǽ��ձ༭���е�)
			*/
		}
	else
		AfxMessageBox("�Ƿ��û�!");
	}
	//spp->m_ctrlComm.SetInputLen(0); //���õ�ǰ���������ݳ���Ϊ0
	//spp->m_ctrlComm.GetInput();//��Ԥ���������������������
	}
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

void CRescuekj2View::OnCeshi(int id) 
{
	// TODO: Add your command handler code here
	CMapXFeature at;
	CString str,str1;
	str1.Format("%d",id);
	int i;
	for(i=1;i<=all.GetCount();i++)
	{
		at = all.Item(i);
		str = at.GetKeyValue();
		//AfxMessageBox(str);
		if(str==str1)
		{
			lyr.DeleteFeature(at);
		}	
	}
	for(i=1;i<=alltr.GetCount();i++)
	{
		at = alltr.Item(i);
		str = at.GetKeyValue();
		//AfxMessageBox(str);
		if(str==str1)
		{
			m_traceLayer.DeleteFeature(at);
		}	
	}

}

LRESULT CRescuekj2View::OnMyMessage(WPARAM wParam, LPARAM lParam)   
{   
	// TODO: �����û��Զ�����Ϣ
	/*CString strtmp;
	strtmp.Format("%d",wParam);
	AfxMessageBox(strtmp); */
	OnCeshi(wParam);
	return 0;   
} 

void CRescuekj2View::OnXiugai() 
{
	// TODO: Add your command handler code here
	
}

void CRescuekj2View::OnDelete() 
{
	// TODO: Add your command handler code here
	
}

void CRescuekj2View::OnView() 
{
	// TODO: Add your command handler code here
	
}
