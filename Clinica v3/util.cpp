//
// Created by Franc on 26/11/2025.
//

#include "util.hpp"

#include <iostream>
#include <limits>

namespace input
{
    void clearInputStream() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int getInt(const std::string& message) {
        return getIntRange(INT_MIN, INT_MAX, message);
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

    std::string getString(const std::string& message) {
        return getStringMaxLength(message.max_size(), message);
    }

    std::string getStringMaxLength(const size_t max_length, const std::string& message)
    {
        std::cout << message;

        std::string str;
        if (!(std::cin >> str)) {
            std::cout << "¡Cadena invalida ingresada!\n";
            clearInputStream();
            return getStringMaxLength(max_length, message);
        }

        if (str.length() > max_length) {
            std::cout << "¡Cadena demasiado grande ingresada! El maximo son " << max_length << " carácteres. \n";
            return getStringMaxLength(max_length, message);
        }

        return str;
    }

    std::string getLine(const std::string& message) {
        std::string str;
        std::cout << message;

        std::getline(std::cin, str);

        return str;
    }


    void waitForInput()
    {
        std::system("pause");
    }
}
