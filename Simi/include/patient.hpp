//
// Created by Franc on 24/10/2025.
//

#pragma once
#include <string>

#define PHONE_NUMBER_LENGTH 10

extern size_t next_id;

class Patient
{
    size_t id = next_id++;

    std::string name;
    std::string surname;

    std::string email;
    std::string phone;
    std::string address;

public:
    Patient() = default;
    //Patient(const Patient& other) = delete;
    //Patient& operator=(const Patient& other) = delete;

    static Patient create();
    void printPatientInfo() const;
    void modifyPatient();

    [[nodiscard]] size_t getID() const { return id; }
    [[nodiscard]] std::string getName() const { return name; }
    [[nodiscard]] std::string getSurname() const { return surname; }
};
