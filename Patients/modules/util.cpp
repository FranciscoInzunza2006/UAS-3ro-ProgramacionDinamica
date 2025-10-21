
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
