; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CQuestionMark
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SAPARiNoMoreBumps.h"

ClassCount=4
Class1=CSAPARiNoMoreBumpsApp
Class2=CSAPARiNoMoreBumpsDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SAPARINOMOREBUMPS_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_SAPARINOMOREBUMPS_DIALOG (English (U.S.))
Class4=CQuestionMark
Resource6=IDD_DIALOG_Q

[CLS:CSAPARiNoMoreBumpsApp]
Type=0
HeaderFile=SAPARiNoMoreBumps.h
ImplementationFile=SAPARiNoMoreBumps.cpp
Filter=N

[CLS:CSAPARiNoMoreBumpsDlg]
Type=0
HeaderFile=SAPARiNoMoreBumpsDlg.h
ImplementationFile=SAPARiNoMoreBumpsDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSAPARiNoMoreBumpsDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=SAPARiNoMoreBumpsDlg.h
ImplementationFile=SAPARiNoMoreBumpsDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_SAPARINOMOREBUMPS_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSAPARiNoMoreBumpsDlg

[DLG:IDD_SAPARINOMOREBUMPS_DIALOG (English (U.S.))]
Type=1
Class=CSAPARiNoMoreBumpsDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_RADIO_BOY,button,1342177289
Control3=IDC_STATIC_BOY,static,1342177283
Control4=IDC_RADIO_PENG,button,1342177289
Control5=IDC_STATIC_PENG,static,1342177283

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[DLG:IDD_DIALOG_Q]
Type=1
Class=CQuestionMark
ControlCount=0

[CLS:CQuestionMark]
Type=0
HeaderFile=QuestionMark.h
ImplementationFile=QuestionMark.cpp
BaseClass=CDialog
Filter=D
LastObject=CQuestionMark
VirtualFilter=dWC

