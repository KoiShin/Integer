#ifndef MULTIPLE_PRECISION_ARITHMETIC_HPP
#define MULTIPLE_PRECISION_ARITHMETIC_HPP

#include <iostream>
#include <cmath>

using namespace std;

#define DIGIT_NUMBER    10
// TODO:例外処理

class Integer {
friend ostream &operator <<(ostream &out, Integer &integer);

public:
    Integer();
    Integer(long number);
    Integer operator +(Integer integer2);
    Integer operator +(long num2);
    Integer operator -(Integer integer2);
    Integer operator -(long num2);
    Integer operator *(Integer integer2);
    Integer operator *(long num2);
    Integer operator /(Integer integer2);
    Integer operator /(long num2);
    Integer operator %(Integer integer2);
    Integer operator %(long num2);
    void operator =(long number);
    void operator +=(Integer integer2);
    void operator +=(long num2);
    void operator -=(Integer integer2);
    void operator -=(long num2);
    void operator *=(Integer integer2);
    void operator *=(long num2);
    void operator /=(Integer integer2);
    void operator /=(long num2);
    void operator %=(Integer integer2);
    void operator %=(long num2);
    bool operator >(Integer integer2);
    bool operator >(long num2);
    bool operator <(Integer integer2);
    bool operator <(long num2);
    bool operator >=(Integer integer2);
    bool operator >=(long num2);
    bool operator <=(Integer integer2);
    bool operator <=(long num2);
    bool operator ==(Integer integer2);
    bool operator ==(long num2);
    bool operator !=(Integer integer2);
    bool operator !=(long num2);
    void operator ++();
    void operator ++(int);
    void operator --();
    void operator --(int);
    void display_number();
    void display_number_zero_suppress();
    int get_int();
    Integer get_abs();
    bool is_zero();
    bool is_prime();
    void clear_by_zero();
    void set_random_number(int digit_number);
    int multiply_by_ten();
    int divided_by_ten();
    Integer power(Integer exponent);
    Integer power(long exponent);
    Integer factorial();

private:
    int num[DIGIT_NUMBER];
    int sign;
    int compare_number(Integer integer2);
    void set_sign(int sign);
    Integer multiple_positive_num(Integer integer2);
    Integer divmod(Integer integer2, bool is_mode_divide);
};

ostream &operator <<(ostream &out, Integer &integer) {
    int i;
    out << ((integer.sign == 1) ? " +" : " -");
    for (i = DIGIT_NUMBER - 1; i >= 0; i--) {
        if (integer.num[i] != 0) break;
    }
    for (; i >= 0; i--) {
        printf("%2d", integer.num[i]);
    }

    return out;
}

Integer::Integer() {
    clear_by_zero();
}

Integer::Integer(long number) {
    *this = number;
}

