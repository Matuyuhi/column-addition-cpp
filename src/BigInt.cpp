//
// Created by matuyuhi on 2023/10/16.
//
#include "../header/BigInt.h"

#pragma region Constructor

/// --- constructor ---
BigInt::BigInt() :
        isNegative(false), maxDigits(MAX_DIGITS_DEFAULT) {
    // +1はnull文字の分
    digits = new char[maxDigits + 1];
    memset(digits, '0', maxDigits);
    digits[maxDigits] = '\0';
}

/// copy constructor
/// @param other コピー元
BigInt::BigInt(const BigInt &other) :
        isNegative(other.isNegative), maxDigits(other.maxDigits) {
    digits = new char[maxDigits + 1];
    memcpy(digits, other.digits, maxDigits + 1);
}

/// constructor
/// 文字が含まれる場合は例外を投げる
/// @param str 数字限定の文字列
BigInt::BigInt(const char *str) : maxDigits(MAX_DIGITS_DEFAULT) {
    int len = int(strlen(str));
    int startIdx = 0;

    if (str[0] == '-') {
        isNegative = true;
        startIdx = 1;  // ネガティブの符号をスキップ
        len--;  // 符号を考慮しないため、長さを1減少させる
    } else if (str[0] == '+') {
        // 同様の処理
        startIdx = 1;
        len--;
    } else {
        isNegative = false;
    }

    for (int i = startIdx; i < startIdx + len; i++) {
        // 0から9の間の文字でない場合
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("Provided string contains non-digit characters.");
        }
    }

    digits = new char[maxDigits + 1];
    memset(digits, '0', maxDigits);
    digits[maxDigits] = '\0';

    for (int i = 0; i < min(len, maxDigits); i++) {
        digits[maxDigits - i - 1] = str[startIdx + len - i - 1];
    }
}

BigInt::~BigInt() {
    delete[] digits;
}
/// --- constructor ---
#pragma endregion

#pragma region Operator
/// --- operator ---

/// overload operator =
BigInt &BigInt::operator=(const BigInt &other) {
    if (this != &other) {
        delete[] digits;

        isNegative = other.isNegative;
        maxDigits = other.maxDigits;
        digits = new char[maxDigits + 1];
        memcpy(digits, other.digits, maxDigits + 1);
    }
    return *this;
}

/// overload operator +
BigInt BigInt::operator+(const BigInt &other) const {
    BigInt result;
    if (!isNegative && !other.isNegative) {
        int carry = 0;
        for (int i = maxDigits - 1; i >= 0; i--) {
            int sum = (digits[i] - '0') + (other.digits[i] - '0') + carry;
            result.digits[i] = (sum % 10) + '0'; // NOLINT(*-narrowing-conversions)
            carry = sum / 10;
        }
    } else if (isNegative && other.isNegative) {
        result = this->absolute() + other.absolute();
        result.isNegative = true;
    } else if (isNegative && !other.isNegative) {     // - & +
        BigInt posThis = *this;
        posThis.isNegative = false;
        if (posThis < other) {
            return other - posThis;
        } else {
            BigInt resultA = posThis - other;
            resultA.isNegative = true;
            return resultA;
        }
    } else {                                            // + & -
        BigInt posOther = other;
        posOther.isNegative = false;
        if (*this < posOther) {
            BigInt resultA = posOther - *this;
            resultA.isNegative = true;
            return resultA;
        } else {
            return *this - posOther;
        }
    }

    return result;
}

/// overload operator -
BigInt BigInt::operator-(const BigInt &other) const {
    if (*this < other) {
        BigInt result = other.absolute() - this->absolute();
        result.isNegative = !other.isNegative;
        return result;
    }

    BigInt result;
    BigInt a = this->absolute();
    BigInt b = other.absolute();
    int borrow = 0;
    for (int i = maxDigits - 1; i >= 0; i--) {
        int diff = (a.digits[i] - '0') - (b.digits[i] - '0') - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = char(diff + '0');
    }
    return result;
}

/// overload operator <<
std::ostream &operator<<(ostream &os, const BigInt &bi) {
    int leadingIdx = 0;

    // 0でない最初の桁を見つける
    while (leadingIdx < MAX_DIGITS_DEFAULT - 1 && bi.digits[leadingIdx] == '0') {
        leadingIdx++;
    }

    // 負の数であれば、マイナス記号を出力
    if (bi.isNegative) {
        os << "-";
    }

    // 数字を出力
    os << (bi.digits + leadingIdx);

    return os;
}

/// overload operator <
bool BigInt::operator<(const BigInt &other) const {
    // 単なる正負で比較
    if (isNegative && !other.isNegative) {
        // thisの方が小さい
        return true;
    }
    if (!isNegative && other.isNegative) {
        // otherの方が大きい
        return false;
    }

    // 桁ごとに比較
    for (int i = 0; i < maxDigits; ++i) {
        if (digits[i] - '0' < other.digits[i] - '0') {
            // otherの方が大きい
            return !isNegative;
        }
        if (digits[i] - '0' > other.digits[i] - '0') {
            // thisの方が大きい
            return isNegative;
        }
    }
    return false;
}
/// --- operator ---
#pragma endregion

/// --- method ---
BigInt BigInt::absolute() const {
    BigInt result = *this;
    result.isNegative = false;

    for (int i = 0; i < maxDigits; i++) {
        if (result.digits[i] == '-') {
            result.digits[i] = '0';
        }
    }
    return result;
}

string BigInt::toStr() const {
    int leadingIdx = 0;
    while (leadingIdx < maxDigits - 1 && (digits[leadingIdx] == '0' || digits[leadingIdx] == '-')) {
        leadingIdx++;
    }
    if (isNegative && leadingIdx < maxDigits - 1) {
        return "-" + std::string(digits + leadingIdx);
    }
    return {digits + leadingIdx};
}

int BigInt::count() const {
    int count = 0;
    for (int i = 0; i < maxDigits; i++) {
        if (digits[i] != '0') {
            count = maxDigits - i;
            break;
        }
    }
    return count;
}
/// --- method ---