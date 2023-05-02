# -*- coding: utf-8 -*-
#
# rakuraku copy and paste
#
# イメージの説明
#    引数 -i : summary.json -> files
#    引数 -o : files        -> summary.json 
#
#
#
#
#
#
#
import argparse
import glob
import os
import json 
import shutil 
from enum import Enum

verbose = [False]

class Mode(Enum) : 
    FILE_TO_JSON = 1
    JSON_TO_FILE = 2

## constants 
TMP_DIR = ".\\tmp"
JSON_FILE_NAME = f"RakuRakuCopipe.json"
OUTPUT_DIR =  f"{TMP_DIR}/output"


def main() :    
    mode = parse_args()
    if mode == Mode.FILE_TO_JSON :
        convert_files_to_json()        
    else :
        convert_json_to_files()



def vprint(*txt) :     
    if verbose[0] :         
        print(*txt)



def convert_files_to_json() :
    print("Execute mode : files to json")        
    os.makedirs(TMP_DIR, exist_ok=True)
    
    file_names, dir_names = get_file_and_dir_names()

    dict_list = []
    for filename in file_names : 
        unit = make_dict_with_readfile(filename)
        dict_list.append(unit)    
    
    work_dir = os.path.dirname(get_fullpath(__file__))
    json_content = {"work_dir": work_dir, "dir_structure": dir_names, "files": dict_list}
    
    with open(JSON_FILE_NAME, "w", encoding="utf-8") as f:
        json.dump(json_content, f, ensure_ascii=False, indent=2)
        f.close()


def convert_json_to_files() :
    print("Execute mode : json to files")

    shutil.rmtree(TMP_DIR)    

    with open(JSON_FILE_NAME, "r", encoding="utf-8") as f:
        json_content = json.load(f)
    

    work_dir = os.path.dirname(get_fullpath(__file__))
    json_work_dir = json_content["work_dir"] 

    os.makedirs(OUTPUT_DIR, exist_ok=True)
    for dir_path in json_content["dir_structure"] : 
        vprint("v010 : json_dir_path : ", dir_path)
        path = dir_path.replace(json_work_dir, OUTPUT_DIR)
        print("Create directory : ", path)
        os.makedirs(path, exist_ok=True)
    
    for unit_dict in json_content["files"]:
        org_filename = unit_dict["filename"]
        outpath = org_filename.replace(json_work_dir, OUTPUT_DIR)        
        print("Create file : ", outpath)

        with open(outpath, "w", encoding="utf-8") as f : 
            f.write(unit_dict["contents"])



def make_dict_with_readfile(filename) :
    ans = {"filename": filename, "contents": ""} 

    with open(filename, 'r', encoding='utf-8') as f : 
        contents = f.read()

    ans["contents"] = contents

    return ans



    

#
# 現在の directory の ファイルをコピーする
#
#
def get_file_and_dir_names() :             
    all_fullpath = []
    
    all_names = glob.glob("./**/*", recursive=True)
    ignores = get_ignore_objs()        
    for n in all_names : 
        fullpath = get_fullpath(n)
        if fullpath in ignores : 
            vprint(f"v007: {fullpath} is included in .gitignore")
            continue
        all_fullpath.append(fullpath)

    
    file_names = [] 
    dir_names = []    
    for n in all_fullpath :         
        if os.path.isfile(n) :            
            file_names.append(n)
        
        if os.path.isdir(n) :
            if TMP_DIR == n : continue
            dir_names.append(n)

    vprint("v005: filenames : ", file_names)
    vprint("v006: dirnames : ", dir_names)    
    
    return file_names, dir_names

#
# name of ignore files and directories defined in .gitignore
#
def get_ignore_objs() :    
    with open(".gitignore", encoding='utf-8') as f :
        tmp_keys = f.readlines()
        keys = []
        for tmp_key in tmp_keys :             
            # remove comment out 
            itr = tmp_key.find('#')
            if itr >= 0 : 
                tmp_key = tmp_key[:itr]
            
            # remove \n, \t, and space.
            key = tmp_key.strip() 
                        
            if key :
                keys.append(key)
            
    vprint("v001: keys in ignorefile : ", keys)

    # This will be return 
    ignore_filenames = []

    for key in keys :         
        tmpfiles = glob.glob(f"**/{key}", recursive=True)        
        vprint(f"v002: key ({key}) : tmpfiles : ", tmpfiles)
        
        for f in tmpfiles :
            filename = get_fullpath(f)
            ignore_filenames.append(filename)
                    
    vprint("v003: fullpath = ", ignore_filenames)
    
    return ignore_filenames


    


def get_fullpath(filename) : 
    return os.path.abspath(filename)


def parse_args() :
    ## description     
    my_desc = 'Description: ファイルをjsonファイルにまとめたり、jsonファイルをfileに分解したり'
    parser = argparse.ArgumentParser(description=my_desc)
        
    parser.add_argument('--files_to_json', '--f2j',
                        action = 'store_true',
                        help = 'Mode : convert files to json')
    parser.add_argument('--json_to_files', '--j2f',
                        action = 'store_true',                            
                        help = 'Mode : convert json to files')

    parser.add_argument('--verbose', '-v',
                        action = 'store_true',                            
                        help = 'verbose print on for debug')

    args = vars(parser.parse_args())
    
    # set verbose mode
    verbose[0] = args["verbose"]        
    vprint("Verbose mode (for debug) start")


    # default : convert files to json mode
    if args['files_to_json'] and args['files_to_json'] : 
        return Mode.FILE_TO_JSON
    elif args['files_to_json'] :
        return Mode.FILE_TO_JSON
    elif args['json_to_files'] :
        return Mode.JSON_TO_FILE
    else :
        return Mode.FILE_TO_JSON





if __name__ == '__main__' :
    main()