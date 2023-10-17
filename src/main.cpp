#include <iostream>
#include <string>
#include "../header/Evaluator.h"


int main() {
    Evaluator evaluator;
    std::string num1, num2;

    std::cout << "初期値> ";
    std::cin >> num1;
    if (num1 == "0") {
        cout << "終了します" << endl;
        return 0;
    }

    while (true) {

        std::cout << "入力> ";
        std::cin >> num2;

        if (num2 == "0") {
            cout << "終了します" << endl;
            break;
        }

        optDouble out = evaluator.evaluate(num1, num2);
        if(!out.has_value()) {
            cout << "入力が不正です" << endl;
            continue;
        }
        num1 = to_string(out.value());
    }

    return 0;
}
