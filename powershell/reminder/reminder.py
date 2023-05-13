# -*- coding: utf-8 -*-
import subprocess
import time
from datetime import datetime 
import re
import os

import sys


def main() : 
    script = get_script_path()
    
    contents, date_str = parse_args()    
    print("Notify : ", f'"{contents}"', date_str)
    time.sleep(2)
    #in_str = input()
    mins = parse_input(date_str)
    print(f"Notify atfer {mins} mins ")
    
    #time = mins * 60
    wait = mins
    
    cmd = f'powershell -WindowStyle Hidden {script} "Reminder" "{contents}" {wait}'
    #cmd = f'powershell {script} "Reminder" "{contents}" {wait}'
    proc = subprocess.Popen(cmd.split())



def get_script_path() :    
    ans = os.path.dirname(os.path.abspath(__file__))
    ans += "\\toast_notify.ps1"
    return ans
    


def parse_args() : 
    args = sys.argv
    if len(args) != 3 :
        print("Error in args")
        print(   "your args : ", args)
        print("Usage : ")
        print("   reminder.py [contents] [min]")
        #print("    - title   : title of toast notification")
        print("    - contents: contents of toast notification")
        print("    - min     : notify timing")
        print("       - 1hours  : 1 hour after")
        print("       - 10(mins): 10 mins after")
        print("       - 15:54   : at 15:54 ") 
        time.sleep(10)
        exit(1)

    #title = args[1]
    contents = args[1]
    date = args[2]
    
    return (contents, date)

def parse_input(in_str_tmp) :
    in_str = in_str_tmp.strip()
    
    if ":" in in_str : 
        dt_now = datetime.now()
        try : 
            hour = int(in_str.split(':')[0])
            minute = int(in_str.split(':')[1])
        except Exception : 
            print("Error 001 : Arg is unproper : ", in_str)
            time.sleep(10)
            exit(1)

        dt = datetime(dt_now.year, dt_now.month, dt_now.day, hour, minute)
        mins = int((dt - dt_now).seconds / 60)
        return mins
    
    else : 
        if "hours" in in_str : 
            m = re.search(r"(\d{1,10})\s*hours", in_str)
            # print(m)
            try :
                h = int(m.group(1))
                return h * 60
            except Exception : 
                print("Error 002 : Arg is unproper : ", in_str)                
                time.sleep(10)
                exit(1)

        else : 
            m = re.search(r"\d{1,10}", in_str)
#            print(m)
            try :
                mins = int(m.group(0))
                return mins
            except Exception :
                print("Error 003 : Arg is unproper : ", in_str)
                time.sleep(10)
                exit(1)

    return -1



if __name__ == "__main__" :
    main()
