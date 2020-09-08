# (未完成) ビルドした efi ファイルを QEMU で起動する
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
