#pragma once

#ifndef CLSCLIENT_H
#define CLSCLIENT_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

// internal includes
#include "clsPerson.h"
#include "clsString.h"
#include "clsTransferLogs.h"
#include "utils.h"
#include "read.h"

using namespace std;

class clsClient : public clsPerson
{
private:
  inline static vector<clsClient> _clients;
  static const string _clientsFile;
  string _accountNumber;
  string _pinCode;
  double _balance;

  static clsClient _convertToClient(string &line, string delimiter = "#//#")
  {
    vector<string> vClientData = clsString::split(line, delimiter);

    return clsClient(
        vClientData[0], vClientData[1], vClientData[2], vClientData[3],
        vClientData[4], vClientData[5], stod(vClientData[6]));
  }

  static string _convertToLine(clsClient &client, string delimiter = "#//#")
  {
    string line = client.getAccountNumber() + delimiter;
    line += client.getPinCode() + delimiter;
    line += client.getFirstName() + delimiter;
    line += client.getLastName() + delimiter;
    line += client.getEmail() + delimiter;
    line += client.getPhone() + delimiter;
    line += to_string(client.getBalance());
    return line;
  }

  bool _saveClients()
  {
    ofstream file(_clientsFile, ios::trunc /* absolute clarity */);
    if (file.is_open())
    {
      for (clsClient &client : _clients)
      {
        string line = _convertToLine(client);
        file << line << endl;
      }

      file.close();
      return true;
    }

    return false;
  }

public:
  clsClient() : clsPerson() {};
  clsClient(
      string firstname, string lastname, string email, string phone,
      string accountNumber, string pinCode, double balance)
      : clsPerson(firstname, lastname, email, phone),
        _accountNumber(accountNumber),
        _pinCode(pinCode),
        _balance(balance)
  {
  }

  // Setters
  void setAccountNumber(string accountNumber) { _accountNumber = accountNumber; }
  void setPinCode(string pinCode) { _pinCode = pinCode; }
  void setBalance(double balance) { _balance = balance; }

  // Getters
  string getAccountNumber() const { return _accountNumber; }
  string getPinCode() const { return _pinCode; }
  double getBalance() const { return _balance; }
  static const vector<clsClient> &getAllClients() { return _clients; }

  static void loadClients()
  {
    _clients.clear();

    ifstream file(_clientsFile);
    if (file.is_open())
    {
      string line;
      while (getline(file, line))
      {
        if (line.empty() == false)
          _clients.push_back(_convertToClient(line));
      }
      file.close();
    }
  }

  static clsClient *find(const string &accountNumber)
  {
    for (clsClient &client : _clients)
    {
      if (client.getAccountNumber() == accountNumber)
      {
        return &client;
      }
    }

    return nullptr;
  }

  bool addClient()
  {
    try
    {
      _clients.push_back(*this);
    }
    catch (...)
    {
      return false;
    }

    ofstream file(_clientsFile, ios::app);
    if (file.is_open())
    {
      string line = _convertToLine(*this);
      file << line << endl;
      file.close();
      return true;
    }

    _clients.pop_back();
    return false;
  }

  bool updateClient()
  {
    for (clsClient &c : _clients)
      if (c.getAccountNumber() == this->getAccountNumber())
      {
        c = *this;
        if (_saveClients() == true)
          return true;
        else
          return false;
      }

    return false;
  }

  bool deleteClient()
  {
    // Find the client first
    auto it = find_if(_clients.begin(), _clients.end(),
                      [accountNumber = getAccountNumber()](const clsClient &c)
                      {
                        return c.getAccountNumber() == accountNumber;
                      });

    // If not found, return false
    if (it == _clients.end())
      return false;

    _clients.erase(it);

    return _saveClients();
  }

  bool deposite(double amount)
  {
    _balance += amount;

    return _saveClients();
  }

  bool withdraw(double amount)
  {
    _balance -= amount;

    return _saveClients();
  }

  bool transfer(clsClient *toClient, double amount)
  {
    return this->withdraw(amount) && toClient->deposite(amount) && clsTransferLogs::writeNewTransferLog(this, toClient, amount, currentUser->getUsername());
  }

  static double totalBalances()
  {
    double total = 0;
    for (clsClient &client : _clients)
      total += client.getBalance();

    return total;
  }
};

const string clsClient::_clientsFile = "clients.txt";

#endif // CLSCLIENT_H