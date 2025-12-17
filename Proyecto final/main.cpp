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
    static constexpr auto file_name = "clients.data";

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
    static constexpr auto file_name = "products.data";

    std::size_t product_id{};
    std::string name;
    float price{};
    std::string provider_name;

    static bool loadOne(Product& a, std::istream& file)
    {
        std::string buf;

        std::getline(file, buf, ',');
        a.product_id = std::stoull(buf);

        std::getline(file, a.name, ',');

        std::getline(file, buf, ',');
        a.price = std::stof(buf);

        std::getline(file, a.provider_name);
        return true;
    }

    static void saveOne(const Product& a, std::ostream& file)
    {
        file << a.product_id << "," << a.name << ',' << a.price << "," << a.provider_name;
    }
};

class Venta : public SystemData<Venta>
{
public:
    static constexpr auto file_name = "sells.data";

    std::size_t client_id{};
    std::size_t user_id{};
    std::time_t timestamp{};
    float total{};

    static bool loadOne(Venta& v, std::istream& file)
    {
        std::string buf;

        std::getline(file, buf, ',');
        v.client_id = std::stoull(buf);
        std::getline(file, buf, ',');
        v.user_id = std::stoull(buf);
        std::getline(file, buf, ',');
        v.timestamp = std::stoll(buf);
        std::getline(file, buf);
        v.total = std::stof(buf);

        return true;
    }

    static void saveOne(const Venta& v, std::ostream& file)
    {
        file << v.client_id << ","
            << v.user_id << ","
            << v.timestamp << ","
            << v.total;
    }
};

class Detalle : public SystemData<Detalle>
{
public:
    static constexpr auto file_name = "details.data";

    std::size_t venta_id{};
    std::size_t product_id{};
    int quantity{};
    float unit_price{};

    static bool loadOne(Detalle& d, std::istream& file)
    {
        std::string buf;

        std::getline(file, buf, ','); d.venta_id   = std::stoull(buf);
        std::getline(file, buf, ','); d.product_id = std::stoull(buf);
        std::getline(file, buf, ','); d.quantity   = std::stoi(buf);
        std::getline(file, buf);      d.unit_price = std::stof(buf);

        return true;
    }

    static void saveOne(const Detalle& d, std::ostream& file)
    {
        file << d.venta_id << ","
             << d.product_id << ","
             << d.quantity << ","
             << d.unit_price;
    }
};

// Globals
std::vector<User> users;
std::vector<Client> clients;
std::vector<Product> products;
std::vector<Venta> ventas;
std::vector<Detalle> detalles;

const User* logged_user = nullptr;

//region Prototypes
bool loadData();
bool saveData();

void registerSell();
void querySells();

void mainMenu();

void registerPatient();
void queryPatient();
void showAllClients();

void clientMenu(Client* patient);
void doCheckup(const Client* patient);
void showHistory(const Client* patient);
void modifyClient(Client* patient);
void deleteClient(const Client* patient);

void showAllProducts();
void registerProduct();
void queryProduct();
void productMenu(Product* product);
void modifyProduct(Product* product);
void deleteProduct(const Product* product);

Client* findClientById(std::size_t id);
Product* findProductById(std::size_t id);

bool login();
//endregion

