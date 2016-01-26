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
void display_number(const Number*);
void display_number_zero_suppress(const Number*);
void set_random_number(Number*, int);
void copy_number(const Number*, Number*);
void get_abs(const Number*, Number*);
int  is_zero(const Number*);
int  multiply_by_ten(const Number*, Number*);
int  divided_by_ten(const Number*, Number*);
void swap_number(Number*, Number*);
int  set_int(Number*, long);
int  get_int(const Number*, int*);
void set_sign(Number*, int);
int  get_sign(const Number*);
int  compare_number(const Number*, const Number*);
int  add(const Number*, const Number*, Number*);
int  subtract(const Number*, const Number*, Number*);
int  increment(const Number*, Number*);
int  decrement(const Number*, Number*);
int  simple_multiple(int, int, int*);
int  multiple_positive_num(const Number*, const Number*, Number*);
int  multiple(const Number*, const Number*, Number*);
int  divide(const Number*, const Number*, Number*, Number*);
int  power(const Number*, const Number*, Number*);

void clear_by_zero(Number *num) {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        num->n[i] = 0;
    }
    set_sign(num, 1);
}

void display_number(const Number *num) {
    int i;
    printf("%s", (get_sign(num) == 1) ? " +" : " -");
    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        printf("%2d", num->n[i]);
    }
}

void display_number_zero_suppress(const Number *num) {
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

void copy_number(const Number *from_num, Number *to_num) {
    int i;
    clear_by_zero(to_num);

    for (i = 0; i < DIGIT_NUMBER; i++) {
        to_num->n[i] = from_num->n[i];
    }
    set_sign(to_num, get_sign(from_num));
}

void get_abs(const Number *num, Number *abs_num) {
    clear_by_zero(abs_num);

    copy_number(num, abs_num);
    set_sign(abs_num, 1);
}

int is_zero(const Number *num) {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        if (num->n[i] != 0) return -1;
    }
    return 0;
}

