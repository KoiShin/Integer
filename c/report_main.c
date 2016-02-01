#include <stdio.h>
#include <math.h>

#define DIGIT_NUMBER      2020
#define DECIMAL_PLACES    1000

#define FALSE 0
#define TRUE  1

typedef int bool;

typedef struct {
    int n[DIGIT_NUMBER];
    int sign;
} Number;

void clear_by_zero(Number *num);
bool is_zero(const Number *num);
int  compare_number(const Number *num, const Number *num2);
void display_number_zero_suppress(const Number *num);
void set_sign(Number *num, int sign);
int  get_sign(const Number *num);
int  set_int(Number *num, long x);
void get_abs(const Number *num, Number *abs_num);
void copy_number(const Number *from_num, Number *to_num);
void swap_number(Number *num, Number *num2);
int  multiply_by_ten(const Number *num, Number *result);
int  divided_by_ten(const Number *num, Number *result);
int  add(const Number *num, const Number *num2, Number *result);
int  increment(const Number *num, Number *result);
int  subtract(const Number *num, const Number *num2, Number *result);
int  multiple_positive_num(const Number *multiplicand,
        const Number *multiplier, Number *result);
int  multiple(const Number *multiplicand, const Number *multiplier,
        Number *result);
int  divide_positive_num(Number *dividend, Number *divisor, Number *result,
        Number *surplus);
int  divide(const Number *dividend, const Number *divisor, Number *result,
        Number *surplus);
int  sqrt_newton(const Number *num, Number *result,
        unsigned long approximation);

int main(void) {
    Number num, tmp, result, two, result_;
    int i;

    // set 4,900,000,001
    set_int(&num, 490000000);
    multiply_by_ten(&num, &tmp);
    increment(&tmp, &num);
    for (i = 0; i < DECIMAL_PLACES * 2; i++) {
        multiply_by_ten(&num, &tmp);
        copy_number(&tmp, &num);
    }

    printf("sqrt(\n");
    display_number_zero_suppress(&num);
    puts(" )\n=");

    sqrt_newton(&num, &result, 1);

    display_number_zero_suppress(&result); putchar('\n');

    set_int(&two, 2);
    power(&result, &two, &result_);
    display_number_zero_suppress(&result_); putchar('\n');

    return 0;
}

void clear_by_zero(Number *num) {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        num->n[i] = 0;
    }
    set_sign(num, 1);
}

bool is_zero(const Number *num) {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        if (num->n[i] != 0) return FALSE;
    }
    return TRUE;
}

int compare_number(const Number *num, const Number *num2) {
    int i;
    int num_sign = get_sign(num);

    if (num_sign > get_sign(num2)) return  1;
    if (num_sign < get_sign(num2)) return -1;

    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        if (num->n[i] > num2->n[i]) return  1 * num_sign;
        if (num->n[i] < num2->n[i]) return -1 * num_sign;
    }
    return 0;
}

void display_number_zero_suppress(const Number *num) {
    int i;
    int count = 0;

    printf("%s", (get_sign(num) == 1) ? " +" : " -");

    for (i = DIGIT_NUMBER - 1; num->n[i] == 0 && i >= 0; i--)
        ;
    for (; i >= 0; i--, count++) {
        printf("%2d", num->n[i]);
        if (count % 30 == 29) {
            putchar('\n');
        }
    }
}

void set_sign(Number *num, int sign) {
    if (sign != 1 && sign != -1) {
        puts("invalid sign!!");
        return;
    }
    num->sign = sign;
}

int get_sign(const Number *num) {
    return num->sign;
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
        if (x / 10 == 0) break;
        x /= 10;
    }
    return 0;
}

void get_abs(const Number *num, Number *abs_num) {
    copy_number(num, abs_num);
    set_sign(abs_num, 1);
}

void copy_number(const Number *from_num, Number *to_num) {
    *to_num = *from_num;
}

void swap_number(Number *num, Number *num2) {
    Number tmp = *num;
    *num       = *num2;
    *num2      = tmp;
}

int multiply_by_ten(const Number *num, Number *result) {
    int i;

    clear_by_zero(result);

    if (num->n[DIGIT_NUMBER - 1] != 0) {
        puts("overflow!!(multiply_by_ten)");
        return -1;
    }

    for (i = 0; i < DIGIT_NUMBER - 1; i++) {
        result->n[i + 1] = num->n[i];
    }
    result->n[0] = 0;

    set_sign(result, get_sign(num));

    return 0;
}

