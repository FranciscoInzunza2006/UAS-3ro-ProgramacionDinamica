
#pragma once

#include <vector>

#include "patient.hpp"

#define SAVE_DIRECTORY "./simi/"
#define PATIENTS_DATA SAVE_DIRECTORY "patients.txt"
#define APPOINTMENTS_DATA SAVE_DIRECTORY "appointments.txt"

extern std::vector<Patient> patients;

bool loadPatientsData();
bool savePatientsData();
