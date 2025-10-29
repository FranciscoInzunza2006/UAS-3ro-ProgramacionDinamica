//
// Created by Franc on 24/10/2025.
//

#include "clinic.hpp"
#include "patient.hpp"

#include <iostream>

bool Clinic::registerPatient()
{
    patients.push_back(Patient.create());
}

bool Clinic::searchPatient()
{

}

bool Clinic::modifyPatient()
{
}

bool Clinic::deletePatient()
{
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

        for (const auto& user : users)
        {
            if (user.username == username)
            {
                if (user.password == password)
                {
                    std::cout << "Bienvenido " << username << ".\n";
                    return true;
                }

                std::cout << "Usuario o contraseña inválidos.\n";
                return false;
            }
        }
        std::cout << "Usuario o contraseña inválidos.\n";
    }

    std::cout << "Máximo numero de intentos alcanzado.\n";
    return false;
}

void Clinic::mainMenu()
{

}
