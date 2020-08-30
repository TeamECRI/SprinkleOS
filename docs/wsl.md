# (未完成) Windows Subsystem for Linux (WSL) で起動する

## 手順
前提: 上記のソフトウェアがすべてインストールされ、PATH (環境変数)が通っている。

1. コマンドラインで下記を実行する
```sudo apt -y update && sudo apt -y upgrade```  
```sudo apt -y install build-essential uuid-dev iasl git gcc-5 nasm python3-distutils```  
```git clone https://github.com/tianocore/edk2.git```  
```cd edk2```  
```git clone https://gitlab.pepepper.cf/ecri/sprinkleos.git```  
```edksetup.bat rebuild```  
```edksetup.bat```
```make -C BaseTools/Source/C```  
