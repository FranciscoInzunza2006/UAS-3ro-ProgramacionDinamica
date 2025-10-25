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
    const std::string needle = input_handler::getString("Introduce la ID del paciente o su primer nombre o apellido: ");

    if (needle.empty()) return;

    // TODO: Return a reference to the patient
    // TODO: Use std::optional
    size_t patient_index = 0;
    // TODO: Separate in two different functions
    bool search_by_id = std::isdigit(needle[0]);
    if (search_by_id)
    {
        // TODO: Safer conversion
        size_t id = std::stoi(needle);
        for (size_t patient_index_ = 0; patient_index_ < patients.size(); patient_index_++)
        {
            if (patients[patient_index_].getID() == id)
            {
                patient_index = patient_index_;
                break;
            }
        }
    }
    else
    {
        // Remove case sensitive
        for (size_t patient_index_ = 0; patient_index_ < patients.size(); patient_index_++)
        {
            if (patients[patient_index_].getName() == needle || patients[patient_index_].getSurname() == needle)
            {
                patient_index = patient_index_;
                break;
            }
        }
    }

    if (patients[patient_index].getID() != 0)
        patientMenu(patient_index);
    else
        std::cout << "No se encontró el paciente.\n";
}

void Clinic::modifyPatient(const Patient& patient_index)
{
    // TODO: Implement this
}

void Clinic::deletePatient(const size_t patient_index)
{
    // FIXME: Doesn't actually erase the patient and doesn't closes the submenu
    if (input_handler::getBool("¿Seguro que quieres borrar al paciente? "))
        patients.erase(patients.begin() + patient_index);
    else
        std::cout << "No se ha borrado al paciente. \n";
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

void Clinic::patientMenu(const size_t patient_index)
{
    Patient* patient {&patients[patient_index]};
    const auto patient_menu = Menu(patient->getName(), {
                                       {"Realizar chequeo", std::bind(&Clinic::registerPatient, this)},
                                       {"Mostrar más información", std::bind(&Patient::printPatientInfo, patient)},
                                       {"Eliminar paciente", std::bind(&Clinic::deletePatient, this, patient_index)},
                                   });
    patient_menu.show();
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
                                    {"Buscar paciente", std::bind(&Clinic::searchPatient, this)},
                                    {"Mostrar pacientes registrados", std::bind(&Clinic::printPatients, this)},
                                });

    main_menu.show();
}
