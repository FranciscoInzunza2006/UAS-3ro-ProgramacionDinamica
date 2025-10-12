
#pragma once

#include <ctime>
#include <string>
#include <vector>

#include "appointment.hpp"
#include "blood_type.hpp"

#define PHONE_NUMBER_LENGTH 11

typedef unsigned int Id;
typedef char PhoneNumber[PHONE_NUMBER_LENGTH];
typedef std::string Email;

typedef struct _patient {
    Id id;
    std::string name;
    std::string last_name;
    std::time_t birth_date;

    Email email;
    PhoneNumber phone_number;
    std::string address;

    BloodType blood_type;
    std::vector<Appointment> medical_record;
} Patient;

Patient registerPatient();
void printPatient(const Patient& patient);
void updatePatientInfo(Patient& patient);
