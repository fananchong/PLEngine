call _load_env.bat

if not exist Python-3.6.2.tar.xz %_curl% -o Python-3.6.2.tar.xz -k -L https://www.python.org/ftp/python/3.6.2/Python-3.6.2.tgz
if exist Python-3.6.2.tar.xz %_7z% x Python-3.6.2.tar.xz -y -aos -o"."
if exist Python-3.6.2.tar %_tar% -xvf Python-3.6.2.tar
if exist Python-3.6.2.tar del /Q Python-3.6.2.tar

cd Python-3.6.2\PCbuild

%_sed% -i "s/PyTypeObject OverlappedType/static PyTypeObject OverlappedType/g" ..\Modules\_winapi.c
%_sed% -i "s/#define Py_TRACE_REFS//g" ..\Include\object.h
%_sed% -i "s/DynamicLibrary/StaticLibrary/g" *.vcxproj
%_sed% -i "s/Py_ENABLE_SHARED/Py_NO_ENABLE_SHARED/g" *.vcxproj
%_sed% -i "s/MultiThreadedDLL/MultiThreaded/g" *.props
%_sed% -i "s/MultiThreadedDebugDLL/MultiThreadedDebug/g" *.props
%_sed% -i "s/_CONSOLE/Py_NO_ENABLE_SHARED;_CONSOLE/g" *.vcxproj

call build.bat -e -p x64 -c Release
call build.bat -e -p x64 -c Debug

%_devenv% pcbuild.sln /build "Debug|x64" /Out build_debug.log
%_devenv% pcbuild.sln /build "Release|x64" /Out build_release.log


if not exist ..\..\..\include\python\win mkdir ..\..\..\include\python\win
copy /Y ..\Include\*.h ..\..\..\include\python\win
copy /Y ..\PC\pyconfig.h ..\..\..\include\python\win

copy /Y amd64\*.pdb ..\..\..\lib_win\
copy /Y amd64\*.lib ..\..\..\lib_win\
copy /Y amd64\*.pyd ..\..\..\lib_win\
copy /Y ..\externals\tcltk64\lib\*.lib ..\..\..\lib_win\

if not exist ..\..\..\..\bin\res\py\win\Lib mkdir ..\..\..\..\bin\res\py\win\Lib
xcopy /Y /S ..\Lib\*.py ..\..\..\..\bin\res\py\win\Lib

cd ..\..\