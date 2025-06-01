#pragma once

#ifndef _CLSUSER_H_
#define _CLSUSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>

#include "./clsPerson.h"
#include "./clsString.h"
#include "./global.h"

using namespace std;

class clsUser : public clsPerson
{
private:
    inline static vector<clsUser> _users;
    static inline const string _usersFile = "users.txt";
    string _username;
    string _password;
    int _permissions;

    static clsUser _convertToUser(string &line, string delimiter = "#//#")
    {
        vector<string> vUsersData = clsString::split(line, delimiter);

        string firstname = vUsersData[0];
        string lastname = vUsersData[1];
        string email = vUsersData[2];
        string phone = vUsersData[3];
        string username = vUsersData[4];
        string password = clsString::decryptText(vUsersData[5]);
        int permissions = stoi(vUsersData[6]);

        return clsUser(firstname, lastname, email, phone, username, password, permissions);
    }

    static string _convertToLine(clsUser &user, string delimiter = "#//#")
    {
        string line = "";
        line += user.getFirstName() + delimiter;
        line += user.getLastName() + delimiter;
        line += user.getEmail() + delimiter;
        line += user.getPhone() + delimiter;
        line += user.getUsername() + delimiter;
        line += clsString::encryptText(user.getPassword()) + delimiter;
        line += to_string(user.getPermissions());
        return line;
    }

    bool _saveUsers()
    {
        ofstream file(_usersFile, ios::trunc /* absolute clarity */);
        if (file.is_open())
        {
            for (clsUser &user : _users)
            {
                string line = _convertToLine(user);
                file << line << endl;
            }

            file.close();
            return true;
        }

        return false;
    }

public:
    clsUser() : clsPerson("", "", "", ""), _username(""), _password(""), _permissions(0) {}

    clsUser(
        string firstname, string lastname, string email, string phone,
        string username, string password, int permissions)
        : clsPerson(firstname, lastname, email, phone),
          _username(username),
          _password(password),
          _permissions(permissions)
    {
    }

    clsUser(const clsUser &user)
        : clsPerson(user.getFirstName(), user.getLastName(), user.getEmail(), user.getPhone()),
          _username(user.getUsername()),
          _password(user.getPassword()),
          _permissions(user.getPermissions())
    {
    }

    // Setters && Getters
    void setUsername(string username) { _username = username; }
    string getUsername() const { return _username; }

    void setPassword(string password) { _password = password; }
    string getPassword() const { return _password; }

    void setPermissions(int permissions) { _permissions = permissions; }
    int getPermissions() const { return _permissions; }

    static void loadUsers()
    {
        _users.clear();

        ifstream file(_usersFile);

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
                    _users.push_back(_convertToUser(line));
            }
            file.close();
        }
    }

    static clsUser *find(const string &username)
    {
        for (clsUser &user : _users)
        {
            if (user.getUsername() == username)
            {
                return &user;
            }
        }

        return nullptr;
    }

    static clsUser *find(const string &username, const string &password)
    {
        for (clsUser &user : _users)
            if (user.getUsername() == username && user.getPassword() == password)
                return &user;

        return nullptr;
    }

    bool addUser()
    {
        ofstream file(_usersFile, ios::app);
        if (file.is_open())
        {
            string line = _convertToLine(*this);
            file << line << endl;
            _users.push_back(*this);
            file.close();
            return true;
        }

        return false;
    }

    bool deleteUser()
    {
        // Find the client first
        auto it = find_if(_users.begin(), _users.end(),
                          [username = getUsername()](const clsUser &user)
                          {
                              return user.getUsername() == username;
                          });

        // If not found, return false
        if (it == _users.end())
            return false;

        _users.erase(it);

        return _saveUsers();
    }

    bool updateUser()
    {
        for (clsUser &user : _users)
            if (user.getUsername() == this->getUsername())
            {
                user = *this;
                if (_saveUsers() == true)
                    return true;
                else
                    return false;
            }

        return false;
    }

    static const vector<clsUser> &getAllUsers() { return _users; }

    bool isAuthorized(int choice)
    {
        int binChoice = pow(2, choice);
        if ((getPermissions() & binChoice) == binChoice)
            return true;
        else
            return false;
    }
};

#endif