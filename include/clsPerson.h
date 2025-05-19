#pragma once

#ifndef CLSPERSON_H
#define CLSPERSON_H

#include <iostream>
#include <string>

#include "interfaceCommunication.h"

using namespace std;

class clsPerson : public interfaceCommunication
{
private:
  string _firstname;
  string _lastname;
  string _email;
  string _phone;

public:
  clsPerson() {};
  clsPerson(string firstname, string lastname, string email, string phone)
      : _firstname(firstname),
        _lastname(lastname),
        _email(email),
        _phone(phone)
  {
  }

  string getFirstName() const { return _firstname; }
  string getLastName() const { return _lastname; }
  string getFullName() const { return _firstname + " " + _lastname; }
  string getEmail() const { return _email; }
  string getPhone() const { return _phone; }

  void setFirstname(string firstname) { _firstname = firstname; }
  void setLastname(string lastname) { _lastname = lastname; }
  void setEmail(string email) { _email = email; }
  void setPhone(string phone) { _phone = phone; }

  void sendEmail(string subject, string body)
  {
    cout << "Email has been sent to " << _email << endl;
  }

  void sendFax(string subject, string body)
  {
    cout << "Fax has been sent to " << _phone << endl;
  }

  void sendSMS(string subject, string body)
  {
    cout << "Message has been sent to " << _phone << endl;
  }
};

#endif // CLSPERSON_H