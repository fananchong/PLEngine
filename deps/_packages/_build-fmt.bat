call _load_env.bat


if not exist fmt-4.0.0.tar.gz %_curl% -o fmt-4.0.0.tar.gz -k -L https://codeload.github.com/fmtlib/fmt/tar.gz/4.0.0
if exist fmt-4.0.0.tar.gz %_7z% x fmt-4.0.0.tar.gz -y -aos -o"."
if exist fmt-4.0.0.tar %_tar% -xvf fmt-4.0.0.tar
if exist fmt-4.0.0.tar del /Q fmt-4.0.0.tar

cd fmt-4.0.0\fmt

echo set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT") >> "CMakeLists.txt"
echo set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd") >> "CMakeLists.txt"
echo set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT") >> "CMakeLists.txt"
echo set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT") >> "CMakeLists.txt"
cmake -G "Visual Studio 15 2017 Win64"

move /Y string.h string.h_
move /Y time.h time.h_

%_devenv% fmt.vcxproj /build "Debug|x64" /Out build_debug.log
%_devenv% fmt.vcxproj /build "RelWithDebInfo|x64" /Out build_release.log

move /Y string.h_ string.h
move /Y time.h_ time.h

if not exist ..\..\..\include\fmtlib mkdir ..\..\..\include\fmtlib
copy /Y *.h ..\..\..\include\fmtlib


if not exist ..\..\..\lib_win\debug mkdir ..\..\..\lib_win\debug
if not exist ..\..\..\lib_win\release mkdir ..\..\..\lib_win\release
copy /Y Debug\fmt.lib ..\..\..\lib_win\debug
copy /Y Debug\fmt.pdb ..\..\..\lib_win\debug
copy /Y RelWithDebInfo\fmt.lib ..\..\..\lib_win\release
copy /Y fmt.dir\RelWithDebInfo\fmt.pdb ..\..\..\lib_win\release

cd ..\..\