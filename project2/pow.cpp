#include <iostream>
#include <string.h>
#include "cal.hpp"
using namespace std;

// 乘方（指数为整型数）

string pow(string n1, string n2)
{
    if (n2 == "0" && n1 == "0")
    {
        cout << "Error! 0^0 doesn't exist." << endl;
        exit(0);
    }
    else if (n2 == "0")
        return "1";
    else if (n1 == "0")
        return "0";
    else
    {
        bool n2IfNegative = false;
        if (n2[0] == '-')
        {
            n2IfNegative = true;
            n2.erase(0, 1);
        }
        int exponent = atoi(n2.c_str());
        string result = n1;
        for (int i = 0; i < exponent - 1; i++)
            result = mul(result, n1);
        if (n2IfNegative)
            result = div("1", result);
        return result;
    }
}
