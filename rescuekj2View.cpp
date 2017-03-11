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
	pWnd = GetDlgItem(IDC_EDIT_HISTORYMEG);    //根据控件ID号获取控件指针，此处为历史显示框
	pWnd->MoveWindow(cx-350,cy-350,320,338,TRUE);    //前两个为起始点，后两个为宽度和高度 
	pWnd = GetDlgItem(IDC_STATIC_HISTORY);    //此处为历史消息
	pWnd->MoveWindow(cx-350,cy-375,70,30,TRUE);    



	/*****      下面用于选择初始值和打开串口        ******/

	m_ComboBox.SetCurSel(0);//打开软件时串口选择框默认显示COM1	
	m_BaudRate_M.SetCurSel(3);//打开软件时波特率选择框默认显示9600
	m_Date_Select_M.SetCurSel(0);//打开软件时数据位选择框默认显示8
	m_StopBit_M.SetCurSel(0);//打开软件时停止位选择框默认显示1
	m_ParityCheck_M.SetCurSel(0);//打开软件时奇偶校验选择框默认显示无校验N
	//下面if语句用于打开默认串口
/************************************************************/
	if(m_ctrlComm.GetPortOpen())
		{
			m_ctrlComm.SetPortOpen(FALSE);//关闭串口
		}		
	m_ctrlComm.SetCommPort(1);//打开软件时默认使用COM1串口
	if(!m_ctrlComm.GetPortOpen())
		{
		m_ctrlComm.SetPortOpen(TRUE);//打开串口
		}		
	else
		{
		AfxMessageBox("cannot open serial port");
		}
			//默认设置打开
	m_ctrlComm.SetSettings("9600,n,8,1");//打开软件时端口设置默认为波特率9600，无校验位，8位数据，1位停止位
	m_ctrlComm.SetInputMode(1); //1：表示以二进制方式检取数据
	m_ctrlComm.SetRThreshold(1); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
	m_ctrlComm.SetInputLen(0); //设置当前接收区数据长度为0
	m_ctrlComm.GetInput();//先预读缓冲区以清除残留数据

	SetDlgItemText(IDC_BUTTON_OPEN,"关闭串口");
	/********     串口设置到此结束      **********/


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
	myAccess.OnInitADOConn();			//连接数据库
	myAccess.Openace();			//打开相应的表
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
			CMapXFeatures fts=m_ctrlMapX.GetLayers().Item(1).AllFeatures();//突出显示选中的图元
			m_ctrlMapX.GetLayers().Item(1).GetSelection().Add(fts);
		}
		else
		{
			m_ctrlMapX.GetLayers().Item(1).GetSelection().ClearSelection();
		}
	}
		xt.GetParts().Item(1).AddXY(yg, xg);//画轨迹
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
	//建立目标轨迹层
	m_traceLayer = m_ctrlMapX.GetLayers().CreateLayer("guiji",NULL, 2);
	m_ctrlMapX.GetLayers().SetAnimationLayer(m_traceLayer);
	m_traceLayer.SetSelectable(FALSE);
	m_traceLayer.SetDrawLabelsAfter(TRUE);//影响标注刷新的关键
	/*到此*/

try
{
	if (ft.CreateDispatch(ft.GetClsid()))
	{
		/*******    在指定经纬度显示      *****/
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
		
		myAccess.Chaxun();		//显示轨迹
	/**********       画轨迹       *******/

		CMapXFeature gt;
		gt.CreateDispatch(ft.GetClsid());
	    gt.Attach(m_ctrlMapX.GetDispatch(FALSE));
	    gt.SetType(miFeatureTypeLine);
	    gt.GetStyle().SetLineColor(miColorRed);
	    gt.GetStyle().SetLineStyle(3);//77-铁轨(参考帮助)
	    gt.GetStyle().SetLineWidth(2);
	    CMapXPoints pts;
	    pts.CreateDispatch(pts.GetClsid());
	    //加入坐标数据
	    pts.AddXY(119.5, 32.5);
	    pts.AddXY(119.4, 32.4);
	    gt.GetParts().Add(pts);
	    //加入到目标图层
	    xt=m_traceLayer.AddFeature((LPDISPATCH)gt); 
		xt.Update();
   /*************      到此     **************/
	//	SetTimer(ID_TIMER_FLASH,1000,NULL);//打开定时器

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
 if (listRect.GetCount()>0)//看链表是否为空
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

            int n=1;  //当前处理缩放控件的TAB值
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
	VARIANT variant_inp;//定义一个VARIANT类对象
	COleSafeArray safearray_inp;//定义一个COleSafeArray对象
	LONG len,k;
	BYTE rxdata[2048];//设置BYTE数组 AN 8—intterthat is not signed.
	CString strtemp;
//显示时间
	time_t m_time;
	tm *t;
	int hour,min,sec;
	int year, mon, day;
	CString st;
	time(&m_time); //获取当前时钟值
	t=localtime(&m_time);  //转换为 tm 结构类型
	hour=t->tm_hour;  //得到小时
	min=t->tm_min; //得到分钟
	sec=t->tm_sec; //得到秒
	year=t->tm_year+1900;  //得到年份
	mon =t->tm_mon+1; //得到月份
	day =t->tm_mday;  //得到日期

	st.Format( " \n %4d 年%2d 月 %2d 日  %02d:%02d:%02d  " , year,mon,day,hour, min, sec);
	m_strRXData=st;



	if (m_ctrlComm.GetCommEvent()==2)//事件值为2表示接收缓冲区内有数据
	{
		////以下你可以根据自己的通信协议加入处理代码
		variant_inp=m_ctrlComm.GetInput();//读缓冲区
		safearray_inp=variant_inp;//VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize();
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
				strtemp.Format("%c",bt);//将字符送入临时变量strtemp存放
				m_strRXData+=strtemp;//加入接收编辑框对应字符串
				}
	}
	UpdateData(FALSE);//更新编辑框内容（主要是接收编辑框中的）
	//消息提示框
		int num;
		CString str,name,unit,position;
		num=1005;
		name="eric";
		unit="university";
		position="cadet";
		str.Format(_T("收到求救信号来自：ID %d,姓名%s,单位%s，职务%s"),num,name,unit,position);
		AfxMessageBox(str);
}

