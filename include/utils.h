#include <string>
#include <vector>

#ifndef UTILS_H
#define UTILS_H

using namespace std;

int randomInRange(int from, int to);
void swap(int *a, int *b);
string lowerString(string txt);
vector<string> splitStr(const string &str, const string &delimiter);
string trimStr(string text, string dir = "");

#endif