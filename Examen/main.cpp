//
// Created by Franc on 03/12/2025.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"

std::size_t next_id = 0;

struct Book {
    std::size_t id{};
    std::string title;
    std::string author;
    int release_year{};
    int pages_count{};
    float price{};
};

std::vector<Book> books;
constexpr auto SAVE_PATH = "books.data";

bool load();
bool save();

void registerBook();
void showBooks();

void queryBook();
void bookMenu();

void modify_book(Book* book);
void delete_book(Book* book);

int main() {
    load();

    bool running = true;
    while (running) {
        std::system("cls");

        separator();
        std::cout << "Biblioteca Paco\n";
        separator();
        std::cout << "  (1) Registrar libro\n";
        std::cout << "  (2) Consultar libros\n";
        std::cout << "  (3) Salir\n";

        separator();
        const int option = input::getIntRange(1, 3);
        separator();

        bool query;
        switch (option) {
            case 1:
                registerBook();
                break;

            case 2:
                showBooks();

                query = input::getInt("¿Realizar consulta? (Sí = 1) : ");
                if (query) queryBook();
                break;

            case 3:
                std::cout << "Hasta pronto!\n";
                running = false;
                break;

            default:;
        }
        separator();
        input::waitForInput();
    }

    if (!save()) return 1;
    return 0;
}

void registerBook() {
    Book book;

    book.id = ++next_id;

    std::cin.ignore();
    book.title = input::getLine("Titulo: ");
    book.author = input::getLine("Autor: ");

    book.release_year = input::getInt("Año de salida: ");
    book.pages_count = input::getInt("Numero de paginas: ");
    std::cout << "Precio: $";
    std::cin >> book.price;

    books.push_back(book);
}

void showBooks() {
    if (books.empty()) {
        std::cout << "No hay hay libros registrados.\n";
        return;
    }

    // Field size
    constexpr int ID_FS = 4;
    constexpr int NAME_FS = 20;
    constexpr int AUTOR_FS = 20;
    constexpr int YEAR_FS = 6;
    constexpr int PAGES_FS = 8;
    constexpr int PRICE_FS = 6;

    std::cout << std::left << std::setw(ID_FS) << "ID" << ' ';
    std::cout << std::setw(NAME_FS) << "Titulo";
    std::cout << std::setw(AUTOR_FS) << "Autor";
    std::cout << std::setw(YEAR_FS) << "Año";
    std::cout << std::setw(PAGES_FS) << "Paginas";
    std::cout << std::setw(PRICE_FS) << "Precio";
    std::cout << std::endl;

    for (const auto& b : books) {
        std::cout << std::right << std::setw(ID_FS) << std::setfill('0') << b.id << std::setfill(' ') << std::left << ' ';
        std::cout << std::setw(NAME_FS) << b.title;
        std::cout << std::setw(AUTOR_FS) << b.author;
        std::cout << std::setw(YEAR_FS) << b.release_year;
        std::cout << std::setw(PAGES_FS) << b.pages_count;
        std::cout << std::setw(PRICE_FS) << b.price;
        std::cout << '\n';
    }

    std::cout << std::right;
}

void queryBook() {
    separator();
    std::size_t id = input::getInt("Ingrese la ID del libro: ");

    Book* b = nullptr;
    int i = 0;
    for (auto& book : books) {
        if (book.id == id) {
            b = &book;
            break;
        }
        i++;
    }

    if (b == nullptr) {
        std::cout << "Libro no encontrado.";
        return;
    }

    separator();
    std::cout << "¿Qué deseas realizar?\n"
                 "  (1) Modificar\n"
                 "  (2) Eliminar\n"
                 "  (3) Nada\n";
    int action = input::getIntRange(1, 3);
    if (action == 3) return;

    separator();
    if (action == 1) {
        modify_book(b);
        return;
    }

    if (action == 2) {
        std::cout << "Borrado.\n";
        books.erase(books.begin() + i);
    }
}

void modify_book(Book* book) {
    std::cin.ignore();
    const std::string title = input::getLine("Ingrese el titulo (deje en blanco para conservar): ");
    if (!title.empty()) {
        book->title = title;
    }

    const std::string author = input::getLine("Ingrese el autor (deje en blanco para conservar): ");
    if (!author.empty()) {
        book->author = author;
    }

    const std::string release_year = input::getLine("Ingrese el año de publicación (deje en blanco para conservar): ");
    if (!release_year.empty()) {
        book->release_year = std::stoi(release_year);
    }

    const std::string pages_count = input::getLine("Ingrese el numero de paginas (deje en blanco para conservar): ");
    if (!pages_count.empty()) {
        book->pages_count = std::stoi(pages_count);
    }

    const std::string price = input::getLine("Ingrese el precio (deje en blanco para conservar): ");
    if (!price.empty()) {
        book->price = std::stof(price);
    }
}

// region Files In Out
bool load() {
    std::ifstream file(SAVE_PATH);
    if (!file.is_open())
        return false;

    while (file.peek() != std::ifstream::traits_type::eof()) {
        Book book;

        // Read ID
        {
            std::string id_buf;
            if (!std::getline(file, id_buf, ',')) break;
            book.id = std::stoull(id_buf);

            if (next_id < book.id)
                next_id = book.id;
        }

        std::getline(file, book.title, ',');
        std::getline(file, book.author, ',');

        {
            std::string int_buffer;
            std::getline(file, int_buffer, ',');
            book.release_year = std::stoi(int_buffer);

            std::getline(file, int_buffer, ',');
            book.pages_count = std::stoi(int_buffer);
        }

        {
            std::string float_buffer;
            std::getline(file, float_buffer);
            book.price = std::stof(float_buffer);
        }

        books.push_back(book);
    }
    return true;
}

bool save() {
    std::ofstream file(SAVE_PATH);
    if (!file.is_open()) return false;

    for (const auto& book : books) {
        file << book.id << ',' << book.title << ',' << book.author << ',' << book.release_year << ','
             << book.pages_count << ',' << book.price << '\n';
    }

    file.close();
    std::cout << "Guardado.\n";
    return true;
}

// endregion
