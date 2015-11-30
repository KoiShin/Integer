#include <stdio.h>
#include "integer.h"

int main(void) {
    Number num, num2, num3;
    int r;

    set_int(&num, 43210);
    printf(" num = ");
    display_number(&num);
    putchar('\n');

    set_int(&num2, 98765);
    printf("num2 = ");
    display_number(&num2);
    putchar('\n');

    clear_by_zero(&num3);

    if (!sub(&num, &num2, &num3)) {
        // sub(&num, &num2, &num3);
        printf("num3 = ");
        display_number(&num3);
        putchar('\n');
    }

    return 0;
}
