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

	/******　　　MapX的初始化      **********/

	CRect rect;
	GetClientRect(&rect);
	cx=rect.Width();
	cy=rect.Height();
	m_ctrlMapX.MoveWindow(20,20,cx-400,cy-30,TRUE);//设置地图的大小
	m_ctrlMapX.SetGeoSet("jiangsu/china2012.gst");
	m_ctrlMapX.SetTitleText("");
	m_ctrlMapX.SetCenterX(118.85);//设置中心点经度纬度
	m_ctrlMapX.SetCenterY(32.06);
	m_ctrlMapX.SetZoom(500);//设置初始缩放大小
	CWnd *pWnd;  
	pWnd = GetDlgItem(IDC_LIST1);    //根据控件ID号获取控件指针，此处为历史显示框
	pWnd->MoveWindow(cx-350,cy-320,320,308,TRUE);    //前两个为起始点，后两个为宽度和高度 
	pWnd = GetDlgItem(IDC_STATIC_HISTORY);    //此处为历史消息
	pWnd->MoveWindow(cx-350,cy-345,70,30,TRUE);    

	m_ctrlMapX.GetLayers().CreateLayer("tmplayer",NULL,1);//建立目标点层
	lyr = m_ctrlMapX.GetLayers().Item("tmplayer");
	m_ctrlMapX.GetLayers().SetAnimationLayer(lyr);
	
	m_traceLayer = m_ctrlMapX.GetLayers().CreateLayer("guiji",NULL, 2);//建立目标轨迹层
	m_ctrlMapX.GetLayers().SetAnimationLayer(m_traceLayer);
	m_traceLayer.SetSelectable(FALSE);
	m_traceLayer.SetDrawLabelsAfter(TRUE);//影响标注刷新的关键

		all = lyr.AllFeatures();
		alltr = m_traceLayer.AllFeatures();

		m_tab.InsertItem(0, _T("串口设置"));
		m_tab.InsertItem(1, _T("功率检测"));
		m_tab.InsertItem(2, _T("身体状况"));
		//设定在Tab内显示的范围
		CRect rc;
		m_tab.GetClientRect(rc);////获得TAB控件的坐标

		/*CString strtmp;
		strtmp.Format("%d %d %d %d",rc.top,rc.bottom,rc.left,rc.right);
		AfxMessageBox(strtmp);*/

		//定位选项卡页的位置，这里可以根据情况自己调节偏移量
		rc.top += 20;
		rc.bottom -= 0;
		rc.left += 0;
		rc.right -= 0;
		//创建两个对话框
		m_page1.Create(IDD_PORT, &m_tab);//&m_tab也可以改成Tab的ID
		m_page2.Create(IDD_GONGLV, &m_tab);
		m_page3.Create(IDD_INFO, &m_tab);
		//将子页面移动到指定的位置
		//m_page1.MoveWindow(&rc);

	/*rc.top = 20;	//定位选项卡页的位置，这里可以根据情况自己调节偏移量
	rc.bottom = 272;
	rc.left = 0;
	rc.right = 293;*/

		m_page1.MoveWindow(&rc);
		m_page2.MoveWindow(&rc);
		m_page3.MoveWindow(&rc);



		//显示子页面
		//显示初始页面
		m_page1.ShowWindow(SW_SHOW);
		m_page2.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_HIDE);
		//保存当前选择
		//m_CurSelTab = 0;
		m_tab.SetCurSel(0);

		for(int i=0;i<50;i++)
			book[i]=0;

	List_Initial();


	num=0;
	/*****      下面用于选择初始值和打开串口        ******/
	m_page1.Oninitial();	//必须放到次对话框创建后
	m_page2.Initial_gonglv();
	m_page3.Initial();
	/********     串口设置到此结束      **********/

	myAccess.OnInitADOConn();			//连接数据库
	myAccess.Openace();

	//cishu=0;
		

	/*****    获得所有控件    ********/
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


	SetTimer(ID_TIMER_FLASH,1000,NULL);//打开定时器

}

/////////////////////////////////////////////////////////////////////////////
// CRescuekj2View printing

