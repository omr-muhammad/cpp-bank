#pragma once

#ifndef CLS_CLIENT_UI_H
#define CLS_CLIENT_UI_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include "./clsScreen.h"
#include "./clsClient.h"
#include "./clsString.h"
#include "./utils.h"
#include "./read.h"

using namespace std;

class clsClientUI : protected clsScreen
{
private:
    static bool isCancelled(
        string &toRead,
        string prompt = "Enter Client Account Number (or 0 to cancel): ")
    {
        cout << prompt << endl;
        getline(cin, toRead);

        return (toRead == "0");
    }

    static string _getUniqueAccountNumber()
    {
        string accountNumber;
        while (true)
        {
            if (isCancelled(accountNumber))
                return "";

            if (clsClient::find(accountNumber) == nullptr)
                return accountNumber;

            cout << "\nAccount number already exists. Please try another one.\n\n";
        }
    }

    static void _readNewClientData(clsClient &client)
    {
        string accountNumber = _getUniqueAccountNumber();
        if (accountNumber.empty())
            return; // User cancelled the operation

        client.setAccountNumber(accountNumber);
        client.setFirstname(read::validatedUserInput<string>("Enter First Name: "));
        client.setLastname(read::validatedUserInput<string>("Enter Last Name: "));
        client.setPhone(read::validatedUserInput<string>("Enter Phone Number: "));
        client.setEmail(read::validatedUserInput<string>("Enter Email: "));
        client.setPinCode(read::validatedUserInput<string>("Enter Pin Code: "));
        client.setBalance(read::validatedUserInput<double>("Enter Account Balance: "));
    }

    static void _readUpdatedClientData(clsClient &client)
    {
        if (read::yesOrNo("Do you want to update first name?") == 'y')
            client.setFirstname(read::validatedUserInput<string>("Enter First Name: "));

        if (read::yesOrNo("Do you want to update last name?") == 'y')
            client.setLastname(read::validatedUserInput<string>("Enter Last Name: "));

        if (read::yesOrNo("Do you want to update phone number?") == 'y')
            client.setPhone(read::validatedUserInput<string>("Enter Phone Number: "));

        if (read::yesOrNo("Do you want to update email?") == 'y')
            client.setEmail(read::validatedUserInput<string>("Enter Email: "));

        if (read::yesOrNo("Do you want to update pin code?") == 'y')
            client.setPinCode(read::validatedUserInput<string>("Enter Pin Code: "));

        if (read::yesOrNo("Do you want to update account balance?") == 'y')
            client.setBalance(read::validatedUserInput<double>("Enter Account Balance: "));
        }

    static clsClient *_findClientUI()
    {
        string accountNumber = "";
        clsClient *client = nullptr;

        while (true)
        {
            if (isCancelled(accountNumber))
                return nullptr;

            client = clsClient::find(accountNumber);

            if (client == nullptr)
            {
                if (read::yesOrNo("Client with account number [" + accountNumber + "] was not found!\nDo you want to try again? [y/n]: ") != 'y')
                    return nullptr;
            }
            else
                break;
        }

        return client;
    }

    static void _print(const clsClient &client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.getFirstName();
        cout << "\nLastName    : " << client.getLastName();
        cout << "\nFull Name   : " << client.getFullName();
        cout << "\nEmail       : " << client.getEmail();
        cout << "\nPhone       : " << client.getPhone();
        cout << "\nAcc. Number : " << client.getAccountNumber();
        cout << "\nPassword    : " << client.getPinCode();
        cout << "\nBalance     : " << client.getBalance();
        cout << "\n___________________\n";
    }

    static void _printClientLine(const clsClient &client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << client.getAccountNumber();
        cout << "| " << setw(20) << left << client.getFullName();
        cout << "| " << setw(12) << left << client.getPhone();
        cout << "| " << setw(20) << left << client.getEmail();
        cout << "| " << setw(10) << left << client.getPinCode();
        cout << "| " << setw(12) << left << client.getBalance();
        cout << endl;
    }

    static void _printListHeader(int clients = 0)
    {
        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(clients) + ") Client(s).";

        _drawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }

    static void _printListBody(const vector<clsClient> &vClients)
    {
        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (const clsClient &client : vClients)
                _printClientLine(client);
    }

    static void _printListFooter()
    {
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }

    static void _printClientBalanceLine(const clsClient &client)
    {

        cout << setw(25) << left << "" << "| " << setw(15) << left << client.getAccountNumber();
        cout << "| " << setw(40) << left << client.getFullName();
        cout << "| " << setw(12) << left << client.getBalance();
        cout << endl;
    }

    static void _printBalanceListHeader()
    {
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n"
             << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\t\t_______________________________________________________";
        cout << "__________________________\n"
             << endl;
    }

    static void _printBalanceListBody(const vector<clsClient> &vClients)
    {
        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (const clsClient &client : vClients)
                _printClientBalanceLine(client);
    }

    static void _printBalanceListFooter(const double &totalBalance)
    {
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n"
             << endl;

        cout << setw(8) << left << "" << "\t\t\t\t\t\t\t     Total Balances = " << totalBalance << endl;
        cout << setw(8) << left << "" << "\t\t\t\t  ( " << utils::convertNumToReadableTxt(totalBalance) << ")";
    }

