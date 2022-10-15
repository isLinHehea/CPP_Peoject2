#include <iostream>
#include <string.h>
#include <map>
#include "cal.hpp"
using namespace std;

// 高精度乘法（大整型数，大浮点数）

// 两个整型数或者浮点数的乘法
string IntegerorFloatMulti(string first, string second)
{
    // 删去小数点并记录小数点的位置
    int firstBehindPoint = 0, secondBehindPoint = 0;
    for (int i = 0; i < first.length(); i++)
    {
        if (first[i] == '.')
        {
            firstBehindPoint = first.length() - i - 1;
            first = first.erase(i, 1);
            break;
        }
    }
    for (int i = 0; i < second.length(); i++)
    {
        if (second[i] == '.')
        {
            secondBehindPoint = second.length() - i - 1;
            second = second.erase(i, 1);
            break;
        }
    }
    // 乘法结束后小数点应该加在乘积的位置
    int theWholeBehindPoint = firstBehindPoint + secondBehindPoint;
    // 将string转化为char*指针类型
    const char *firstNum = first.c_str();
    const char *secondNum = second.c_str();
    bool firstNegative = false;
    bool secondNegative = false;
    int firstLength = first.length();
    int secondLength = second.length();
    // 判断两个数字的正负性
    if (*firstNum == '-')
    {
        firstNegative = true;
        firstLength--;
        firstNum++;
    }
    if (*secondNum == '-')
    {
        secondNegative = true;
        secondLength--;
        secondNum++;
    }
    // 两数乘积位数一定不大于两数长度
    int theWholeLength = firstLength + secondLength;
    int *result = new int[theWholeLength]{0};
    string resultStr;

    // Multi相乘
    for (int i = firstLength - 1; i >= 0; i--)
    {
        int k = firstLength - i - 1;
        for (int j = secondLength - 1; j >= 0; j--)
        {
            result[k++] += (firstNum[i] - '0') * (secondNum[j] - '0');
            // Carry进位
            if (result[k - 1] >= 10)
            {
                result[k] += result[k - 1] / 10;
                result[k - 1] %= 10;
            }
        }
    }
    // 负号的考虑
    if (firstNegative != secondNegative)
        resultStr += "-";
    // 判断并去掉乘积前面多余的0
    bool checkZero = false;
    for (int i = 0; i < theWholeLength; i++)
    {
        if (!checkZero)
        {
            if (result[theWholeLength - i - 1] != 0)
                checkZero = true;
        }
        if (checkZero)
            resultStr += to_string(result[theWholeLength - i - 1]);
    }
    // 加上小数点
    if (theWholeBehindPoint != 0)
    {
        int pointLoc = resultStr.length() - theWholeBehindPoint;
        while (pointLoc < 1)
        {
            resultStr = "0" + resultStr;
            pointLoc = resultStr.length() - theWholeBehindPoint;
        }
        resultStr = resultStr.insert(resultStr.length() - theWholeBehindPoint, ".");
    }
    return resultStr;
}
// 乘法
string mul(string n1, string n2)
{
    if (n1 == "0" || n2 == "0")
        return "0";
    string result = IntegerorFloatMulti(n1, n2);
    return result;
}
