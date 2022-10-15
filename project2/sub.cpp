#include <iostream>
#include <string.h>
#include "cal.hpp"
#include <cstring>
using namespace std;

// 高精度减法（整型数，浮点数,大整型数，大浮点数）

// int*变string
string func(int *arr, int len)
{
    string str;
    for (int i = 0; i < len; i++)
        str += to_string(arr[i]);
    return str;
}

// string变int*
int *func(string str)
{
    int *arr = new int[str.length()];
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < str.length(); i++)
        arr[i] = str[i] - '0';
    return arr;
}

// 补码
string getComplement(string str, int len)
{
    int deta = len - str.length();
    string zero = "";
    zero = zero.append(deta, '0');
    str = zero + str;
    int *n = new int[len];
    for (int i = 0; i < len; i++)
        n[i] = 9;
    int *complement = new int[len];
    for (int i = 0; i < len; i++)
        complement[i] = 0;
    for (int i = 0; i < str.length(); i++)
        complement[len - str.length() + i] = n[len - str.length() + i] - (str[i] - '0');
    string comStr = func(complement, len);
    return add(comStr, "1");
}

// 数字开头补0
void addFrontZero(string &str, int len)
{
    int detaLength = len - str.length();
    string zero = "";
    zero = zero.append(detaLength, '0');
    str = zero + str;
}

// 大整型数减法
string integerSub(string n1, string n2)
{
    int n1Length = n1.length();
    int n2Length = n2.length();
    if (ifBigger(n1, n2) == 0)
        return "0";

    if (getBiggerNumber(n1, n2) == n1)
    {
        string complement = getComplement(n2, n1Length);
        string result;
        result = add(n1, complement);
        result = result.erase(0, 1);
        result.erase(0, result.find_first_not_of('0'));
        return result;
    }
    else
    {
        string complement1 = getComplement(n2, n2Length);
        string sum;
        sum = add(n1, complement1);
        string complement2 = getComplement(sum, sum.length());
        complement2.erase(0, complement2.find_first_not_of('0'));
        return complement2.insert(0, "-");
    }
}

// 大浮点数减法
string floatSub(string n1, string n2)
{
    int point1Loc = n1.find('.');
    int point2Loc = n2.find('.');
    string n1Left = n1.substr(0, point1Loc), n2Left = n2.substr(0, point2Loc);
    string n1Right = n1.substr(point1Loc + 1, n1.length());
    string n2Right = n2.substr(point2Loc + 1, n2.length());
    addZero(n1Right, n2Right);
    string rightMin = integerSub(n1Right, n2Right);
    if (rightMin[0] == '-' && n1Left != "0")
    {
        n1Right = "1" + n1Right;
        rightMin = integerSub(n1Right, n2Right);
        n1Left = sub(n1Left, "1");
    }
    string leftMin = integerSub(n1Left, n2Left);
    if (rightMin[0] == '-')
    {
        rightMin = rightMin.erase(0, 1);
        addFrontZero(rightMin, n2Right.length());
        if (!ifNegative(leftMin))
        {
            leftMin = "-" + leftMin;
        }
    }
    else
        addFrontZero(rightMin, n2Right.length());
    string result = leftMin + "." + rightMin;
    return result;
}

// 混合运算
string mixedSub(string n1, string n2)
{
    if (ifFloat(n2))
    {
        int point2Loc = n2.find('.');
        string n2Left = n2.substr(0, point2Loc);
        string n2Right = n2.substr(point2Loc + 1, n2.length());
        n1 = integerSub(n1, "1");
        int zeroLength = n2Right.length();
        string n1Right = "1";
        n1Right = n1Right.append(zeroLength, '0');
        string leftMin = integerSub(n1, n2Left);
        string rightMin = integerSub(n1Right, n2Right);
        int deta = n2Right.length() - rightMin.length();
        string zero = "";
        zero = zero.append(deta, '0');
        rightMin = zero + rightMin;
        string result = leftMin + "." + rightMin;
        return result;
    }
    else
    {
        int point1Loc = n1.find('.');
        string n1Left = n1.substr(0, point1Loc);
        string n1Right = n1.substr(point1Loc + 1, n1.length());
        string leftSum = integerSub(n1Left, n2);
        string result = leftSum + "." + n1Right;
        return result;
    }
}

// 减法
string sub(string n1, string n2)
{
    if (ifFloat(n1) && ifFloat(n2))
        return floatSub(n1, n2);
    else if (!ifFloat(n1) && !ifFloat(n2))
        return integerSub(n1, n2);
    else
        return mixedSub(n1, n2);
}