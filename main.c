#include <stdio.h>
#include "integer.h"

int check_adder() {
    int i;
    Number num, num2, num_result;
    int loop_count = 100000;
    int actual, expected;

    srandom(time(NULL));
    clear_by_zero(&num_result);

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

int check_subtracter() {
    int i;
    Number num, num2, num_result;
    int loop_count = 100000;
    int actual, expected;

    clear_by_zero(&num_result);

    for (i = 0; i < loop_count; i++) {
        int a = random() % 10000000;
        int b = random() % 10000000;

        set_int(&num,  a);
        set_int(&num2, b);
        // printf("a        = %d\n", a);
        // printf("b        = %d\n", b);

        expected = a - b;
        // printf("expected = %d\n", expected);

        subtract(&num, &num2, &num_result);
        // display_number(&num_result);
        // putchar('\n');

        get_int(&num_result, &actual);
        // printf("actual   = %d\n", actual);

        if (actual != expected) {
            puts("NG!!");
        }
        // putchar('\n');
    }

    puts("OK.");
    return 0;
}

int main(void) {
    srandom(time(NULL));
    check_subtracter();

    return 0;
}
