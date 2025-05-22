#pragma once

#ifndef CLSLOGINREGISTERUI_H
#define CLSLOGINREGISTERUI_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "./clsScreen.h"
#include "./clsString.h"
#include "./clsLoginRegister.h"

using namespace std;

class clsLoginRegisterUI : protected clsScreen
{
private:
  static void _printLogLine(const clsLoginRegister &log)
  {
    cout << setw(8) << left << "" << "| " << setw(35) << left << log.getLoggedDate();
    cout << "| " << setw(20) << left << log.getLoggedUsername();
    cout << "| " << setw(20) << left << clsString::encryptText(log.getLoggedUserPassword());
    cout << "| " << setw(10) << left << log.getLoggedUserPermissions();
    cout << endl;
  }

  static void _printLogsListHeader()
  {
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
    cout << "| " << left << setw(20) << "UserName";
    cout << "| " << left << setw(20) << "Password";
    cout << "| " << left << setw(10) << "Permissions";
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
  }

  static void _printLogsListBody(const vector<clsLoginRegister> &vLogs)
  {
    if (vLogs.size() == 0)
      cout << "\t\t\t\tNo Logins Available In the System!";
    else
      for (const clsLoginRegister &log : vLogs)
        _printLogLine(log);
  }

  static void _printLogsListFooter()
  {
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
  }

public:
  static void printLogsList()
  {
    vector<clsLoginRegister> logs = clsLoginRegister::getAllLogs();

    _drawScreenHeader("\t    Login Register List Screen", "\t    (" + to_string(logs.size()) + ") Log(s).");

    _printLogsListHeader();
    _printLogsListBody(logs);
    _printLogsListFooter();
  }
};

#endif // CLSLOGINREGISTERUI_H