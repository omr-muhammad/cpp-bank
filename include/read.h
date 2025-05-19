#ifndef READ_H
#define READ_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

namespace read
{

  template <typename inputFlow>
  void handleInput(inputFlow &input)
  {
    if constexpr (is_same_v<inputFlow, string>)
    {
      getline(cin, input);
    }
    else
    {
      cin >> input;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }

  template <typename inputType>
  inputType validatedUserInput(string message)
  {
    inputType input;

    cout << message << endl;

    read::handleInput<inputType>(input);

    while (cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Invalid Input, " << message << endl;

      read::handleInput<inputType>(input);
    }

    return input;
  };

  template <typename typeInRange>
  typeInRange numInRange(string message, typeInRange from, typeInRange to)
  {
    typeInRange num;

    cout << message << endl;
    cin >> num;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (num < from || num > to || cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Invalid Input, " << message << endl;
      cin >> num;
    }

    return num;
  }

  char yesOrNo(string message);
}

#endif