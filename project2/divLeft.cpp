#include <iostream>
#include <string.h>
#include "cal.hpp"
using namespace std;

// 取余（除数为整型数，被除数为整形数）

string divLeft(string n1, string n2)
{
    bool n1IfNegative = false;
    if (n1[0] == '-')
    {
        n1IfNegative = true;
        n1.erase(0, 1);
    }
    if (n2[0] == '-')
        n2.erase(0, 1);
    string remainder;
    if (n2 == "0")
    {
        cout << "ERROR! Zero can not be divided. " << endl;
        exit(0);
    }
    if (n1 == "0")
        remainder = "0";
    int res = ifBigger(n1, n2);
    if (res < 0)
        remainder = n1;
    else if (res == 0)
        remainder = "0";
    else
    {
        string str = "";
        str.append(n1, 0, n2.length() - 1);
        for (int i = n2.length() - 1; i < n1.length(); i++)
        {
            str = str + n1[i];
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
                    str = addOrSub(str, product, '-');
                    break;
                }
            }
        }
        remainder = str;
    }
    if (n1IfNegative == true && remainder[0] != '0')
        remainder = "-" + remainder;
    return remainder;
}