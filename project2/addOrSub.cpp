#include <iostream>
#include <string.h>
#include "cal.hpp"
#include <cstring>
using namespace std;

// 判断是否是负数
bool ifNegative(string str)
{
    if (str[0] == '-')
        return true;
    else
        return false;
}

// 负数变正数
string negToPos(string str)
{
    return str.erase(0, 1);
}

// 正数变负数
string posToNeg(string str)
{
    return str.insert(0, "-");
}

// 加或减
string addOrSub(string n1, string n2, char symbol)
{
    if (n1 == "0" && n2 == "0")
        return "0";
    else if (n1 == "0")
    {
        if (symbol == '+')
            return n2;
        else
            return n2.erase(0, 1);
    }
    else if (n2 == "0")
        return n1;
    if (!ifNegative(n1) && !ifNegative(n2))
    {
        if (symbol == '+')
            return add(n1, n2);
        else
            return sub(n1, n2);
    }
    else if (ifNegative(n1) && ifNegative(n2))
    {
        n1 = negToPos(n1);
        n2 = negToPos(n2);
        string result;
        if (symbol == '+')
            result = add(n1, n2);
        else
            result = sub(n1, n2);
        return posToNeg(result);
    }
    else if (!ifNegative(n1) && ifNegative(n2))
    {
        n2 = negToPos(n2);
        if (symbol == '+')
            return sub(n1, n2);
        else
            return add(n1, n2);
    }
    else
    {
        n1 = negToPos(n1);
        if (symbol == '+')
            return sub(n2, n1);
        else
        {
            string result;
            result = add(n1, n2);
            return posToNeg(result);
        }
    }
}