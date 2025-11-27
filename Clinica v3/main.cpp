//
// Created by Franc on 26/11/2025.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <ctime>
#include <optional>
#include <vector>

#include "util.hpp"

struct User
{
    std::size_t id;
    std::string username;
    std::string password;
};

std::size_t patient_next_id = 0;
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
void patientMenu(Patient& patient);

void registerPatient();
void queryPatient();
void showPatients();

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
    logged_user = &users[0];
    //if (!login()) return 1;

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
            registerPatient();
            break;

        case 2:
            queryPatient();
            break;

        case 3:
            showPatients();
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

void patientMenu(Patient& patient)
{
    while (true) {
        std::system("cls");

        separator();
        std::cout << "Menu de paciente\n";
        separator();
        std::cout << "ID: " << patient.id << "\n";
        std::cout << "Nombre completo: " << patient.first_name << ' ' << patient.last_name << "\n";
        std::cout << "Correo: " << patient.email << "\n";
        std::cout << "Teléfono: " << patient.phone_number << "\n";
        std::cout << "Dirección: " << patient.address << "\n";
        separator();
        std::cout << "  (1) Realizar chequeo\n";
        std::cout << "  (2) Modificar información\n";
        std::cout << "  (3) Eliminar paciente\n";
        std::cout << "  (4) Salir\n";

        separator();
        const int option = input::getIntRange(1, 4);
        if (option == 4) return;

        separator();
        switch (option) {
        case 1:

            break;

        case 2:

            break;

        case 3:

            break;

        default: ;
        }
        separator();
        input::waitForInput();
    }
}

bool loadData()
{
    if (users.empty())
    {
        users.push_back({1, "admin", "admin"});
    }

    std::ifstream file;

    // Pacientes
    file.open("patients.data");
    if (!file.is_open())
    {
        std::cout << "Hubo un error abriendo el archivo con la información de los pacientes.\n";
        return false;
    }
    while (!file.eof())
    {
        Patient patient;
        {
            std::string id_buffer;
            std::getline(file, id_buffer, ',');
            patient.id = std::stoull(id_buffer);
        }
        std::getline(file, patient.first_name, ',');
        std::getline(file, patient.last_name, ',');
        std::getline(file, patient.email, ',');
        std::getline(file, patient.phone_number, ',');
        std::getline(file, patient.address);

        patients.push_back(patient);
    }

    return true;
}

bool saveData()
{
    return true;
}

void registerPatient()
{
    constexpr int PHONE_NUMBER_LENGTH = 10;
    Patient patient;
    patient.id = ++patient_next_id;

    patient.first_name = input::getString("Ingresa el nombre del paciente: ");
    patient.last_name = input::getString("Ingresa los apellidos: ");

    patient.email = input::getString("Ingresa el correo: ");
    patient.phone_number = input::getStringMaxLength(PHONE_NUMBER_LENGTH, "Ingresa el numero de telefono: ");
    patient.address = input::getString("Ingresa la dirección: ");

    std::cout << "El paciente se ha registrado con la id: " << patient.id << std::endl;

    patients.push_back(patient);
}

void queryPatient()
{
    // Search by name too
    const std::size_t needle = input::getInt("Ingresa la ID del paciente: ");

    std::optional<Patient> patient;
    for (const auto& p : patients)
    {
        if (p.id == needle)
        {
            patient = p;
            break;
        }
    }

    if (!patient.has_value())
    {
        std::cout << "No se encontró el paciente.\n";
        return;
    }
    patientMenu(patient.value());
}

void showPatients()
{
}
