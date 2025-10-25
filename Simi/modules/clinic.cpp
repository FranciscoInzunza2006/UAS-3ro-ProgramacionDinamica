//
// Created by Franc on 24/10/2025.
//

#include "clinic.hpp"
#include "patient.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "input_handler.hpp"
#include "menu.hpp"

void Clinic::registerPatient()
{
    const auto patient = Patient::create();
    patients.push_back(patient);

    std::cout << "Paciente registrado con la ID: " << patient.getID() << '\n';
}

void Clinic::searchPatient()
{

}

void Clinic::modifyPatient()
{
}

void Clinic::deletePatient()
{
}

void Clinic::printPatients() const
{
    // TODO: Print as a cool looking table
    for (auto&& patient : patients)
    {
        std::cout << '#' << patient.getID() << ' ' << patient.getName() << '\n';
    }
}

bool Clinic::loginAttempt(const std::string& username, const std::string& password) const
{
    for (const auto& user : users)
    {
        if (user.username == username)
        {
            return user.username == password;
        }
    }
    return false;
}

bool Clinic::login()
{
    users.push_back(User("admin", "admin"));
    users.push_back(User("Francisco", "12345678"));

    for (int attempt = 0; attempt < MAX_LOGIN_ATTEMPTS; attempt++)
    {
        const std::string username = input_handler::getString("Ingresa tu usuario: ");
        const std::string password = input_handler::getString("Ingresa tu contraseña: ");

        if (loginAttempt(username, password))
        {
            std::cout << "Bienvenido " << username << ".\n";
            return true;
        }

        std::cout << "Usuario o contraseña inválidos.\n";
    }

    std::cout << "Máximo numero de intentos alcanzado.\n";
    return false;
}

void Clinic::mainMenu()
{
    // TODO: This doesn't work when functions are private, search a way to make it work.
    // std::bind is there since registerPatient isn't static so it needs the object
    const auto main_menu = Menu("Clinica \"El Simi\"", {
        {"Registrar paciente", std::bind(&Clinic::registerPatient, this)},
        {"Buscar paciente", std::bind(&Clinic::registerPatient, this)},
        {"Mostrar pacientes registrados", std::bind(&Clinic::printPatients, this)},
    });

    main_menu.show();
}
