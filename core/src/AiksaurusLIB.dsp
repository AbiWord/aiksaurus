# Microsoft Developer Studio Project File - Name="AiksaurusLIB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AiksaurusLIB - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AiksaurusLIB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AiksaurusLIB.mak" CFG="AiksaurusLIB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AiksaurusLIB - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AiksaurusLIB - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AiksaurusLIB - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_STATIC_BUILD" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\Aiksaurus.lib"

!ELSEIF  "$(CFG)" == "AiksaurusLIB - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_STATIC_BUILD" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\Aiksaurus.lib"
# Begin Custom Build
ProjDir=.
InputPath=.\Debug\Aiksaurus.lib
SOURCE="$(InputPath)"

"$(ProjDir) config.h.msc > $(ProjDir) config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	type

# End Custom Build

!ENDIF 

# Begin Target

# Name "AiksaurusLIB - Win32 Release"
# Name "AiksaurusLIB - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Aiksaurus.cpp
# End Source File
# Begin Source File

SOURCE=.\AiksaurusC.cpp
# End Source File
# Begin Source File

SOURCE=.\AiksaurusException.cpp
# End Source File
# Begin Source File

SOURCE=.\AsciiCompare.cpp
# End Source File
# Begin Source File

SOURCE=.\MeaningsFile.cpp
# End Source File
# Begin Source File

SOURCE=.\WordsFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Aiksaurus.h
# End Source File
# Begin Source File

SOURCE=.\AiksaurusC.h
# End Source File
# Begin Source File

SOURCE=.\AiksaurusException.h
# End Source File
# Begin Source File

SOURCE=.\AsciiCompare.h
# End Source File
# Begin Source File

SOURCE=.\MeaningsFile.h
# End Source File
# Begin Source File

SOURCE=.\MeaningsHash.h
# End Source File
# Begin Source File

SOURCE=.\WordsFile.h
# End Source File
# Begin Source File

SOURCE=.\WordsHash.h
# End Source File
# Begin Source File

SOURCE=.\WordStream.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\config.h.msc

!IF  "$(CFG)" == "AiksaurusLIB - Win32 Release"

# Begin Custom Build
ProjDir=.
InputPath=.\config.h.msc

"$(ProjDir)\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(ProjDir)\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "AiksaurusLIB - Win32 Debug"

# Begin Custom Build
ProjDir=.
InputPath=.\config.h.msc

"$(ProjDir)\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(ProjDir)\config.h

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
