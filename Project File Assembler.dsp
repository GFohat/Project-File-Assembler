# Microsoft Developer Studio Project File - Name="Project File Assembler" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Project File Assembler - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Project File Assembler.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Project File Assembler.mak" CFG="Project File Assembler - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Project File Assembler - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Project File Assembler - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/WinLINK/Develop/Project File Assembler", JPIOAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Project File Assembler - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Project File Assembler - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Project File Assembler - Win32 Release"
# Name "Project File Assembler - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\axsimpledatagrid.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicThread3.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicThread3StartParams.cpp
# End Source File
# Begin Source File

SOURCE=.\BrushHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildListing.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildReporter.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboListItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CompareHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlPopulator.cpp
# End Source File
# Begin Source File

SOURCE=.\CopyHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\CsvHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSourceInfoHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\DirBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\DirInitHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInputBox.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOpenAProject.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQuickHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSplash.cpp
# End Source File
# Begin Source File

SOURCE=.\EditListItem.cpp
# End Source File
# Begin Source File

SOURCE=.\FileCopyReport.cpp
# End Source File
# Begin Source File

SOURCE=.\FileCopyThread.cpp
# End Source File
# Begin Source File

SOURCE=.\FileCopyThreadParams.cpp
# End Source File
# Begin Source File

SOURCE=.\FileInfoStrings.cpp
# End Source File
# Begin Source File

SOURCE=.\FileListItemData.cpp
# End Source File
# Begin Source File

SOURCE=.\FileListSortParams.cpp
# End Source File
# Begin Source File

SOURCE=.\FileMetaData.cpp
# End Source File
# Begin Source File

SOURCE=.\FixedFileInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FontHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCacheItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCacheItemHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\ListColumnData.cpp
# End Source File
# Begin Source File

SOURCE=.\ListColumnsHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\ListGeneralFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\ListSorter.cpp
# End Source File
# Begin Source File

SOURCE=.\ListSortParams.cpp
# End Source File
# Begin Source File

SOURCE=.\ListTickSetter.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalProps.cpp
# End Source File
# Begin Source File

SOURCE=.\LogEntryData.cpp
# End Source File
# Begin Source File

SOURCE=.\Pipes\NamedPipeClient.cpp
# End Source File
# Begin Source File

SOURCE=.\OleDbErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\PageBatFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\PageData.cpp
# End Source File
# Begin Source File

SOURCE=.\PageDataProps.cpp
# End Source File
# Begin Source File

SOURCE=.\PageInstallShield.cpp
# End Source File
# Begin Source File

SOURCE=.\PageLogging.cpp
# End Source File
# Begin Source File

SOURCE=.\PageLoggingOwnerData.cpp
# End Source File
# Begin Source File

SOURCE=.\PageOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\PagePfaData.cpp
# End Source File
# Begin Source File

SOURCE=.\PageStepDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\PageStepType.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamsCopyProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamsShowFilePCPosition.cpp
# End Source File
# Begin Source File

SOURCE=.\PfaArchiveHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\PfaDataListItem.cpp
# End Source File
# Begin Source File

SOURCE=.\PfaMainSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\PfaStep.cpp
# End Source File
# Begin Source File

SOURCE=.\PfaStepHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\Pipes\PipeServerInstanceThreadParams.cpp
# End Source File
# Begin Source File

SOURCE=.\Pipes\PipeServerThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Pipes\PipeServerThreadParams.cpp
# End Source File
# Begin Source File

SOURCE=".\Project File Assembler.cpp"
# End Source File
# Begin Source File

SOURCE=".\Project File Assembler.rc"
# End Source File
# Begin Source File

SOURCE=".\Project File AssemblerDlg.cpp"
# End Source File
# Begin Source File

SOURCE=".\ProjectFileAssembler.idl"
# ADD MTL /h "ProjectFileAssembler_i.h" /iid "ProjectFileAssembler_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\PropSheetCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\SheetStepProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashThreadUI.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemTime2.cpp
# End Source File
# Begin Source File

SOURCE=.\XLateFieldText.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\axsimpledatagrid.h
# End Source File
# Begin Source File

SOURCE=.\BasicThread3.h
# End Source File
# Begin Source File

SOURCE=.\BasicThread3StartParams.h
# End Source File
# Begin Source File

SOURCE=.\BrushHolder.h
# End Source File
# Begin Source File

SOURCE=.\BuildListing.h
# End Source File
# Begin Source File

SOURCE=.\BuildReporter.h
# End Source File
# Begin Source File

SOURCE=.\ButtonIcon.h
# End Source File
# Begin Source File

SOURCE=.\ComboListItem.h
# End Source File
# Begin Source File

