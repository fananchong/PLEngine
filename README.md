# PLEngine

C++ / Python 游戏服务端引擎


### 编译说明

#### window

1. 打开`适用于 VS 2017 的 x64 本机工具命令提示`控制台
1. 执行下列语句，获取依赖库和工程文件：
  ```dos
  git submodule update --init --force -- "tools/build"
  cd deps\lib_win
  gen.bat
  cd ..\..\build
  premake5-win.bat
  ```  
1. 打开PhysxWrap.sln，编译

#### linux

1. 执行下列语句，获取依赖库并编译：
  ```bash
  git submodule update --init --force -- "tools/build"
  cd deps/lib_linux
  ./gen.sh
  cd ../../build
  ./premake5-linux.sh
  make
  ```



### 特性

 - 内嵌python至PNODE


### TODO

 - python 热更新
