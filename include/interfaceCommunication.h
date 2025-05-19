#pragma once

#ifndef INTERFACE_COMMUNICATION_H
#define INTERFACE_COMMUNICATION_H

#include <string>

using namespace std;

class interfaceCommunication
{
public:
  virtual void sendEmail(string subject, string body) = 0;
  virtual void sendFax(string subject, string body) = 0;
  virtual void sendSMS(string subject, string body) = 0;
};

#endif // INTERFACE_COMMUNICATION_H