#ifndef MULTIPLE_PRECISION_ARITHMETIC
#define MULTIPLE_PRECISION_ARITHMETIC

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DIGIT_NUMBER    10

typedef struct NUMBER {
    int n[DIGIT_NUMBER];
    int sign;
} Number;

void clear_by_zero(Number*);
void display_number(Number*);
void display_number_zero_suppress(Number*);
void set_random_number(Number*, int);
void copy_number(Number*, Number*);
void get_abs(Number*, Number*);
int  is_zero(Number*);
int  multiply_by_ten(Number*, Number*);
int  divided_by_ten(Number*, Number*);
void swap_number(Number*, Number*);
int  set_int(Number*, long);
int  get_int(Number*, int*);
void set_sign(Number*, int);
int  get_sign(Number*);
int  compare_number(Number*, Number*);
int  add(Number*, Number*, Number*);
int  subtract(Number *num, Number *num2, Number *result);

void clear_by_zero(Number *num) {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        num->n[i] = 0;
    }
    set_sign(num, 1);
}

void display_number(Number *num) {
    int i;
    printf("%s", (get_sign(num) == 1) ? " +" : " -");
    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        printf("%2d", num->n[i]);
    }
}

void display_number_zero_suppress(Number *num) {
    int i;
    printf("%s", (get_sign(num) == 1) ? " +" : " -");
    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        if (num->n[i] != 0) break;
    }
    for (; i >= 0; i--) {
        printf("%2d", num->n[i]);
    }
}

void set_random_number(Number *num, int digit_number) {
    int i, sign;

    if (digit_number > DIGIT_NUMBER) {
        puts("digit number is too long!!");
        return;
    }

    clear_by_zero(num);
    for (i = 0; i < digit_number; i++) {
        num->n[i] = random() % 10;
    }
    sign = (random() % 2 == 0) ? 1 : -1;
    set_sign(num, sign);
}

void copy_number(Number *from_num, Number *to_num) {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        to_num->n[i] = from_num->n[i];
    }
    set_sign(to_num, get_sign(from_num));
}

void get_abs(Number *num, Number *abs_num) {
    copy_number(num, abs_num);
    set_sign(abs_num, 1);
}

int is_zero(Number *num) {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        if (num->n[i] != 0) return -1;
    }
    return 0;
}

int multiply_by_ten(Number *num, Number *computation) {
    int i;

    if (num->n[DIGIT_NUMBER - 1] != 0) {
        puts("overflow!!");
        return -1;
    }

    for (i = 0; i < DIGIT_NUMBER - 1; i++) {
        computation->n[i + 1] = num->n[i];
    }
    computation->n[0] = 0;

    return 0;
}

int divided_by_ten(Number *num, Number *computation) {
    int i, surplus;

    if (num->n[DIGIT_NUMBER - 1] != 0) {
        puts("underflow!!");
        return -1;
    }
    surplus = (get_sign(num) == 1) ? num->n[0] : num->n[0] * -1;

    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        computation->n[i - 1] = num->n[i];
    }
    computation->n[DIGIT_NUMBER - 1] = 0;

    return surplus;
}

void swap_number(Number *num, Number *num2) {
    Number tmp;
    tmp = *num;
    *num = *num2;
    *num2 = tmp;
}

int set_int(Number *num, long x) {
    int i;

    clear_by_zero(num);
    if (x < 0) {
        set_sign(num, -1);
        x *= -1;
    }

    for (i = 0; i < DIGIT_NUMBER; i++) {
        if (i >= DIGIT_NUMBER) return -1;
        num->n[i] = x % 10;
        x /= 10;
    }

    return 0;
}

int get_int(Number *num, int *x) {
    int i;
    *x = 0;

    for (i = 0; i < DIGIT_NUMBER; i++) {
        *x += num->n[i] * pow(10, i);
    }
    if (num->sign == -1) {
        *x *= -1;
    }
    return 0;
}

void set_sign(Number *num, int sign) {
    if (sign != 1 && sign != -1) {
        puts("invalid sign!!");
    }
    num->sign = (sign == 1) ? 1 : -1;
}

int get_sign(Number *num) {
    return (num->sign == 1) ? 1 : -1;
}

int compare_number(Number *num, Number *num2) {
    int i;
    int sign = get_sign(num);
    if (get_sign(num) > get_sign(num2)) return  1;
    if (get_sign(num) < get_sign(num2)) return -1;

    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        if (num->n[i] > num2->n[i]) return  1 * sign;
        if (num->n[i] < num2->n[i]) return -1 * sign;
    }
    return 0;
}

int add(Number *num, Number *num2, Number *result) {
    int carry = 0;
    int tmp;
    int i;

    clear_by_zero(result);

    for (i = 0; i < DIGIT_NUMBER; i++) {
        tmp = num->n[i] + num2->n[i] + carry;
        result->n[i] = tmp % 10;
        carry = tmp / 10;
    }
    if (carry != 0) {
        puts("overflow!!");
        return -1;
    }

    return 0;
}

int subtract(Number *num, Number *num2, Number *result) {
    int borrow = 0;
    int minuend;
    int i;

    clear_by_zero(result);

    if (compare_number(num, num2) == -1) {
        swap_number(num, num2);
        set_sign(result, -1);
    }

    for (i = 0; i < DIGIT_NUMBER; i++) {
        minuend = num->n[i] - borrow;
        if (minuend >= num2->n[i]) {
            result->n[i] = minuend - num2->n[i];
            borrow = 0;
        } else {
            result->n[i] = minuend - num2->n[i] + 10;
            borrow = 1;
        }
    }
    swap_number(num2, num);

    if (borrow != 0) {
        puts("underflow!!");
        return -1;
    }

    return 0;
}

#endif