int divided_by_ten(const Number *num, Number *result) {
    int i, surplus;

    clear_by_zero(result);

    if (num->n[DIGIT_NUMBER - 1] != 0) {
        puts("underflow!!");
        return -1;
    }
    surplus = (get_sign(num) == 1) ? num->n[0] : num->n[0] * -1;

    for (i = DIGIT_NUMBER - 1; i > 0; i--) {
        result->n[i - 1] = num->n[i];
    }
    result->n[DIGIT_NUMBER - 1] = 0;

    set_sign(result, get_sign(num));

    return surplus;
}

int add(const Number *num, const Number *num2, Number *result) {
    int carry = 0;
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
        int tmp = num->n[i] + num2->n[i] + carry;
        result->n[i] = tmp % 10;
        carry = tmp / 10;
    }

    if (carry != 0) {
        puts("overflow!!(add)");
        return -1;
    }

    return 0;
}

int increment(const Number *num, Number *result) {
    Number one; /* = */ set_int(&one, 1);

    return add(num, &one, result);
}

int subtract(const Number *num, const Number *num2, Number *result) {
    Number num_;  /* = */ copy_number(num, &num_);
    Number num2_; /* = */ copy_number(num2, &num2_);
    int borrow = 0;
    int minuend;
    int i;
    bool is_swapped = FALSE;

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
        is_swapped = TRUE;
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

    if (is_swapped) {
        swap_number(&num2_, &num_);
    }

    if (borrow != 0) {
        puts("underflow!!(subtract)");
        return -1;
    }

    return 0;
}

int multiple_positive_num(const Number *multiplicand,
        const Number *multiplier, Number *result) {
    int i;
    int multiplicand_i, multiplier_i;
    int carry = 0;
    int r;
    int top_multiplicand, top_multiplier;
    Number result_;    /* = */ clear_by_zero(&result_);
    Number tmp_result; /* = */ clear_by_zero(&tmp_result);
    clear_by_zero(result);

    for (top_multiplicand = DIGIT_NUMBER - 1;
            multiplicand->n[top_multiplicand] == 0; top_multiplicand--)
        ;

    for (top_multiplier = DIGIT_NUMBER - 1;
            multiplier->n[top_multiplier] == 0; top_multiplier--)
        ;

    for (multiplier_i = 0; multiplier_i <= top_multiplier + 1;
            multiplier_i++) {
        Number tmp;  /* = */ clear_by_zero(&tmp);
        Number tmp2; /* = */ clear_by_zero(&tmp2);

        for (multiplicand_i = 0; multiplicand_i <= top_multiplicand + 1;
                multiplicand_i++) {
            int mul = multiplicand->n[multiplicand_i]
                    * multiplier->n[multiplier_i] + carry;
            tmp.n[multiplicand_i] = mul % 10;
            carry = mul / 10;
        }

        for (i = 0; i < multiplier_i; i++) {
            r = multiply_by_ten(&tmp, &tmp2);
            if (r != 0) return -1;
            copy_number(&tmp2, &tmp);
        }

        r = add(&result_, &tmp, &tmp_result);
        if (r != 0) return -1;
        copy_number(&tmp_result, &result_);
    }
    copy_number(&result_, result);

    return 0;
}

int multiple(const Number *multiplicand, const Number *multiplier,
        Number *result) {
    Number abs_multiplicand; /* = */ get_abs(multiplicand,  &abs_multiplicand);
    Number abs_multiplier;   /* = */ get_abs(multiplier, &abs_multiplier);
    int positive_multiplicand   = (get_sign(multiplicand)  == 1) ? 1 : 0;
    int positive_multiplier     = (get_sign(multiplier)    == 1) ? 1 : 0;
    int r;

    clear_by_zero(result);

    r = multiple_positive_num(&abs_multiplicand, &abs_multiplier, result);

    if (positive_multiplicand && positive_multiplier) {
        set_sign(result, 1);
    } else if (positive_multiplicand && !positive_multiplier) {
        set_sign(result, -1);
    } else if (!positive_multiplicand && positive_multiplier) {
        set_sign(result, -1);
    } else if (!positive_multiplicand && !positive_multiplier) {
        set_sign(result, 1);
    } else {
        return -1;
    }

    if (r == -1) {
        puts("overflow(multiple)");
    }
    return r;
}