SOURCE=.\CompareHelp.h
# End Source File
# Begin Source File

SOURCE=.\ConsBatFiles.h
# End Source File
# Begin Source File

SOURCE=.\ConstAppearance.h
# End Source File
# Begin Source File

SOURCE=.\ConstColours.h
# End Source File
# Begin Source File

SOURCE=.\ConstCompareResult.h
# End Source File
# Begin Source File

SOURCE=.\ConstCsvSetup.h
# End Source File
# Begin Source File

SOURCE=.\ConstDatasourceProps.h
# End Source File
# Begin Source File

SOURCE=.\ConstDynamicCtrlIDs.h
# End Source File
# Begin Source File

SOURCE=.\ConstEventTypes.h
# End Source File
# Begin Source File

SOURCE=.\ConstGlobals.h
# End Source File
# Begin Source File

SOURCE=.\ConstInstallShield.h
# End Source File
# Begin Source File

SOURCE=.\ConstLists.h
# End Source File
# Begin Source File

SOURCE=.\ConstMenus.h
# End Source File
# Begin Source File

SOURCE=.\ConstMsgs.h
# End Source File
# Begin Source File

SOURCE=.\ConstOptions.h
# End Source File
# Begin Source File

SOURCE=.\Pipes\ConstPipe.h
# End Source File
# Begin Source File

SOURCE=.\Pipes\ConstPipeMsgs.h
# End Source File
# Begin Source File

SOURCE=.\ConstReport.h
# End Source File
# Begin Source File

SOURCE=.\ConstSQL.h
# End Source File
# Begin Source File

SOURCE=.\ConstStepDetails.h
# End Source File
# Begin Source File

SOURCE=.\ConstStepStatus.h
# End Source File
# Begin Source File

SOURCE=.\ConstStepTypes.h
# End Source File
# Begin Source File

SOURCE=.\ConstTokens.h
# End Source File
# Begin Source File

SOURCE=.\ConstUDL.h
# End Source File
# Begin Source File

SOURCE=.\ControlPopulator.h
# End Source File
# Begin Source File

SOURCE=.\CopyHelper.h
# End Source File
# Begin Source File

SOURCE=.\csafe.h
# End Source File
# Begin Source File

SOURCE=.\CsvHelper.h
# End Source File
# Begin Source File

SOURCE=.\DataSourceInfoHolder.h
# End Source File
# Begin Source File

SOURCE=.\DebugTimer.h
# End Source File
# Begin Source File

SOURCE=.\DirBrowser.h
# End Source File
# Begin Source File

SOURCE=.\DirInitHandler.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddFiles.h
# End Source File
# Begin Source File

SOURCE=.\DlgInputBox.h
# End Source File
# Begin Source File

SOURCE=.\DlgOpenAProject.h
# End Source File
# Begin Source File

SOURCE=.\DlgQuickHelp.h
# End Source File
# Begin Source File

SOURCE=.\DlgSplash.h
# End Source File
# Begin Source File

SOURCE=.\EditListItem.h
# End Source File
# Begin Source File

SOURCE=.\FileCopyReport.h
# End Source File
# Begin Source File

SOURCE=.\FileCopyThread.h
# End Source File
# Begin Source File

SOURCE=.\FileCopyThreadParams.h
# End Source File
# Begin Source File

SOURCE=.\FileInfoStrings.h
# End Source File
# Begin Source File

SOURCE=.\FileListItemData.h
# End Source File
# Begin Source File

SOURCE=.\FileListSortParams.h
# End Source File
# Begin Source File

SOURCE=.\FileMetaData.h
# End Source File
# Begin Source File

SOURCE=.\FixedFileInfo.h
# End Source File
# Begin Source File

SOURCE=.\FontHandler.h
# End Source File
# Begin Source File

SOURCE=.\ImportADO.h
# End Source File
# Begin Source File

SOURCE=.\ListCacheItem.h
# End Source File
# Begin Source File

SOURCE=.\ListCacheItemHolder.h
# End Source File
# Begin Source File

SOURCE=.\ListColumnData.h
# End Source File
# Begin Source File

SOURCE=.\ListColumnsHelper.h
# End Source File
# Begin Source File

SOURCE=.\ListGeneralFiles.h
# End Source File
# Begin Source File

SOURCE=.\ListSorter.h
# End Source File
# Begin Source File

SOURCE=.\ListSortParams.h
# End Source File
# Begin Source File

SOURCE=.\ListTickSetter.h
# End Source File
# Begin Source File

SOURCE=.\LocalProps.h
# End Source File
# Begin Source File

SOURCE=.\LogEntryData.h
# End Source File
# Begin Source File

SOURCE=.\Pipes\NamedPipeClient.h
# End Source File
# Begin Source File

