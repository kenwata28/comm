
#from operator import index
import re
from collections import deque
#from work.common.com import color_txt
from com import *
from IfBlock import ConditionAndBlock, IfBlocks
import CodeTypes as ctypes
from IfParser import parse_if, colorize

def main():
    code = read_code("test2.cc")

    str_idxs = ctypes.str_indexs(code)
    cmt_idxs = ctypes.cmt_indexs(code)

    code_types = ctypes.parse_code_types(str_idxs, cmt_idxs, code)

    # for c, type in zip(code, code_types):
    #     col_func = [white_text, str_text, cmt_text,
    #                 green_text, red_text, cyan_text]
    #     print(col_func[type](c), end="")

    # c_code = parse_if(code)
    # colorize(code, code_types)
    parse_if(code, code_types)
    #write_code("ans.cc", c_code)





def read_code(filename):
    with open(filename, "r") as f:
        ans = f.read()

    return ans


def write_code(filename, code):
    with open(filename, "w") as f:
        f.write(code)


if __name__ == "__main__":
    main()
