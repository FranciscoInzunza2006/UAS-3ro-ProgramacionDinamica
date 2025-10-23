
#include "patient.hpp"

#include <iostream>
#include <string>

#include "util.hpp"
Id next_id = 1;

// TODO: Implement all the other fields
Patient registerPatient() {
    Patient patient;

    patient.id = next_id++;

    patient.name = getString("Ingresa el nombre del paciente:");
    patient.last_name = getString("Ingresa los apellidos: ");

    patient.email = getString("Ingresa el correo: ");
    patient.phone_number = getStringMaxLength(PHONE_NUMBER_LENGTH, "Ingresa el numero de telefono: ");
    patient.address = getString("Ingresa la dirección: ");

    std::cout << "El paciente se ha registrado con la id: " << patient.id << std::endl;

    return patient;
}

// TODO: Print other fields
void printPatient(const Patient& patient) {
    std::cout << "Id: " << patient.id << std::endl;
    std::cout << "Nombre: " << patient.name << std::endl;
    std::cout << "Apellidos: " << patient.last_name << std::endl;
    std::cout << "Correo: " << patient.email << std::endl;
    std::cout << "Numero de telefono: " << patient.phone_number << std::endl;
    std::cout << "Dirección: " << patient.address << std::endl;
}

void updatePatientInfo(Patient& patient) {
    std::string new_name = getStringOrNothing("Ingrese el nombre (deje en blanco para conservar): ");
    if (!new_name.empty()) {
        patient.name = new_name;
    }

    std::string new_last_name = getStringOrNothing("Ingrese los apellidos (deje en blanco para conservar): ");
    if (!new_last_name.empty()) {
        patient.last_name = new_last_name;
    }

    std::string new_email = getStringOrNothing("Ingrese el correo (deje en blanco para conservar): ");
    if (!new_email.empty()) {
        patient.email = new_email;
    }

    std::string new_phone_number = getStringOrNothing("Ingrese el numero de telefono (deje en blanco para conservar): ");
    if (!new_phone_number.empty()) {
        patient.phone_number = new_phone_number;
    }

    std::string new_address = getStringOrNothing("Ingrese la dirección (deje en blanco para conservar): ");
    if (!new_address.empty()) {
        patient.address = new_address;
    }
}