int divide_positive_num(Number *dividend, Number *divisor, Number *result,
        Number *surplus) {
    Number tmp; /* = */ clear_by_zero(&tmp);
    int count = 0;
    int i;
    clear_by_zero(result);
    clear_by_zero(surplus);

    if (is_zero(divisor)) return -1;

    while (compare_number(dividend, divisor) == 1) {
        multiply_by_ten(divisor, &tmp);
        if (compare_number(dividend, &tmp) != 1) break;
        copy_number(&tmp, divisor);
        count++;
    }

    for (i = 0; i <= count; i++) {
        multiply_by_ten(result, &tmp); copy_number(&tmp, result);
        while (compare_number(dividend, divisor) > -1) {
            increment(result, &tmp);           copy_number(&tmp, result);
            subtract(dividend, divisor, &tmp); copy_number(&tmp, dividend);
        }
        divided_by_ten(divisor, &tmp); copy_number(&tmp, divisor);
    }
    copy_number(dividend, surplus);

    return 0;
}

int divide(const Number *dividend, const Number *divisor, Number *result,
        Number *surplus) {
    Number abs_dividend; /* = */ get_abs(dividend,  &abs_dividend);
    Number abs_divisor;  /* = */ get_abs(divisor, &abs_divisor);
    int positive_dividend   = (get_sign(dividend)  == 1) ? 1 : 0;
    int positive_divisor    = (get_sign(divisor)   == 1) ? 1 : 0;
    int r;

    clear_by_zero(result);
    clear_by_zero(surplus);

    r = divide_positive_num(&abs_dividend, &abs_divisor, result, surplus);

    if (positive_dividend && positive_divisor) {
        set_sign(result,  1);
        set_sign(surplus, 1);
    } else if (positive_dividend && !positive_divisor) {
        set_sign(result, -1);
        set_sign(surplus, 1);
    } else if (!positive_dividend && positive_divisor) {
        set_sign(result,  -1);
        set_sign(surplus, -1);
    } else if (!positive_dividend && !positive_divisor) {
        set_sign(result,   1);
        set_sign(surplus, -1);
    } else {
        return -1;
    }

    if (is_zero(result)) {
        set_sign(result, 1);
    }

    if (is_zero(surplus)) {
        set_sign(surplus, 1);
    }

    if (r != 0) {
        puts("Error(divide)");
    }
    return r;
}

int sqrt_newton(const Number *num, Number *result,
        unsigned long approximation) {
    int i;
    Number approximation_; /* = */ clear_by_zero(&approximation_);
    Number before_num;     /* = */ clear_by_zero(&before_num);
    Number two_before_num; /* = */ clear_by_zero(&two_before_num);
    Number dummy;          /* = */ clear_by_zero(&dummy);
    Number tmp_;           /* = */ clear_by_zero(&tmp_);
    Number five;           /* = */ set_int(&five, 5);

    clear_by_zero(result);

    // set approximation
    set_int(&tmp_, approximation);
    for (i = 0; i < DECIMAL_PLACES; i++) {
        multiply_by_ten(&tmp_, &approximation_);
        copy_number(&approximation_, &tmp_);
    }

    if (is_zero(&approximation_)) {
        copy_number(num, result);
        return 0;
    }

    copy_number(&approximation_, &before_num);
    copy_number(&approximation_, &two_before_num);

    while (1) {
        Number tmp;  /* = */ clear_by_zero(&tmp);
        Number tmp2; /* = */ clear_by_zero(&tmp2);
        copy_number(&before_num, &two_before_num);
        copy_number(&approximation_, &before_num);

        // x = (before_num + (num / before_num)) / 2
        divide(num, &before_num, &tmp, &dummy);
        add(&before_num, &tmp, &tmp2);
        multiple(&tmp2, &five, &tmp);
        divided_by_ten(&tmp, &approximation_);

        if (compare_number(&approximation_, &before_num) == 0) break; // converge
        if (compare_number(&approximation_, &two_before_num) != 0) continue;

        // oscillation
        if (compare_number(&before_num, &approximation_) == -1) {
            copy_number(&before_num, &approximation_); // select more smaller value
        }
        break;
    }
    copy_number(&approximation_, result);
    return 0;
}
