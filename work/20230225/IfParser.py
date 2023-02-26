

import re
from collections import deque
from com import *
from IfBlock import ConditionAndBlock, IfBlocks

#
#    Main
#
def parse_if(code, code_types):
    struct_ifs = []
    itr = 0
    while itr < len(code) :
        blocks = IfBlocks()
        cab = ConditionAndBlock()

        #
        #  Find "if" block
        #    (Not "else_if" or "else" block)
        #
        itr = find_first_if(itr, code, code_types) # find index of first if
        if itr < 0 :
            break
        cab.index = itr

        # Find condition in "if (cond) {block} "
        itr, itr_pair = find_brackets_pair_after_if(itr, code, code_types)
        cab.condition_index_pair = [itr, itr_pair]
        itr = itr_pair # current itr is ')'

        # Find block in "if (cond) {block} "
        itr, itr_pair = find_brackets_pair_of_if_block(itr, code, code_types)
        cab.block_index_pair = [itr, itr_pair]
        itr = itr_pair # current itr is '}' or ';'

        # Append an unit of if block (ConditionAndBlock()) to IfBlocks()
        itr += 1
        blocks.components.append(cab)

        #
        #  Find "else_if" or "else" block
        #
        while 1 :
            itr_tmp = find_first_index_of_else(itr, code, code_types)
            print(f"find_first index of else {itr_tmp}")
            if itr_tmp < 0 :
                break

            itr = itr_tmp
            cab_other = ConditionAndBlock()
            cab_other.index = itr
            print(f"cab_other_start {cab_other.index} : #{code[itr]}#")
            itr += 4 # move iterator from "[e]lse" to "else[]"
            tmp = is_elseif(itr, code, code_types)

            if tmp < 0 : # last else
                # Find block in " else {block} "
                itr, itr_pair = find_brackets_pair_of_if_block(itr, code, code_types)
                cab_other.block_index_pair = [itr, itr_pair]

                itr = itr_pair + 1  # after '}' or ';'
                blocks.components.append(cab_other)
                break # after lase else, stop

            else : # elfe if
                itr = tmp
                # Find condition in "else if (cond) {block} "
                itr, itr_pair = find_brackets_pair_after_if(itr, code, code_types)
                cab_other.condition_index_pair = [itr, itr_pair]
                itr = itr_pair

                # Find block in " else if (cond) {block} "
                itr, itr_pair = find_brackets_pair_of_if_block(itr, code, code_types)
                cab_other.block_index_pair = [itr, itr_pair]

                itr = itr_pair + 1  # after '}' or ';'
                blocks.components.append(cab_other)


        struct_ifs.append(blocks)



    for blocks in struct_ifs :
        print("\n---------------")
        blocks.print(code)



#
# itr のあとの 直近の () のペアの位置を返す。
# 例えば、以下のような感じ
#      ↓        ↓
#   if (conditon) { *** }
#   ↑
# (itr)
#
def find_brackets_pair_after_if(itr, code, code_types) :
    itr = find_first_key("(", itr, code, code_types)

    if itr < 0 :
        print("can't find '(' after if !!!")
        exit(1)

    itr_pair = search_pair(itr, code, code_types)

    if itr_pair < 0 :
        print("can't find '()' pair after if !!!")
        exit(1)

    return itr, itr_pair

#
# itr のあとの 直近のif文のブロックの最初と最後のindexのペアの位置を返す。
# 下記の二つの場合に対応している。
# -- example 1 ---------------
#                 ↓     ↓ (results)
#   if (conditon) { *** }
#               ↑
#             (itr)
#
# -- example 2 ---------------
#             (itr)
#               ↓
#   if (conditon)
#       *****;
#       ↑    ↑　(results)
#
def find_brackets_pair_of_if_block(itr, code, code_types) :
    itr = find_first_index_of_block(itr, code, code_types)
    if code[itr] == "{" :
        itr_pair = search_pair(itr, code, code_types)
        if itr_pair < 0 :
            print("can't find '{}' block pair after if () !!!")
            exit(1)
    else :
        # No {} like
        # - if (**) printf("aaa");
        # - if (**)
        #     printf("aaa");
        itr_pair = find_first_key(";", itr, code, code_types)

    return itr, itr_pair

