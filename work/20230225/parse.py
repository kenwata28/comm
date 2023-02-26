import re
from com import *


def main():
    code = get_code("test.cc")
#    chk_backslash_end(code)

    parsed_code = parse_c_code(code)
    print(parsed_code)

    # print(repr(code))


def get_code(filename):
    with open(filename, "r") as f:
        ans = f.read()

    return ans


def chk_backslash_end(code):
    lines = re.split("\n", code)
    cmt_out = False
    for l in lines:

        if re.search(r'//.*\\$', l):
            cmt_out = True

        if cmt_out:
            print(red_text(l))
        else:
            print(green_text(l))

        if cmt_out and not re.search(r'.*\\$', l):
            cmt_out = False


def remove_comments(code):
    """ Remove C-style comment from GLSL code string """
    # pattern 1 :
    #  - "str"
    #  - 'str'
    # pattern 2 :
    #  - /* comment */
    #  - // comment
    #pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*\n)"
    pattern = r'((?<!\\)"[^"]*(?:(?<!\\)"|\\$))|((?<!\\)\'[^\']*(?:(?<!\\)\'|\\$))|(/\*.*?\*/|//.*?$)'

    # first group captures quoted strings (double or single)
    # second group captures comments (//single-line or /* multi-line */)
    regex = re.compile(pattern, re.MULTILINE | re.DOTALL)

    def do_replace(match):
        # if the 2nd group (capturing comments) is not None,
        # it means we have captured a non-quoted (real) comment string.
        if match.group(2) is not None:
            return ""  # so we will return empty to remove the comment
        else:  # otherwise, we will return the 1st group
            return match.group(1)  # captured quoted-string

    return regex.sub(do_replace, code)


# def remove_comments(code):
#     # Remove block comments (greedy)
#     # /* コメント */
#     pattern = r'/\*.*?\*/'
#     code = re.sub(pattern, '', code, flags=re.DOTALL)


#     # # Remove line comments (non-greedy)
#     # pattern = r'"(?:\\.|[^\\"])*"|\'(?:\\.|[^\\\'])*\'|//.*?$|/\*.*?\*/'
#     # code = re.sub(pattern, lambda m: m.group() if m.group().startswith(
#     #     '"') or m.group().startswith("'") else '', code, flags=re.DOTALL | re.MULTILINE)

#     return code


# def remove_comments(code):
#     # Remove block comments (greedy)
#     pattern = r'/\*.*?\*/'
#     code = re.sub(pattern, '', code, flags=re.DOTALL)

#     # Remove line comments (non-greedy)
#     pattern = r'"(?:\\.|[^\\"])*"|\'(?:\\.|[^\\\'])*\'|//.*?$|/\*.*?\*/'
#     code = re.sub(pattern, lambda m: m.group() if m.group().startswith(
#         '"') or m.group().startswith("'") else '', code, flags=re.DOTALL | re.MULTILINE)

#     return code


# def remove_comments(code):
#     # Remove block comments
#     pattern = r'/\*.*?\*/'
#     code = re.sub(pattern, '', code, flags=re.DOTALL)

#     # Remove line comments
#     pattern = r'//.*?(?=(?<!\\)")'
#     code = re.sub(pattern, '', code)

#     return code


def indent_code(code):
    # Split code into lines
    lines = code.split('\n')

    # Remove leading/trailing whitespace from each line
    lines = [line.strip() for line in lines]

    # Remove empty lines
    lines = [line for line in lines if line]

    # Add indentation
    indentation = 0
    for i, line in enumerate(lines):
        if line.startswith('}'):
            indentation -= 4
        lines[i] = ' ' * indentation + line
        if line.endswith('{'):
            indentation += 4

    # Combine lines back into a single string
    code = '\n'.join(lines)

    return code


def parse_c_code(code):
    # Remove comments
    code = remove_comments(code)

    # Indent code
    code = indent_code(code)

    return code


if __name__ == "__main__":
    main()
