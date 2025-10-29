//
// Created by Franc on 24/10/2025.
//

#include "patient.hpp"

#include <iostream>
#include <ostream>

#include "input_handler.hpp"

size_t next_id = 1;

Patient Patient::create()
{
    Patient patient;

    patient.name = input_handler::getString("Ingresa el nombre del paciente: ");
    patient.surname = input_handler::getString("Ingresa los apellidos: ");

    patient.email = input_handler::getString("Ingresa el correo: ");
    patient.phone = input_handler::getStringMaxLength(PHONE_NUMBER_LENGTH, "Ingresa el numero de telefono: ");
    patient.address = input_handler::getString("Ingresa la dirección: ");

    //std::cout << "El paciente se ha registrado con la id: " << patient.id << std::endl;

    return patient;
}

void Patient::printPatientInfo() const
{
    std::cout << "ID: #" << id << '\n';
    std::cout << "Nombre completo: " << name << ' ' << surname << '\n';
    std::cout << "Correo: " << email << '\n';
    std::cout << "Numero de teléfono: " << phone << '\n';
    std::cout << "Dirección: " << address << '\n';
}

void Patient::modifyPatient()
{
    std::string new_name = input_handler::getStringOrNothing("Ingrese el nombre (deje en blanco para conservar): ");
    if (!new_name.empty()) {
        name = new_name;
    }

    std::string new_last_name = input_handler::getStringOrNothing("Ingrese los apellidos (deje en blanco para conservar): ");
    if (!new_last_name.empty()) {
        surname = new_last_name;
    }

    std::string new_email = input_handler::getStringOrNothing("Ingrese el correo (deje en blanco para conservar): ");
    if (!new_email.empty()) {
        email = new_email;
    }

    std::string new_phone_number = input_handler::getStringOrNothing("Ingrese el numero de telefono (deje en blanco para conservar): ");
    if (!new_phone_number.empty()) {
        phone = new_phone_number;
    }

    std::string new_address = input_handler::getStringOrNothing("Ingrese la dirección (deje en blanco para conservar): ");
    if (!new_address.empty()) {
        address = new_address;
    }
}