SOURCE=.\OleDbErrorHandler.h
# End Source File
# Begin Source File

SOURCE=.\PageBatFiles.h
# End Source File
# Begin Source File

SOURCE=.\PageData.h
# End Source File
# Begin Source File

SOURCE=.\PageDataProps.h
# End Source File
# Begin Source File

SOURCE=.\PageInstallShield.h
# End Source File
# Begin Source File

SOURCE=.\PageLogging.h
# End Source File
# Begin Source File

SOURCE=.\PageLoggingOwnerData.h
# End Source File
# Begin Source File

SOURCE=.\PageOptions.h
# End Source File
# Begin Source File

SOURCE=.\PagePfaData.h
# End Source File
# Begin Source File

SOURCE=.\PageStepDetails.h
# End Source File
# Begin Source File

SOURCE=.\PageStepType.h
# End Source File
# Begin Source File

SOURCE=.\ParamsCopyProgress.h
# End Source File
# Begin Source File

SOURCE=.\ParamsShowFilePCPosition.h
# End Source File
# Begin Source File

SOURCE=.\PfaArchiveHandler.h
# End Source File
# Begin Source File

SOURCE=.\PfaDataListItem.h
# End Source File
# Begin Source File

SOURCE=.\PfaMainSheet.h
# End Source File
# Begin Source File

SOURCE=.\PfaStep.h
# End Source File
# Begin Source File

SOURCE=.\PfaStepHolder.h
# End Source File
# Begin Source File

SOURCE=.\PictureHelper.h
# End Source File
# Begin Source File

SOURCE=.\Pipes\PipeServerInstanceThreadParams.h
# End Source File
# Begin Source File

SOURCE=.\Pipes\PipeServerThread.h
# End Source File
# Begin Source File

SOURCE=.\Pipes\PipeServerThreadParams.h
# End Source File
# Begin Source File

SOURCE=".\Project File Assembler.h"
# End Source File
# Begin Source File

SOURCE=".\Project File AssemblerDlg.h"
# End Source File
# Begin Source File

SOURCE=.\PropSheetCommon.h
# End Source File
# Begin Source File

SOURCE=.\ReportHelper.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SheetStepProperties.h
# End Source File
# Begin Source File

SOURCE=.\SplashThreadUI.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemTime2.h
# End Source File
# Begin Source File

SOURCE=.\tblLogging.H
# End Source File
# Begin Source File

SOURCE=.\THR.h
# End Source File
# Begin Source File

SOURCE=.\VersionNo.h

!IF  "$(CFG)" == "Project File Assembler - Win32 Release"

# Begin Custom Build
OutDir=.\Release
InputPath=.\VersionNo.h
InputName=VersionNo

"$(OutDir)\$(InputName)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(OutDir)\$(InputName)

# End Custom Build

!ELSEIF  "$(CFG)" == "Project File Assembler - Win32 Debug"

# Begin Custom Build
OutDir=.\Debug
InputPath=.\VersionNo.h
InputName=VersionNo

"$(OutDir)\$(InputName)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(OutDir)\$(InputName)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XLateFieldText.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\Graphics\aah logo - banner 2.bmp"
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\icon_failure.ico
# End Source File
# Begin Source File

SOURCE=.\RES\icon_success.ico
# End Source File
# Begin Source File

SOURCE=.\RES\icon_warning.ico
# End Source File
# Begin Source File

SOURCE=".\res\Project File Assembler.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Project File Assembler.rc2"
# End Source File
# Begin Source File

SOURCE=".\Project File Assembler.rgs"
# End Source File
# End Group
# Begin Source File

SOURCE=.\Debug\msado15.tlh
# End Source File
# Begin Source File

SOURCE=.\Debug\msado15.tli
# End Source File
# Begin Source File

SOURCE=".\Documentation\Project File Assembler II.doc"
# End Source File
# Begin Source File

SOURCE=".\Database\Project File Assembler.mdb"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Project File Assembler : {3378EBDB-24C7-479E-9EA6-B955306E142F}
# 	2:5:Class:CAxSimpleDataGrid
# 	2:10:HeaderFile:axsimpledatagrid.h
# 	2:8:ImplFile:axsimpledatagrid.cpp
# End Section
# Section Project File Assembler : {00040004-46CF-0000-125E-002000000000}
# 	1:24:IDR_PROJECTFILEASSEMBLER:103
# End Section
# Section Project File Assembler : {FE10BF68-B99D-4982-A1EC-067C00FFDDA2}
# 	2:21:DefaultSinkHeaderFile:axsimpledatagrid.h
# 	2:16:DefaultSinkClass:CAxSimpleDataGrid
# End Section
