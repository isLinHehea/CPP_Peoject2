#include <iostream>
#include <string.h>
#include "cal.hpp"
#include <cstring>
using namespace std;

// 高精度加法（整型数，浮点数,大整型数，大浮点数）

// 判断是否是浮点数
bool ifFloat(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '.')
            return true;
    }
    return false;
}

// 得到更大的数字
string getBiggerNumber(string n1, string n2)
{
    int n1Length = n1.length();
    int n2Length = n2.length();
    if (n1Length > n2Length)
        return n1;
    else if (n1Length < n2Length)
        return n2;
    else
    {
        bool bigger = true;
        for (int i = 0; i < n1Length; i++)
        {

            int m1 = n1[i] - '0';
            int m2 = n2[i] - '0';
            if (m1 < m2)
            {
                bigger = false;
                break;
            }
            else if (m1 == m2)
                continue;
            else
                break;
        }
        if (bigger)
            return n1;
        else
            return n2;
    }
}

// 得到更小的数字
string getSmallerNumber(string n1, string n2)
{
    int n1Length = n1.length();
    int n2Length = n2.length();
    if (n1Length > n2Length)
        return n2;
    else if (n1Length < n2Length)
        return n1;
    else
    {
        bool bigger = true;
        for (int i = 0; i < n1Length; i++)
        {

            int m1 = n1[i] - '0';
            int m2 = n2[i] - '0';
            if (m1 < m2)
            {
                bigger = false;
                break;
            }
            else if (m1 == m2)
                continue;
            else
                break;
        }
        if (bigger)
            return n2;
        else
            return n1;
    }
}

// 大整型数相加
string integerAdd(string n1, string n2)
{
    string n1Temp = n1;
    string n2Temp = n2;
    n1 = getSmallerNumber(n1Temp, n2Temp);
    n2 = getBiggerNumber(n1Temp, n2Temp);
    int n1Length = n1.length();
    int n2Length = n2.length();
    int ans[n2Length + 1];
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < n1Length; i++)
    {
        ans[i] += (n1[n1Length - i - 1] - '0') + (n2[n2Length - i - 1] - '0');
        if (ans[i] >= 10)
        {
            ans[i] -= 10;
            ans[i + 1]++;
        }
    }
    for (int i = n1Length; i < n2Length; i++)
    {
        ans[i] += n2[n2Length - i - 1] - '0';
        if (ans[i] >= 10)
        {
            ans[i] -= 10;
            ans[i + 1]++;
        }
    }
    string result;
    for (int i = 0; i < n2Length + 1; i++)
        result.append(to_string(ans[n2Length - i]));
    if (result[0] == '0')
        result = result.erase(0, 1);
    return result;
}

// 补0
void addZero(string &n1, string &n2)
{
    int detaLength = n1.length() - n2.length();
    if (detaLength > 0)
        n2 = n2.append(detaLength, '0');
    else if (detaLength < 0)
        n1 = n1.append(-detaLength, '0');
}

// 大浮点数相加
string floatAdd(string n1, string n2)
{
    int point1Loc = n1.find('.');
    int point2Loc = n2.find('.');
    string n1Left = n1.substr(0, point1Loc), n2Left = n2.substr(0, point2Loc);
    string n1Right = n1.substr(point1Loc + 1, n1.length());
    string n2Right = n2.substr(point2Loc + 1, n2.length());
    addZero(n1Right, n2Right);
    string leftSum = integerAdd(n1Left, n2Left);
    string rightSum = integerAdd(n1Right, n2Right);
    if (rightSum.length() > n1Right.length() && rightSum.length() > n2Right.length())
    {
        rightSum = rightSum.erase(0, 1);
        leftSum = integerAdd(leftSum, "1");
    }
    string result = leftSum + "." + rightSum;
    return result;
}

// 混合运算
string mixedAdd(string n1, string n2)
{
    int point2Loc = n2.find('.');
    string n2Left = n2.substr(0, point2Loc);
    string n2Right = n2.substr(point2Loc + 1, n2.length());
    string leftSum = integerAdd(n1, n2Left);
    string result = leftSum + "." + n2Right;
    return result;
}

// 加法
string add(string n1, string n2)
{
    if (ifFloat(n1) && ifFloat(n2))
        return floatAdd(n1, n2);
    else if (!ifFloat(n1) && !ifFloat(n2))
        return integerAdd(n1, n2);
    else if (ifFloat(n1))
        return mixedAdd(n2, n1);
    else
        return mixedAdd(n1, n2);
}