
#include "patient.hpp"

#include <iostream>
#include <string>

#include "util.hpp"
static Id next_id = 1;

// TODO: Implement all the other fields
Patient registerPatient() {
    Patient patient;

    std::string name;
    std::cout << "Ingrese el nombre: ";
    std::cin >> name;

    // Email email;
    // std::cout << "Ingrese el correo: ";
    // std::cin >> email;

    patient.id = next_id++;
    patient.name = name;
    // patient.email = email;

    std::cout << "El paciente se ha registrado con la id: " << patient.id << std::endl;

    return patient;
}

// TODO: Print other fields
void printPatient(const Patient& patient) {
    std::cout << "Id: " << patient.id << std::endl;
    std::cout << "Nombre: " << patient.name << std::endl;
    // std::cout << "Correo: " << patient.email << std::endl;
}

void updatePatientInfo(Patient& patient) {
    std::string new_name = getStringOrNothing("Ingrese el nuevo nombre (deje en blanco para conservar): ");
    if (!new_name.empty()) {
        patient.name = new_name;
    }
}