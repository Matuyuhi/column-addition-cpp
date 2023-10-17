//
// Created by matuyuhi on 2023/10/16.
//

#ifndef WORK01_EVALUATOR_H
#define WORK01_EVALUATOR_H

#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

using namespace std;

/// 最大桁数
static const int MAX_DIGITS_DEFAULT = 50;

/// BigIntクラス
/// 50桁の整数を扱う
/// 50桁を超える場合は上位の桁が切り捨てられる
/// + or -演算子を含む場合は-1とする
class BigInt {
private:
    // constにしてないので扱い注意
    int maxDigits;
    char *digits;

public:
    BigInt();

    explicit BigInt(const char *str);

    BigInt(const BigInt &other);

    ~BigInt();

    // +演算子のオーバーロード
    BigInt operator+(const BigInt &other) const;

    // -演算子のオーバーロード
    BigInt operator-(const BigInt &other) const;

    [[nodiscard]] string toStr() const;

    [[nodiscard]] int count() const;

    [[nodiscard]] BigInt absolute() const;

    friend std::ostream &operator<<(std::ostream &os, const BigInt &bi);

    bool operator<(const BigInt &other) const;

    BigInt &operator=(const BigInt &other);

    bool isNegative;
};

#endif //WORK01_EVALUATOR_H
