# 右クリックに関するレジストリの変更のまとめ。

*NOTE* レジストリの変更は最悪、windows OSをぶち壊す。なので、慎重にやったほうが良いです。

## 参考記事
https://qiita.com/NumLocker/items/f8016f1aed7207b850fb


## まとめ。
HKCU/Software/Classes/*いろいろ*/shell をいじる。
いろいろには複数種類ある
- `Directory/shell` : フォルダ. ライブラリとかドライブは含まないよ
- `Directory/Background/shell` : フォルダの背景
- `*/shell` : いろいろなファイル形式
- `SystemFileAssociations\.[拡張子]\Shell` : 特定の拡張子. .png とか
- `SystemFileAssociations\[種類]\shell` : audio とか image とか。音声ファイルとか、テキストファイルとか目的別の種類に対応する。完璧じゃないよ。
- `lnkfile/shell` : 
- `AllFilesystem/shell` : いろいろなファイルについて、ただし、フォルダの背景部分とかは対応できない。



## background とファイルをいじるようにする。
- フォルダのバックグラウンド
`コンピューター\HKEY_CLASSES_ROOT\Directory\Background\shell\registry_test\command` を追加し、
その値のデータを以下のようにした。
`"C:\Users\kenwa\AppData\Local\Microsoft\WindowsApps\python.exe" "C:\Users\kenwa\work\comm\work\20230502\test.py" "%V"`

- 全ファイル
`コンピューター\HKEY_CLASSES_ROOT\AllFilesystemObjects\shell\regist_test\command`
`"C:\Users\kenwa\AppData\Local\Microsoft\WindowsApps\python.exe" "C:\Users\kenwa\work\comm\work\20230502\test.py" "%V"`

ちなみに pythonw だと python の window を開かねぇ。