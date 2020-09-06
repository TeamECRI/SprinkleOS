# (未完成) Ubuntu をホストとして起動する

## 環境
* Ubuntu 20.04 LTS
* (確認済み) Windows Subsystem for Linux

## ビルド
コマンドラインで下記を実行する  
* パッケージの更新  
```sudo apt -y update && sudo apt -y upgrade```  
* ビルドに必要なパッケージをインストール (gcc を除く)  
```sudo apt -y install build-essential uuid-dev iasl git nasm python3-distutils```  
* gcc-5 をインストール  
Ubuntu 20.04 では既定では gcc-5 をインストールできません。ソースを追加します。  
`echo "deb http://archive.ubuntu.com/ubuntu xenial main" | sudo tee /etc/apt/sources.list.d/xenial.list`  
`sudo apt -y update`  
`sudo apt -y install gcc-5`  
* edk2 をクローン、submodule を更新  
```git clone https://github.com/tianocore/edk2.git/```  
```git submodule update --init```  
* SprinkleOS をクローン  
```cd edk2```  
```git clone https://gitlab.pepepper.cf/ecri/sprinkleos.git/```  
* edk2 を設定  
```. edksetup.sh```
* `target.txt` の編集  
`Conf/target.txt` を開き、以下を編集する。  
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