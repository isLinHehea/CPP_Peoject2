#include <iostream>
#include <string.h>
#include "cal.hpp"
#include <cstdlib>
using namespace std;

/*
实现的功能
1、加减乘除（浮点数，整形数，大浮点数，大整形数）
2、变量的输入
3、乘方（指数为整形数）
4、取余（除数为整型数，被除数为整形数）
*/

// 判断运算符号的优先级
int symLevel(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    }
    return 0;
}

// 数字栈符号栈，出栈计算并将结果存入数字栈
bool calculate(vector<string> &numbers, vector<char> &symbols, int level)
{
    char symbol = symbols.back();
    if (level <= symLevel(symbol))
    {
        string n1, n2, result;
        n2 = numbers.back();
        numbers.pop_back();
        n1 = numbers.back();
        result = Math(n1, n2, symbol);
        numbers.pop_back();
        symbols.pop_back();
        numbers.push_back(result);
        return true;
    }
    else
        return false;
}

// 计算器
string betterCalculator(string str)
{
    // 数字栈建立
    vector<string> numbers;
    // 符号栈建立
    vector<char> symbols;
    // 记录数字的临时string
    string number = "";
    int index = 0;
    while (index < str.length())
    {
        // 第一个是数字且为负数
        if (index == 0 && str[index] == '-')
        {
            number.append("-");
            index++;
        }
        // 左括号且括号右边为负数
        else if (str[index] == '(' && str[index + 1] == '-')
        {
            symbols.push_back(str[index++]);
            number.append("-");
            index++;
            while ((str[index] >= '0' && str[index] <= '9') || str[index] == '.')
            {
                if (str[index] == '.')
                {
                    number.append(".");
                    index++;
                }
                else
                    number.append(to_string(str[index++] - '0'));
            }
            numbers.push_back(number);
            number = "";
            if (str[index] == ')')
            {
                symbols.pop_back();
                index++;
            }
        }
        // 数字
        else if ((str[index] >= '0' && str[index] <= '9') || str[index] == '.')
        {
            while ((str[index] >= '0' && str[index] <= '9') || str[index] == '.')
            {
                if (str[index] == '.')
                {
                    number.append(".");
                    index++;
                }
                else
                    number.append(to_string(str[index++] - '0'));
            }
            numbers.push_back(number);
            number = "";
        }
        // 运算符号
        else
        {
            if (symbols.empty() || str[index] == '(')
                symbols.push_back(str[index++]);
            // 加减
            else if (symLevel(str[index]) == 1)
            {
                // 栈顶为左括号
                if (symbols.back() == '(')
                    symbols.push_back(str[index++]);
                // 栈顶为加减号或乘除号出栈运算
                else if (symLevel(symbols.back()) == 1 || symLevel(symbols.back()) == 2 || symLevel(symbols.back()) == 3)
                {
                    while (true)
                    {
                        bool ifContinue = calculate(numbers, symbols, 1);
                        if (!ifContinue)
                            break;
                    }
                    symbols.push_back(str[index++]);
                }
            }
            // 乘除或取余
            else if (symLevel(str[index]) == 2)
            {
                // 栈顶为左括号
                if (symbols.back() == '(')
                    symbols.push_back(str[index++]);
                else if (symLevel(symbols.back()) == 1)
                    symbols.push_back(str[index++]);
                else if (symLevel(symbols.back()) == 2 || symLevel(symbols.back()) == 3)
                {
                    while (true)
                    {
                        bool ifContinue = calculate(numbers, symbols, 2);
                        if (!ifContinue)
                            break;
                    }
                    symbols.push_back(str[index++]);
                }
            }
            // 乘方
            else if (symLevel(str[index]) == 3)
            {
                // 栈顶为左括号
                if (symbols.back() == '(')
                    symbols.push_back(str[index++]);
                else if (symLevel(symbols.back()) == 1 || symLevel(symbols.back()) == 2)
                    symbols.push_back(str[index++]);
                else if (symLevel(symbols.back()) == 3)
                {
                    while (true)
                    {
                        bool ifContinue = calculate(numbers, symbols, 3);
                        if (!ifContinue)
                            break;
                    }
                    symbols.push_back(str[index++]);
                }
            }
            else if (str[index] == ')')
            {
                while (symbols.back() != '(')
                    calculate(numbers, symbols, 0);
                symbols.pop_back();
                index++;
            }
        }
    }
    while (symbols.size() >= 1 && numbers.size() >= 2)
        calculate(numbers, symbols, 0);
    symbols.push_back(str[index++]);
    return numbers.back();
}



// 变量结构体
struct Variables
{
    char variName;
    string VariValue;
};

// 替换变量
void toExpress(Variables variables[], string &str, int variNum)
{
    for (int i = 0; i < variNum; i++)
    {
        int len = str.length();
        int index = 0;
        while (index <= len)
        {
            char symbol = variables[i].variName;
            string number = variables[i].VariValue;
            if (str[index] == symbol)
            {
                str = str.erase(index, 1);
                str = str.insert(index, number);
                index += number.length();
            }
            else
                index++;
        }
    }
}

