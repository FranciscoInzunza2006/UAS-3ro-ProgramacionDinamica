//
// Created by Franc on 24/10/2025.
//

#include "input_handler.hpp"

#include <iostream>
#include <limits>
#include <string>

int input_handler::getInt(const std::string& message) {
    return getIntRange(INT_MIN, INT_MAX, message);
}

int input_handler::getIntRange(const int min, const int max, const std::string& message) {
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

bool input_handler::getBool(const std::string& message) {
    std::cout << message;

    bool boolean;
    if (std::cin >> boolean) return boolean;

    std::cout << "¡Valor invalido ingresado!\n";
    clearInputStream();
    return getBool(message);
}

std::string input_handler::getString(const std::string& message) {
    return getStringMaxLength(message.max_size(), message);
}

std::string input_handler::getStringMaxLength(const size_t max_length, const std::string& message)
{
    std::cout << message;

    std::string str;
    if (!(std::cin >> str)) {
        std::cout << "¡Valor invalido ingresado!\n";
        clearInputStream();
        return getStringMaxLength(max_length, message);
    }

    if (str.length() > max_length) {
        std::cout << "¡Valor demasiado grande ingresado! El maximo son " << max_length << " carácteres. \n";
        return getStringMaxLength(max_length, message);
    }

    return str;
}

void input_handler::clearInputStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void input_handler::waitForInput() {
    std::cout << std::flush;

    clearInputStream();
    std::cin.get();
}