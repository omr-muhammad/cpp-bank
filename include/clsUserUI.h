#pragma once

#ifndef CLSUSERUI_H
#define CLSUSERUI_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>

#include "./clsScreen.h"
#include "./clsUser.h"
#include "./clsString.h"
#include "./utils.h"
#include "./read.h"
#include "./clsClient.h"
#include "./clsClientUI.h"

using namespace std;

class clsUserUI : protected clsScreen
{
private:
  static bool _isCancelled(
      string &toRead,
      string prompt = "Enter Username (or 0 to cancel): ")
  {
    cout << prompt << endl;
    getline(cin, toRead);

    return (toRead == "0");
  }

  static string _getUniqueUsername()
  {
    string username;
    while (true)
    {
      if (_isCancelled(username))
        return "";

      if (clsUser::find(username) == nullptr)
        return username;

      cout << "Username already exists. Please try another one.\n";
    }
  }

  static int _readUserPermissions(clsUser &user)
  {
    int permissions = 0;

    if (read::yesOrNo("Do you want to give full access? [y/n]: ") == 'y')
      return -1;

    if (read::yesOrNo("Do you want to give access to show client list? [y/n]: ") == 'y')
      permissions += pow(2, 0);

    if (read::yesOrNo("Do you want to give access to add new client? [y/n]: ") == 'y')
      permissions += pow(2, 1);

    if (read::yesOrNo("Do you want to give access to delete client? [y/n]: ") == 'y')
      permissions += pow(2, 2);

    if (read::yesOrNo("Do you want to give access to update client? [y/n]: ") == 'y')
      permissions += pow(2, 3);

    if (read::yesOrNo("Do you want to give access to find client? [y/n]: ") == 'y')
      permissions += pow(2, 4);

    if (read::yesOrNo("Do you want to give access to transactions? [y/n]: ") == 'y')
      permissions += pow(2, 5);

    if (read::yesOrNo("Do you want to give access to manage users? [y/n]: ") == 'y')
      permissions += pow(2, 6);

    if (read::yesOrNo("Do you want to give access to show logs? [y/n]: ") == 'y')
      permissions += pow(2, 7);

    return permissions;
  }

  static void _readNewUserData(clsUser &user)
  {
    user.setUsername(_getUniqueUsername());
    user.setFirstname(read::validatedUserInput<string>("Enter First Name: "));
    user.setLastname(read::validatedUserInput<string>("Enter Last Name: "));
    user.setEmail(read::validatedUserInput<string>("Enter Email: "));
    user.setPhone(read::validatedUserInput<string>("Enter Phone Number: "));
    user.setPassword(read::validatedUserInput<string>("Enter Password: "));
    user.setPermissions(_readUserPermissions(user));
  }

  static void _readUpdatedUserData(clsUser &user)
  {
    if (read::yesOrNo("Do you want to update first name? [y/n]: ") == 'y')
      user.setFirstname(read::validatedUserInput<string>("Enter First Name: "));

    if (read::yesOrNo("Do you want to update last name? [y/n]: ") == 'y')
      user.setLastname(read::validatedUserInput<string>("Enter Last Name: "));

    if (read::yesOrNo("Do you want to update email? [y/n]: ") == 'y')
      user.setEmail(read::validatedUserInput<string>("Enter Email: "));

    if (read::yesOrNo("Do you want to update phone number? [y/n]: ") == 'y')
      user.setPhone(read::validatedUserInput<string>("Enter Phone Number: "));

    if (read::yesOrNo("Do you want to update password? [y/n]: ") == 'y')
    {
      if (read::validatedUserInput<string>("Enter Old Password: ") == user.getPassword())
        user.setPassword(read::validatedUserInput<string>("Enter Password: "));
      else
        cout << "Wrong Password!\n";
    }

    if (read::yesOrNo("Do you want to update permissions? [y/n]: ") == 'y')
      user.setPermissions(_readUserPermissions(user));
  }

