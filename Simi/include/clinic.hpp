//
// Created by Franc on 24/10/2025.
//

#pragma once

#include <string>
#include <iostream>
#include <optional>
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
    std::vector<Appointment> appointments;

    void registerPatient();
    void searchPatient();
    void modifyPatient(Patient& patient);
    void deletePatient(const Patient& patient);

    std::optional<std::reference_wrapper<Patient>> searchPatientById(size_t id);
    std::optional<std::reference_wrapper<Patient>> searchPatientByName(const std::string& name);

    void patientMenu(Patient& patient);
    [[nodiscard]] bool loginAttempt(const std::string& username, const std::string& password) const;

    void makeAppointment(const Patient& patient);
public:
    void printPatients() const;

    bool login() const;
    void mainMenu();

    bool loadUsers();
    bool saveUsers() const;

    bool loadPatients();
    bool savePatients() const;

    bool loadAppointments();
    bool saveAppointments() const;
};
