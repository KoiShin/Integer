#ifndef MULTIPLE_PRECISION_ARITHMETIC_HPP
#define MULTIPLE_PRECISION_ARITHMETIC_HPP

#include <iostream>
#include <cmath>

using namespace std;

#define DIGIT_NUMBER    10
// TODO:例外処理

class Integer {
public:
    Integer();
    Integer(long number);
    Integer operator +(Integer integer2);
    Integer operator -(Integer integer2);
    // int operator *();
    // int operator /();
    // int operator %();
    // int operator =();
    // int operator +=();
    // int operator -=();
    // int operator *=();
    // int operator /=();
    // int operator %=();
    // bool operator <();
    // bool operator >();
    // bool operator <=();
    // bool operator >=();
    // bool operator ==();
    // bool operator !=();
    void operator ++();
    void operator --();
    void display_number();
    void display_number_zero_suppress();
    void clear_by_zero();
    int compare_number(Integer integer2);
    Integer get_abs();
    void set_random_number(int digit_number);
    void swap_number(Integer *integer2);
    bool is_zero();
    int get_int();
    Integer multiply_by_ten();
    Integer divided_by_ten();

private:
    int num[DIGIT_NUMBER];
    int sign;
    void set_sign(int sign);
};

Integer::Integer() {
    clear_by_zero();
    set_sign(1);
}

Integer::Integer(long number) {
    int i;

    clear_by_zero();
    set_sign(1);
    if (number < 0) {
        set_sign(-1);
        number *= -1;
    }

    for (i = 0; i < DIGIT_NUMBER; i++) {
        if (i >= DIGIT_NUMBER) {
            cout << "Some error occurred" << endl;
        }
        num[i] = number % 10;
        number /= 10;
    }
}

Integer Integer::operator +(Integer integer2) {
    Integer result;
    int carry = 0;
    int tmp;
    int i;

    result.clear_by_zero();

    for (i = 0; i < DIGIT_NUMBER; i++) {
        tmp = this->num[i] + integer2.num[i] + carry;
        result.num[i] = tmp % 10;
        carry = tmp / 10;
    }
    if (carry != 0) {
        puts("overflow!!");
    }
    return result;
}

Integer Integer::operator -(Integer integer2) {
    Integer result;
    int borrow = 0;
    int minuend;
    int i;

    result.clear_by_zero();

    if (this->compare_number(integer2) == -1) {
        this->swap_number(&integer2);
        result.set_sign(-1);
    }

    for (i = 0; i < DIGIT_NUMBER; i++) {
        minuend = this->num[i] - borrow;
        if (minuend >= integer2.num[i]) {
            result.num[i] = minuend - integer2.num[i];
            borrow = 0;
        } else {
            result.num[i] = minuend - integer2.num[i] + 10;
            borrow = 1;
        }
    }
    this->swap_number(&integer2);

    if (borrow != 0) {
        puts("underflow!!");
    }

    return result;
}
// TODO:+=を実装した後にこれを使うように書き換える
void Integer::operator ++() {
    Integer one(1);
    *this = *this + one;
}

void Integer::operator --() {
    Integer one(1);
    *this = *this - one;
}

void Integer::set_sign(int sign) {
    if (sign != 1 && sign != -1) {
        puts("invalid sign!!");
    }
    this->sign = (sign == 1) ? 1 : -1;
}

void Integer::clear_by_zero() {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        num[i] = 0;
    }
    set_sign(1);
}

void Integer::display_number() {
    int i;
    cout << ((sign == 1) ? " +" : " -");
    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        cout.width(2);
        cout << num[i];
    }
    cout << endl;
}

void Integer::display_number_zero_suppress() {
    int i;
    cout << ((sign == 1) ? " +" : " -");
    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        if (num[i] != 0) break;
    }
    for (; i >= 0; i--) {
        cout.width(2);
        cout << num[i];
    }
    cout << endl;
}

int Integer::compare_number(Integer integer2) {
    int i;
    if (this->sign > integer2.sign) return  1;
    if (this->sign < integer2.sign) return -1;

    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        if (this->num[i] > integer2.num[i]) return  1 * this->sign;
        if (this->num[i] < integer2.num[i]) return -1 * this->sign;
    }
    return 0;
}

void Integer::swap_number(Integer *integer2) {
    Integer tmp;
    tmp = *this;
    *this = *integer2;
    *integer2 = tmp;
}

Integer Integer::get_abs() {
    Integer abs_num;
    abs_num = *this;
    abs_num.set_sign(1);
    return abs_num;
}

bool Integer::is_zero() {
    int i;
    for (i = 0; i < DIGIT_NUMBER; i++) {
        if (num[i] != 0) return false;
    }
    return true;
}

void Integer::set_random_number(int digit_number) {
    int i;
    int sign;

    if (digit_number > DIGIT_NUMBER) {
        cout << "digit number is too long!!" << endl;
        return;
    }

    clear_by_zero();
    for (i = 0; i < digit_number; i++) {
        num[i] = random() % 10;
    }
    sign = (random() % 2 == 0) ? 1 : -1;
    set_sign(sign);
}

int Integer::get_int() {
    int i;
    int number = 0;

    for (i = 0; i < DIGIT_NUMBER; i++) {
        number += num[i] * pow(10, i);
    }
    if (sign == -1) {
        number *= -1;
    }
    return number;
}

Integer Integer::multiply_by_ten() {
    Integer result;
    int i;

    if (this->num[DIGIT_NUMBER - 1] != 0) {
        puts("overflow!!");
    }

    for (i = 0; i < DIGIT_NUMBER - 1; i++) {
        result.num[i + 1] = this->num[i];
    }
    result.num[0] = 0;

    return 0;
}

Integer Integer::divided_by_ten() {
    Integer result;
    int i;
    int surplus;

    if (this->num[DIGIT_NUMBER - 1] != 0) {
        puts("underflow!!");
    }
    surplus = (this->sign == 1) ? this->num[0] : this->num[0] * -1;

    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        result.num[i - 1] = this->num[i];
    }
    result.num[DIGIT_NUMBER - 1] = 0;

    return surplus;
}

#endif
