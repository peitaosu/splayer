!define ADDONSFREE 1
!define INTERNATIONAL 1


!include "inc.Var.nsi"

Function .onInit
 !include "inc.OnInt.nsi"

FunctionEnd

OutFile "..\..\SPlayerSetupInt.exe"

; Uninstaller

Section "Uninstall"
  
  !include "inc.uninstall.nsi"
  
SectionEnd



!include "Desctext.nsi"
