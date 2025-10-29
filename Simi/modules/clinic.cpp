//
// Created by Franc on 24/10/2025.
//

#include "clinic.hpp"

#include <iomanip>

#include "patient.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "input_handler.hpp"
#include "menu.hpp"
#include "print+.hpp"

void makeAppointment() {
    bool diabetes = input_handler::getBool("¿Eres diabetico? (S=1/N=0) : ");
    bool condicion = input_handler::getBool("¿Cuentas con alguna condicional? (S=1/N=0) : ");
    bool raro = input_handler::getBool("¿Eres furro? (S=1/N=0) : ");
    bool sida = input_handler::getBool("¿Tienes sida? (S=1/N=0) : ");
    bool futuro_tieso = input_handler::getBool("¿Tienes cancer? (S=1/N=0) : ");

    if (futuro_tieso) {
        std::cout << "Lmao, ahí quedaste carnal.\n";
        return;
    }

    if (raro) {
        if (sida) {
            std::cout << "Debiste usar protección.\n";
        } else {
            std::cout << "Usa protección, eres un peligro andante.\n";
        }

        return;
    }

    if (sida) {
        std::cout << "Usa protección siempre, informa a tu pareja y futuras parejas de esta situación\n";
        return;
    }

    if (condicion) {
        std::cout << "Explica más a detalle tu condición para poder recetarte medicamentos acorde.\n";
        return;
    }

    if (diabetes) {
        std::cout << "Pase a la farmacia para darle insulina.\n";
        return;
    }

    std::cout << "Si estabas tan sano, ¿Por qué viniste?\n";
}

void Clinic::registerPatient()
{
    const auto patient = Patient::create();
    patients.push_back(patient);

    std::cout << "Paciente registrado con la ID: " << patient.getID() << '\n';
}

void Clinic::searchPatient()
{
    const std::string needle = input_handler::getString("Introduce la ID del paciente o su primer nombre o apellido: ");

    if (needle.empty()) return;

    // TODO: Cleaner conversion
    std::optional<std::reference_wrapper<Patient>> patient;
    if (std::isdigit(needle[0]))
    {
        const size_t id = std::stoi(needle);
        patient = searchPatientById(id);
    }
    else
    {
        patient = searchPatientByName(needle);
    }

    if (!patient.has_value())
    {
        std::cout << "No se encontró el paciente.\n";
        return;
    }
    patientMenu(patient->get());
}

void Clinic::modifyPatient(Patient& patient)
{
    patient.modifyPatient();
}

std::optional<std::reference_wrapper<Patient>> Clinic::searchPatientById(const size_t id)
{
    // TODO: Binary search
    for (auto& patient : patients)
    {
        if (patient.getID() == id)
        {
            return std::ref(patient);
        }
    }

    return std::nullopt;
}

std::optional<std::reference_wrapper<Patient>> Clinic::searchPatientByName(const std::string& name)
{
    for (size_t patient_index = 0; patient_index < patients.size(); patient_index++)
    {
        Patient& patient = patients[patient_index];
        if (patient.getName() == name || patient.getSurname() == name)
        {
            return patient;
        }
    }

    return std::nullopt;
}

void Clinic::deletePatient(const Patient& patient)
{
    if (!input_handler::getBool("¿Seguro que quieres borrar al paciente? "))
    {
        std::cout << "Se ha cancelado la operación. \n";
        return;
    }

    size_t patient_index;
    for (patient_index = 0; patient_index < patients.size(); patient_index++)
    {
        if (patients[patient_index].getID() == patient.getID())
        {
            break;
        }
    }

    // Close submenu since the patient has been removed
    patients.erase(patients.begin() + patient_index);
}

void Clinic::printPatients() const
{
    const int IDW = 4; // Width
    const char IDF = '0'; // Fill

    const int NAMEW = 25;
    const int EMAILW = 20;
    const int PHONEW = PHONE_NUMBER_LENGTH + 1;
    const int ADDRESSW = 25;

    const std::string headers =
        "| ID  | Nombre                   | Correo              | Teléfono   | Dirección                |";
    const std::string separator = std::string(headers.length() - 2, '-');

    std::cout << separator << '\n';
    std::cout << headers << '\n';
    std::cout << separator << '\n';
    for (auto&& patient : patients)
    {
        std::cout << "| " << std::setw(IDW) << std::setfill(IDF) << patient.getID() << std::setfill(' ');
        std::cout << "| " << std::left << std::setw(NAMEW) << patient.getName();
        std::cout << "| " << std::left << std::setw(EMAILW) << patient.getEmail();
        std::cout << "| " << std::setw(PHONEW) << patient.getPhone();
        std::cout << "| " << std::left << std::setw(ADDRESSW) << patient.getAddress();
        std::cout << "|\n";
    }
    std::cout << separator << '\n';
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

void Clinic::patientMenu(Patient& patient)
{
    // const auto patient_menu = Menu(patient.getName(), {
    //                                    {"Realizar chequeo", [this] { registerPatient(); }},
    //                                    {"Mostrar más información", [patient] { patient.printPatientInfo(); }},
    //                                    {"Modificar información", std::bind(&modifyPatient, patient)},
    //                                    {"Eliminar paciente", [this, patient] { deletePatient(patient); }},
    //                                });

    while (true)
    {
        cool::clearScreen();

        cool::separator();
        std::cout << "Paciente:" << patient.getName() << '\n';
        cool::separator();

        std::cout << "(1) Realizar chequeo" << '\n';
        std::cout << "(2) Mostrar más información" << '\n';
        std::cout << "(3) Modificar información" << '\n';
        std::cout << "(4) Eliminar paciente" << '\n';
        std::cout << "(5) Salir" << '\n';

        cool::separator();

        const int chosen_option = input_handler::getIntRange(1, 5);
        if (chosen_option == 5)
            return;

        cool::clearScreen();

        switch (chosen_option)
        {
        case 1:
            makeAppointment();
            break;

        case 2:
            patient.printPatientInfo();
            break;

        case 3:
            patient.modifyPatient();
            break;

        case 4:
            deletePatient(patient);
            return;
        default: ;
        }

        input_handler::waitForInput();
    }
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
    const auto main_menu = Menu("Clinica \"El Simi\"", {
                                    {"Registrar paciente", [this] { registerPatient(); }},
                                    {"Buscar paciente", [this] { searchPatient(); }},
                                    {"Mostrar pacientes registrados", [this] { printPatients(); }},
                                });

    main_menu.show();
}
