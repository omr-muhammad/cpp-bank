#pragma once

#ifndef CLSLOG_IN_OUT_H
#define CLSLOG_IN_OUT_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "./clsScreen.h"
#include "./clsUser.h"
#include "./global.h"
#include "./clsMainScreen.h"
#include "./clsLoginRegister.h"

using namespace std;

class clsLogInOut : protected clsScreen
{
private:
  static bool _login(string username, string password)
  {
    clsUser *user = clsUser::find(username, password);

    if (user != nullptr)
    {
      currentUser = user;
      failedLoginAttempts = 0;
      return clsLoginRegister::writeNewLogs();
    }

    return false;
  }

public:
  static void loginScreen()
  {
    system("cls");
    _drawScreenHeader("\t  Login Screen");

    string username, password;

    do
    {
      cout << "Enter Username? ";
      cin >> username;

      cout << "Enter Password? ";
      cin >> password;

      if (_login(username, password))
        break;
      else
      {
        cout << "\n\nInvalid Username/Password!\n";
        failedLoginAttempts++;
        cout << "You have " << 3 - failedLoginAttempts << " attempts left.\n\n";

        if (failedLoginAttempts >= 3)
        {
          cout << "\n\nYou have been locked out of the system after 3 failed attempts.\n";
          return;
        }
      }
    } while (true);

    clsMainScreen::showMainMenu();
  }
};

#endif // CLSLOG_IN_OUT_H