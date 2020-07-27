# 必要そうなもの

## OS の基本機能(優先度順?)
* メモリ管理
* タスク管理
* 入出力管理
* CUI
* ファイルシステム (ファイルシステムドライバとかをinitramfsみたいな形で持つ)
* アプリの実行 (ELF形式?)
* GUI (framebuffer)

## 上記以外の"リッチ"な機能
* テキストエディター
* ターミナル (CUI 脱却後)

# あったらうれしいけど絶対実装が面倒な奴
* Windows/Linux 互換ドライバーレイヤー
* Windows/Linux 互換アプリケーションレイヤー

# 参考になりそうなサイト
* http://yuma.ohgami.jp/x86_64-Jisaku-OS/
* https://www.slideshare.net/uchan_nos/uefielf
* 最新情報処理概論 改訂版 P.96~P.98
* 平成30年度キタミ式応用情報技術者 P.268~P.333
