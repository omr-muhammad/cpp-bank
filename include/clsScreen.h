#pragma once

#ifndef CLSSCREEN_H
#define CLSSCREEN_H

#include <iostream>
#include <ctime>

#include "./global.h"

using namespace std;

class clsScreen
{
protected:
  static void _drawScreenHeader(string title, string subTitle = "")
  {
    system("cls");

    string username = currentUser == nullptr ? "" : currentUser->getUsername();
    time_t t = time(0);
    // char* dt = ctime(&t); eg. "Wed May 17 17:15:00 2023"
    tm *now = localtime(&t);

    cout << "\t\t\t\t\t______________________________________";
    cout << "\n\n\t\t\t\t\t  " << title;
    if (subTitle != "")
    {
      cout << "\n\t\t\t\t\t  " << subTitle;
    }
    cout << "\n\t\t\t\t\t______________________________________\n";
    cout << "\t\t\t\t\tUser: " << username << endl;
    cout << "\t\t\t\t\tDate: " << now->tm_mday << '/' << (now->tm_mon + 1) << '/' << (now->tm_year + 1900) << "\n\n";
  }
};

#endif // CLSSCREEN_H