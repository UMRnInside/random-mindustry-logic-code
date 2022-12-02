#!/usr/bin/env python3
# Convert Mindustry Logic `draw color`, `draw rect` and `drawflush`
# into an array of int53_t
import sys
instructions = []

for line in sys.stdin:
    tokens = line.split()
    if len(tokens) <= 0:
        continue
    if tokens[0] == "drawflush":
        instructions.append(3)
    if tokens[0] != "draw":
        continue
    args = list(map(int, tokens[2:6]))
    high_part = args[0]<<4 | args[1]<<12 | args[2]<<20 | args[3]<<28
    low_part = 0
    if tokens[1] == "color":
        instructions.append(1 | high_part)
    elif tokens[1] == "rect":
        instructions.append(2 | high_part)

memory_block_name = "cell"
memory_block_size = 64
memory_block_id = 1
pos = 0

result = []
for v in instructions:
    result.append(f"write {v} {memory_block_name}{memory_block_id} {pos}")
    pos += 1
    if pos == memory_block_size:
        memory_block_id += 1
        pos = 0

print("\n".join(result))
