# (未完成) Windows Subsystem for Linux (WSL) で起動する

## 環境
* Windows Subsystem for Linux
* Ubuntu 20.04 LTS

## ビルド
コマンドラインで下記を実行する  
* アップデート  
```sudo apt -y update && sudo apt -y upgrade```  
* ビルドに必要なパッケージをインストール  
```sudo apt -y install build-essential uuid-dev iasl git gcc-5 nasm python3-distutils```  
* edk2 をクローン  
```git clone https://github.com/tianocore/edk2.git```  
* SprinkleOS をクローン  
```cd edk2```  
```git clone https://gitlab.pepepper.cf/ecri/sprinkleos.git```  
* edk2 のconfigなどを生成する  
```. edksetup.sh```
* target.txt の編集  
`Conf/target.txt`を開き、以下を編集する。  
`- ACTIVE_PLATFORM       = EmulatorPkg/EmulatorPkg.dsc`  
`+ ACTIVE_PLATFORM       = sprinkleos/sprinkleos.dsc`  
`- TARGET_ARCH           = IA32`  
`+ TARGET_ARCH           = X64`  
`- TOOL_CHAIN_TAG        = VS2015x86`  
`+ TOOL_CHAIN_TAG        = GCC5`  

* ビルド  
```build```  
成果物は `Build/SprinkleOSX64/DEBUG_GCC5/X64/sprinkleos.efi` にあります。

## 起動

## 参考
* [Using EDK II with Native GCC · tianocore/tianocore.github.io Wiki](https://github.com/tianocore/tianocore.github.io/wiki/Using-EDK-II-with-Native-GCC#Install_required_software_from_apt)