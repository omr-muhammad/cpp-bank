# Bank Project

## Overview

This is a C++ project for managing a banking system. It includes features for handling clients, users, transactions, and logs.

## Features

- User authentication and login
- Client management
- Transaction processing
- Transfer logs
- Comprehensive UI for managing banking operations

## Project Structure

```
.
├── clients.txt
├── logins.txt
├── main.cpp
├── README.md
├── transfer-logs.txt
├── users.txt
├── build/
│   └── output.exe
├── include/
│   ├── clsBankApp.h
│   ├── clsClient.h
│   ├── clsClientUI.h
│   ├── clsDate.h
│   ├── clsLogin.h
│   ├── clsLoginRegister.h
│   ├── clsLoginRegisterUI.h
│   ├── clsMainScreen.h
│   ├── clsPerson.h
│   ├── clsScreen.h
│   ├── clsString.h
│   ├── clsTransactionsScreen.h
│   ├── clsTransferLogs.h
│   ├── clsTransferLogsList.h
│   ├── clsUser.h
│   ├── clsUserUI.h
│   ├── global.h
│   ├── interfaceCommunication.h
│   ├── read.h
│   └── utils.h
└── src/
    ├── global.cpp
    └── read.cpp
```

## Build Instructions

To build the project, use the provided VS Code tasks:

### Build

Run the task `Build C++ Project` to compile the project and generate the executable `output.exe` in the `build/` directory.

### Debug Build

Run the task `Build C++ Project (Debug)` to compile the project with debug symbols and generate the executable `output_debug.exe` in the `build/` directory.

## Usage

1. Run the executable `output.exe`.
2. For Admin Access, use the credentials:
   - Username: `omaho`
   - Password: `1234`
3. For User Access, use the credentials:
   - Username: `bobbrown`
   - Password: `1234`

## Dependencies

- g++ compiler

## License

This project is licensed under the MIT License.