void CRescuekj2View::List_Initial()
{
	m_List1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List1.InsertColumn(0, "编号",LVCFMT_CENTER, 40, 0);
	m_List1.InsertColumn(1, "信息类别",LVCFMT_CENTER, 80, 0);
	m_List1.InsertColumn(2, "姓名",LVCFMT_CENTER, 50, 0);
	m_List1.InsertColumn(3, "身体状况",LVCFMT_CENTER, 100, 0);	
	m_List1.InsertColumn(4, "经度",LVCFMT_CENTER, 100, 0);
	m_List1.InsertColumn(5, "纬度",LVCFMT_CENTER, 100, 0);
	m_List1.InsertColumn(6, "高度",LVCFMT_CENTER, 50, 0);
	m_List1.InsertColumn(7, "紧急联系电话1",LVCFMT_CENTER, 100, 0);
	m_List1.InsertColumn(8, "紧急联系电话2",LVCFMT_CENTER, 100, 0);
	m_List1.InsertColumn(9, "时间",LVCFMT_CENTER, 150, 0);
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


void CRescuekj2View::OnZoomIn() //放大工具
{
	this->m_ctrlMapX.SetCurrentTool(miZoomInTool);	
}

void CRescuekj2View::OnZoomOut() //缩小工具
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.SetCurrentTool(miZoomOutTool);	
}

void CRescuekj2View::OnMovePan()	//抓手工具
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.SetCurrentTool(miPanTool);	
}

void CRescuekj2View::OnCenter() //居中工具
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.SetCurrentTool(miCenterTool);	
}

void CRescuekj2View::OnJiantou() //箭头工具
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.SetCurrentTool(miArrowTool);
}

void CRescuekj2View::OnTuCengSet() //图层设置
{
	// TODO: Add your command handler code here
	this->m_ctrlMapX.GetLayers().LayersDlg();
}

