//
// Created by Franc on 04/11/2025.
//

#include <iostream>
#include <string>

bool is_valid_message(const std::string& message);

int main()
{
    std::cout << "Mensajeria de Mercado Libre";

    while (true)
    {
        std::cout << "Mensaje: ";
        std::string message;
        std::getline(std::cin, message);

        if (message == "exit")
            break;

        if (is_valid_message(message))
        {
            std::cout << "Mensaje enviado correctamente.\n";
        } else
        {
            std::cout << "El mensaje no ha sido enviado por incumplir las normas de la plataforma.\n";
        }
    }

    return 0;
}


/**
 * Conditions that invalidate a message:
 *  - Phone number
 *  - Email
 *
 * @param message
 * @return
 */
bool is_valid_message(const std::string& message)
{
    return false;
}