int main()
{
    system("chcp 65001 && cls");
    if (!loadData())
    {
        std::cout << "Un error ocurrió cargando los datos.\n";
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
        std::cout << "Tiendas el Paco\n";
        separator();
        std::cout << "  (1) Realizar venta\n";
        std::cout << "  (2) Historial de ventas\n";
        std::cout << "  (3) Clientes\n";
        std::cout << "  (4) Productos\n";
        std::cout << "  (5) Salir\n";
        // Admin menu
        if (is_admin)
        {
            //std::cout << "  (6) Consultar usuarios\n";
        }

        separator();
        const int option = input::getIntRange(1, is_admin ? 6 : 5);
        separator();

        switch (option)
        {
        case 1:
            registerSell();
            break;

        case 2:
            querySells();
            break;

        case 3:
            showAllClients();
            break;

        case 4:
            showAllProducts();
            break;

        case 5:
            std::cout << "Hasta pronto!\n";
            return;

        case 6:
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

    clients.push_back(patient);
}

void queryPatient()
{
    // Search by name too
    const std::string needle = input::getString("Ingresa la ID del paciente o su Nombre: ");

    std::size_t needle_id;
    try
    {
        needle_id = std::stoul(needle);
    }
    catch (const std::exception& e)
    {
        needle_id = -1;
    }


    Client* patient = nullptr;
    for (auto& p : clients)
    {
        if (p.id == needle_id || p.first_name.find(needle) != std::string::npos || p.last_name.find(needle) !=
            std::string::npos)
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
    clientMenu(patient);
}

void showAllClients()
{
    if (clients.empty())
    {
        std::cout << "No hay pacientes registrados.\n";
        goto menu;
    }

    //region Print all patients
    {
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

        for (const auto& p : clients)
        {
            std::cout << std::right << std::setw(ID_FS) << std::setfill('0') << p.id << std::setfill(' ') << std::left
                <<
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

menu:
    separator();
    std::cout << "  (1) Consultar cliente\n";
    std::cout << "  (2) Dar de alta a un cliente\n";
    std::cout << "  (3) Salir\n";
    separator();
    const int option = input::getIntRange(1, 3);
    if (option == 3) return;

    separator();
    switch (option)
    {
    case 1:
        queryPatient();
        break;

    case 2:
        registerPatient();
        break;
    default: ;
    }
    //separator();
    //input::waitForInput();
}

//endregion

//region Clientes
void clientMenu(Client* patient)
{
    enum OPTIONS
    {
        HISTORY = 1,
        MODIFY,
        DELETE,
        EXIT,
    };

    while (true)
    {
        std::system("cls");

        separator();
        std::cout << "Menu de cliente\n";
        separator();
        std::cout << "ID: " << patient->id << "\n";
        std::cout << "Nombre completo: " << patient->first_name << ' ' << patient->last_name << "\n";
        std::cout << "Correo: " << patient->email << "\n";
        std::cout << "Teléfono: " << patient->phone_number << "\n";
        std::cout << "Dirección: " << patient->address << "\n";
        separator();
        std::cout << "  (" << HISTORY << ") Mostrar historial de compras\n";
        std::cout << "  (" << MODIFY << ") Modificar información\n";
        std::cout << "  (" << DELETE << ") Eliminar paciente\n";
        std::cout << "  (" << EXIT << ") Salir\n";

        separator();
        const int option = input::getIntRange(1, EXIT);
        if (option == EXIT) return;

        separator();
        switch (option)
        {
        case HISTORY:
            //showHistory(patient);
            break;

        case MODIFY:
            modifyClient(patient);
            break;

        case DELETE:
            deleteClient(patient);
            std::cout << "Cliente eliminado.\n";
            return;

        default: ;
        }
        separator();
        input::waitForInput();
    }
}

void deleteClient(const Client* patient)
{
    clients.erase(std::vector<Client>::const_iterator(patient));

    // If the id is -1 the patient won't be saved... Nah, just nuke it
    //patient.id = -1;
}

void modifyClient(Client* patient)
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

    const std::string new_phone_number = input::getLine(
        "Ingrese el numero de telefono (deje en blanco para conservar): ");
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

Client* findClientById(std::size_t id)
{
    for (auto& c : clients)
        if (c.id == id)
            return &c;
    return nullptr;
}

Product* findProductById(std::size_t id)
{
    for (auto& p : products)
        if (p.id == id)
            return &p;
    return nullptr;
}

void registerSell()
{
    if (clients.empty() || products.empty())
    {
        std::cout << "Debe haber clientes y productos registrados.\n";
        return;
    }

    // 1. Select client
    const std::size_t client_id = input::getInt("ID del cliente: ");
    Client* client = findClientById(client_id);

    if (!client)
    {
        std::cout << "Cliente no encontrado.\n";
        return;
    }

    Venta venta;
    venta.assignId();
    venta.client_id = client->id;
    venta.user_id = logged_user->id;
    venta.timestamp = std::time(nullptr);
    venta.total = 0.0f;

    std::vector<Detalle> detalles_tmp;

    // 2. Add products
    while (true)
    {
        const std::size_t product_id = input::getInt("ID del producto (0 para terminar): ");
        if (product_id == 0) break;

        Product* product = findProductById(product_id);
        if (!product)
        {
            std::cout << "Producto no encontrado.\n";
            continue;
        }

        const int quantity = input::getIntRange(1, 1000, "Unidades: ");

        Detalle d;
        d.assignId();
        d.venta_id = venta.id;
        d.product_id = product->id;
        d.quantity = quantity;
        d.unit_price = product->price;

        venta.total += quantity * product->price;
        detalles_tmp.push_back(d);

        std::cout << product->name << 'x' << quantity << " agregado.\n";
    }

    if (detalles_tmp.empty())
    {
        std::cout << "Venta cancelada (sin productos).\n";
        return;
    }

    // 3. Persist
    ventas.push_back(venta);
    for (auto& d : detalles_tmp)
        detalles.push_back(d);

    std::cout << "Venta registrada. Total: $" << venta.total << "\n";
}

void querySells()
{
    if (ventas.empty())
    {
        std::cout << "No hay ventas registradas.\n";
        return;
    }

    for (const auto& v : ventas)
    {
        const Client* c = findClientById(v.client_id);

        std::cout << "Venta ID: " << v.id << "\n";
        std::cout << "Cliente: "
                  << (c ? c->first_name + " " + c->last_name : "Desconocido")
                  << "\n";

        std::cout << "Fecha: "
                  << std::put_time(std::localtime(&v.timestamp), "%d/%m/%Y %H:%M")
                  << "\n";

        std::cout << "Total: $" << v.total << "\n";
        std::cout << "Productos:\n";

        for (const auto& d : detalles)
        {
            if (d.venta_id == v.id)
            {
                const Product* p = findProductById(d.product_id);
                std::cout << "  - "
                          << (p ? p->name : "Producto eliminado")
                          << " x" << d.quantity
                          << " ($" << d.unit_price << ")\n";
            }
        }

        separator();
    }
}

//region Productos
void showAllProducts()
{
    if (products.empty())
    {
        std::cout << "No hay productos registrados.\n";
        goto menu;
    }

    //region Print all products
    {
        // Field size
        constexpr int ID_FS = 4;
        constexpr int NAME_FS = 35;
        constexpr int PRICE_FS = 8;
        constexpr int PROVIDER_FS = 35;

        std::cout << std::left << std::setw(ID_FS) << "ID" << ' ';
        std::cout << std::setw(NAME_FS) << "Nombre";
        std::cout << std::setw(PRICE_FS) << "Precio";
        std::cout << std::setw(PROVIDER_FS) << "Proveedor";
        std::cout << std::endl;

        for (const auto& p : products)
        {
            std::cout << std::right << std::setw(ID_FS) << std::setfill('0') << p.id << std::setfill(' ') << std::left
                <<
                ' ';
            std::cout << std::setw(NAME_FS) << p.name;
            std::cout << std::setw(PRICE_FS) << p.price;
            std::cout << std::setw(PROVIDER_FS) << p.provider_name;
            std::cout << '\n';
        }

        std::cout << std::right;
    }
    //endregion

menu:
    separator();
    std::cout << "  (1) Consultar producto\n";
    std::cout << "  (2) Dar de alta un producto\n";
    std::cout << "  (3) Salir\n";
    separator();
    const int option = input::getIntRange(1, 3);
    if (option == 3) return;

    separator();
    switch (option)
    {
    case 1:
        queryProduct();
        break;

    case 2:
        registerProduct();
        break;
    default: ;
    }
}

void queryProduct()
{
    // Search by name too
    const std::string needle = input::getString("Ingresa la ID del producto o su Nombre: ");

    std::size_t needle_id;
    try
    {
        needle_id = std::stoul(needle);
    }
    catch (const std::exception& e)
    {
        needle_id = -1;
    }


    Product* product = nullptr;
    for (auto& p : products)
    {
        if (p.id == needle_id || p.name.find(needle) != std::string::npos)
        {
            product = &p;
            break;
        }
    }

    if (product == nullptr)
    {
        std::cout << "No se encontró el producto.\n";
        return;
    }
    productMenu(product);
}

void registerProduct()
{
    Product product;
    product.assignId();

    std::cin.ignore();
    product.name = input::getLine("Ingresa el nombre del producto: ");

    product.price = input::getFloat("Ingresa el precio del producto: ");

    std::cin.ignore();
    product.provider_name = input::getLine("Ingresa el proveedor: ");

    std::cout << "El producto se ha registrado con la id: " << product.id << std::endl;
    products.push_back(product);
}

void productMenu(Product* product)
{
    enum OPTIONS
    {
        MODIFY = 1,
        DELETE,
        EXIT,
    };

    while (true)
    {
        std::system("cls");

        separator();
        std::cout << "Menu de producto\n";
        separator();
        std::cout << "ID: " << product->id << "\n";
        std::cout << "Nombre: " << product->name << "\n";
        std::cout << "Precio: $" << product->price << "\n";
        std::cout << "Proveedor: " << product->provider_name << "\n";
        separator();
        std::cout << "  (" << MODIFY << ") Modificar información\n";
        std::cout << "  (" << DELETE << ") Eliminar paciente\n";
        std::cout << "  (" << EXIT << ") Salir\n";

        separator();
        const int option = input::getIntRange(1, EXIT);
        if (option == EXIT) return;

        separator();
        switch (option)
        {
        case MODIFY:
            modifyProduct(product);
            break;

        case DELETE:
            deleteProduct(product);
            std::cout << "Cliente eliminado.\n";
            return;

        default: ;
        }
        separator();
        input::waitForInput();
    }
}

void deleteProduct(const Product* product)
{
    products.erase(std::vector<Product>::const_iterator(product));

    // If the id is -1 the patient won't be saved... Nah, just nuke it
    //patient.id = -1;
}

void modifyProduct(Product* product)
{
    std::cin.ignore();
    const std::string new_name = input::getLine("Ingrese el nombre (deje en blanco para conservar): ");
    if (!new_name.empty())
    {
        product->name = new_name;
    }

    const std::string new_price = input::getLine("Ingrese el precio (deje en blanco para conservar): ");
    if (!new_price.empty())
    {
        try
        {
            product->price = std::stof(new_price);
        }
        catch (const std::exception&)
        {
            std::cout << "Valor invalido ingresado.\n";
        }
    }

    const std::string new_provider =
        input::getLine("Ingrese el nombre del proveedor (deje en blanco para conservar): ");
    if (!new_provider.empty())
    {
        product->provider_name = new_provider;
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

    if (!Client::loadAll(clients)) return false;
    if (!Product::loadAll(products)) return false;
    if (!Venta::loadAll(ventas)) return false;
    if (Detalle::loadAll(detalles)) return false;

    return true;
}

bool saveData()
{
    if (!User::saveAll(users)) return false;
    if (!Client::saveAll(clients)) return false;
    if (!Venta::saveAll(ventas)) return false;
    if (!Detalle::saveAll(detalles)) return false;
    if (!Product::saveAll(products)) return false;

    // Replace originals
    User::updateFiles();
    Product::updateFiles();
    Client::updateFiles();
    Venta::updateFiles();
    Detalle::updateFiles();

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