  static clsUser *_findUserUI()
  {
    string username = "";
    clsUser *user;

    while (true)
    {
      if (_isCancelled(username))
        return nullptr;

      user = clsUser::find(username);

      if (user == nullptr)
      {
        if (read::yesOrNo("User with Username [" + username + "] was not found!\nDo you want to try again? [y/n]: ") != 'y')
          return nullptr;
      }
      else
        break;
    }
  }

  static void _printUserLine(const clsUser &user)
  {
    cout << setw(8) << left << "" << "| " << setw(12) << left << user.getUsername();
    cout << "| " << setw(25) << left << user.getFullName();
    cout << "| " << setw(12) << left << user.getPhone();
    cout << "| " << setw(20) << left << user.getEmail();
    cout << "| " << setw(10) << left << user.getPassword();
    cout << "| " << setw(12) << left << user.getPermissions();
    cout << endl;
  }

  static void _printUsersListHeader()
  {
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "______________________________________________\n"
         << endl;

    cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
    cout << "| " << left << setw(25) << "Full Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(20) << "Email";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(12) << "Permissions";
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "______________________________________________\n"
         << endl;
  }

  static void _printUsersListBody(const vector<clsUser> &vUsers)
  {
    if (vUsers.size() == 0)
      cout << "\t\t\t\tNo Users Available In the System!";
    else
      for (clsUser user : vUsers)
        _printUserLine(user);
  }

  static void _printUsersListFooter()
  {
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "______________________________________________\n"
         << endl;
  }

  static void _print(const clsUser &user)
  {
    cout << "\nUser Card:";
    cout << "\n___________________";
    cout << "\nFirstName   : " << user.getFirstName();
    cout << "\nLastName    : " << user.getLastName();
    cout << "\nFull Name   : " << user.getFullName();
    cout << "\nEmail       : " << user.getEmail();
    cout << "\nPhone       : " << user.getPhone();
    cout << "\nUser Name   : " << user.getUsername();
    cout << "\nPermissions : " << user.getPermissions();
    cout << "\n___________________\n";
  }

public:
  static void usersListUI()
  {
    vector<clsUser> vUsers = clsUser::getAllUsers();

    string title = "\t  User List Screen";
    string subTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

    _drawScreenHeader(title, subTitle);

    _printUsersListHeader();
    _printUsersListBody(vUsers);
    _printUsersListFooter();
  }

  static void addNewUserUI()
  {
    _drawScreenHeader("\t  Add New User Screen");

    clsUser user;
    _readNewUserData(user);

    if (user.getUsername().empty())
    {
      cout << "\nOperation has been cancelled!\n";
      return;
    }

    if (user.addUser())
    {
      cout << "\nUser has been added successfully!\n\n";
      _print(user);
    }
    else
      cout << "\nError: User has not been added!\n";
  }

  static void updateUserUI()
  {
    _drawScreenHeader("\t  Update User Screen");

    clsUser *user = _findUserUI();

    if (user == nullptr)
    {
      cout << "\nOperation has been cancelled!\n";
      return;
    }

    _print(*user);
    _readUpdatedUserData(*user);

    if (user->updateUser())
    {
      cout << "\nUser has been updated successfully!\n\n";
      _print(*user);
    }
    else
      cout << "\nError: User has not been updated!\n";
  }

  static void deleteUserUI()
  {
    _drawScreenHeader("\t  Delete User Screen");

    clsUser *user = _findUserUI();

    if (user == nullptr)
    {
      cout << "\nOperation has been cancelled!\n";
      return;
    }

    _print(*user);

    if (read::yesOrNo("Are you sure you want to delete this user? [y/n]: ") == 'y')
    {
      if (user->deleteUser())
        cout << "\nUser has been deleted successfully!\n";
      else
        cout << "\nError: User has not been deleted!\n";
    }
    else
      cout << "\nOperation has been cancelled!\n";
  }

  static void findUserUI()
  {
    _drawScreenHeader("\t  Find User Screen");

    clsUser *user = _findUserUI();

    if (user == nullptr)
    {
      cout << "\nOperation has been cancelled!\n";
      return;
    }

    _print(*user);
  }
};

#endif // CLSUSERUI_H