// 检查计算器关闭语句
void ifClosed(string str)
{
    if (str == "closed")
    {
        cout << "The calculator ends!" << endl;
        exit(0);
    }
}

// 检测待计算表达式的合理性
bool ifValid(string str)
{
    string theWholeChar = "+-*/^%0123456789.()";
    for (int i = 0; i < str.length(); i++)
    {
        if (theWholeChar.find(str[i]) == -1)
            return false;
    }
    return true;
}

// 检测变量数量的合理性
bool ifNumValid(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] - '0' > 9 || str[i] - '0' < 0)
            return false;
    }
    return true;
}

// 检测变量的合理性
bool ifVariValid(string str)
{
    string theWholeChar = "+-*/^%0123456789.";
    string theWholeNumChar = "0123456789.";
    if (theWholeChar.find(str[0]) != -1 || str[1] != '=')
        return false;
    for (int i = 2; i < str.length(); i++)
    {
        if (theWholeNumChar.find(str[i]) == -1)
            return false;
    }
    return true;
}

// 判断变量是否存在
bool ifVariExist(Variables variables[], char symbol, int len)
{
    for (int i = 0; i < len; i++)
    {
        char symbolExist = variables[i].variName;
        if (symbolExist == symbol)
            return true;
    }
    return false;
}

// 删去数字开头的0
void deleteZero(string &str)
{
    int notZeroLoc = str.find_first_not_of('0');
    if (notZeroLoc != -1)
        str = str.substr(notZeroLoc, str.length());
}

// Main函数
int main()
{
    cout << "The calculator starts!" << endl;
    // 选择输入表达式的类型（直接输入或定义变量）
    cout << "Please select the form of the expression to be calculated:" << endl;
    cout << "Direct input / Variables defined(input di/vd)." << endl;
    string inputForm;
    getline(cin, inputForm);
    ifClosed(inputForm);
    // 检测类型的合理性
    while (true)
    {
        if (inputForm == "di" || inputForm == "vd")
            break;
        else
        {
            cout << "Error! Wrong form input." << endl;
            cout << "Please input again:" << endl;
        }
        getline(cin, inputForm);
        ifClosed(inputForm);
    }
    // 直接输入
    if (inputForm == "di")
    {
        // 多次使用
        while (true)
        {
            cout << "Please input the expression to be calculated:" << endl;
            string str;
            getline(cin, str);
            ifClosed(str);
            // 检测待计算的表达式的合理性
            while (true)
            {
                if (ifValid(str))
                {
                    // 计算
                    string result = betterCalculator(str);
                    cout << result << endl;
                    break;
                }
                else
                {
                    cout << "Error! Wrong expression input." << endl;
                    cout << "Please input again:" << endl;
                }
                getline(cin, str);
                ifClosed(str);
            }
        }
    }
    // 定义变量
    else if (inputForm == "vd")
    {
        // 多次使用
        while (true)
        {
            cout << "Please input the number of variables:" << endl;
            string variNumStr;
            getline(cin, variNumStr);
            ifClosed(variNumStr);
            // 检测输入的定义变量个数的合理性
            while (true)
            {
                if (ifNumValid(variNumStr))
                    break;
                else
                {
                    cout << "Error! Wrong number input." << endl;
                    cout << "Please input again:" << endl;
                }
                getline(cin, variNumStr);
                ifClosed(variNumStr);
            }
            int variNum = 0;
            deleteZero(variNumStr);
            variNum = atoi(variNumStr.c_str());
            Variables variables[variNum];
            cout << "Please input " + variNumStr + " variables:" << endl;
            for (int i = 0; i < variNum; i++)
            {
                string str;
                getline(cin, str);
                ifClosed(str);
                // 检测定义的变量的合理性
                while (true)
                {
                    if (ifVariValid(str))
                        break;
                    else
                    {
                        cout << "Error! Wrong variable input." << endl;
                        cout << "Please input again:" << endl;
                    }
                    getline(cin, str);
                    ifClosed(str);
                }
                // 判断变量是否存在
                if (!ifVariExist(variables, str[0], i))
                {
                    variables[i].variName = str[0];
                    string value = str.substr(2, str.length());
                    variables[i].VariValue = value;
                }
                else
                {
                    cout << "Error! The variable already exists." << endl;
                    cout << "Please input again:" << endl;
                    i--;
                }
            }
            cout << "Please input the expression to be calculated:" << endl;
            string str;
            getline(cin, str);
            ifClosed(str);
            // 转化为没有变量的表达式
            toExpress(variables, str, variNum);
            string result = betterCalculator(str);
            cout << result << endl;
        }
    }
    return 0;
}

// for debug
// int main()
// {
//     cout << "The calculator starts!  " << endl;
//     cout << "Please enter the expression to be calculated:  " << endl;
//     string str = "212.545000002-0.345242";
//     string result = betterCalculator(str);
//     cout << result << endl;
//     return 0;
// }
// int main()
// {
//     string a = "12";
//     string b = "3.9977";
//     string c = "12";
//     string d = "1";
//     cout << sub(c, d) << endl;
//     cout << sub(a, b) << endl;
//     return 0;
// }