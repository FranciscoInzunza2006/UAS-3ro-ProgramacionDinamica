//
// Created by Franc on 26/11/2025.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <ctime>
#include <iomanip>
#include <vector>

#include "util.hpp"

//
// Created by Franc on 26/11/2025.
//

// -------------------------------------------------------------
// SystemData: CRTP base class
// Each Derived class gets its own next_id and file_name
// -------------------------------------------------------------
template <typename T>
class SystemData
{
public:
    static inline std::size_t next_id = 0;
    std::size_t id{};

    void assignId()
    {
        id = ++next_id;
    }

    static bool loadAll(std::vector<T>& out)
    {
        std::ifstream file(T::file_name);
        if (!file.is_open())
            return false;

        while (file.peek() != std::ifstream::traits_type::eof())
        {
            T item;

            // Read ID
            std::string id_buf;
            if (!std::getline(file, id_buf, ',')) break;
            item.id = std::stoull(id_buf);

            if (next_id < item.id)
                next_id = item.id;

            // Load derived fields
            if (!T::loadOne(item, file)) break;

            out.push_back(item);
        }
        return true;
    }

    static bool saveAll(const std::vector<T>& items)
    {
        const std::string temp_name = std::string(T::file_name) + ".temp";
        std::ofstream file(temp_name);
        if (!file.is_open()) return false;

        for (const auto& item : items)
        {
            file << item.id << ",";
            T::saveOne(item, file);
            file << "\n";
        }
        return true;
    }

    static void updateFiles()
    {
        const std::string name = T::file_name;
        const std::string temp_name = name + ".temp";
        const std::string backup_name = name + ".bak";

        std::remove(backup_name.c_str());
        std::rename(name.c_str(), backup_name.c_str());
        std::rename(temp_name.c_str(), name.c_str());
    }
};

class User : public SystemData<User>
{
public:
    static constexpr auto file_name = "users.data";

    std::string username;
    std::string password;

    static bool loadOne(User& u, std::istream& file)
    {
        std::getline(file, u.username, ',');
        std::getline(file, u.password);
        return true;
    }

    static void saveOne(const User& u, std::ostream& file)
    {
        file << u.username << "," << u.password;
    }
};

class Client : public SystemData<Client>
{
public:
    static constexpr auto file_name = "patients.data";

    std::string first_name;
    std::string last_name;
    std::string email;
    std::string phone_number;
    std::string address;

    static bool loadOne(Client& p, std::istream& file)
    {
        std::getline(file, p.first_name, ',');
        std::getline(file, p.last_name, ',');
        std::getline(file, p.email, ',');
        std::getline(file, p.phone_number, ',');
        std::getline(file, p.address);
        return true;
    }

    static void saveOne(const Client& p, std::ostream& file)
    {
        file << p.first_name << "," << p.last_name << ","
             << p.email << "," << p.phone_number << ","
             << p.address;
    }
};

class Product : public SystemData<Product>
{
public:
    static constexpr auto file_name = "appointments.data";

    std::size_t patient_id{};
    std::string foo;

    static bool loadOne(Product& a, std::istream& file)
    {
        std::string buf;

        std::getline(file, buf, ',');
        a.patient_id = std::stoull(buf);

        std::getline(file, a.foo);
        return true;
    }

    static void saveOne(const Product& a, std::ostream& file)
    {
        file << a.patient_id << "," << a.foo;
    }
};

class Venta : public SystemData<Venta>
{
public:
    static constexpr auto file_name = "appointments.data";

    std::size_t patient_id{};
    std::string foo;

    static bool loadOne(Venta& a, std::istream& file)
    {
        std::string buf;

        std::getline(file, buf, ',');
        a.patient_id = std::stoull(buf);

        std::getline(file, a.foo);
        return true;
    }

    static void saveOne(const Venta& a, std::ostream& file)
    {
        file << a.patient_id << "," << a.foo;
    }
};

class Detalle : public SystemData<Detalle>
{
public:
    static constexpr auto file_name = "appointments.data";

    std::size_t patient_id{};
    std::string foo;

    static bool loadOne(Detalle& a, std::istream& file)
    {
        std::string buf;

        std::getline(file, buf, ',');
        a.patient_id = std::stoull(buf);

        std::getline(file, a.foo);
        return true;
    }

