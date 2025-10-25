//
// Created by Franc on 24/10/2025.
//

#pragma once

#include <string>
#include <iostream>
#include  <vector>

#include "user.hpp"

#define MAX_LOGIN_ATTEMPTS 5


class Clinic
{
    std::vector<User> users = std::vector<User>();
    std::vector<int> patients;
public:
    bool login();
};
