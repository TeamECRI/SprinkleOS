# (未完成) Wine on Windows で起動する
## 必要なソフトウェア
* [Git for Windows](https://gitforwindows.org/)
* (GUI が必要であれば) [TortoiseGit](https://tortoisegit.org/)
    * これ以外にも Git を GUI で扱うためのソフトウェアは存在しますので、適宜選んでください。
* [Python (バージョン 3.7 以降)](https://www.python.org/downloads/windows/)
* [Cygwin](https://cygwin.com/install.html) またはそれに準ずる UNIX ライクな環境を提供する互換レイヤー
* [MinGW](https://ja.osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/) またはそれ以外のWindows向け gcc (cl.exe とかでもOK?)
* [LLVM](https://chocolatey.org/packages/llvm)

## 手順
前提: 上記のソフトウェアがすべてインストールされ、PATH が通っている。

1. コマンドラインで下記を実行する
```git clone https://github.com/tianocore/edk2.git```  
```cd edk2```  
```git clone https://gitlab.pepepper.cf/ecri/sprinkleos.git```  
```. edksetup.sh```  
```make -C BaseTools/Source/C```  
