//
// Created by Franc on 24/10/2025.
//

#include "clinic.hpp"

#include <fstream>
#include <iomanip>

#include "patient.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "input_handler.hpp"
#include "print+.hpp"

void Clinic::makeAppointment(const Patient& patient) {
    bool high_temp = input_handler::getBool("¿Sientes una alta temperatura? (S=1/N=0) : ");
    bool covid = input_handler::getBool("¿Sufriste covid? (S=1/N=0) : ");
    bool diabetes = input_handler::getBool("¿Eres diabetico? (S=1/N=0) : ");
    bool vih = input_handler::getBool("¿Sufres alguna enfermedad de transmisión sexual? (S=1/N=0) : ");
    bool gay = input_handler::getBool("¿Eres gay? (S=1/N=0) : ");

    std::cout << "Gracias por venir.\n";

    appointments.emplace_back(next_id++,patient.getID(),high_temp, diabetes, vih, covid, gay);
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
        std::cout << "| " << std::right << std::setw(IDW) << std::setfill(IDF) << patient.getID() << std::setfill(' ');
        std::cout << "| " << std::left << std::setw(NAMEW) << patient.getName();
        std::cout << "| " << std::left << std::setw(EMAILW) << patient.getEmail();
        std::cout << "| " << std::setw(PHONEW) << patient.getPhone();
        std::cout << "| " << std::left << std::setw(ADDRESSW) << patient.getAddress();
        std::cout << "|\n";
    }
    std::cout << separator << '\n';
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
        std::cout << "(4) Eliminar paciente" << '\n';Wstd::cout << "(5) Mostrar citas del paciente" << '\n';
        std::cout << "(6) Salir" << '\n';

        cool::separator();

        const int chosen_option = input_handler::getIntRange(1, 6);
        if (chosen_option == 6)
            return;

        cool::clearScreen();

        switch (chosen_option)
        {
        case 1:
            makeAppointment(patient);
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

        case 5:
            for (const auto& ap : appointments)
            {
                if (ap.patient_id == patient.getID())
                {

                }
            }
            break;

        default: ;
        }

        input_handler::waitForInput();
    }
}

void Clinic::mainMenu()
{
    while (true)
    {
        cool::clearScreen();

        cool::separator();
        std::cout << "Clinica \"El Simi\"\n";
        cool::separator();

        std::cout << "(1) Registrar paciente" << '\n';
        std::cout << "(2) Buscar paciente" << '\n';
        std::cout << "(3) Mostrar pacientes registrados" << '\n';
        std::cout << "(4) Salir" << '\n';

        cool::separator();

        const int chosen_option = input_handler::getIntRange(1, 4);
        if (chosen_option == 4)
            return;

        cool::clearScreen();

        switch (chosen_option)
        {
        case 1:
            registerPatient();
            break;

        case 2:
            searchPatient();
            break;

        case 3:
            printPatients();
            break;
        default: ;
        }

        input_handler::waitForInput();
    }
}

bool Clinic::login() const
{
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
bool Clinic::loginAttempt(const std::string& username, const std::string& password) const
{
    for (const auto& user : users)
    {
        if (user.username == username)
        {
            return user.password == password;
        }
    }
    return false;
}

/// File stuff
#define PATIENTS_PATH "data.txt"
#define USERS_PATH "users.txt"
#define APPOINTMENTS_PATH "appointments.txt"

bool Clinic::loadUsers()
{
    std::ifstream file(USERS_PATH);
    if (!file)
    {
        std::cout << "No se puedo abrir el archivo con los empleados.\n";
        return false;
    }

    std::string username;
    std::string password;
    while (std::getline(file, username, ','))
    {
        std::getline(file, password);

        users.emplace_back(username, password);
    }
    file.close();
    return true;
}

bool Clinic::saveUsers() const
{
    std::ofstream file(USERS_PATH);
    if (!file)
    {
        std::cout << "No se puedo abrir el archivo para guardar los datos de los empleados.\n";
        return false;
    }

    for (const auto& user : users)
    {
        file << user.username << ',' << user.password << '\n';
    }
    file.close();
    return true;
}

bool Clinic::loadPatients()
{
    std::ifstream file(PATIENTS_PATH);
    if (!file)
    {
        std::cout << "No se puedo abrir el archivo con los datos de los pacientes\n";
        return false;
    }

    std::string id;
    std::string name;
    std::string surname;
    std::string email;
    std::string phone;
    std::string address;
    while (std::getline(file, id))
    {
        std::getline(file, name);
        std::getline(file, surname);
        std::getline(file, email);
        std::getline(file, phone);
        std::getline(file, address);

        patients.emplace_back(std::stoull(id), name, surname, email, phone, address);
    }
    file.close();
    return true;
}

bool Clinic::savePatients() const
{
    std::ofstream file(PATIENTS_PATH);
    if (!file)
    {
        std::cout << "No se puedo abrir el archivo para guardar los datos de los pacientes\n";
        return false;
    }

    for (const auto& patient : patients)
    {
        file << patient.getID() << '\n';
        file << patient.getName() << '\n';
        file << patient.getSurname() << '\n';
        file << patient.getEmail() << '\n';
        file << patient.getPhone() << '\n';
        file << patient.getAddress() << '\n';
    }
    file.close();
    return true;
}

bool Clinic::loadAppointments()
{
    std::ifstream file(APPOINTMENTS_PATH);
    if (!file)
    {
        std::cout << "No se puedo abrir el archivo con los datos de las citas\n";
        return false;
    }

    std::string id;
    std::string patient_id;
    std::string high_temp;
    std::string diabetes;
    std::string vih;
    std::string covid;
    std::string gay;
    while (std::getline(file, id, ','))
    {
        std::getline(file, patient_id, ',');

        std::getline(file, high_temp, ',');
        std::getline(file, diabetes, ',');
        std::getline(file, vih, ',');
        std::getline(file, covid, ',');
        std::getline(file, gay, ',');

        appointments.emplace_back(
            std::stoull(id),
            std::stoull(patient_id),
            high_temp == "1",
            diabetes == "1",
            vih == "1",
            covid == "1",
            gay == "1"
            );
    }
    file.close();
    return true;
}

bool Clinic::saveAppointments() const
{
    std::ofstream file(APPOINTMENTS_PATH);
    if (!file)
    {
        std::cout << "No se puedo abrir el archivo para guardar los datos de las citas\n";
        return false;
    }

    for (const auto& app : appointments)
    {
        file << app.appointment_id << ',' << app.patient_id << ',' << app.high_temp << ',' << app.diabetes << ',' << app.vih << ',' << app.covid << ',' << app.gay << '\n';
    }
    file.close();
    return true;
}

