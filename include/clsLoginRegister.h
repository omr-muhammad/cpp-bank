#pragma once

#ifndef CLSLOGIN_REGISTER_H
#define CLSLOGIN_REGISTER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "./clsDate.h"
#include "./global.h"

using namespace std;

class clsLoginRegister
{
private:
  string _loggedDate, _loggedUsername, _loggedUserPassword, _loggedUserPermissions;
  inline static vector<clsLoginRegister> _loginRegister;
  static const string _loginRegisterFile;

  static clsLoginRegister _convertToLoginRegister(string &line, string delimiter = "#//#")
  {
    vector<string> vLoginRegisterData = clsString::split(line, delimiter);

    // Variables for clarity
    string loggedDate = vLoginRegisterData[0];
    string loggedUsername = vLoginRegisterData[1];
    string loggedUserPassword = clsString::decryptText(vLoginRegisterData[2]);
    string loggedUserPermissions = vLoginRegisterData[3];

    return clsLoginRegister(loggedDate, loggedUsername, loggedUserPassword, loggedUserPermissions);
  }

  static string _convertToLine(clsLoginRegister &loginRegister, string delimiter = "#//#")
  {
    string line = "";
    line += loginRegister._loggedDate + delimiter;
    line += loginRegister._loggedUsername + delimiter;
    line += clsString::encryptText(loginRegister._loggedUserPassword) + delimiter;
    line += loginRegister._loggedUserPermissions;

    return line;
  }

public:
  clsLoginRegister(
      string loggedDate, string loggedUsername,
      string loggedUserPassword, string loggedUserPermissions)
      : _loggedDate(loggedDate),
        _loggedUsername(loggedUsername),
        _loggedUserPassword(loggedUserPassword),
        _loggedUserPermissions(loggedUserPermissions)
  {
  }

  string getLoggedDate() const { return _loggedDate; }
  string getLoggedUsername() const { return _loggedUsername; }
  string getLoggedUserPassword() const { return _loggedUserPassword; }
  string getLoggedUserPermissions() const { return _loggedUserPermissions; }

  static void loadLoginRegister()
  {
    _loginRegister.clear();

    ifstream file(_loginRegisterFile);

    // Check if the file is empty
    if (file.peek() == ifstream::traits_type::eof())
    {
      file.close();
      return;
    }

    if (file.is_open())
    {
      string line;
      while (getline(file, line))
      {
        if (line.empty() == false)
          _loginRegister.push_back(_convertToLoginRegister(line));
      }
      file.close();
    }
  }

  static bool writeNewLogs()
  {
    clsDate date;
    clsLoginRegister newLog(date.loggedDate(), currentUser->getUsername(), currentUser->getPassword(), to_string(currentUser->getPermissions()));

    ofstream file(_loginRegisterFile, ios::app);
    if (file.is_open())
    {
      file << _convertToLine(newLog) << endl;
      file.close();
      _loginRegister.push_back(newLog);
      return true;
    }

    _loginRegister.pop_back();
    return false;
  }

  static vector<clsLoginRegister> getAllLogs()
  {
    return _loginRegister;
  }
};

const string clsLoginRegister::_loginRegisterFile = "logins.txt";

#endif // CLSLOGIN_REGISTER_H