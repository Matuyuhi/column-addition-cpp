//
// Created by matuyuhi on 2023/10/16.
//

#ifndef WORK01_EVALUATOR_H
#define WORK01_EVALUATOR_H

#include <optional>
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <iomanip>
#include <functional>
#include <regex>
#include <cmath>
#include <format>
#include <sstream>


using namespace std;
using optDouble = optional<double>;

class Evaluator {
private:
    map<string, function<double(double)>> functions;
    vector<pair<regex, string>> regexFunctions;

    static double printAndOutAddition(double num1, double num2) ;
    static double printAndOutSubtraction(double num1, double num2) ;
    double evaluatorInput(const std::string &input);
    static int getMaxWidth(double n1, double n2, double r);
    static bool hasAnyDecimal(double n1, double n2, double r);
    static void formatValue(double val, int w, bool forceDecimal = false);

    /// <summary>
    /// 文字列内の+-x/演算子を解釈して結果を返す
    /// </summary>
    /// <param name="expr">演算子を含む文字列(見つからなければそのまま返す)</param>
    /// <returns>計算結果</returns>
    double evaluateExpression(const string& expr);
public:
    Evaluator();
    optDouble evaluate(const std::string& input1, const std::string& input2);
};

#endif //WORK01_EVALUATOR_H
