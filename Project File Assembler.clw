; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPageData
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "project file assembler.h"
LastPage=0

ClassCount=26
Class1=CAutoListCtrl
Class2=CBuildListing
Class3=CDlgInputBox
Class4=CDlgQuickHelp
Class5=CFolderDialog
Class6=CPageBatFiles
Class7=CPageInstallShield
Class8=CPagePfaData
Class9=CPageStepType
Class10=CPfaMainSheet
Class11=CProjectFileAssemblerApp
Class12=CAboutDlg
Class13=CProjectFileAssemblerDlg
Class14=CSheetStepProperties

ResourceCount=23
Resource1=IDD_PAGE_LOGGING (English (U.S.))
Resource2=IDD_PAGE_DATA (English (U.S.))
Resource3=IDD_PAGE_BATCH_FILES (English (U.S.))
Resource4=IDD_DLG_OPEN_PROJECT
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_DLG_SPLASH
Resource7=IDR_MNU_PROJECT
Resource8=IDD_PAGE_STEP_DETAILS (English (U.S.))
Resource9=IDR_MNU_CTXT_PFADATA
Resource10=IDD_PROJECTFILEASSEMBLER_DIALOG (English (U.S.))
Class15=CPageStepDetails
Resource11=IDD_PAGE_PFA_DATA (English (U.S.))
Class16=CDlgAddFiles
Class17=CEditListItem
Class18=CComboListItem
Resource12=IDD_DLG_ADD_FILES
Resource13=IDD_PAGE_OPTIONS (English (U.S.))
Resource14=IDD_PAGE_DATA_PROPS (English (U.S.))
Class19=CDlgOpenAProject
Resource15=IDD_PAGE_STEP_TYPE (English (U.S.))
Resource16=IDD_DLG_STRING_REQUESTER
Resource17=IDD_PAGE_INSTALLSHIELD (English (U.S.))
Class20=CPageOptions
Resource18=IDR_MNU_ACTION
Class21=CPageDataProps
Resource19=IDD_PAGE_LOGGING_ADO (English (U.S.))
Class22=CDlgSplash
Class23=CStaticSelfDraw
Class24=CButtonIcon
Resource20=IDR_MNU_PPAGE_DATA
Class25=CPageLogging
Resource21=IDD_DLG_HELP
Resource22=IDD_DIALOG_BUILD
Class26=CPageData
Resource23=IDR_MNU_MINIMAL

