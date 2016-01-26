#include <stdio.h>
#include "integer.h"

int main(void) {
    int i;
    Number num, num2, num_result, num_surplus;
    int loop_count = 1000;
    int actual_result, actual_surplus;
    int expected_result, expected_surplus;

    srandom(time(NULL));

    for (i = 0; i < loop_count; i++) {
        int a = random() % 1000;
        int b = random() % 1000;

        // a *= (random() % 2 == 0) ? 1: -1;
        // b *= (random() % 2 == 0) ? 1: -1;
        set_int(&num,  a);
        set_int(&num2, b);

        expected_result = a / b;
        expected_surplus = a % b;

        divide(&num, &num2, &num_result, &num_surplus);
        get_int(&num_result, &actual_result);
        get_int(&num_surplus, &actual_surplus);

        if (actual_result != expected_result || actual_surplus != expected_surplus) {
            puts("NG!!");
            return -1;
        }
    }

    puts("OK.");
    return 0;
}
