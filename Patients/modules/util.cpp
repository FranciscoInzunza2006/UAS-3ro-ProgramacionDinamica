
#include "util.hpp"

#include <iostream>
#include <limits>
#include <string>

void clearInputStream();

int getInt(const std::string& message) {
    std::cout << message;

    int number;
    if (std::cin >> number) return number;

    std::cout << "¡Valor invalido ingresado!\n";
    clearInputStream();
    return getInt(message);
}

int getIntRange(const int min, const int max, const std::string& message) {
    std::cout << message;

    int number;
    if (!(std::cin >> number)) {
        std::cout << "¡Valor invalido ingresado!\n";
        clearInputStream();
        return getIntRange(min, max, message);
    }

    if (number < min || number > max) {
        std::cout << "¡Valor fuera del rango! " << min << '-' << max << '\n';
        return getIntRange(min, max, message);
    }

    return number;
}

bool getBool(const std::string& message) {
    std::cout << message;

    bool number;
    if (std::cin >> number) return number;

    std::cout << "¡Valor invalido ingresado!\n";
    clearInputStream();
    return getBool(message);
}

std::string getString(const std::string& message) {
    std::cout << message;

    std::string str;
    if (std::cin >> str) return str;

    std::cout << "¡Valor invalido ingresado!\n";
    clearInputStream();
    return getString(message);
}

std::string getStringMaxLength(const int max_length, const std::string& message) {
    std::cout << message;

    std::string str;
    if (!(std::cin >> str)) {
        std::cout << "¡Valor invalido ingresado!\n";
        clearInputStream();
        return getStringMaxLength(max_length, message);
    }

    if (str.length() > (size_t)max_length) {
        std::cout << "¡Valor demasiado grande ingresado! El maximo son " << max_length << " carácteres. \n";
        return getStringMaxLength(max_length, message);
    }

    return str;
}

// FIXME: Causes "waitForInput" to requiere 2 enters.
std::string getStringOrNothing(const std::string& message) {
    clearInputStream();
    std::string str;
    std::cout << message;
    std::getline(std::cin, str);

    return str;
}

void waitForInput() {
    std::cout << std::flush;

    clearInputStream();
    std::cin.get();
}

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
