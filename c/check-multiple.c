#include <stdio.h>
#include "integer.h"

int main(void) {
    int i;
    Number num, num2, num_result;
    int loop_count = 1000;
    int actual, expected;

    srandom(time(NULL));

    for (i = 0; i < loop_count; i++) {
        int a = random() % 1000;
        int b = random() % 1000;

        a *= (random() % 2 == 0) ? 1: -1;
        b *= (random() % 2 == 0) ? 1: -1;
        set_int(&num,  a);
        set_int(&num2, b);

        expected = a * b;

        multiple(&num, &num2, &num_result);
        get_int(&num_result, &actual);

        if (actual != expected) {
            puts("NG!!");
            return -1;
        }
    }

    puts("OK.");
    return 0;
}
