import re

def itr_to_num_of_line(itr, code) :
    tmp = code[0:itr + 1]
    tmps = re.split(r"(?<!\\)\n", tmp)
    return len(tmps)








class Color:
    BLACK = '\033[30m'
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    BLUE = '\033[34m'
    PURPLE = '\033[35m'
    CYAN = '\033[36m'
    WHITE = '\033[37m'
    END = '\033[0m'
    BOLD = '\038[1m'
    UNDERLINE = '\033[4m'
    INVISIBLE = '\033[08m'
    REVERCE = '\033[07m'

def cmt_text(txt):
    return color_txt(txt, 0x6A, 0x99, 0x55)

def str_text(txt):
    return color_txt(txt, 0xCE, 0x91, 0x78)

def green_text(txt):
    return Color.GREEN + txt + Color.END


def white_text(txt):
    return Color.WHITE + txt + Color.END


def red_text(txt):
    return Color.RED + txt + Color.END


def purple_text(txt):
    return Color.PURPLE + txt + Color.END


def blue_text(txt):
    return Color.BLUE + txt + Color.END


def yellow_text(txt):
    return Color.YELLOW + txt + Color.END


def cyan_text(txt):
    return Color.CYAN + txt + Color.END


# 文字の色指定
def color_txt(txt, r, g, b):
    return f"\033[38;2;{r};{g};{b}m{txt}\033[0m"
