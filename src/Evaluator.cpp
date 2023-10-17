//
// Created by matuyuhi on 2023/10/16.
//
#include "../header/Evaluator.h"

Evaluator::Evaluator() {
    functions["sqrt"] = [](double arg) {
        return sqrt(arg);
    };
    functions["sin"] = [](double arg) {
        return sin(arg);
    };
    functions["cos"] = [](double arg) {
        return cos(arg);
    };
    functions["tan"] = [](double arg) {
        return tan(arg);
    };

    regexFunctions = {
            {regex(R"(sqrt\((.+?)\))"), "sqrt"},
            {regex(R"(sin\((.+?)\))"), "sin"},
            {regex(R"(cos\((.+?)\))"), "cos"},
            {regex(R"(tan\((.+?)\))"), "tan"}
    };
}


double Evaluator::evaluateExpression(const string& expr) {
    smatch match;

    // 先に関数評価を行います
    for (const auto& [r, functionName] : regexFunctions) {
        if (regex_search(expr, match, r)) {
            double argValue = evaluateExpression(match[1].str());
            double value = functions.at(functionName)(argValue);
            return value;
        }
    }

    // +
    regex simpleAddition(R"(([\d\.]+)\+([\d\.]+))");
    if (regex_search(expr, match, simpleAddition)) {
        double val1 = evaluateExpression(match[1].str());
        double val2 = evaluateExpression(match[2].str());
        return val1 + val2;
    }

    // -
    regex simpleSubtraction(R"(([\d\.]+)\-([\d\.]+))");
    if (regex_search(expr, match, simpleSubtraction)) {
        double val1 = evaluateExpression(match[1].str());
        double val2 = evaluateExpression(match[2].str());
        return val1 - val2;
    }

    // x
    regex simpleMultiplication(R"(([\d\.]+)\*([\d\.]+))");
    if (regex_search(expr, match, simpleMultiplication)) {
        double val1 = evaluateExpression(match[1].str());
        double val2 = evaluateExpression(match[2].str());
        return val1 * val2;
    }

    // ÷
    regex simpleDivision(R"(([\d\.]+)\/([\d\.]+))");
    if (regex_search(expr, match, simpleDivision)) {
        double val1 = evaluateExpression(match[1].str());
        double val2 = evaluateExpression(match[2].str());
        return val1 / val2;
    }

    return stod(expr);
}

std::tuple<std::string, size_t, size_t> extractNestedFunction(const std::string& input, const std::string& funcName) {
    std::string prefix = funcName + "(";
    size_t pos = input.find(prefix);

    if (pos == std::string::npos) {
        return {"", std::string::npos, std::string::npos};
    }

    int depth = 0;
    size_t startPos = pos + prefix.size();
    for (size_t i = startPos; i < input.size(); i++) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth == 0) {
                return {input.substr(startPos, i - startPos), pos, i + 1};
            }
            depth--;
        }
    }

    return {"", std::string::npos, std::string::npos};
}

double Evaluator::evaluatorInput(const std::string &input) {
    string currentInput = input;

    bool replaced = true;
    // 関数を含む式を評価する
    while (replaced) {
        replaced = false;
        for (const auto& [r, functionName] : regexFunctions) {
            auto [nestedFunction, startPos, endPos] = extractNestedFunction(currentInput, functionName);
            if (!nestedFunction.empty()) {
                double argValue = evaluatorInput(nestedFunction);
                double value = functions.at(functionName)(argValue);
                string replacement = std::format("{:.4f}", value);
                currentInput = currentInput.substr(0, startPos) + replacement + currentInput.substr(endPos);
                replaced = true;
                break;
            }
        }
    }

    // 括弧に含まれる加減乗除を評価する
    return evaluateExpression(currentInput);
}

int Evaluator::getMaxWidth(double n1, double n2, double r) {
    // length()のint代入のwarningを回避する
    int w1 = (n1 == static_cast<int>(n1)) ? static_cast<int>(to_string(static_cast<int>(n1)).length()) : static_cast<int>(to_string(n1).length());
    int w2 = (n2 == static_cast<int>(n2)) ? static_cast<int>(to_string(static_cast<int>(n2)).length()) : static_cast<int>(to_string(n2).length());
    int wr = (r == static_cast<int>(r)) ? static_cast<int>(to_string(static_cast<int>(r)).length()) : static_cast<int>(to_string(r).length());
    return max({w1, w2, wr});
}

bool Evaluator::hasAnyDecimal(double n1, double n2, double r) {
    return (n1 != static_cast<int>(n1)) || (n2 != static_cast<int>(n2)) || (r != static_cast<int>(r));
}

void Evaluator::formatValue(double val, int w, bool forceDecimal) {
    if (forceDecimal || val != static_cast<int>(val)) {
        cout << std::format("{:>{}.4f}\n", val, w);
    } else {
        cout << std::format("{:>{}.0f}\n", val, w);
    }
}

double Evaluator::printAndOutAddition(double num1, double num2) {
    double result = num1 + num2;
    int width = getMaxWidth(num1, num2, result);
    bool anyDecimal = hasAnyDecimal(num1, num2, result);

    formatValue(num1, width + 2, anyDecimal);
    cout << "+";
    formatValue(num2, width + 1, anyDecimal);
    cout << string(width + 2, '-') << endl;
    formatValue(result, width + 2, anyDecimal);

    return result;
}

double Evaluator::printAndOutSubtraction(double num1, double num2) {
    double result = num1 - num2;
    int width = getMaxWidth(num1, num2, result);
    bool anyDecimal = hasAnyDecimal(num1, num2, result);

    formatValue(num1, width + 2, anyDecimal);
    cout << "-";
    formatValue(num2, width + 1, anyDecimal);
    cout << string(width + 2, '-') << endl;
    formatValue(result, width + 2, anyDecimal);

    return result;
}


optDouble Evaluator::evaluate(const string& input1, const string& input2) {
    try {
        double num1 = evaluatorInput(input1);
        double num2 = evaluatorInput(input2);

        if (num2 < 0) {
            return printAndOutSubtraction(num1, -num2);
        } else {
            return printAndOutAddition(num1, num2);
        }
    } catch (const std::exception& e) {
        return nullopt;
    }
}