    static void _printCancelMessage(string message = "\nOperation has been cancelled!")
    {
        cout << message << endl;
    }

    static double getAmount(clsClient *client, string action)
    {
        double amount = read::validatedUserInput<double>("Enter " + action + " Amount or (0) to cancel: ");

        if (amount == 0)
            return 0;

        string lowerAction = clsString::lowerStr(action);
        while ((lowerAction == "withdraw" || lowerAction == "transfer") && amount > client->getBalance())
        {
            cout << "\nError: Amount exceeds the available balance!\n";

            amount = read::validatedUserInput<double>("Enter " + action + " Amount or (0) to cancel: ");

            if (amount == 0)
                return 0;
        }

        if (read::yesOrNo("Are you sure you want to perform this action? [y/n]: ") != 'y')
            return 0;

        return amount;
    }

public:
    static void addNewClientUI()
    {
        _drawScreenHeader("\t  Add New Client Screen");

        clsClient client;
        _readNewClientData(client);

        if (client.getAccountNumber().empty())
        {
            cout << "\nOperation has been cancelled!\n";
            return;
        }

        if (client.addClient())
        {
            cout << "\nClient has been added successfully!\n\n";
            _print(client);
        }
        else
            cout << "\nError: Client has not been added!\n";
    }

    static void updateClientUI()
    {
        _drawScreenHeader("\t  Update Client Screen");

        clsClient *client = _findClientUI();

        if (client == nullptr)
        {
            cout << "\nOperation has been cancelled!\n";
            return;
        }

        _print(*client);
        _readUpdatedClientData(*client);

        if (client->updateClient())
        {
            cout << "\nClient has been updated successfully!\n\n";
            _print(*client);
        }
        else
            cout << "\nError: Client has not been updated!\n";
    }

    static void deleteClientUI()
    {
        _drawScreenHeader("\t  Delete Client Screen");

        clsClient *client = _findClientUI();

        if (client == nullptr)
        {
            cout << "\nOperation has been cancelled!\n";
            return;
        }

        _print(*client);

        if (read::yesOrNo("Are you sure you want to delete this client?") == 'y')
        {
            if (client->deleteClient())
                cout << "\nClient has been deleted successfully!\n";
            else
                cout << "\nError: Client has not been deleted!\n";
        }
        else
            cout << "\nOperation has been cancelled!\n";
    }

    static void findClientUI()
    {
        _drawScreenHeader("\t  Find Client Screen");

        clsClient *client = _findClientUI();

        if (client == nullptr)
        {
            cout << "\nOperation has been cancelled!\n";
            return;
        }

        _print(*client);
    }

    static void depositUI()
    {
        _drawScreenHeader("\t   Deposit Screen");

        clsClient *client = _findClientUI();

        if (client == nullptr)
            return _printCancelMessage();

        _print(*client);
        cout << "\n\n";

        double amount = getAmount(client, "Deposit");

        if (amount == 0)
            return _printCancelMessage();

        if (client->deposite(amount))
        {
            cout << "\nDeposit has been done successfully!\n";
            cout << "\nNew Balance is: " << client->getBalance();
        }
        else
            cout << "\nError: Deposit has not been done!\n";
    }

    static void withdrawUI()
    {
        _drawScreenHeader("\t   Withdraw Screen");

        clsClient *client = _findClientUI();

        if (client == nullptr)
            return _printCancelMessage();

        _print(*client);
        cout << "\n\n";

        double amount = getAmount(client, "Withdraw");

        if (amount == 0)
            return _printCancelMessage();

        if (client->withdraw(amount))
        {
            cout << "\nWithdraw has been done successfully!\n";
            cout << "\nNew Balance is: " << client->getBalance();
        }
        else
            cout << "\nError: Withdraw has not been done!\n";
    }

    static void transferUI()
    {
        _drawScreenHeader("\t    Transfer Screen");

        clsClient *fromClient = _findClientUI();
        if (fromClient == nullptr)
            return _printCancelMessage();

        _print(*fromClient);

        clsClient *toClient = _findClientUI();
        if (toClient == nullptr)
            return _printCancelMessage();

        while (fromClient->getAccountNumber() == toClient->getAccountNumber())
        {
            cout << "\nError: You can't transfer to the same account!\n";

            toClient = _findClientUI();

            if (toClient == nullptr)
                return _printCancelMessage();
        }
        clsClientUI::_print(*toClient);

        double amount = getAmount(fromClient, "Transfer");

        if (amount == 0)
            return _printCancelMessage();

        if (fromClient->transfer(toClient, amount))
        {
            cout << "\nTransfer has been done successfully!\n";
            _print(*fromClient);
            cout << "\n\n";
            _print(*toClient);
        }
        else
            cout << "\nError: Transfer has not been done!\n";
    }

    static void clientsListUI()
    {
        vector<clsClient> vClients = clsClient::getAllClients();

        _printListHeader(vClients.size());
        _printListBody(vClients);
        _printListFooter();
    }

    static void totalBalanceListUI()
    {
        vector<clsClient> vClients = clsClient::getAllClients();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _drawScreenHeader(Title, SubTitle);

        _printBalanceListHeader();
        _printBalanceListBody(vClients);
        _printBalanceListFooter(clsClient::totalBalances());
    }
};

#endif // CLS_CLIENT_UI_H