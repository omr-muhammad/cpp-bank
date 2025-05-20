#pragma once

#ifndef CLSMAINSCREEN_H
#define CLSMAINSCREEN_H

#include <iostream>
#include <iomanip>

#include "read.h"
#include "clsScreen.h"
#include "clsClientUI.h"
#include "clsTransactionsScreen.h"
#include "clsLog-in-out.h"
#include "clsUser.h"
#include "clsLoginRegisterUI.h"

class clsMainScreen : protected clsScreen
{
private:
  enum enMainMenueOptions
  {
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenue = 6,
    eManageUsers = 7,
    eLogsList = 8,
    eExit = 9
  };

  static short _readMainMenuOption()
  {
    cout << setw(37) << left << "" << "Choose what do you want to do?\n";
    short choice = read::numInRange("Enter Your Choice", 1, 9);
    return choice;
  }

  static void _goBackToMainMenu()
  {
    cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";
    system("pause>0");
    showMainMenu();
  }

  static void _showAllClientsScreen()
  {
    clsClientUI::clientsListUI();
  }

  static void _showAddNewClientsScreen()
  {
    clsClientUI::addNewClientUI();
  }

  static void _showDeleteClientScreen()
  {
    clsClientUI::deleteClientUI();
  }

  static void _showUpdateClientScreen()
  {
    clsClientUI::updateClientUI();
  }

  static void _showFindClientScreen()
  {
    clsClientUI::findClientUI();
  }

  static void _showTransactionsMenu()
  {
    clsTransactionsScreen::showTransactionsMenu();
  }

  static void _showManageUsersMenu()
  {
    cout << "\nManage Users Menu Screen Will be here...\n";
  }

  static void _showLogsList()
  {
    clsLoginRegisterUI::printLogsList();
  }

  static void _logout()
  {
    clsLogInOut::logoutScreen();
  }

  static void _perfromMainMenuOption(enMainMenueOptions mainMenueOption)
  {
    system("cls");

    if (!currentUser->isAuthorized((int)mainMenueOption))
      _drawScreenHeader("\t    Access Denied! Contact Your Admin.");
    else
    {
      switch (mainMenueOption)
      {
      case enMainMenueOptions::eListClients:
        _showAllClientsScreen();
        break;

      case enMainMenueOptions::eAddNewClient:
        _showAddNewClientsScreen();
        break;

      case enMainMenueOptions::eDeleteClient:
        _showDeleteClientScreen();
        break;

      case enMainMenueOptions::eUpdateClient:
        _showUpdateClientScreen();
        break;

      case enMainMenueOptions::eFindClient:
        _showFindClientScreen();
        break;

      case enMainMenueOptions::eShowTransactionsMenue:
        _showTransactionsMenu();
        break;

      case enMainMenueOptions::eManageUsers:
        _showManageUsersMenu();
        break;

      case enMainMenueOptions::eLogsList:
        _showLogsList();
        break;

      case enMainMenueOptions::eExit:
        return _logout();
      }
    }

    _goBackToMainMenu();
  }

public:
  static void showMainMenu()
  {
    system("cls");
    _drawScreenHeader("\t\tMain Screen");

    cout << setw(37) << left << "" << "===========================================\n";
    cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
    cout << setw(37) << left << "" << "===========================================\n";
    cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
    cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
    cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
    cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
    cout << setw(37) << left << "" << "\t[5] Find Client.\n";
    cout << setw(37) << left << "" << "\t[6] Transactions.\n";
    cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
    cout << setw(37) << left << "" << "\t[8] Login Register.\n";
    cout << setw(37) << left << "" << "\t[9] Logout.\n";
    cout << setw(37) << left << "" << "===========================================\n";

    _perfromMainMenuOption(
        enMainMenueOptions(
            _readMainMenuOption()));
  }
};

#endif // CLSMAINSCREEN_H
