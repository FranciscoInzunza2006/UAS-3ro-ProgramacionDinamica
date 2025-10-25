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
    // TODO: The other fields, better if we format them a bit
}

void Patient::modifyPatient()
{
    return;
}
