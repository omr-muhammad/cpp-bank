#pragma once

#ifndef CLSTRANSFER_LOGS_H
#define CLSTRANSFER_LOGS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "./clsDate.h"
#include "./global.h"
#include "./clsScreen.h"

using namespace std;

class clsTransferLogs : protected clsScreen
{
private:
  string _transferDate, _fromAccountNumber, _toAccountNumber, _fromBalance, _toBalance, _amount, _username;
  inline static vector<clsTransferLogs> _transferLogs;
  static const string _transferLogsFile;

  static clsTransferLogs _convertToTransferLog(string &line, string delimiter = "#//#")
  {
    vector<string> vTransferLogData = clsString::split(line, delimiter);

    return clsTransferLogs(vTransferLogData[0], vTransferLogData[1], vTransferLogData[2], vTransferLogData[3], vTransferLogData[4], vTransferLogData[5], vTransferLogData[6]);
  }

  static string _convertToLine(clsTransferLogs &transferLog, string delimiter = "#//#")
  {
    string line = "";
    line += transferLog._transferDate + delimiter;
    line += transferLog._fromAccountNumber + delimiter;
    line += transferLog._toAccountNumber + delimiter;
    line += transferLog._amount + delimiter;
    line += transferLog._fromBalance + delimiter;
    line += transferLog._toBalance + delimiter;
    line += transferLog._username;

    return line;
  }

public:
  clsTransferLogs(
      string transferDate, string fromAcc, string toAcc, string amount,
      string fromBalance, string toBalance, string username)
      : _transferDate(transferDate), _fromAccountNumber(fromAcc),
        _toAccountNumber(toAcc), _amount(amount),
        _fromBalance(fromBalance), _toBalance(toBalance),
        _username(username) {}

  string getTransferDate() const { return _transferDate; }
  string getFromAccountNumber() const { return _fromAccountNumber; }
  string getFromBalance() const { return _fromBalance; }
  string getToAccountNumber() const { return _toAccountNumber; }
  string getToBalance() const { return _toBalance; }
  string getAmount() const { return _amount; }
  string getUsername() const { return _username; }

  static void loadTransferLogs()
  {
    _transferLogs.clear();

    ifstream file(_transferLogsFile);

    if (file.is_open())
    {
      string line;
      while (getline(file, line))
      {
        if (line.empty() == false)
          _transferLogs.push_back(_convertToTransferLog(line));
      }
      file.close();
    }
  }

  static bool writeNewTransferLog(string fromAcc, string toAcc, double fromBlc, double toBlc, double amount, string username)
  {
    clsDate date;
    clsTransferLogs newTransferLog(date.loggedDate(), fromAcc, toAcc, to_string(fromBlc), to_string(toBlc), to_string(amount), username);

    fstream file(_transferLogsFile, ios::app);

    if (file.is_open())
    {
      file << _convertToLine(newTransferLog) << endl;
      _transferLogs.push_back(newTransferLog);
      file.close();
      return true;
    }

    return false;
  }

  static vector<clsTransferLogs> getAllTransferLogs() { return _transferLogs; }
};

const string clsTransferLogs::_transferLogsFile = "transferLogs.txt";

#endif // CLSTRANSFER_LOGS_H