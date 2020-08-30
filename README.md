# 必要そうなもの

## OS の基本機能 (優先度順?)
* メモリ管理
* タスク管理
* 入出力管理
* CUI
* ファイルシステム (ファイルシステムドライバとかをinitramfsみたいな形で持つ)
* アプリの実行 (ELF形式?)
* GUI (フレームバッファ)

## アプリケーション開発に必要になりそうなもの
* gcc / binutils / glibc移植

## 上記以外の機能
* シェル
* テキストエディター
* ターミナル (CUI 脱却後)

## あったらうれしいけど絶対実装が面倒な奴
* Windows/Linux 互換ドライバーレイヤー
* Windows/Linux 互換アプリケーションレイヤー (gcc移植には必須?)

# 参考になりそうな資料
* [フルスクラッチで作る!x86_64自作OS](http://yuma.ohgami.jp/x86_64-Jisaku-OS/)
* [UEFIによるELFバイナリの起動](https://www.slideshare.net/uchan_nos/uefielf)
* 最新情報処理概論 改訂版 P.96 ~ P.98
* キタミ式イラストIT塾 応用情報技術者 平成30年度 (情報処理技術者試験) P.268 ~ P.333

# ビルド方法
```git clone https://github.com/tianocore/edk2.git```  
```cd edk2```  
```git clone https://gitlab.pepepper.cf/ecri/sprinkleos.git```  
```. edksetup.sh```  
```make -C BaseTools/Source/C```  
Conf/target.txtのACTIVE_PLATFORMをsprinkleos/sprinkleos.dscに TARGET_ARCHをX64に TOOL_CHAIN_TAGをGCC5に  
```build```  
出来上がったBuild/SprinkleOSX64/DEBUG_GCC5/X64/sprinkleos.efiを上手いこと起動