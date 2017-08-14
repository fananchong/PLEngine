
git rev-list HEAD > version.log
for /f %%a in (version.log) do (
    set id=%%a
    goto :label1
)
:label1

set out_file=..\..\..\deps\include\plengine\version.h

echo #ifndef __VERSION_H__ > %out_file%
echo #define __VERSION_H__ >> %out_file%
echo #define APP_VERSION "%id%" >> %out_file%
echo #define APP_BUILD_TIME "%date:~0,10% %time:~0,8%" >> %out_file%
echo #endif >> %out_file%

del /Q /F version.log