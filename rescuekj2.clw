; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=add
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rescuekj2.h"
LastPage=0

ClassCount=7
Class1=CRescuekj2App
Class2=CRescuekj2Doc
Class3=CRescuekj2View
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_RESCUEKJ2_FORM
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX
Class6=add
Class7=AdoAccess
Resource4=IDD_DIALOG1

[CLS:CRescuekj2App]
Type=0
HeaderFile=rescuekj2.h
ImplementationFile=rescuekj2.cpp
Filter=N
LastObject=Cen_ter

[CLS:CRescuekj2Doc]
Type=0
HeaderFile=rescuekj2Doc.h
ImplementationFile=rescuekj2Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CRescuekj2Doc

[CLS:CRescuekj2View]
Type=0
HeaderFile=rescuekj2View.h
ImplementationFile=rescuekj2View.cpp
Filter=D
LastObject=ID_APP_EXIT
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=Cen_ter
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=rescuekj2.cpp
ImplementationFile=rescuekj2.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[DLG:IDD_RESCUEKJ2_FORM]
Type=1
Class=CRescuekj2View
ControlCount=16
Control1=IDC_MAP1,{9D6ED188-5910-11D2-98A6-00A0C9742CCA},1342242816
Control2=IDC_EDIT_HISTORYMEG,edit,1352728644
Control3=IDC_STATIC_HISTORY,static,1342308363
Control4=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control5=IDC_STATIC_ALL,button,1342308359
Control6=IDC_STATIC_HAO,static,1342308352
Control7=IDC_COMBO_PORT,combobox,1344471043
Control8=IDC_STATIC_BOTE,static,1342308352
Control9=IDC_COMBO_BOTE,combobox,1344471043
Control10=IDC_STATIC_DATA,static,1342308352
Control11=IDC_COMBO_DATA,combobox,1344471043
Control12=IDC_STATIC_JIAOYAN,static,1342308352
Control13=IDC_COMBO_JIAOYAN,combobox,1344471043
Control14=IDC_STATIC_STOP,static,1342308352
Control15=IDC_COMBO_STOP,combobox,1344471043
Control16=IDC_BUTTON_OPEN,button,1342373888

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=Zoom_In
Command5=Zoom_Out
Command6=Move_Pan
Command7=Cen_ter
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=add
ControlCount=10
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

[CLS:add]
Type=0
HeaderFile=add.h
ImplementationFile=add.cpp
BaseClass=CDialog
Filter=D
LastObject=add
VirtualFilter=dWC

[CLS:AdoAccess]
Type=0
HeaderFile=AdoAccess.h
ImplementationFile=AdoAccess.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=AdoAccess

[DB:AdoAccess]
DB=1
DBType=ODBC
ColumnCount=0

