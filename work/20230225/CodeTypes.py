
import re
from com import *

# --------------------------------
#
#  parse comment or string
#
# --------------------------------
def parse_code_types(str_idxs, cmt_idxs, code):
    for j in cmt_idxs:
        if j in str_idxs:
            print("comp. of cmt_idx has same str_idx")
            exit(1)

    code_types = []
    for i, c in enumerate(code):
        c_type = 0
        if i in str_idxs:
            c_type = 1
        if i in cmt_idxs:
            c_type = 2

        code_types.append(c_type)

    return code_types


def str_indexs(code):
    #pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*\n)"
    #pattern = r'((?<!\\)"[^"]*(?:(?<!\\)"|\\$))|((?<!\\)\'[^\']*(?:(?<!\\)\'|\\$))|(/\*.*?\*/|//.*?$)'
    #pattern = r'(".*?(?:(?<!\\)"))|((?<!\\)\'[^\']*(?:(?<!\\)\'|\\$))'

    #pattern = r'(".*?(?:(?<!\\)"))|((?<!\\)\'[^\']*(?:(?<!\\)\'|\\$))|(/\*.*?\*/|//.*?$)'
    pattern = r'(".*?(?:(?<!\\)"))|((?<!\\)\'[^\']*(?:(?<!\\)\'|\\$))|(/\*.*?\*/|//.*?(?:(?<!\\)$))'
    regex = re.compile(pattern, re.MULTILINE | re.DOTALL)

    ms = regex.finditer(code)

    indexs = []
    for m in ms:
        # print()
        # print(m)
        # print(m.groups())
        if m.group(3) != None:
            continue

        l = [i for i in range(m.span()[0], m.span()[1])]
        indexs.extend(l)

    return indexs


def cmt_indexs(code):
    pattern = r'(".*?(?:(?<!\\)"))|((?<!\\)\'[^\']*(?:(?<!\\)\'|\\$))|(/\*.*?\*/|//.*?(?:(?<!\\)$))'
    regex = re.compile(pattern, re.MULTILINE | re.DOTALL)

    ms = regex.finditer(code)

    indexs = []
    for m in ms:
        #        print(m)
        if m.group(1) != None or m.group(2) != None:
            continue
        l = [i for i in range(m.span()[0], m.span()[1])]
        indexs.extend(l)

    return indexs
