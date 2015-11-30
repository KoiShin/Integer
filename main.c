#include <stdio.h>
#include "integer.h"

int main(void) {
    Number num, num2;
    int r;

    set_int(&num, -12345);
    printf(" num = ");
    display_number(&num);
    putchar('\n');

    copy_number(&num, &num2);
    set_sign(&num2, 1);
    printf("num2 = ");
    display_number(&num2);
    putchar('\n');

    r = get_sign(&num2);
    printf("get_sign() = %d\n", r);

    r = compare_number(&num, &num2);
    printf("compare_number() = %d\n", r);

    return 0;
}
