# -*- coding: utf-8 -*-
#
#  message box の出力を行う。
#
#
#
from ctypes import *

def main() : 

    message_box("debug", "なんてこった。")
    print('start')


def message_box(title, contents) :
    user32 = windll.user32
    user32.MessageBoxW(
        0, 
        contents,
        title,         
        0x00000040)



if __name__ == '__main__' :
    main()