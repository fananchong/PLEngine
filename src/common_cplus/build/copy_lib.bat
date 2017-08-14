
if exist ..\bin\Debug\plengine_common.lib copy /Y ..\bin\Debug\plengine_common.lib ..\..\..\deps\lib_win\debug\plengine.lib
if exist ..\bin\Debug\plengine_common.pdb copy /Y ..\bin\Debug\plengine_common.pdb ..\..\..\deps\lib_win\debug\plengine.pdb
if exist ..\bin\Release\plengine_common.lib copy /Y ..\bin\Release\plengine_common.lib ..\..\..\deps\lib_win\release\plengine.lib
if exist obj\x64\Release\plengine_common.pdb copy /Y obj\x64\Release\plengine_common.pdb ..\..\..\deps\lib_win\release\plengine.pdb

if not exist ..\..\..\deps\include\plengine mkdir ..\..\..\deps\include\plengine
copy /Y ..\*.h ..\..\..\deps\include\plengine

pause