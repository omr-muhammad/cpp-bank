#pragma once

#ifndef CLSTRANSFERLOGSLIST_H
#define CLSTRANSFERLOGSLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "./clsScreen.h"
#include "./clsTransferLogs.h"

using namespace std;

class clsTransferLogsList : protected clsScreen
{
private:
  static void _printTransferLogLine(const clsTransferLogs &transferLog)
  {
    cout << setw(8) << left << "" << "| " << setw(23) << left << transferLog.getTransferDate();
    cout << "| " << setw(8) << left << transferLog.getFromAccountNumber();
    cout << "| " << setw(8) << left << transferLog.getToAccountNumber();
    cout << "| " << setw(8) << left << transferLog.getAmount();
    cout << "| " << setw(10) << left << transferLog.getFromBalance();
    cout << "| " << setw(10) << left << transferLog.getToBalance();
    cout << "| " << setw(8) << left << transferLog.getUsername();
    cout << endl;
  }

  static void _printTransferLogsListHeader()
  {
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
    cout << "| " << left << setw(8) << "from.Acct";
    cout << "| " << left << setw(8) << "to.Acct";
    cout << "| " << left << setw(8) << "Amount";
    cout << "| " << left << setw(10) << "from.Balance";
    cout << "| " << left << setw(10) << "to.Balance";
    cout << "| " << left << setw(8) << "User";

    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
  }

  static void _printTransferLogsListBody(const vector<clsTransferLogs> &vTransferLogs)
  {
    if (vTransferLogs.size() == 0)
      cout << "\t\t\t\tNo Transfers Available In the System!";
    else
      for (const clsTransferLogs &log : vTransferLogs)
        _printTransferLogLine(log);
  }

  static void _printTransferLogsListFooter()
  {
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
  }

public:
  static void printTransferLogsList()
  {
    vector<clsTransferLogs> transferLogs = clsTransferLogs::getAllTransferLogs();

    string Title = "\tTransfer Log List Screen";
    string SubTitle = "\t    (" + to_string(transferLogs.size()) + ") Record(s).";

    _drawScreenHeader(Title, SubTitle);

    _printTransferLogsListHeader();
    _printTransferLogsListBody(transferLogs);
    _printTransferLogsListFooter();
  }
};

#endif // CLSTRANSFERLOGSLIST_H