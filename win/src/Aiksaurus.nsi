; This is a file for creating an installer for Aiksaurus using NSIS 
; by Michael D. Pritchett <mpritchett@attglobal.net>

; Do a Cyclic Redundancy Check to make sure the installer 
; was not corrupted by the download.  
CRCCheck on

; The name of the installer
Name "Aiksaurus"
Icon "setup.ico"
OutFile "setup_aiksaurus.exe"

; License Information
LicenseText "This program is Licensed under the GNU General Public License (GPL)."
LicenseData "Copying"

; The default installation directory
InstallDir $PROGRAMFILES\Aiksaurus

; Registry key to check for directory (so if you install again, it will overwrite the old one automatically)
InstallDirRegKey HKLM SOFTWARE\Aiksaurus "Install_Dir"

; The text to prompt the user to enter a directory
ComponentText "This will install Aiksaurus on your computer. Select other install options."

; The text to prompt the user to enter a directory
DirText "Choose a directory to install in to:"

EnabledBitmap  checkbox.bmp
DisabledBitmap emptybox.bmp

; The stuff that must be installed
; binary, license, and American dictionary
Section "Aiksaurus.exe (required)"
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; Set output path to the installation directory.
	SetOutPath $INSTDIR
	File "Aiksaurus.exe"
	File "AiksaurusCL.exe"
	File "..\..\data\words.dat"
	File "..\..\data\meanings.dat"
	File /oname=copying.txt "Copying"

	WriteRegStr HKLM "Software\Aiksaurus" "Install_Dir" "$INSTDIR"
	WriteRegStr HKLM "Software\Aiksaurus" "Data_Dir" "$INSTDIR\"

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Aiksaurus" "DisplayName" "Aiksaurus (remove only)"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Aiksaurus" "UninstallString" '"$INSTDIR\UninstallAiksaurus.exe"'

	; New Uninstaller 
	WriteUninstaller "UninstallAiksaurus.exe"

SectionEnd

; OPTIONAL Start Menu Shortcut
Section "Start Menu Shortcut"
	CreateDirectory "$SMPROGRAMS\Aiksaurus"
	CreateShortCut "$SMPROGRAMS\Aiksaurus\Uninstall Aiksaurus.lnk" "$INSTDIR\UninstallAiksaurus.exe" "" "$INSTDIR\UninstallAiksaurus.exe" 0
	CreateShortCut "$SMPROGRAMS\Aiksaurus\Aiksaurus.lnk" "$INSTDIR\Aiksaurus.exe" "" "$INSTDIR\Aiksaurus.exe" 0
SectionEnd

; OPTIONAL Desktop Shortcut 
Section "Desktop Shortcut"
	CreateShortCut "$DESKTOP\Aiksaurus.lnk" "$INSTDIR\Aiksaurus.exe" "" "$INSTDIR\Aiksaurus.exe" 0
SectionEnd

; uninstall stuff
UninstallText "This will uninstall Aiksaurus. Hit next to continue."
;UninstallExeName "UninstallAiksaurus.exe"

; special uninstall section.
Section "Uninstall"

	MessageBox MB_OKCANCEL "This will delete $INSTDIR and all subdirectories and files?" IDOK DoUnInstall
	
	Abort "Quitting the uninstall process"

	DoUnInstall:
	; remove registry keys
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Aiksaurus"
	DeleteRegKey HKLM SOFTWARE\Aiksaurus

	; remove start menu shortcuts.
	Delete "$SMPROGRAMS\Aiksaurus\*.*"

	; remove desktop shortcut.
	Delete "$DESKTOP\Aiksaurus.lnk"

	; remove directories used
	RMDir "$SMPROGRAMS\Aiksaurus"
	RMDir /r "$INSTDIR"

SectionEnd

; eof