void CRescuekj2View::OnTimer(UINT nIDEvent) //定时器函数
{
	// TODO: Add your message handler code here and/or call default

	if(ID_TIMER_FLASH==nIDEvent)
	{
		m_bFlash=!m_bFlash;
		if(m_bFlash)
		{
			CMapXFeatures fts=lyr.AllFeatures();//突出显示选中的图元
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
	//xt.GetParts().Item(i).AddXY(y, x);//画轨迹
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
	m_ctrlMapX.GetLayers().CreateLayer("tmplayer",NULL,1);//建立目标点层
	lyr = m_ctrlMapX.GetLayers().Item("tmplayer");
	m_ctrlMapX.GetLayers().SetAnimationLayer(lyr);
	
	m_traceLayer = m_ctrlMapX.GetLayers().CreateLayer("guiji",NULL, 2);//建立目标轨迹层
	m_ctrlMapX.GetLayers().SetAnimationLayer(m_traceLayer);
	m_traceLayer.SetSelectable(FALSE);
	m_traceLayer.SetDrawLabelsAfter(TRUE);//影响标注刷新的关键



	CMapXFeature ft,st;
try
{
	if (ft.CreateDispatch(ft.GetClsid()))
	{
		ft.Attach(m_ctrlMapX.GetDispatch());
		ft = m_ctrlMapX.GetFeatureFactory().CreateSymbol();
		CMapXStyle s = ft.GetStyle();
		s.SetSymbolType(miSymbolTypeBitmap);
		s.SetSymbolBitmapSize(8);  //飞机大小
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

	/**********       画轨迹       *******/
try
{
		CMapXFeature gt,ft;

		CString strtmp,strtmp1;
		strtmp.Format("%d",id);

		gt.CreateDispatch(gt.GetClsid());
	    gt.Attach(m_ctrlMapX.GetDispatch(FALSE));
	    gt.SetType(miFeatureTypeLine);
	    gt.GetStyle().SetLineColor(miColorRed);
	    gt.GetStyle().SetLineStyle(3);//77-铁轨(参考帮助)
	    gt.GetStyle().SetLineWidth(3);
	    CMapXPoints pts;
	    pts.CreateDispatch(pts.GetClsid());
	    //加入坐标数据
	    pts.AddXY(y0, x0);
	    pts.AddXY(y1, x1);
	    gt.GetParts().Add(pts);//加入到目标图层

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
   /*************      到此     **************/

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
		s.SetSymbolBitmapSize(15);  //飞机大小
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
        Invalidate(); //强制重绘窗口
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
	VARIANT variant_inp;//定义一个VARIANT类对象
	COleSafeArray safearray_inp;//定义一个COleSafeArray对象
	LONG len,k;
	BYTE rxdata[2048];//设置BYTE数组 AN 8—intterthat is not signed.
	char buf[50];
	bool cha=false;
	CString strtemp,strst,str_id,str_lgtd,str_latd,str_height,str_num,str_leibie;
	strtemp="";
	//显示时间
	time_t m_time;
	tm *t;
	int hour,min,sec;
	int year, mon, day;
	CString name;//str_receive,
	time(&m_time); //获取当前时钟值
	t=localtime(&m_time);  //转换为 tm 结构类型
	hour=t->tm_hour;  //得到小时
	min=t->tm_min; //得到分钟
	sec=t->tm_sec; //得到秒
	year=t->tm_year+1900;  //得到年份
	mon =t->tm_mon+1; //得到月份
	day =t->tm_mday;  //得到日期



	//st.Format( "\n %4d 年%2d 月 %2d 日  %02d:%02d:%02d  " , year,mon,day,hour, min, sec);
	strst.Format( "%4d/%2d/%2d  %02d:%02d:%02d ",year,mon,day,hour, min, sec);
	CRescuekj2App *spp = (CRescuekj2App *)AfxGetApp();


	//strtemp.Format("data %d",cishu);//将字符送入临时变量strtemp存放
	//cishu++;
	Sleep(50);  
	//

	if (spp->m_ctrlComm.GetCommEvent()==2)//事件值为2表示接收缓冲区内有数据
	{
		////以下你可以根据自己的通信协议加入处理代码

		//AfxMessageBox("data");
		variant_inp=spp->m_ctrlComm.GetInput();//读缓冲区
		safearray_inp=variant_inp;//VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize();
		//if(len==0)return;
				//strtemp.Format("length:%d",len);//将字符送入临时变量strtemp存放
				//AfxMessageBox(strtemp);

		for(k=0;k<len;k++)
			{
				safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
			}
		for(k=0;k<len;k++)//将数组转换为Cstring型变量
			{
				BYTE bt=*(char*)(rxdata+k);
			//if(m_ctrlHexSend.GetCheck())//如果是HEX显示则转为16进制
			//	strtemp.Format("%02x ",bt);	//将16进制数送入临时变量strtemp存放
			//	else
				buf[k]=bt;
				//strtemp.Format("%d",bt);//将字符送入临时变量strtemp存放
				//AfxMessageBox(strtemp);
			//	str_receive+=strtemp;//加入接收编辑框对应字符串
			}

	//消息提示框$GLJC

	char *p=strstr(buf,"$GLZK");
	char *q=strstr(buf,"$TXXX");
	if(p!=NULL)
	{
		
		if(buf[7]==0x03&&buf[8]==0x00&&buf[9]==0x14)//判断用户机地址是否合法	
		{
			int value[10];
			for(int i=0;i<10;i++)
				value[i]=buf[10+i];
			m_page2.Show_gonglv(value);
		}
		else
			AfxMessageBox("非法用户!");
	}
	else 
		if(q!=NULL)
	{
		if(buf[7]==0x03&&buf[8]==0x00&&buf[9]==0x14)//判断用户机地址是否合法	
		{
			int id,bloodshou,bloodzh,beat,height;
			double lgtd,latd,temper;
			id=(unsigned char)buf[19]*256+(unsigned char)buf[20];

			str_num.Format("%d",num);
			str_id.Format("%d",id);

			if(buf[18]==0)
			{
				cha=myAccess.Chaxun(id);
			//	AfxMessageBox("测试!");
				if(cha==true)
				{
					lgtd=((unsigned char)buf[23]/60.0+buf[22])/60+buf[21];
					latd=((unsigned char)buf[27]/60.0+buf[26])/60+buf[25];
					
					this->m_ctrlMapX.SetCenterX(lgtd);//以该点为中心
					this->m_ctrlMapX.SetCenterY(latd);
					this->m_ctrlMapX.SetZoom(5);

					if(book[id]==0)
					{
						PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
						biaodian(id,lgtd,latd);//在地图上标点
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
					str_leibie = "求救";
					
				}
			}
			else
			{	
				strtemp.Format("收到ID为%d的自检信号!",id);
				str_leibie = "自检";
				MessageBox(strtemp,"自检信号",0);
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
			/*strtemp.Format("ID: %d, 姓名: %s, 位置: %d°%d'%d \"E,  %d°%d'%d \"N",id,name,(unsigned char)buf[20],buf[21],buf[22],(unsigned char)buf[24],buf[25],buf[26]);
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
			UpdateData(FALSE);//更新编辑框内容(主要是接收编辑框中的)
			*/
		}
	else
		AfxMessageBox("非法用户!");
	}
	//spp->m_ctrlComm.SetInputLen(0); //设置当前接收区数据长度为0
	//spp->m_ctrlComm.GetInput();//先预读缓冲区以清除残留数据
	}
}
void CRescuekj2View::OnAppExit() 
{
	// TODO: Add your command handler code here
		myAccess.ExitConnect();				//关闭数据库
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
	// TODO: 处理用户自定义消息
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
