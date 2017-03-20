; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=add
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rescuekj2.h"
LastPage=0
CDK=Y

ClassCount=10
Class1=add
Class2=AdoAccess
Class3=CMainFrame
Class4=CRescuekj2App
Class5=CAboutDlg
Class6=CRescuekj2Doc
Class7=CRescuekj2View

ResourceCount=7
Resource1=IDD_RESCUEKJ2_FORM
Resource2=IDD_PORT
Resource3=IDD_DIALOG1
Resource4=IDD_GONGLV
Resource5=IDR_MAINFRAME
Class8=portset
Class9=gonglv
Resource6=IDD_ABOUTBOX
Class10=info
Resource7=IDD_INFO

[CLS:add]
Type=0
BaseClass=CDialog
HeaderFile=add.h
ImplementationFile=add.cpp
LastObject=add
Filter=D
VirtualFilter=dWC

[CLS:AdoAccess]
Type=0
HeaderFile=AdoAccess.h
ImplementationFile=AdoAccess.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CRescuekj2App]
Type=0
BaseClass=CWinApp
HeaderFile=rescuekj2.h
ImplementationFile=rescuekj2.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=rescuekj2.cpp
ImplementationFile=rescuekj2.cpp

[CLS:CRescuekj2Doc]
Type=0
BaseClass=CDocument
HeaderFile=rescuekj2Doc.h
ImplementationFile=rescuekj2Doc.cpp

[CLS:CRescuekj2View]
Type=0
BaseClass=CFormView
HeaderFile=rescuekj2View.h
ImplementationFile=rescuekj2View.cpp
LastObject=IDC_MSCOMM1
Filter=D
VirtualFilter=VWC

[DB:AdoAccess]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_RESCUEKJ2_FORM]
Type=1
Class=CRescuekj2View
ControlCount=5
Control1=IDC_MAP1,{9D6ED188-5910-11D2-98A6-00A0C9742CCA},1342242816
Control2=IDC_EDIT_HISTORYMEG,edit,1352728644
Control3=IDC_STATIC_HISTORY,static,1342308363
Control4=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control5=IDC_TAB1,SysTabControl32,1350565888

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=IDC_VIEW
Command11=IDC_ADD
Command12=IDC_DELETE
Command13=Zoom_In
Command14=Zoom_Out
Command15=Move_Pan
Command16=Cen_ter
Command17=IDC_SET
Command18=IDC_CESHI
Command19=IDC_JIANTOU
Command20=ID_APP_ABOUT
CommandCount=20

[DLG:IDD_GONGLV]
Type=1
Class=gonglv
ControlCount=0

[DLG:IDD_PORT]
Type=1
Class=portset
ControlCount=12
Control1=IDC_STATIC_ALL,button,1342308359
Control2=IDC_COMBO_PORT,combobox,1344471043
Control3=IDC_STATIC_BOTE,static,1342308352
Control4=IDC_COMBO_BOTE,combobox,1344471043
Control5=IDC_STATIC_DATA,static,1342308352
Control6=IDC_COMBO_DATA,combobox,1344471043
Control7=IDC_STATIC_JIAOYAN,static,1342308352
Control8=IDC_COMBO_JIAOYAN,combobox,1344471043
Control9=IDC_STATIC_STOP,static,1342308352
Control10=IDC_COMBO_STOP,combobox,1344471043
Control11=IDC_BUTTON_OPEN,button,1342373888
Control12=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=Zoom_In
Command5=Zoom_Out
Command6=Move_Pan
Command7=Cen_ter
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:portset]
Type=0
HeaderFile=portset.h
ImplementationFile=portset.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO_STOP
VirtualFilter=dWC

[CLS:gonglv]
Type=0
HeaderFile=gonglv.h
ImplementationFile=gonglv.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Cen_ter

[DLG:IDD_INFO]
Type=1
Class=info
ControlCount=14
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC_SHOU,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC_SHU,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_TEMP,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_BEAT,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC_PINGGU,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC_ID,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC_NAME,static,1342308352

[CLS:info]
Type=0
HeaderFile=info.h
ImplementationFile=info.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Cen_ter

[DLG:IDD_DIALOG1]
Type=1
Class=add
ControlCount=23
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1_ID,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2_NAME,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3_GROUP,edit,1350631428
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4_JOB,edit,1350631428
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_SEX,edit,1350631552
Control17=IDC_EDIT_AGE,edit,1350631552
Control18=IDC_EDIT_XUEXING,edit,1350631552
Control19=IDC_EDIT_PHONE1,edit,1350631552
Control20=IDC_EDIT_PHONE2,edit,1350631552
Control21=IDC_EDIT_PHONE3,edit,1350631552
Control22=IDC_EDIT_PHONE4,edit,1350631552
Control23=IDC_EDIT_PHONE5,edit,1350631552

