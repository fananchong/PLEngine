REM ����VS·��

set CUR_PATH=%~dp0

set _devenv="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.com"

REM ����curl·��
set _curl=%CUR_PATH%\..\..\tools\build\curl-win\curl.exe

REM ����7z·��
set _7z=%CUR_PATH%\..\..\tools\build\7z-win\7z.exe

REM ����tar·��
set _tar=%CUR_PATH%\..\..\tools\build\tar-win\WinTar_1_0_2.exe

REM ����sed·��
set _sed=%CUR_PATH%\..\..\tools\build\sed-win\sed.exe

REM ����svn·��
set PATH=C:\Test;%PATH%

REM ����MSBuild·��
set PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\amd64;%PATH%
