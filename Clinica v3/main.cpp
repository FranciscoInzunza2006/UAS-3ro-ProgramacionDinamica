//
// Created by Franc on 26/11/2025.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <ctime>
#include <iomanip>
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
    std::size_t id{};
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string phone_number;
    std::string address;
};

std::size_t appointment_next_id = 0;

struct Appointment
{
    std::size_t id{};
    std::size_t patient_id{};

    std::string foo;
};

// Globals
std::vector<User> users;
std::vector<Patient> patients;
std::vector<Appointment> appointments;

const User* logged_user;

//region Prototypes
bool loadData();
bool saveData();

void mainMenu();
void registerPatient();
void queryPatient();
void showPatients();

void patientMenu(Patient& patient);
void doCheckup(const Patient& patient);
void showHistory(const Patient& patient);
void modifyPatient(Patient& patient);
void deletePatient(const Patient& patient);

bool login();
//endregion

int main()
{
    system("chcp 65001 && cls");
    if (!loadData())
    {
        std::cout << "Un error ocurrió cargando los datos.";
        return 1;
    }

    logged_user = &users[0];
    //if (!login()) return 1;

    mainMenu();

    saveData();
    return 0;
}

//region Main menu
void mainMenu()
{
    const bool is_admin = logged_user->id == 1;
    while (true)
    {
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

        switch (option)
        {
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
    if (patients.empty())
    {
        std::cout << "No hay pacientes registrados.\n";
        return;
    }

    // Field size
    constexpr int ID_FS = 4;
    constexpr int NAME_FS = 35;
    constexpr int EMAIL_FS = 25;
    constexpr int PHONE_FS = 11;
    constexpr int ADDRESS_FS = 30;

    std::cout << std::left << std::setw(ID_FS) << "ID" << ' ';
    std::cout << std::setw(NAME_FS) << "Nombre completo";
    std::cout << std::setw(EMAIL_FS) << "Correo";
    std::cout << std::setw(PHONE_FS) << "Telefono";
    std::cout << std::setw(ADDRESS_FS) << "Dirección";
    std::cout << std::endl;

    for (const auto& p : patients)
    {
        std::cout << std::right << std::setw(ID_FS) << std::setfill('0') << p.id << std::setfill(' ') << std::left <<
            ' ';
        std::cout << std::setw(NAME_FS) << (p.first_name + ' ' + p.last_name);
        std::cout << std::setw(EMAIL_FS) << p.email;
        std::cout << std::setw(PHONE_FS) << p.phone_number;
        std::cout << std::setw(ADDRESS_FS) << p.address;
        std::cout << '\n';
    }

    std::cout << std::right;
}

//endregion

//region Patient menu
void patientMenu(Patient& patient)
{
    enum OPTIONS
    {
        CHECKUP = 1,
        HISTORY,
        MODIFY,
        DELETE,
        EXIT,
    };

    while (true)
    {
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
        std::cout << "  (" << CHECKUP << ") Realizar chequeo\n";
        std::cout << "  (" << HISTORY << ") Mostrar historial medico\n";
        std::cout << "  (" << MODIFY << ") Modificar información\n";
        std::cout << "  (" << DELETE << ") Eliminar paciente\n";
        std::cout << "  (" << EXIT << ") Salir\n";

        separator();
        const int option = input::getIntRange(1, EXIT);
        if (option == EXIT) return;

        separator();
        switch (option)
        {
        case CHECKUP:
            doCheckup(patient);
            break;

        case HISTORY:
            showHistory(patient);
            break;

        case MODIFY:
            modifyPatient(patient);
            break;

        case DELETE:
            deletePatient(patient);
            std::cout << "Paciente eliminado.\n";
            return;

        default: ;
        }
        separator();
        input::waitForInput();
    }
}

void doCheckup(const Patient& patient)
{
    Appointment a;

    std::cin.ignore();
    a.foo = input::getLine("Imagina que realizamos la consulta, escribe el resultado: ");

    a.id = ++appointment_next_id;
    a.patient_id = patient.id;

    appointments.push_back(a);
}

void showHistory(const Patient& patient)
{
    bool has_history = false;
    for (const auto& appointment : appointments)
    {
        if (appointment.patient_id == patient.id)
        {
            has_history = true;
            std::cout << "ID: " << appointment.id << " COSO: " << appointment.foo << '\n';
        }
    }

    if (!has_history)
    {
        std::cout << "El historial esta vacio.\n";
    }
}

void deletePatient(const Patient& patient)
{
    int index = 0;
    for (const auto& p : patients)
    {
        if (p.id == patient.id) break;
        index++;
    }
    patients.erase(patients.begin() + index);

    // If the id is -1 the patient won't be saved... Nah, just nuke it
    //patient.id = -1;
}

void modifyPatient(Patient& patient)
{
    std::cin.ignore();
    std::string new_name = input::getLine("Ingrese el nombre (deje en blanco para conservar): ");
    if (!new_name.empty())
    {
        patient.first_name = new_name;
    }

    std::string new_last_name = input::getLine("Ingrese los apellidos (deje en blanco para conservar): ");
    if (!new_last_name.empty())
    {
        patient.last_name = new_last_name;
    }

    std::string new_email = input::getLine("Ingrese el correo (deje en blanco para conservar): ");
    if (!new_email.empty())
    {
        patient.email = new_email;
    }

    std::string new_phone_number = input::getLine("Ingrese el numero de telefono (deje en blanco para conservar): ");
    if (!new_phone_number.empty())
    {
        patient.phone_number = new_phone_number;
    }

    std::string new_address = input::getLine("Ingrese la dirección (deje en blanco para conservar): ");
    if (!new_address.empty())
    {
        patient.address = new_address;
    }
}

//endregion

//region Files In Out

// Source - https://stackoverflow.com/a
// Posted by GManNickG, modified by community. See post 'Timeline' for change history
// Retrieved 2025-11-26, License - CC BY-SA 4.0

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
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
    if (!is_empty(file))
    {
        while (!file.eof())
        {
            Patient patient;
            {
                std::string id_buffer;
                std::getline(file, id_buffer, ',');
                patient.id = std::stoull(id_buffer);

                if (patient_next_id < patient.id)
                {
                    patient_next_id = patient.id + 1;
                }
            }
            std::getline(file, patient.first_name, ',');
            std::getline(file, patient.last_name, ',');
            std::getline(file, patient.email, ',');
            std::getline(file, patient.phone_number, ',');
            std::getline(file, patient.address);

            patients.push_back(patient);
        }
    }

    file.close();

    file.open("appointments.data");
    if (!file.is_open())
    {
        std::cout << "Hubo un error abriendo el archivo con la citas realizadas.\n";
        return false;
    }
    if (!is_empty(file))
    {
        while (!file.eof())
        {
            Appointment appointment;
            {
                std::string id_buffer;
                std::getline(file, id_buffer, ',');
                appointment.id = std::stoull(id_buffer);

                std::getline(file, id_buffer, ',');
                appointment.patient_id = std::stoull(id_buffer);

                if (appointment_next_id < appointment.id)
                {
                    appointment_next_id = appointment.id + 1;
                }
            }
            std::getline(file, appointment.foo);

            appointments.push_back(appointment);
        }
    }

    file.close();

    return true;
}

bool saveData()
{
    return true;
}

//endregion

//region Login
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

//endregion
