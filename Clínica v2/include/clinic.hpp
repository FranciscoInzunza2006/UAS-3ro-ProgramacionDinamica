//
// Created by Franc on 24/10/2025.
//

#pragma once

#include <string>
#include <iostream>
#include  <vector>

#define MAX_LOGIN_ATTEMPTS 5

typedef struct
{
    std::string username;
    std::string password;
} User;

class Clinic
{
    std::vector<User> users = std::vector<User>();
    std::vector<int> patients;

    bool registerPatient();
    bool searchPatient();
    bool modifyPatient();
    bool deletePatient();

public:
    bool login();
    void mainMenu();
};
