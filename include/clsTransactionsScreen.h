#pragma once

#ifndef CLSTRANSACTIONSSCREEN_H
#define CLSTRANSACTIONSSCREEN_H

#include <iostream>
#include <iomanip>

#include "read.h"
#include "clsScreen.h"
#include "clsClientUI.h"
#include "clsTransferLogsList.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
  enum _enTransactionsMenuOptions
  {
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalances = 3,
    eTransfer = 4,
    eTransferList = 5,
    eMainMenu = 6
  };

  static short _readTransactionsMenuOption()
  {
    cout << setw(37) << left << "" << "Choose what do you want to do?\n";
    short choice = read::numInRange("Enter Your Choice", 1, 6);
    return choice;
  }

  static void _goBackToTransactionsMenu()
  {
    cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menu...\n";
    system("pause>0");
    showTransactionsMenu();
  }

  static void _showDepositScreen()
  {
    clsClientUI::depositUI();
  }

  static void _showWithdrawScreen()
  {
    clsClientUI::withdrawUI();
  }

  static void _showTotalBalances()
  {
    clsClientUI::totalBalanceListUI();
  }

  static void _showTransferScreen()
  {
    clsClientUI::transferUI();
  }

  static void _showTransferLogsScreen()
  {
    clsTransferLogsList::printTransferLogsList();
  }

  static void _perfromTransactionsMenuOption(_enTransactionsMenuOptions option)
  {
    system("cls");

    switch (option)
    {
    case _enTransactionsMenuOptions::eDeposit:
      _showDepositScreen();
      break;

    case _enTransactionsMenuOptions::eWithdraw:
      _showWithdrawScreen();
      break;

    case _enTransactionsMenuOptions::eTotalBalances:
      _showTotalBalances();
      break;

    case _enTransactionsMenuOptions::eTransfer:
      _showTransferScreen();
      break;

    case _enTransactionsMenuOptions::eTransferList:
      _showTransferLogsScreen();
      break;

    case _enTransactionsMenuOptions::eMainMenu:
      return;
    }

    _goBackToTransactionsMenu();
  }

public:
  static void showTransactionsMenu()
  {
    system("cls");
    _drawScreenHeader("\t\tTransactions Menu");

    cout << setw(37) << left << "" << "===========================================\n";
    cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
    cout << setw(37) << left << "" << "===========================================\n";
    cout << setw(37) << left << "" << "\t[1] Deposit.\n";
    cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
    cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
    cout << setw(37) << left << "" << "\t[4] Transfer.\n";
    cout << setw(37) << left << "" << "\t[5] Transfer Logs.\n";
    cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
    cout << setw(37) << left << "" << "===========================================\n";

    _perfromTransactionsMenuOption(
        _enTransactionsMenuOptions(_readTransactionsMenuOption()));
  }
};

#endif // CLSTRANSACTIONSMENU_H
