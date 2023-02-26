
import re
from com import *

from dataclasses import dataclass, field

@dataclass
class ConditionAndBlock :

    index : int = 0
    condition_index_pair: list = field(default_factory = list)
    block_index_pair: list = field(default_factory = list)


    def get_str_of_condition(self, code) :
        if len(self.condition_index_pair) == 0 :
            return ""
        i0 = self.condition_index_pair[0]
        i1 = self.condition_index_pair[1]
        return code[i0:i1+1]

    def get_str_of_block(self, code) :
        i0 = self.block_index_pair[0]
        i1 = self.block_index_pair[1]
        return code[i0:i1 + 1]

    def print(self, code) :
        condi = self.get_str_of_condition(code)
        blk = self.get_str_of_block(code)
        print(f"If starts {self.index} (line#{itr_to_num_of_line(self.index, code)})")
        print(purple_text("condition : "))
        print(condi)
        print(purple_text("block : "))
        print(blk)


@dataclass
class IfBlocks :
    components : list = field(default_factory = list)

    def print(self, code) :
        if len(self.components) == 0 :
            print("empty blocks")


        print(green_text(f"Block set start {self.components[0].index}"))
        print(f"components size : {len(self.components)}")
        for c in self.components :
            c.print(code)
            print()