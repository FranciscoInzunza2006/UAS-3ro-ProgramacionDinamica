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
    void patientMenu(const size_t patient_index);
public:
    void registerPatient();
    void searchPatient();
    void modifyPatient(const Patient& patient);
    void deletePatient(size_t patient_index);

    void printPatients() const;

    bool login();
    void mainMenu();
};
