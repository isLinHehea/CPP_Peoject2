#include <iostream>
#include <vector>
#include <string.h>
#include <cstdlib>
using namespace std;

string Math(string n1, string n2, char symbol);

string addOrSub(string n1, string n2, char symbol);
string add(string n1, string n2);
string sub(string n1, string n2);
string mul(string n1, string n2);
string div(string n1, string n2);
string pow(string n1, string n2);
string divLeft(string n1, string n2);


string getBiggerNumber(string n1, string n2);
bool ifFloat(string str);
void addZero(string &n1, string &n2);
int ifBigger(string n1, string n2);
bool ifNegative(string str);