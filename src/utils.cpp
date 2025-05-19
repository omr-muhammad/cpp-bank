#include "../include/utils.h"
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

int randomInRange(int from, int to)
{
  return from + (rand() % (to - from + 1));
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

string lowerString(string txt)
{
  for (size_t i = 0; i < txt.length(); i++)
  {
    txt[i] = tolower(txt[i]);
  }

  return txt;
}

vector<string> splitStr(const string &str, const string &delimiter)
{
  vector<string> result;
  size_t start = 0;                 // Start position of the current word
  size_t end = str.find(delimiter); // Find the first occurrence of the delimiter

  // Loop through the string to find all occurrences of the delimiter
  while (end != string::npos)
  {
    // Extract the substring from start to end (excluding the delimiter)
    result.push_back(str.substr(start, end - start));
    // Move the start position to the character after the delimiter
    start = end + delimiter.length();
    // Find the next occurrence of the delimiter
    end = str.find(delimiter, start);
  }

  // Add the last word (after the last delimiter)
  result.push_back(str.substr(start));

  return result;
}

string trimStr(string text, string dir)
{
  string toTrim = text;

  if (dir.empty() || dir == "l")
  {
    short firstCharPos = 0;
    while (toTrim[firstCharPos] == ' ')
    {
      firstCharPos++;
    }

    toTrim = toTrim.substr(firstCharPos, toTrim.length());
    if (dir == "l")
      return toTrim;
  }

  // If it didn't return from previous if so we need this to work regardless direction
  short lastCharPos = toTrim.length() - 1;
  while (toTrim[lastCharPos] == ' ')
  {
    lastCharPos--;
  }

  toTrim = toTrim.substr(0, lastCharPos + 1);
  return toTrim;
}