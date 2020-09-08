# ビルドした efi ファイルを QEMU で起動する
## 必要なもの
* QEMU
* [ubuntu.md](ubuntu.md) で使用したファイル群
## 手順
1. ビルドした efi ファイルを起動するための OVMF をビルドする
* `~/edk2/Conf/target.txt` の `ACTIVE_PLATFORM` を `OvmfPkg/OvmfPkgX64.dsc`に変更し、`build` コマンドを実行する。
* `edk2/OvmfPkg` ディレクトリ内で、`. build.sh` を実行する。  
ここでエラーが発生した場合、edk2 のディレクトリに戻り、下記のコマンドを実行して再度試してみる。
```
git submodule update --init --recursive
sudo apt install acpica-tools
```
2. ビルドした OVMF を使って起動する
以下のようにQEMUを起動すればよいです。  
このとき、以下のファイルがコマンドを実行するディレクトリに存在していることを確認してください。  
* `OVMF_CODE.fd` (`Build/OvmfX64/DEBUG_GCC5/FV/OVMF_CODE.fd` からコピー)  
* `OVMF_VARS.fd` (`Build/OvmfX64/DEBUG_GCC5/FV/OVMF_CODE.fd` からコピー)  
また、以下のファイルを実行するディレクトリの `EFI/BOOT/` 中に `BOOTX64.efi` とリネームして配置してください。
* `sprinkleos.efi` (`Build/SprinkleOSX64/DEBUG_GCC5/X64/sprinkleos.efi` からコピー)  
**実行するコマンド**  
`qemu-system-x86_64 -drive if=pflash,format=raw,readonly,file=OVMF_CODE.fd -drive if=pflash,format=raw,file=OVMF_VARS.fd -hda fat:rw:.`

## 留意点
* 更新した SprinkleOS を読み込むには、efi ファイルを再配置後 QEMU のコマンドを実行し直してください。
* Windows 環境では、QEMU に PATH が通っていることを確認してください。
