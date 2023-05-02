

## toast_notify.ps1 
`toast_notify.ps1` が main の toast通知機能。

本当は python の library を使う方が良かったが、pip install しなければならなかったため、
powershell の機能をわざわざ使った。

```powershell
test.ps1 title contents mins
```
で、 mins 後に contents の内容の toast 通知をすることができる。


## reminder.py 
`reminder.py` が 実際に動かすところ。

```powershell 
reminder.py [contents] [mins]
# ex.)
#  reminder.py 内容だよ 20
#  reminder.py "後で やりましょう" 17:00
```
で動かすことが可能。

`[mins]` には 以下の3種類の入力がある。
- 20mins (2だけでも可能)
- 1hours
- 16:47