#
# これは if 分のブロックを解析する過程において、
# else もしくは else if であるかを判断するのに、使う。
# もし、else if の場合は i の iterator を返し、その他の場合(else) は -1 を返す。
#
# 以下のように 最初の if 文の後の else が終わったところに iterator があると仮定しており、
#
#                                     ↓ (itr)
# case 1 : if (condition) {block} else if () {...
# cese 2 : if (condition) {block} else () { ...
#
# もし case 1 (else if) の場合なら、else if の i の iterator を返し、
# もし case 2 (else) の場合なら -1 を返す。
# また、case 1/2 どちらでもない場合も -1 を返す。(これはcのソースにバグがある場合だと思ってくだせぇ)
# そのため、実装上では if を探索している。
def is_elseif(idx, code, code_types) :
    index = idx
    for i in range(idx, len(code)) :
        if code_types[i] > 0 : # skip comment out and string type
            continue

        if re.match(r"[^i\s]", code[i]) : # not else or else if
            return -1

        if code[i] == "i" :
            index = i
            break

    if code[index:index+2] != "if" :
        return -1

    return index



def find_first_index_of_else(idx, code, code_types) :
    index = idx
    for i in range(idx, len(code)) :
        if code_types[i] > 0 : # skip comment out and string type
            continue

        if re.match(r"[^e\s]", code[i]) : # no else or else i
            return -1

        if code[i] == "e" :
            index = i
            break

    if code[index:index+4] != "else" :
        return -1

    return index


# find_brackets_pair_of_if_block(itr, code, code_types) で使う。
#
# つまり if (condition) block の block 部分の 最初の iterator を探す。
# - block 部分は { 始まりの場合
# - 関数や変数の名前 (a ~ Z か _) 始まりの場合
# の２通り
def find_first_index_of_block(idx, code, code_types) :
    for i in range(idx, len(code)) :
        if code_types[i] > 0 : # skip comment out and string type
            continue

        if re.match(r"[{a-zA-Z_]", code[i]) :
            return i

    return -1




def find_first_key(unit_key, idx, code, code_types):
    for i in range(idx, len(code)) :
        if code_types[i] > 0 : # skip comment out and string type
            continue
        if code[i] == unit_key :
            return i
    return -1 # cannot find key

#
# if block の始まりを探す。
#   ↓ ここ
#   if (***) {
#       ***
#   } else if (***) {
#       ***
#   } else {
#       ***
#   }
#
# ただし、引数の idx の後の iterator を返す。
def find_first_if(idx, code, code_types):
    ms = re.finditer(r"(?:(?<!else))\s+if\b", code) ## else じゃない if
    for m in ms :
        index = m.span()[1] - 2 # index of 'i'f
        # print(f"----------------------------(input idx{idx})")
        # print(f"index : {index} : code {code[index]}")
        # print(m)
        # print(code[m.span()[0] - 5: m.span()[1] + 5])


        if index < idx : # skip
            continue

        if code_types[index] > 0 : # skip comment out and string type
            continue

        return index

    return -1

    # for m in ms:


def search_pair(idx, code, code_types):
    key = code[idx]
    key_pairs = {
        "{": "}", "(": ")", "[": "]"
    }
    pair = key_pairs[key]

    count_key = 1
    for index in range(idx + 1, len(code)):
        if (count_key <= 0):
            return index - 1 # success to find

        if code_types[index] > 0:  # skip comment out and string type
            continue

        c = code[index]

        if c == key:  # is c '{' ?
            count_key += 1
        elif c == pair:  # is c '}' ?
            count_key -= 1
        else:
            continue

    return -1 # Fail to find


# Input
# - str_idxs (list of index, const): string type      の index の list
# - cmt_idxs (list of index, const): comment out type の index の list
# - code (list of char, const) :
# Return
# - list of code type (1: string, 2: comment out)
def colorize(code, code_types):
    idx = 0
    l_pairs = []
    for idx in range(0, len(code)):
        if code_types[idx] > 0:  # skip comment out and string type
            continue
        c = code[idx]
        if c in ["{", "(", "["]:
            idx_pair = search_pair(idx, code, code_types)
            l_pairs.append([idx, idx_pair, 0])

    # [index of key, index of key pair, depth]
    stack = deque()
    for i, l in enumerate(l_pairs):
        # print()
        # print("stack is ", end="")
        # print(stack)
        # print("current is ", end="")
        # print(l)
        while len(stack) > 0 and stack[-1][1] < l[0]:
            # print("pop")
            stack.pop()

        l[2] = len(stack) + 1
        stack.append(l)  # increment depth

    # print(l_pairs)

    for i, c in enumerate(code):
        i_col = 0
        for l in l_pairs:
            if i == l[0] or i == l[1]:
                i_col = l[2]
                break

        if code_types[i] > 0:
            col_func = [white_text, str_text, cmt_text]
            print(col_func[code_types[i]](c), end="")
        else:
            col_func = [white_text, green_text, blue_text, cyan_text, yellow_text,
                        purple_text, red_text]
            print(col_func[i_col](c), end="")
