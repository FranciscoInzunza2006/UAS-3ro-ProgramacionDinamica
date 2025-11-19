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
    Patient(size_t id, const std::string& name, const std::string& surname, const std::string& email,
        const std::string& phone, const std::string& address)
        : id(id),
          name(name),
          surname(surname),
          email(email),
          phone(phone),
          address(address)
    {
    }

    //Patient(const Patient& other) = delete;
    //Patient& operator=(const Patient& other) = delete;

    static Patient create();
    void printPatientInfo() const;
    void modifyPatient();

    [[nodiscard]] size_t getID() const { return id; }
    [[nodiscard]] std::string getName() const { return name; }
    [[nodiscard]] std::string getSurname() const { return surname; }
    
    [[nodiscard]] std::string getEmail() const { return email; }
    [[nodiscard]] std::string getPhone() const { return phone; }
    [[nodiscard]] std::string getAddress() const { return address; }

};
