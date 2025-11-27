//
// Created by Franc on 26/11/2025.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <ctime>
#include <vector>

#include "util.hpp"

struct User
{
    std::size_t id;
    std::string username;
    std::string password;
};

struct Patient
{
    std::size_t id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string phone_number;
    std::string address;
};

struct Appointment
{
    std::size_t id;
    std::size_t patient_id;

    std::string foo;
};

// Globals
std::vector<User> users;
std::vector<Patient> patients;
std::vector<Appointment> appointments;

const User* logged_user;

bool loadData();
bool saveData();

void mainMenu();
void patientMenu();

bool login();

static void separator()
{
    std::cout << "────────────────────────────────────────────────────────────────\n";
    //std::cout << "-----------------------------------------------" << std::endl;
}

int main()
{
    system("chcp 65001 && cls");
    loadData();

    if (!login()) return 1;

    mainMenu();

    saveData();
    return 0;
}

static bool loginAttempt(const std::string_view username, const std::string_view password)
{
    for (const auto& user : users)
    {
        if (user.username == username)
        {
            if (user.password == password)
            {
                logged_user = &user;
                return true;
            }
        }
    }
    return false;
}

bool login()
{
    constexpr int MAX_ATTEMPTS = 3;
    for (int i = 0; i < MAX_ATTEMPTS; i++)
    {
        const std::string username = input::getString("Ingresa tu usuario: ");
        const std::string password = input::getString("Ingresa tu contraseña: ");

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

void mainMenu()
{
    const bool is_admin = logged_user->id == 1;
    while (true) {
        std::system("cls");

        separator();
        std::cout << "Clinica el SIMI\n";
        separator();
        std::cout << "  (1) Registrar paciente\n";
        std::cout << "  (2) Consultar pacientes\n";
        std::cout << "  (3) Mostrar pacientes registrados\n";
        std::cout << "  (4) Salir\n";
        // Admin menu
        if (is_admin)
        {
            std::cout << "  (5) Consultar usuarios\n";
        }

        separator();
        const int option = input::getIntRange(1, is_admin ? 5 : 4);
        separator();

        switch (option) {
        case 1:
            std::cout << "Añadir paciente.";
            break;

        case 2:
            std::cout << "Consultar pacientes.";
            break;

        case 3:
            std::cout << "Mostrar pacientes registrados.";
            break;

        case 4:
            std::cout << "Hasta pronto!\n";
            return;

        case 5:
            if (!is_admin) continue;
            break;

        default: ;
        }
        separator();
        input::waitForInput();
    }
}

void patientMenu()
{
}

bool loadData()
{
    if (users.size() == 0)
    {
        users.push_back({1, "admin", "admin"});
    }

    return true;
}

bool saveData()
{
    return true;
}