Integer Integer::operator +(Integer integer2) {
    int carry = 0;
    Integer result;

    if (*this >= 0 && integer2 < 0) {
        Integer abs_num = integer2.get_abs();
        result = *this - abs_num;
        return result;
    }

    if (*this < 0 && integer2 >= 0) {
        Integer abs_num = this->get_abs();
        result = integer2 - abs_num;
        return result;
    }

    if (*this < 0 && integer2 < 0) {
        Integer abs_num = this->get_abs();
        Integer abs_num2 = integer2.get_abs();
        result = abs_num + abs_num2;
        result.set_sign(-1);
        return result;
    }

    for (int i = 0; i < DIGIT_NUMBER; i++) {
        int sum = num[i] + integer2.num[i] + carry;
        result.num[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry != 0) {
        cout << "overflow!!(add)" << endl;
    }

    return result;
}

Integer Integer::operator +(long num2) {
    Integer integer2 = num2;
    return *this + integer2;
}

Integer Integer::operator -(Integer integer2) {
    Integer num_ = *this;
    Integer num2_ = integer2;
    Integer result;
    int borrow = 0;

    if (num2_ < 0) {
        Integer abs_num = num2_.get_abs();
        result = num_ + abs_num;
        return result;
    }

    if (num_ < 0 && num2_ >= 0) {
        Integer abs_num = num_.get_abs();
        result = abs_num + num2_;
        result.set_sign(-1);
        return result;
    }

    if (num_ < num2_) {
        swap(num_, num2_);
        result.set_sign(-1);
    }

    for (int i = 0; i < DIGIT_NUMBER; i++) {
        int minuend = num_.num[i] - borrow;
        if (minuend >= num2_.num[i]) {
            result.num[i] = minuend - num2_.num[i];
            borrow = 0;
        } else {
            result.num[i] = minuend - num2_.num[i] + 10;
            borrow = 1;
        }
    }

    if (borrow != 0) {
        cout << "underflow!!(subtract)" << endl;
    }

    return result;
}

Integer Integer::operator -(long num2) {
    Integer integer2 = num2;
    return *this - integer2;
}

Integer Integer::multiple_positive_num(Integer integer2) {
    int carry = 0;
    int top_multiplicand, top_multiplier;
    Integer result;

    for (top_multiplicand = DIGIT_NUMBER - 1;
            num[top_multiplicand] == 0; top_multiplicand--)
        ;

    for (top_multiplier = DIGIT_NUMBER - 1;
            integer2.num[top_multiplier] == 0; top_multiplier--)
        ;

    for (int multiplier_i = 0; multiplier_i <= top_multiplier + 1;
            multiplier_i++) {
        Integer tmp;

        for (int multiplicand_i = 0; multiplicand_i <= top_multiplicand + 1;
                multiplicand_i++) {
            int mul = num[multiplicand_i]
                    * integer2.num[multiplier_i] + carry;
            tmp.num[multiplicand_i] = mul % 10;
            carry = mul / 10;
        }

        for (int i = 0; i < multiplier_i; i++) {
            tmp.multiply_by_ten();
        }

        result += tmp;
    }

    return result;
}

Integer Integer::operator *(Integer integer2) {
    Integer abs_multiplicand = this->get_abs();
    Integer abs_multiplier = integer2.get_abs();
    Integer result = abs_multiplicand.multiple_positive_num(abs_multiplier);;
    int positive_multiplicand = (*this >= 0) ? 1 : 0;
    int positive_multiplier   = (integer2 >= 0) ? 1 : 0;

    if (positive_multiplicand && !positive_multiplier) {
        result.set_sign(-1);
    } else if (!positive_multiplicand && positive_multiplier) {
        result.set_sign(-1);
    }
    return result;
}

Integer Integer::operator *(long num2) {
    Integer integer2 = num2;
    return *this * integer2;
}

Integer Integer::divmod(Integer integer2, bool is_mode_divide) {
    Integer result, surplus;
    int cnt;

    if (integer2 == 0) return -1;

    for (cnt = 0; *this >= integer2; cnt++) {
        integer2.multiply_by_ten();
    }

    for (int i = 0; i <= cnt; i++) {
        result.multiply_by_ten();
        while (*this >= integer2) {
            result++;
            *this -= integer2;
        }
        integer2.divided_by_ten();
    }
    surplus = *this;

    return (is_mode_divide == true) ? result : surplus;
}

Integer Integer::operator /(Integer integer2) {
    Integer abs_dividend = this->get_abs();
    Integer abs_divisor = integer2.get_abs();
    Integer result = abs_dividend.divmod(abs_divisor, true);
    int positive_dividend = (*this >= 0) ? 1 : 0;
    int positive_divisor  = (integer2 >= 0) ? 1 : 0;

    if (positive_dividend && !positive_divisor) {
        result.set_sign(-1);
    } else if (!positive_dividend && positive_divisor) {
        result.set_sign(-1);
    }

    return result;
}

Integer Integer::operator /(long num2) {
    Integer integer2 = num2;
    return *this / integer2;
}

Integer Integer::operator %(Integer integer2) {
    Integer abs_dividend = this->get_abs();
    Integer abs_divisor = integer2.get_abs();
    Integer surplus = abs_dividend.divmod(abs_divisor, false);
    int positive_dividend = (*this >= 0) ? 1 : 0;
    int positive_divisor  = (integer2 >= 0) ? 1 : 0;

    if (!positive_dividend && positive_divisor) {
        surplus.set_sign(-1);
    } else if (!positive_dividend && !positive_divisor) {
        surplus.set_sign(-1);
    }

    return surplus;
}

Integer Integer::operator %(long num2) {
    Integer integer2 = num2;
    return *this % integer2;
}

void Integer::operator =(long number) {
    clear_by_zero();

    if (number < 0) {
        set_sign(-1);
        number *= -1;
    }

    for (int i = 0; i < DIGIT_NUMBER; i++) {
        if (i >= DIGIT_NUMBER) {
            cout << "overflow!!" << endl;
        }
        num[i] = number % 10;
        number /= 10;
    }
}

void Integer::operator +=(Integer integer2) {
    Integer result = *this + integer2;
    *this = result;
}

void Integer::operator +=(long num2) {
    Integer integer2 = num2;
    *this += integer2;
}

void Integer::operator -=(Integer integer2) {
    Integer result = *this - integer2;
    *this = result;
}

void Integer::operator -=(long num2) {
    Integer integer2 = num2;
    *this -= integer2;
}

void Integer::operator *=(Integer integer2) {
    Integer result = *this * integer2;
    *this = result;
}

void Integer::operator *=(long num2) {
    Integer integer2 = num2;
    *this *= integer2;
}

void Integer::operator /=(Integer integer2) {
    Integer result = *this / integer2;
    *this = result;
}

void Integer::operator /=(long num2) {
    Integer integer2 = num2;
    *this /= integer2;
}

void Integer::operator %=(Integer integer2) {
    Integer result = *this % integer2;
    *this = result;
}

void Integer::operator %=(long num2) {
    Integer integer2 = num2;
    *this %= integer2;
}

void Integer::operator ++() {
    *this += 1;
}

void Integer::operator --() {
    *this -= 1;
}

void Integer::operator ++(int) {
    *this += 1;
}

void Integer::operator --(int) {
    *this -= 1;
}

int Integer::compare_number(Integer integer2) {
    if (this->sign > integer2.sign) return  1;
    if (this->sign < integer2.sign) return -1;

    for (int i = DIGIT_NUMBER - 1; i >= 0; i--) {
        if (this->num[i] > integer2.num[i]) return  1 * this->sign;
        if (this->num[i] < integer2.num[i]) return -1 * this->sign;
    }
    return 0;
}

bool Integer::operator >(Integer integer2) {
    if (compare_number(integer2) == 1) return true;
    else return false;
}

bool Integer::operator >(long num2) {
    Integer integer2 = num2;
    return *this > integer2;
}

bool Integer::operator <(Integer integer2) {
    if (compare_number(integer2) == -1) return true;
    else return false;
}

bool Integer::operator <(long num2) {
    Integer integer2 = num2;
    return *this < integer2;
}

bool Integer::operator >=(Integer integer2) {
    if (compare_number(integer2) >= 0) return true;
    else return false;
}

bool Integer::operator >=(long num2) {
    Integer integer2 = num2;
    return *this >= integer2;
}

bool Integer::operator <=(Integer integer2) {
    if (compare_number(integer2) <= 0) return true;
    else return false;
}

bool Integer::operator <=(long num2) {
    Integer integer2 = num2;
    return *this <= integer2;
}

bool Integer::operator ==(Integer integer2) {
    if (compare_number(integer2) == 0) return true;
    else return false;
}

bool Integer::operator ==(long num2) {
    Integer integer2 = num2;
    return *this == integer2;
}

bool Integer::operator !=(Integer integer2) {
    if (compare_number(integer2) != 0) return true;
    else return false;
}

bool Integer::operator !=(long num2) {
    Integer integer2 = num2;
    return *this != integer2;
}

void Integer::display_number() {
    cout << ((sign == 1) ? " +" : " -");
    for (int i = DIGIT_NUMBER - 1; i >= 0; i--) {
        printf("%2d", num[i]);
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
        printf("%2d", num[i]);
    }
    cout << endl;
}

void Integer::set_sign(int sign) {
    if (sign != 1 && sign != -1) {
        cout << "invalid sign!!(set_sign)" << endl;
    }
    this->sign = (sign == 1) ? 1 : -1;
}

int Integer::get_int() {
    int number = 0;

    for (int i = 0; i < DIGIT_NUMBER; i++) {
        number += num[i] * pow(10, i);
    }
    if (sign == -1) {
        number *= -1;
    }

    return number;
}

Integer Integer::get_abs() {
    Integer abs_num = *this;
    abs_num.set_sign(1);
    return abs_num;
}

bool Integer::is_zero() {
    for (int n : num) {
        if (n != 0) return false;
    }
    return true;
}

bool Integer::is_prime() {
    Integer integer = *this;
    Integer division = 3;
    Integer remain;
    Integer max = integer / 2;

    if (integer.num[0] % 2 == 0) return false;
    if (integer == 1) return false;

    while (1) {
        if (division >= max) break;

        remain = integer % division;
        if (remain == 0) return false;

        division += 2;
    }

    return true;
}

void Integer::clear_by_zero() {
    for (int &n : num) {
        n = 0;
    }
    set_sign(1);
}

void Integer::set_random_number(int digit_number) {
    int sign;

    if (digit_number > DIGIT_NUMBER) {
        cout << "digit number is too long!!" << endl;
        return;
    }

    clear_by_zero();
    for (int i = 0; i < digit_number; i++) {
        num[i] = random() % 10;
    }
    sign = (random() % 2 == 0) ? 1 : -1;
    set_sign(sign);
}

int Integer::multiply_by_ten() {
    Integer result;

    if (num[DIGIT_NUMBER - 1] != 0) {
        cout << "overflow!!(multiply_by_ten)" << endl;
        return -1;
    }

    for (int i = 0; i < DIGIT_NUMBER - 1; i++) {
        result.num[i + 1] = num[i];
    }
    result.num[0] = 0;
    *this = result;

    return 0;
}

int Integer::divided_by_ten() {
    Integer result;

    if (num[DIGIT_NUMBER - 1] != 0) {
        cout << "underflow!!(divided_by_ten)" << endl;
        return -1;
    }

    for (int i = DIGIT_NUMBER - 1; i >= 0; i--) {
        result.num[i - 1] = num[i];
    }
    result.num[DIGIT_NUMBER - 1] = 0;
    *this = result;

    return 0;
}

Integer Integer::power(Integer exponent) {
    Integer result = 1;
    Integer i;

    if (*this == 0) {
        result = 0;
        return result;
    }
    if (*this == 1 || exponent == 0) {
        return result;
    }

    while (1) {
        if (i >= exponent) break;
        result *= *this;
        i++;
    }

    return result;
}

Integer Integer::power(long exponent) {
    Integer integer2 = exponent;
    return power(integer2);
}

Integer Integer::factorial() {
    Integer integer = *this;
    Integer result = 1;

    while (integer != 0) {
        result *= integer;
        integer--;
    }
    return result;
}

#endif
