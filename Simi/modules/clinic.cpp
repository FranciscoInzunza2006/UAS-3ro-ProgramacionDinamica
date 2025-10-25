//
// Created by Franc on 24/10/2025.
//

#include "clinic.hpp"
#include "patient.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "menu.hpp"
#include "print+.hpp"

void Clinic::registerPatient()
{
    patients.push_back(Patient::create());
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

bool Clinic::loginAttempt(const std::string& username, const std::string& password) const
{
    for (const auto& user : users)
    {
        if (user.username == username)
        {
            if (user.password == password)
            {
                return true;
            }
            return false;
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
        std::string username;
        std::cout << "Ingresa tu usuario: ";
        std::cin >> username;

        std::string password;
        std::cout << "Ingresa tu contraseña: ";
        std::cin >> password;

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
    // std::bind is there since registerPatient isn't static so it needs the object
    const auto main_menu = Menu("Clinica \"El Simi\"", {
        {"Registrar paciente", std::bind(&Clinic::registerPatient, this)}
    });

    main_menu.show();
}
