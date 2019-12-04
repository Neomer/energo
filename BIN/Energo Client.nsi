; The name of the installer
Name "ÀÈÈÑ Energo"

; The file to write
OutFile "Energo v.1.0.3 Client.exe"

; The default installation directory
InstallDir $DESKTOP\Energo

; Request application privileges for Windows Vista
RequestExecutionLevel user

;--------------------------------

; Pages

Page directory
Page instfiles

;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ;Executable files
  File report.exe
  CreateShortCut "$DESKTOP\Energo - Îò÷åòû.lnk" "$OUTDIR\report.exe"
  
  ;Libraries
  File pgredrv.dll
  File libeay32.dll
  File libgcc_s_dw2-1.dll
  File libiconv-2.dll
  File libintl-8.dll
  File QtCore4.dll
  File QtGui4.dll
  File ssleay32.dll
  File libpq.dll
  File mingwm10.dll

  ;Other files
  File energo.conf

  ;Counter plugins

  ;Reports
  SetOutPath $INSTDIR\reports
  File reports\BalansRpt.dll
  File reports\CheckDataRpt.dll
  File reports\DataViewRpt.dll
  File reports\FeederDataRpt.dll
  File reports\OperView.dll


  SetOutPath $INSTDIR\logs


SectionEnd ; end the section