[CLS:CAutoListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=autolistctrl.h
ImplementationFile=autolistctrl.cpp

[CLS:CBuildListing]
Type=0
BaseClass=CDialog
HeaderFile=BuildListing.h
ImplementationFile=BuildListing.cpp

[CLS:CDlgInputBox]
Type=0
BaseClass=CDialog
HeaderFile=DlgInputBox.h
ImplementationFile=DlgInputBox.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgInputBox

[CLS:CDlgQuickHelp]
Type=0
BaseClass=CDialog
HeaderFile=DlgQuickHelp.h
ImplementationFile=DlgQuickHelp.cpp

[CLS:CFolderDialog]
Type=0
BaseClass=CFileDialog
HeaderFile=folder_dialog.h
ImplementationFile=folder_dialog.cpp

[CLS:CPageBatFiles]
Type=0
BaseClass=CPropertyPage
HeaderFile=PageBatFiles.h
ImplementationFile=PageBatFiles.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_RED_BATCH_CONTENTS

[CLS:CPageInstallShield]
Type=0
BaseClass=CPropertyPage
HeaderFile=PageInstallShield.h
ImplementationFile=PageInstallShield.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_LCTRL_IS_PROJECTS

[CLS:CPagePfaData]
Type=0
BaseClass=CPropertyPage
HeaderFile=PagePfaData.h
ImplementationFile=PagePfaData.cpp
Filter=D
VirtualFilter=idWC
LastObject=ID_PROJECT_ARCHIVE_IMPORT

[CLS:CPageStepType]
Type=0
BaseClass=CPropertyPage
HeaderFile=PageStepType.h
ImplementationFile=PageStepType.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_CMBO_STEP_TYPE

[CLS:CPfaMainSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=PfaMainSheet.h
ImplementationFile=PfaMainSheet.cpp
Filter=W
VirtualFilter=hWC
LastObject=CPfaMainSheet

[CLS:CProjectFileAssemblerApp]
Type=0
BaseClass=CWinApp
HeaderFile=Project File Assembler.h
ImplementationFile=Project File Assembler.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Project File AssemblerDlg.cpp
ImplementationFile=Project File AssemblerDlg.cpp

[CLS:CProjectFileAssemblerDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=Project File AssemblerDlg.h
ImplementationFile=Project File AssemblerDlg.cpp
Filter=D
VirtualFilter=idWC
LastObject=CProjectFileAssemblerDlg

[CLS:CSheetStepProperties]
Type=0
BaseClass=CPropertySheet
HeaderFile=SheetStepProperties.h
ImplementationFile=SheetStepProperties.cpp
LastObject=CSheetStepProperties

[DLG:IDD_DIALOG_BUILD]
Type=1
Class=CBuildListing
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDC_LIST1,SysListView32,1350631433
Control3=IDC_BTN_SOURCE,button,1342242816
Control4=IDC_BTN_DEST_DIR,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_SOURCEDIR,edit,1350631552
Control7=IDC_EDIT_DEST_DIR,edit,1350631552
Control8=IDC_BTN_FILE_NAME,button,1342242816
Control9=IDC_LBL_FILE_NAME,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_BTN_BUILD_LIST,button,1342242816
Control15=IDC_BTN_CHECK_ALL,button,1342242816
Control16=IDC_BTN_SCAN_DIR,button,1342242816
Control17=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_STRING_REQUESTER]
Type=1
Class=CDlgInputBox
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ED_TEXT,edit,1350631553
Control4=IDC_STATIC,button,1342177287
Control5=IDC_BN_BROWSE_DIR,button,1342242816
Control6=IDC_ED_PROMPT,edit,1342244933

[DLG:IDD_DLG_HELP]
Type=1
Class=CDlgQuickHelp
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_RED_HELPTEXT,RICHEDIT,1352730948

[DLG:IDD_PAGE_BATCH_FILES]
Type=1
Class=CPageBatFiles

[DLG:IDD_PAGE_INSTALLSHIELD]
Type=1
Class=CPageInstallShield

[DLG:IDD_PAGE_PFA_DATA]
Type=1
Class=CPagePfaData

[DLG:IDD_PAGE_STEP_TYPE]
Type=1
Class=CPageStepType

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_PROJECTFILEASSEMBLER_DIALOG]
Type=1
Class=CProjectFileAssemblerDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROJECTFILEASSEMBLER_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDC_LIST1,SysListView32,1350631437
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_LBL_FILEPATH,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CHECK2,button,1342242819
Control9=IDC_BTN_BUILD_LISTNG,button,1342242816
Control10=IDC_PROGRESS_ASSEMBLER,msctls_progress32,1350565889
Control11=IDC_PROGRESS_FILE,msctls_progress32,1350565889
Control12=IDC_BN_QUICK_HELP,button,1342242816

[DLG:IDD_PAGE_BATCH_FILES (English (U.S.))]
Type=1
Class=CPageBatFiles
ControlCount=10
Control1=IDC_ED_CUR_BATFILE,edit,1350633600
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BN_RUN_BATFILE,button,1342242816
Control4=IDC_ED_CUR_RESULTSFILE,edit,1350633600
Control5=IDC_STATIC,button,1342177287
Control6=IDC_BN_OPEN_RSLTS,button,1342242816
Control7=IDC_RED_RECV,RICHEDIT,1352730948
Control8=IDC_BN_TEST_PIPE,button,1342242816
Control9=IDC_LCTRL_BATFILES,SysListView32,1350631437
Control10=IDC_RED_BATCH_CONTENTS,RICHEDIT,1352730692

[DLG:IDD_PAGE_INSTALLSHIELD (English (U.S.))]
Type=1
Class=CPageInstallShield
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RDO_IS_10,button,1342181385
Control3=IDC_RDO_IS_12,button,1342181385
Control4=IDC_BN_LAUNCH_IS,button,1342242816
Control5=IDC_BN_EXPLORE,button,1342242816
Control6=IDC_LCTRL_IS_PROJECTS,SysListView32,1350631437
Control7=IDC_LCTRL_IS_MEDIA,SysListView32,1350631437

[DLG:IDD_PAGE_PFA_DATA (English (U.S.))]
Type=1
Class=CPagePfaData
ControlCount=19
Control1=IDC_LST_PROJECT_ITEMS,SysListView32,1350631425
Control2=IDC_PRGRS_BATCH,msctls_progress32,1350565888
Control3=IDC_PRGRS_FILE,msctls_progress32,1350565889
Control4=IDC_ED_DFLT_SRC_DIR,edit,1350633600
Control5=IDC_ED_DFLT_DEST_DIR,edit,1350633600
Control6=IDC_BN_BROWSE_DFLT_SRC_DIR,button,1342242816
Control7=IDC_BN_BROWSE_DFLT_DEST_DIR,button,1342242816
Control8=IDC_CHK_LOCK,button,1342246915
Control9=IDC_STATIC_DFLT_SRC,static,1342308352
Control10=IDC_STATIC_DFLT_DEST,static,1342308352
Control11=IDC_BN_EXPORT_CSV,button,1342242816
Control12=IDC_ED_CUR_PROJECT,edit,1350633601
Control13=IDC_BN_EXPORT_CSV_TICKED,button,1342242816
Control14=IDC_ED_ROW_COUNT,edit,1350633601
Control15=IDC_BN_SEL_ALL,button,1342242816
Control16=IDC_BN_SEL_NONE,button,1342242816
Control17=IDC_BN_SEL_INVERT,button,1342242816
Control18=IDC_BN_SEL_HIGHLIGHTED,button,1342242816
Control19=IDC_BN_REFRESH,button,1342242816

[DLG:IDD_PAGE_STEP_TYPE (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_CMBO_STEP_TYPE,combobox,1478557955

[MNU:IDR_MNU_CTXT_PFADATA]
Type=1
Class=?
Command1=ID_CTXT_ADDASTEP
Command2=ID_CTXT_EDITASTEP
Command3=ID_CTXT_COPYASTEP
Command4=ID_CTXT_DELETEASTEP
Command5=ID_CTXT_ADDSINGLEFILES
Command6=ID_CTXT_REORDINATE
Command7=ID_CTXT_EXPLORESOURCE
Command8=ID_CTXT_EXPLOREDESTINATION
CommandCount=8

[DLG:IDD_PAGE_STEP_DETAILS (English (U.S.))]
Type=1
Class=CPageStepDetails
ControlCount=16
Control1=IDC_RED_TEXT_SRCFILE,RICHEDIT,1350631492
Control2=IDC_ED_LABEL_SRCFILE,edit,1350633600
Control3=IDC_RED_TEXT_SOURCEDIR,RICHEDIT,1350631492
Control4=IDC_ED_LABEL_SOURCEDIR,edit,1350633600
Control5=IDC_RED_TEXT_DESTDIR,RICHEDIT,1350631492
Control6=IDC_ED_LABEL_DESTDIR,edit,1350633600
Control7=IDC_RED_TEXT_DESTFILE,RICHEDIT,1350631492
Control8=IDC_ED_LABEL_DESTFILE,edit,1350633600
Control9=IDC_BN_SRC_FILE,button,1342242816
Control10=IDC_BN_SRC_DIR,button,1342242816
Control11=IDC_BN_DEST_DIR,button,1342242816
Control12=IDC_BN_DEST_FILE,button,1476460544
Control13=IDC_CMBO_STEP_TYPE,combobox,1344340227
Control14=IDC_STATIC,button,1342177287
Control15=IDC_BN_SRC_DIR_DEFAULT,button,1342242816
Control16=IDC_BN_DEST_DIR_DEFAULT,button,1342242816

[CLS:CPageStepDetails]
Type=0
HeaderFile=PageStepDetails.h
ImplementationFile=PageStepDetails.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_BN_SRC_DIR_DEFAULT

[DLG:IDD_DLG_ADD_FILES]
Type=1
Class=CDlgAddFiles
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_CUR_FILES,SysListView32,1350631433
Control4=IDC_ED_CUR_DIR,edit,1350631552
Control5=IDC_BN_BROWSE,button,1342242816
Control6=IDC_BN_SEL_ALL,button,1342242816
Control7=IDC_BN_SEL_NONE,button,1342242816
Control8=IDC_BN_SEL_INVERT,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_BN_SEL_HIGHLIGHTED,button,1342242816

[CLS:CDlgAddFiles]
Type=0
HeaderFile=DlgAddFiles.h
ImplementationFile=DlgAddFiles.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_CUR_FILES

[CLS:CEditListItem]
Type=0
HeaderFile=EditListItem.h
ImplementationFile=EditListItem.cpp
BaseClass=CRichEditCtrl
Filter=W
LastObject=CEditListItem
VirtualFilter=WC

[CLS:CComboListItem]
Type=0
HeaderFile=ComboListItem.h
ImplementationFile=ComboListItem.cpp
BaseClass=CComboBox
Filter=W

[MNU:IDR_MNU_PROJECT]
Type=1
Class=?
Command1=ID_PROJECT_NEW
Command2=ID_PROJECT_OPEN
Command3=ID_PROJECT_SAVEAS
Command4=ID_PROJECT_DELETE
CommandCount=4

[MNU:IDR_MNU_ACTION]
Type=1
Class=?
Command1=ID_ACTION_VALIDATEPROJECT
Command2=ID_ACTION_COPYPROJECTFILES
CommandCount=2

[DLG:IDD_DLG_OPEN_PROJECT]
Type=1
Class=CDlgOpenAProject
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_EXIST_PROJECTS,SysListView32,1350631437

[CLS:CDlgOpenAProject]
Type=0
HeaderFile=DlgOpenAProject.h
ImplementationFile=DlgOpenAProject.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_EXIST_PROJECTS

[MNU:IDR_MNU_PPAGE_DATA]
Type=1
Class=?
Command1=ID_FILE_EXIT
Command2=ID_PROJECT_NEW
Command3=ID_PROJECT_OPEN
Command4=ID_PROJECT_SAVEAS
Command5=ID_PROJECT_DELETE
Command6=ID_PROJECT_ARCHIVE_EXPORT
Command7=ID_PROJECT_ARCHIVE_IMPORT
Command8=ID_ACTION_VALIDATEPROJECT
Command9=ID_ACTION_COPYPROJECTFILES
CommandCount=9

[MNU:IDR_MNU_MINIMAL]
Type=1
Class=?
Command1=ID_FILE_EXIT
CommandCount=1

[DLG:IDD_PAGE_OPTIONS (English (U.S.))]
Type=1
Class=CPageOptions
ControlCount=1
Control1=IDC_AXSIMPLEDATAGRIDCTRL1,{FE10BF68-B99D-4982-A1EC-067C00FFDDA2},1342242816

[CLS:CPageOptions]
Type=0
HeaderFile=PageOptions.h
ImplementationFile=PageOptions.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_AXSIMPLEDATAGRIDCTRL1

[DLG:IDD_PAGE_DATA_PROPS (English (U.S.))]
Type=1
Class=CPageDataProps
ControlCount=1
Control1=IDC_LIST_DATA_PROPS,SysListView32,1350631437

[CLS:CPageDataProps]
Type=0
HeaderFile=PageDataProps.h
ImplementationFile=PageDataProps.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPageDataProps

[DLG:IDD_DLG_SPLASH]
Type=1
Class=CDlgSplash
ControlCount=0

[CLS:CDlgSplash]
Type=0
HeaderFile=DlgSplash.h
ImplementationFile=DlgSplash.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgSplash

[CLS:CStaticSelfDraw]
Type=0
HeaderFile=StaticSelfDraw.h
ImplementationFile=StaticSelfDraw.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CStaticSelfDraw

[CLS:CButtonIcon]
Type=0
HeaderFile=ButtonIcon.h
ImplementationFile=ButtonIcon.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CButtonIcon

[DLG:IDD_PAGE_LOGGING (English (U.S.))]
Type=1
Class=CPageLogging
ControlCount=5
Control1=IDC_LIST_LOG,SysListView32,1350635533
Control2=IDC_LIST_CATEGORIES,SysListView32,1350631433
Control3=IDC_RED_LOG_TEXT,RICHEDIT,1352730948
Control4=IDC_RED_LOG_SOURCE,RICHEDIT,1352730948
Control5=IDC_RED_LOG_SQL,RICHEDIT,1352730948

[CLS:CPageLogging]
Type=0
HeaderFile=PageLogging.h
ImplementationFile=PageLogging.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=dWC
LastObject=CPageLogging

[DLG:IDD_PAGE_LOGGING_ADO (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_LIST_LOG,SysListView32,1350631437
Control2=IDC_LIST_CATEGORIES,SysListView32,1350631433
Control3=IDC_RED_LOG_TEXT,RICHEDIT,1352730948
Control4=IDC_RED_LOG_SOURCE,RICHEDIT,1352730948
Control5=IDC_RED_LOG_SQL,RICHEDIT,1352730948

[DLG:IDD_PAGE_DATA (English (U.S.))]
Type=1
Class=CPageData
ControlCount=2
Control1=IDC_AXSIMPLEDATAGRIDCTRL1,{FE10BF68-B99D-4982-A1EC-067C00FFDDA2},1342242816
Control2=IDC_ED_CLICKED,edit,1352730692

[CLS:CPageData]
Type=0
HeaderFile=PageData.h
ImplementationFile=PageData.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_AXSIMPLEDATAGRIDCTRL1

