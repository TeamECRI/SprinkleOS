# 必要そうなもの, 実装予定のもの

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