; The name of the installer
Name "Energo Ядро"

; The file to write
OutFile "Energo v.1.0.3 Full.exe"

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
  File recv.exe
  File scheduler.exe
  File xmlimport.exe
  File conf.exe
  
  ;Libraries

  ;Core libs
  File libeay32.dll
  File libgcc_s_dw2-1.dll
  File libiconv-2.dll
  File libintl-8.dll
  File ssleay32.dll
  File ociliba.dll
  File libpq.dll
  File mingwm10.dll
  File qextserialport1.dll

  ;Qt libs
  File QtCore4.dll
  File QtGui4.dll
  File QtXml4.dll
  File QtNetwork4.dll
  
  ;Energo libs
  File pgredrv.dll
  File oradrv.dll
  File GSMConnection.dll

  ;Drivers
  File merc320.dll
  File set4tmplugin.dll
  File acdrv.dll

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

  ; Sql scripts
  SetOutPath $INSTDIR\sql
  File "sql\1. Create tables 2012-04-10.backup"
  File "sql\2. Insert global data 2012-04-10.backup"
  File "sql\3. create users.sql"

  ;Creating shortcuts
  SetOutPath $INSTDIR
  CreateShortCut "$DESKTOP\Energo - Отчеты.lnk" "$INSTDIR\report.exe"
  CreateShortCut "$DESKTOP\Energo - Диспетчер опроса.lnk" "$INSTDIR\scheduler.exe"
  CreateShortCut "$DESKTOP\Energo - Импорт макетов.lnk" "$INSTDIR\xmlimport.exe"
  CreateShortCut "$DESKTOP\Energo - Конфигуратор.lnk" "$INSTDIR\conf.exe"


SectionEnd ; end the section
