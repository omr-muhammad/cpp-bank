#pragma once

#ifndef CLSDATE_H
#define CLSDATE_H

#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class clsDate
{
private:
  int _day;
  int _month;
  int _year;
  tm *_date;

  string _dayName(int wDay) const
  {
    vector<string> daysInWeek = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    return daysInWeek[wDay];
  }

  bool _isLeapYear(int year)
  {
    return (year % 100 != 0 && year % 4 == 0) || year % 400 == 0;
  }

  bool _validDate(clsDate date)
  {
    if (date.getDay() <= 0 || date.getDay() > 31 || date.getMon() <= 0 || date.getMon() > 12 || date.getYear() <= 0)
      return false;

    if ((date.getMon() == 4 || date.getMon() == 6 || date.getMon() == 9 || date.getMon() == 11) && date.getDay() > 30)
      return false;

    if (date.getMon() == 2)
      if ((_isLeapYear(date.getYear()) && date.getDay() > 29) || date.getDay() > 28)
        return false;

    return true;
  }

public:
  clsDate()
  {
    time_t t = time(0);
    tm *now = localtime(&t);
    _date = now;
    _day = now->tm_mday;
    _month = now->tm_mon + 1;
    _year = now->tm_year + 1900;
  }

  clsDate(int day, int month, int year) : _day(day), _month(month), _year(year)
  {
    if (!_validDate(*this))
      throw "Invalid Date";
    else
      _date = new tm{0, 0, 0, day, month - 1, year - 1900};

    if (mktime(_date) == -1)
      throw "Failed to compute date";
  }

  ~clsDate()
  {
    delete _date;
  }

  int getDay() const { return _day; }
  int getMon() const { return _month; }
  int getYear() const { return _year; }
  int getDayOfWeek() const { return _date->tm_wday; }
  int getDayOfYear() const { return _date->tm_yday; }
  int getWeekOfYear() const { return _date->tm_yday / 7; }
  string getDayName() const { return _dayName(_date->tm_wday); }
  string getDate() const
  {
    return to_string(_day) + "/" + to_string(_month) + "/" + to_string(_year);
  }
  string getTime() const
  {
    return to_string(_date->tm_hour) + ":" + to_string(_date->tm_min) + ":" + to_string(_date->tm_sec);
  }
  tm *getFullDate() const { return _date; }

  void printDate() const
  {
    cout << _day << "/" << _month << "/" << _year;
  }

  string loggedDate() const
  {
    return getDate() + " - " + getTime();
  }
};

#endif // CLSDATE_H