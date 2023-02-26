import re


def eval_condition(condition) :
    eq = condition
    ans = bool(eq)
    return ans


def ConvertTF(eq : str) -> str:
    eq = re.sub(r"\b(true)\b", "True", eq)
    eq = re.sub(r"\b(false)\b", "False", eq)
    return eq