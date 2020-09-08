# [ECRI](https://gitlab.pepepper.cf/ECRI) / SprinkleOS
Challenge of Hand-made OS.

# ドキュメント
* [必要そうなもの, 実装予定のもの](docs/todo.md)
* [参考資料](docs/references.md)

# ビルド, 実行
* [ビルドする (Ubuntu 20.04 LTS)](docs/ubuntu.md)
* [QEMU で起動する](docs/qemu.md)

<!-- 
```git clone https://github.com/tianocore/edk2.git```  
```cd edk2```  
```git clone https://gitlab.pepepper.cf/ecri/sprinkleos.git```  
```. edksetup.sh```  
```make -C BaseTools/Source/C```  
Conf/target.txtのACTIVE_PLATFORMをsprinkleos/sprinkleos.dscに TARGET_ARCHをX64に TOOL_CHAIN_TAGをGCC5に  
```build```  
出来上がったBuild/SprinkleOSX64/DEBUG_GCC5/X64/sprinkleos.efiを上手いこと起動
-->