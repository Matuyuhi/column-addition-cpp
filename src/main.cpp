#include <iostream>
#include <format>
#include <string>
#include "../header/BigInt.h"

using namespace std;

/// 縦に整列したスタイルで出力する
/// @param a 左辺
/// @param b 右辺
/// @param result 結果
/// @return void
void printArithmeticStyle(const BigInt &a, const BigInt &b, const BigInt &result) {
    int count = max(a.count(), max(b.count(), result.count()));

    cout << format("{:>{}}", a.toStr(), count + 2) << endl;
    if (b.isNegative) {
        cout << "- " << format("{:>{}}", b.absolute().toStr(), count) << endl;
    } else {
        cout << "+ " << format("{:>{}}", b.toStr(), count) << endl;
    }
    cout << string(count + 2, '-') << endl;
    cout << format("{:>{}}", result.toStr(), count + 2) << endl;
}

int main() {
    string num1, num2;

    cout << "終了する場合は0を入力してください" << endl;

    while (true) {
        cout << "初期値> ";
        cin >> num1;
        if (num1 == "0") {
            cout << "終了します" << endl;
            return 0;
        }
        try {
            BigInt a(num1.c_str());
            break;
        } catch (invalid_argument &e) {
            cout << "不正な入力です" << endl;
            continue;
        }
    }


    while (true) {

        cout << "入力> ";
        cin >> num2;

        if (num2 == "0") {
            cout << "終了します" << endl;
            break;
        }
        BigInt a;
        BigInt b;
        try {
            a = BigInt(num1.c_str());
            b = BigInt(num2.c_str());
        } catch (invalid_argument &e) {
            cout << "不正な入力です" << endl;
            continue;
        }


        BigInt out = a + b;
        printArithmeticStyle(a, b, out);
        num1 = out.toStr();
    }

    cout << "今までの合計は " << num1 << " でした" << endl;

    return 0;
}
