//
// Created by Franc on 24/10/2025.
//

#pragma once

#include <string>
#include <iostream>
#include  <vector>

#include "patient.hpp"

#define MAX_LOGIN_ATTEMPTS 5

typedef struct
{
    std::string username;
    std::string password;
} User;

class Clinic
{
    std::vector<User> users = std::vector<User>();
    std::vector<Patient> patients;

    [[nodiscard]] bool loginAttempt(const std::string& username, const std::string& password) const;
public:
    void registerPatient();
    void searchPatient();
    void modifyPatient();
    void deletePatient();

    void printPatients() const;

    bool login();
    void mainMenu();
};
