#include <stdio.h>
#include "integer.h"

int compare_int(int a, int b) {
    if (a > b)      return 1;
    else if (a < b) return -1;
    else            return 0;
}

int main(void) {
    int i;
    Number num, num2;
    int loop_count = 100000;
    int actual, expected;

    srandom(time(NULL));

    for (i = 0; i < loop_count; i++) {
        int a = random() % 10000000;
        int b = random() % 10000000;

        a *= (random() % 2 == 0) ? 1: -1;
        b *= (random() % 2 == 0) ? 1: -1;
        set_int(&num,  a);
        set_int(&num2, b);

        expected = compare_number(&num, &num2);
        actual   = compare_int(a, b);

        if (actual != expected) {
            puts("NG!!");
            return -1;
        }
    }

    puts("OK.");
    return 0;
}
