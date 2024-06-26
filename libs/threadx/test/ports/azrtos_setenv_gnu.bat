@ECHO OFF

ECHO INFO: Setting up the environment for ARM GCC...

SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\10 2021.10\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\10 2021.07\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\10 2020-q4-major\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\9 2020-q2-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\9 2019-q4-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\8 2019-q3-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\8 2018-q4-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\7 2018-q2-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Arm Embedded Toolchain\7 2017-q4-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Tools ARM Embedded\9 2020-q2-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Tools ARM Embedded\9 2019-q4-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Tools ARM Embedded\8 2019-q3-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Tools ARM Embedded\8 2018-q4-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Tools ARM Embedded\7 2018-q2-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
SET AZRTOS_GCC_DIR="%ProgramFiles(x86)%\GNU Tools ARM Embedded\7 2017-q4-update\bin"
IF EXIST %AZRTOS_GCC_DIR% GOTO AZRTOS_GCC_DIR_FOUND
ECHO ERROR: GCC directory not found
EXIT /B 2

:AZRTOS_GCC_DIR_FOUND
IF EXIST %AZRTOS_GCC_DIR%\arm-none-eabi-gcc.exe GOTO GCC_FOUND
ECHO ERROR: arm-none-eabi-gcc.exe is not found in the GCC directory: %AZRTOS_GCC_DIR%
EXIT /B 2

:GCC_FOUND
ECHO INFO: arm-none-eabi-gcc.exe is here %AZRTOS_GCC_DIR%

IF DEFINED TL_PATH GOTO TL_PATH_DEFINED
SET TL_PATH=%AZRTOS_GCC_DIR:"=%

:TL_PATH_DEFINED
ECHO INFO: TL_PATH defined as %TL_PATH%

WHERE /Q arm-none-eabi-gcc.exe
IF %ERRORLEVEL% NEQ 0 GOTO GCC_NOT_IN_PATH
ECHO INFO: arm-none-eabi-gcc.exe is already in the path.
GOTO DONE

:GCC_NOT_IN_PATH
SET PATH=%TL_PATH%;%PATH%

:DONE
ECHO INFO: ARM GCC environment setup completed successfully!
