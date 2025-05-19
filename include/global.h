#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include "clsUser.h"

clsUser *currentUser = nullptr;
int failedLoginAttempts = 0;

#endif // GLOBAL_H
