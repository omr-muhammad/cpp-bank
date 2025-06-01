#pragma once

#ifndef CLSBANKAPP_H
#define CLSBANKAPP_H

#include <iostream>
#include <string>
#include <iomanip>

#include "./clsLogin.h"
#include "./global.h"
#include "./clsUser.h"
#include "./clsClient.h"
#include "./clsLoginRegister.h"

using namespace std;

class clsBankApp
{
private:
    static void _loadData()
    {
        // Load all data at startup
        clsUser::loadUsers();
        clsClient::loadClients();
        clsLoginRegister::loadLoginRegister();
    }

public:
    static void run()
    {
        _loadData();

        while (true)
        {
            if (failedLoginAttempts >= 3)
                break;
            clsLogin::loginScreen();
        }

        // std::cout << "\n\nYou have been locked out of the system after 3 failed attempts.\n";
    }
};

#endif // CLSBANKAPP_H