#include <stdio.h>
#include "integer.h"

int main(void) {
    int i;
    Number num, num2, num_result;
    int loop_count = 100000;
    int actual, expected;

    srandom(time(NULL));

    for (i = 0; i < loop_count; i++) {
        int a = random() % 10000000;
        int b = random() % 10000000;

        set_int(&num,  a);
        set_int(&num2, b);

        expected = a + b;

        add(&num, &num2, &num_result);
        get_int(&num_result, &actual);

        if (actual != expected) {
            puts("NG!!");
            return -1;
        }
    }

    puts("OK.");
    return 0;
}