int multiply_by_ten(const Number *num, Number *computation) {
    int i;

    clear_by_zero(computation);

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

int divided_by_ten(const Number *num, Number *computation) {
    int i, surplus;

    clear_by_zero(computation);

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

    for (i = 0; i < DIGIT_NUMBER; i++) {
        if (i >= DIGIT_NUMBER) return -1;
        num->n[i] = x % 10;
        x /= 10;
    }

    if (x >= 0) {
        set_sign(num, 1);
    } else {
        set_sign(num, -1);
        x *= -1;
    }

    return 0;
}

int get_int(const Number *num, int *x) {
    int i;
    *x = 0;

    for (i = 0; i < DIGIT_NUMBER; i++) {
        *x += num->n[i] * pow(10, i);
    }
    if (get_sign(num) == -1) {
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

int get_sign(const Number *num) {
    return (num->sign == 1) ? 1 : -1;
}

int compare_number(const Number *num, const Number *num2) {
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

int add(const Number *num, const Number *num2, Number *result) {
    int carry = 0;
    int tmp;
    int i;

    clear_by_zero(result);

    if (get_sign(num) == 1 && get_sign(num2) == -1) {
        Number abs_num;
        get_abs(num2, &abs_num);
        subtract(num, &abs_num, result);
        return 0;
    }
    if (get_sign(num) == -1 && get_sign(num2) == 1) {
        Number abs_num;
        get_abs(num, &abs_num);
        subtract(num2, &abs_num, result);
        return 0;
    }
    if (get_sign(num) == -1 && get_sign(num2) == -1) {
        Number abs_num, abs_num2;
        get_abs(num, &abs_num);
        get_abs(num2, &abs_num2);
        add(&abs_num, &abs_num2, result);
        set_sign(result, -1);
        return 0;
    }

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

int subtract(const Number *num, const Number *num2, Number *result) {
    Number num_, num2_;
    int borrow = 0;
    int minuend;
    int i;
    int swap_flg = 0;

    copy_number(num, &num_);
    copy_number(num2, &num2_);
    clear_by_zero(result);

    if (get_sign(&num2_) == -1) {
        Number abs_num;
        get_abs(&num2_, &abs_num);
        add(&num_, &abs_num, result);
        return 0;
    }
    if (get_sign(&num_) == -1 && get_sign(&num2_) == 1) {
        Number abs_num;
        get_abs(&num_, &abs_num);
        add(&abs_num, &num2_, result);
        set_sign(result, -1);
        return 0;
    }

    if (compare_number(&num_, &num2_) == -1) {
        swap_flg = 1;
        swap_number(&num_, &num2_);
        set_sign(result, -1);
    }

    for (i = 0; i < DIGIT_NUMBER; i++) {
        minuend = num_.n[i] - borrow;
        if (minuend >= num2_.n[i]) {
            result->n[i] = minuend - num2_.n[i];
            borrow = 0;
        } else {
            result->n[i] = minuend - num2_.n[i] + 10;
            borrow = 1;
        }
    }

    if (swap_flg) {
        swap_number(&num2_, &num_);
    }

    if (borrow != 0) {
        puts("underflow!!");
        return -1;
    }

    return 0;
}

int increment(const Number *num, Number *result) {
    Number one;
    set_int(&one, 1);
    clear_by_zero(result);

    return add(num, &one, result);
}

int decrement(const Number *num, Number *result) {
    Number one;
    set_int(&one, 1);
    clear_by_zero(result);

    return subtract(num, &one, result);
}

int simple_multiple(int num, int num2, int *result) {
    int i;
    int multiplier   = (num > num2) ? num2 : num;   // かける数
    int multiplicand = (num > num2) ? num  : num2;  // かけられる数

    *result = 0;

    for (i = 0; i < multiplier; i++) {
        *result += multiplicand;
    }

    return 0;
}

int multiple_positive_num(const Number *num, const Number *num2, Number *result) {
    int i;
    int num_i, num2_i;
    int carry = 0;
    int r;
    Number result_, tmp_result;
    clear_by_zero(result);
    clear_by_zero(&result_);
    clear_by_zero(&tmp_result);

    for (num2_i = 0; num2_i < DIGIT_NUMBER - 1; num2_i++) {
        Number tmp3, tmp4;
        clear_by_zero(&tmp3);
        clear_by_zero(&tmp4);

        for (num_i = 0; num_i < DIGIT_NUMBER - 1; num_i++) {
            int mul = num->n[num_i] * num2->n[num2_i] + carry;
            tmp3.n[num_i] = mul % 10;
            carry = mul / 10;
        }

        for (i = 0; i < num2_i; i++) {
            r = multiply_by_ten(&tmp3, &tmp4);
            if (r != 0) return -1;
            copy_number(&tmp4, &tmp3);
        }

        r = add(&result_, &tmp3, &tmp_result);
        if (r != 0) return -1;
        copy_number(&tmp_result, &result_);
    }

    copy_number(&result_, result);

    return 0;
}

int multiple(const Number *num, const Number *num2, Number *result) {
    Number abs_num, abs_num2;
    get_abs(num,  &abs_num);
    get_abs(num2, &abs_num2);
    int positive_num  = (get_sign(num)  == 1) ? 1 : 0;
    int positive_num2 = (get_sign(num2) == 1) ? 1 : 0;
    int r;

    clear_by_zero(result);

    if (positive_num && positive_num2) {
        r = multiple_positive_num(num, num2, result);
        set_sign(result, 1);
    } else if (positive_num && !positive_num2) {
        r = multiple_positive_num(num, &abs_num2, result);
        set_sign(result, -1);
    } else if (!positive_num && positive_num2) {
        r = multiple_positive_num(&abs_num, num2, result);
        set_sign(result, -1);
    } else if (!positive_num && !positive_num2) {
        r = multiple_positive_num(&abs_num, &abs_num2, result);
        set_sign(result, 1);
    } else {
        return -1;
    }

    if (r == -1) {
        puts("underflow");
    }
    return r;
}

//                      被除数                   除数              商              剰余
int divide(const Number *dividend, const Number *divisor, Number *result, Number *surplus) {
    Number tmp, dividend_;

    clear_by_zero(result);
    clear_by_zero(surplus);
    clear_by_zero(&tmp);
    clear_by_zero(&dividend_);

    if (is_zero(divisor) == 0) return -1;

    copy_number(dividend, &dividend_);

    while (1) {
        if (compare_number(&dividend_, divisor) < 0) break;
        increment(result, &tmp);             copy_number(&tmp, result);
        subtract(&dividend_, divisor, &tmp); copy_number(&tmp, &dividend_);
    }
    copy_number(&dividend_, surplus);

    return 0;
}

int power(const Number *base, const Number *exponent, Number *result) {
    int i = 0;
    int exponent_;
    Number result_;

    get_int(exponent, &exponent_);
    set_int(result, 1);
    clear_by_zero(&result_);

    if (exponent_ <  0) return -2;
    if (exponent_ == 0) return  0;

    while (1) {
        if (i >= exponent_) break;
        multiple(result, base, &result_);
        copy_number(&result_, result);
        i++;
    }

    return 0;
}

#endif
