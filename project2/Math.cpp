#include <iostream>
#include <string.h>
#include "cal.hpp"
using namespace std;

// 计算逻辑
string Math(string n1, string n2, char symbol)
{
    string ans = "";
    switch (symbol)
    {
    case '+':
    case '-':
    {
        ans = addOrSub(n1, n2, symbol);
        break;
    }
    case '*':
    {
        ans = mul(n1, n2);
        break;
    }
    case '/':
    {
        ans = div(n1, n2);
        break;
    }
    case '^':
    {
        ans = pow(n1, n2);
        break;
    }
    case '%':
    {
        ans = divLeft(n1, n2);
        break;
    }
    default:
        break;
    }
    return ans;
}