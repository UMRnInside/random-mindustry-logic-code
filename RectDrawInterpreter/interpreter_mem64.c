#include <mlogevo/mem.h>
#include <mlogevo/io.h>
#include <mlogevo/block_control.h>

#define MEMORY_SIZE 64

extern struct MlogObject display1;

void main() {
    int links, tmp;
    asm ("set %0 @links" : "=r" (links) );
    for (int i=0;i<links;i++) {
        struct MlogObject cell = getlink(i);
        asm ("op strictEqual %0 %1 %2" : "=r" (tmp) : "r"(cell), "r"(display1) );
        if (tmp) {
            continue;
        }
        for (int j=0;j<MEMORY_SIZE;++j) {
            // WARNING: this `int` is not exactly int32_t
            // it is int53 due to IEEE 754
            int instruction = memread_i32(cell, j);
            int type = instruction & 0x0F;
            int arg1 = (instruction >> 4) & 0xFF;
            int arg2 = (instruction >> 12) & 0xFF;
            int arg3 = (instruction >> 20) & 0xFF;
            int arg4 = (instruction >> 28) & 0xFF;
            if (type == 0) {
                draw_flush(display1);
                return;
            } else if (type == 1) {
                draw_set_color(arg1, arg2, arg3, arg4);
            } else if (type == 2) {
                draw_rectangle(arg1, arg2, arg3, arg4);
            } else if (type == 3) {
                draw_flush(display1);
            }
            /* asm volatile (
                ""
                : 
                : "r" (type), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4)
            );
            */
        }
    }
    draw_flush(display1);
}
