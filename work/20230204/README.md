# Usage 
TypeRunyer.exe を実行

# For developper

## How to build
MinGW の g++ を使う。
makefile を使って build　する。

```powershell
# cd /path/to/this/work/dir
mingw32-make.exe
```

## 現在の構造

- IconDisplayer : アイコンを表示させる
- RunningLevl   : 猫の走る速度のレベル

猫が走る
- thread で `DisplayRunning()` で動かしている。
  - IconDisplayer が猫の画像を変更
  - RunningLevel が猫の
  - 猫の ico ファイルを 回しているだけ。
  - `ThreadData share`  を使って time interval を設定して、速度を帰る

速度調整
  - ランニングレベルを誰かが調整する。
  - 調整されたレベルを







```mermaid 
flowchart LR

A[WinMain]
AB[WindowsHookEx]
ABA[KeyBoardProc]

A --> AB 

AB --- ABA

```