    static void saveOne(const Detalle& a, std::ostream& file)
    {
        file << a.patient_id << "," << a.foo;
    }
};

// Globals
std::vector<User> users;
std::vector<Client> patients;
std::vector<Product> products;
std::vector<Venta> appointments;
std::vector<Detalle> detalles;

const User* logged_user = nullptr;

//region Prototypes
bool loadData();
bool saveData();

void mainMenu();
void registerPatient();
void queryPatient();
void showPatients();

void patientMenu(Client* patient);
void doCheckup(const Client* patient);
void showHistory(const Client* patient);
void modifyPatient(Client* patient);
void deletePatient(const Client* patient);

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
    if (!login()) return 1;

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
    Client patient;

    patient.assignId();
    patient.first_name = input::getString("Ingresa el nombre del paciente: ");
    patient.last_name = input::getString("Ingresa los apellidos: ");

    patient.email = input::getString("Ingresa el correo: ");
    patient.phone_number = input::getStringMaxLength(PHONE_NUMBER_LENGTH, "Ingresa el numero de telefono: ");

    std::cin.ignore();
    patient.address = input::getLine("Ingresa la dirección: ");

    std::cout << "El paciente se ha registrado con la id: " << patient.id << std::endl;

    patients.push_back(patient);
}

void queryPatient()
{
    // Search by name too
    const std::size_t needle = input::getInt("Ingresa la ID del paciente: ");

    Client* patient = nullptr;
    for (auto& p : patients)
    {
        if (p.id == needle)
        {
            patient = &p;
            break;
        }
    }

    if (patient == nullptr)
    {
        std::cout << "No se encontró el paciente.\n";
        return;
    }
    patientMenu(patient);
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
void patientMenu(Client* patient)
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
        std::cout << "ID: " << patient->id << "\n";
        std::cout << "Nombre completo: " << patient->first_name << ' ' << patient->last_name << "\n";
        std::cout << "Correo: " << patient->email << "\n";
        std::cout << "Teléfono: " << patient->phone_number << "\n";
        std::cout << "Dirección: " << patient->address << "\n";
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

void doCheckup(const Client* patient)
{
    Venta a;

    std::cin.ignore();
    a.foo = input::getLine("Imagina que realizamos la consulta, escribe el resultado: ");

    a.assignId();
    a.patient_id = patient->id;

    appointments.push_back(a);
}

void showHistory(const Client* patient)
{
    bool has_history = false;
    for (const auto& appointment : appointments)
    {
        if (appointment.patient_id == patient->id)
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

void deletePatient(const Client* patient)
{
    patients.erase(std::vector<Client>::const_iterator(patient));

    // If the id is -1 the patient won't be saved... Nah, just nuke it
    //patient.id = -1;
}

void modifyPatient(Client* patient)
{
    std::cin.ignore();
    const std::string new_name = input::getLine("Ingrese el nombre (deje en blanco para conservar): ");
    if (!new_name.empty())
    {
        patient->first_name = new_name;
    }

    const std::string new_last_name = input::getLine("Ingrese los apellidos (deje en blanco para conservar): ");
    if (!new_last_name.empty())
    {
        patient->last_name = new_last_name;
    }

    const std::string new_email = input::getLine("Ingrese el correo (deje en blanco para conservar): ");
    if (!new_email.empty())
    {
        patient->email = new_email;
    }

    const std::string new_phone_number = input::getLine("Ingrese el numero de telefono (deje en blanco para conservar): ");
    if (!new_phone_number.empty())
    {
        patient->phone_number = new_phone_number;
    }

    const std::string new_address = input::getLine("Ingrese la dirección (deje en blanco para conservar): ");
    if (!new_address.empty())
    {
        patient->address = new_address;
    }
}

//endregion

//region Files In Out

bool loadData()
{
    if (!User::loadAll(users))
    {
        User admin;
        admin.assignId();
        admin.username = "admin";
        admin.password = "admin";
        users.push_back(admin);
    }

    if (!Client::loadAll(patients)) return false;
    if (!Venta::loadAll(appointments)) return false;

    return true;
}

bool saveData()
{
    if (!User::saveAll(users)) return false;
    if (!Client::saveAll(patients)) return false;
    if (!Venta::saveAll(appointments)) return false;

    // Replace originals
    User::updateFiles();
    Client::updateFiles();
    Venta::updateFiles();

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
            return false; // Optimization because usernames are unique
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
