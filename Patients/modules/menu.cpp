
#include "menu.hpp"

#include <iostream>

#include "clinic.hpp"
#include "patient.hpp"
#include "util.hpp"

void searchPatient();
void patientMenu(Patient& patient);

void separator();

void systemMenu() {
    while (true) {
        system("cls");

        separator();
        std::cout << "Clinica el SIMI\n";
        separator();
        std::cout << "  (1) Registrar paciente\n";
        std::cout << "  (2) Consultar pacientes\n\n";

        std::cout << "  (3) Programar cita\n";
        std::cout << "  (4) Consultar citas\n\n";

        std::cout << "  (5) Salir\n";
        separator();

        int option = getIntRange(1, 5);
        separator();
        switch (option) {
            case 1:
                patients.push_back(registerPatient());
                break;

            case 2:
                searchPatient();
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                std::cout << "Hasta pronto!\n";
                return;
                break;
        }
        separator();
        waitForInput();
    }
}

void searchPatient() {
    Id id = getInt("Ingrese la ID del paciente: ");
    separator();
    for (auto&& patient : patients) {
        if (patient.id == id) {
            printPatient(patient);
            separator();
            patientMenu(patient);
            return;
        }
    }

    std::cout << "Paciente no encontrado.\n";
}

void patientMenu(Patient& patient) {
    std::cout << "  (1) Modificar información del paciente\n";
    std::cout << "  (2) Consultar citas\n";
    std::cout << "  (3) Eliminar paciente (y citas relacionadas)\n\n";
    std::cout << "  (4) No hacer nada.\n";
    separator();
    int action = getIntRange(1, 4);

    if (action != 4) {
        switch (action) {
            case 1:
                updatePatientInfo(patient);
                separator();
                printPatient(patient);
                break;
                // TODO: Implement other functions
        }
        separator();
    }
}

void separator() {
    std::cout << "────────────────────────────────────────────────────────────────\n";
}