void CRescuekj2View::OnSelchangeComboPort() 
{
	// TODO: Add your control notification handler code here

	m_Index=((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->GetCurSel();//当前选中的行
	/*
	CString str;
	str.Format(_T("%d"), m_Index);
	AfxMessageBox(str);*/

	((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(m_Index);//设置当前选中的行的内容为显示的内容
	if(m_ctrlComm.GetPortOpen())//当要改变时则要先关闭串口才可以用按键进行打开，所以先判断当前串口是否打开
		{//如果是打开的则先关闭
		m_ctrlComm.SetPortOpen(FALSE);//关闭串口
		}		
	SetDlgItemText(IDC_BUTTON_OPEN,"打开串口");//将打开或关才按钮改为"打开串口"显示状态	
}

void CRescuekj2View::OnSelchangeComboBote() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_BaudRate=((CComboBox*)GetDlgItem(IDC_COMBO_BOTE))->GetCurSel();//当前选中的行	
////***********************************************************/
///根据当前选中的值进行波特率设置
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
	m_Date_Select=((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetCurSel();//当前选中的行
	
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
	m_StopBit=((CComboBox*)GetDlgItem(IDC_COMBO_STOP))->GetCurSel();//当前选中的行
	
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
	m_ParityCheck=((CComboBox*)GetDlgItem(IDC_COMBO_JIAOYAN))->GetCurSel();//当前选中的行
	
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
//检查是否改变默认的串口值，没有改变m_Index的值是0的，否则则不为0
	if(m_Index<0)//串口的默认值没有改变	
		{	
			switch(m_ctrlComm.GetPortOpen())//点击打开或关闭串口按键时，根据当前串口是否打开进行相应操作
			{
			case 1:	

					/**************************************************************/
				
					//当前串口是打开的则进行关串口操作
					m_ctrlComm.SetPortOpen(FALSE);//关闭串口
					SetDlgItemText(IDC_BUTTON_OPEN,"打开串口");//更改按键指示
					UpdateData(FALSE);//更新按键状态
					break;
			case 0://当前串口是关闭的则进行开串口操作
					m_ctrlComm.SetCommPort(1);//如果要打开串口则应先选择哪个串口
					m_ctrlComm.SetPortOpen(TRUE);//打开串口
					SetDlgItemText(IDC_BUTTON_OPEN,"关闭串口");//更改按键指示
					UpdateData(FALSE);
					break;
			default : AfxMessageBox("cannot open or close serial port");	
			}
		}
	else//串口的默认值有改变
		{
		switch(m_ctrlComm.GetPortOpen())//点击打开或关闭串口按键时，根据当前串口是否打开进行相应操作
			{
			case 0://当前串口是关闭的则进行开串口操作	
					m_ctrlComm.SetCommPort(m_Index+1);//如果要打开串口则应先选择哪个串口
					m_ctrlComm.SetPortOpen(TRUE);//打开串口
					SetDlgItemText(IDC_BUTTON_OPEN,"关闭串口");//更改按键指示					
					UpdateData(FALSE);//更新按键状态
					break;
			case 1: 
				
					//当前串口是打开的则进行关串口操作					
					m_ctrlComm.SetPortOpen(FALSE);
					SetDlgItemText(IDC_BUTTON_OPEN,"打开串口");					
					UpdateData(FALSE);
					break;
			default : AfxMessageBox("cannot open serial port");
			}
		}
	if(m_Index<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_PORT))->SetCurSel(0);//如果没有另外进行串口选择则显示COM1
	if(m_BaudRate<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_BOTE))->SetCurSel(3);//如果没有另外进行波特率选择则显示9600
	if(m_Date_Select<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->SetCurSel(0);////如果没有另外进行数据位选择则显示8
	if(m_StopBit<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_STOP))->SetCurSel(0);//如果没有另外进行停止位选择则显示1
	if(m_ParityCheck<0)
		((CComboBox*)GetDlgItem(IDC_COMBO_JIAOYAN))->SetCurSel(0);//如果没有另外进行校验位选择则显示没有校验位N
}


void CRescuekj2View::OnAppExit() 
{
	// TODO: Add your command handler code here
		myAccess.ExitConnect();				//关闭数据库
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
