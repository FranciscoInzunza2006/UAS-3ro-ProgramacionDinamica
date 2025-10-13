
#include <filesystem>
#include <fstream>
#include <iostream>

#include "clinic.hpp"
#include "patient.hpp"

std::vector<Patient> patients;

bool loadPatientsData() {
    if (!std::filesystem::exists(PATIENTS_DATA)) {
        std::cout << "No existe el archivo con los datos de los pacientes.\n";
        return false;
    }

    std::ifstream file;
    file.open(PATIENTS_DATA, std::fstream::in);
    if (!file.is_open()) {
        std::cout << "Ocurrio un error abriendo el archivo.\n";
        return false;
    }

    Patient patient;
    while (file >> patient.id) {
        file >> patient.name;
        // file >> patient.last_name;
        // file >> patient.birth_date;

        // file >> patient.email;
        // file >> patient.phone_number;
        // file >> patient.address;

        // unsigned int blood_type;
        // file >> blood_type;
        // patient.blood_type = static_cast<BloodType>(blood_type);

        printPatient(patient);
        patients.push_back(patient);
        if (patient.id > next_id)
            next_id = patient.id + 1;
    }

    file.close();
    return true;
}

bool savePatientsData() {
    if (!std::filesystem::exists(SAVE_DIRECTORY)) {
        if (!std::filesystem::create_directory(SAVE_DIRECTORY)) {
            std::cout << "Algo salió mal creando la carpeta para guardar los archivos.\n";
            return false;
        }
    }

    std::ofstream file;
    file.open(PATIENTS_DATA, std::fstream::out);
    if (!file.is_open()) {
        std::cout << "Ocurrio un error guardando el archivo.\n";
        return false;
    }

    for (auto &&patient : patients) {
        file << patient.id << std::endl;

        file << patient.name << std::endl;
        // file << patient.last_name << std::endl;
        // file << patient.birth_date << std::endl;

        // file << patient.email << std::endl;
        // file << patient.phone_number << std::endl;
        // file << patient.address << std::endl;

        // file << patient.blood_type << std::endl;
    }

    file.close();
    return true;
}
