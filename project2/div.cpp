#include <iostream>
#include <string.h>
#include "cal.hpp"
using namespace std;

// 高精度除法（整型数，浮点数,大整型数，大浮点数）

// 删去小数点，补齐相差的位数
void toInt(string &n1, string &n2)
{
    int n1BehindPoint = 0, n2BehindPoint = 0;
    int point1Loc = n1.find('.');
    int point2Loc = n2.find('.');
    if (point1Loc >= 0 && point1Loc < n1.length() - 1)
        n1BehindPoint = n1.length() - point1Loc - 1;
    else
        n1BehindPoint = 0;
    if (point2Loc >= 0 && point2Loc < n1.length() - 1)
        n2BehindPoint = n2.length() - point2Loc - 1;
    else
        n2BehindPoint = 0;
    int deta = abs(n1BehindPoint - n2BehindPoint);
    // 删去小数点，补齐相差的位数
    if (n1BehindPoint != 0 && n1BehindPoint < n2BehindPoint)
    {
        n1.erase(point1Loc, 1);
        n2.erase(point2Loc, 1);
        for (int i = 1; i <= deta; i++)
            n1 = n1 + "0";
    }
    else if (n2BehindPoint != 0 && n1BehindPoint >= n2BehindPoint)
    {
        n1.erase(point1Loc, 1);
        n2.erase(point2Loc, 1);
        for (int i = 1; i <= deta; i++)
            n2 = n2 + "0";
    }
    else if (n1BehindPoint == 0 && n2BehindPoint != 0)
    {
        n2.erase(point2Loc, 1);
        for (int i = 1; i <= deta; i++)
            n1 = n1 + "0";
    }
    else if (n2BehindPoint == 0 && n1BehindPoint != 0)
    {
        n1.erase(point1Loc, 1);
        for (int i = 1; i <= deta; i++)
            n2 = n2 + "0";
    }
}

// 比较两个数字的大小（正数，整形数）
int ifBigger(string n1, string n2)
{
    // 若n1大于n2，返回值大于0；若n1小于于n2，返回值大于0；
    // 若n1等于n2，返回值等于0
    if (n1.length() > n2.length())
        return 1;
    else if (n1.length() < n2.length())
        return -1;
    else
        return n1.compare(n2);
}

// 除法
string div(string n1, string n2)
{
    if (n2 == "0")
    {
        cout << "ERROR! Zero can not be divided. " << endl;
        cout << "Zero can not be divided !" << endl;
        exit(0);
    }
    if (n1 == "0")
        return "0";
    // 判断正负
    bool n1IfNegative = false;
    bool n2IfNegative = false;
    if (n1[0] == '-')
    {
        n1IfNegative = true;
        n1.erase(0, 1);
    }
    if (n2[0] == '-')
    {
        n2IfNegative = true;
        n2.erase(0, 1);
    }
    // 删去小数点
    if ((n1.find('.') >= 0 && n1.find('.') <= n1.length() - 1) || (n2.find('.') >= 0 && n2.find('.') <= n2.length() - 1))
        toInt(n1, n2);
    // 删去数字开头多余的0
    n1.erase(0, n1.find_first_not_of('0'));
    n2.erase(0, n2.find_first_not_of('0'));
    // 除法运算
    string str = "";
    str.append(n1, 0, n2.length() - 1);
    // 控制保留位数
    int cnt = 0;
    int index = n2.length() - 1;
    string result;

    while (str != "0" || index <= n1.length() - 1)
    {
        if (index > n1.length() - 1)
        {
            // 若除不尽，默认保留20位小数
            if (cnt >= 21)
                break;
            // 补0
            str = str + "0";
            cnt++;
        }
        else
            str = str.append(1, n1[index]);
        str.erase(0, str.find_first_not_of('0'));
        if (str.empty())
            str = "0";
        for (char ch = '9'; ch >= '0'; ch--)
        {
            string product = "";
            product.append(1, ch);
            product = mul(product, n2);
            if (ifBigger(product, str) <= 0)
            {
                result.append(1, ch);
                str = addOrSub(str, product, '-');
                break;
            }
        }
        index++;
    }
    int L = result.length();
    // 借位情况
    if (cnt > 0)
        result.insert(L - cnt, ".");
    // 小数点在开头，例如.12
    if (result[0] == '.')
        result = "0" + result;
    // 小数点前是0，例如00.12
    if (result[result.find_first_not_of('0')] != '.')
        result.erase(0, result.find_first_not_of('0'));
    if (result.empty())
        result = "0";
    if (n1IfNegative != n2IfNegative)
        result = result.insert(0, "-");
    // 四舍五入
    if (ifFloat(result))
    {
        int digit = result.length() - result.find('.') - 1;
        if (digit == 21 && result[result.length() - 1] - '0' >= 5)
        {
            result = result.erase(result.length() - 1, 1);
            result = add(result, "0.00000000000000000001");
        }
    }

    return result;
}
