# -*- coding: utf-8 -*-

from ctypes import *
import sys
import time


def main() : 
    args = sys.argv
    print(args)
    
    if len(args) != 2 :
        message_box("debug", "Error 001 : args is wrong")    
    
    print('start')
    message_box("debug", args[1]) 
    print('done')
    time.sleep(10)
    


def message_box(title, contents) :    
    user32 = windll.user32
    user32.MessageBoxW(
        0, 
        contents,
        title,         
        0x00000040)



if __name__ == '__main__' :
    main()