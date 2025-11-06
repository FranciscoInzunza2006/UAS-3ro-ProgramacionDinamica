//
// Created by Franc on 04/11/2025.
//

#include <algorithm>
#include <iostream>
#include <string>

bool is_valid_message(const std::string& message);

bool contains_email(const std::string& message);
bool contains_phone_number(const std::string& message);
bool contains_blacklisted_word(const std::string& message);

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
        }
        else
        {
            std::cout << "El mensaje no ha sido enviado por incumplir las normas de la plataforma.\n";
        }
    }

    return 0;
}


/**
 * Conditions that invalidate a message:
 *  - Contains a Phone number
 *  - Contains an Email
 *
 *  - Contains the word:
 *      - Whatsapp
 *      - Telegram
 * @param message
 * @return
 */
bool is_valid_message(const std::string& message)
{
    std::string sample = message;
    std::transform(sample.begin(), sample.end(), sample.begin(), [](const unsigned char c) { return std::tolower(c); });

    return !(contains_phone_number(sample) || contains_blacklisted_word(sample));
    //return !(contains_email(sample) || contains_phone_number(sample) || contains_blacklisted_word(sample));
}

bool contains_email(const std::string& message)
{
    for (const auto c : message)
    {
        if (c == '@')
        {
            return true;
        }
    }

    return false;
}

bool contains_phone_number(const std::string& message)
{
    int numbers_next_to_each_other = 0;
    for (const char& c : message)
    {
        if (std::isspace(c) || c == '-')
            continue;

        if (std::isdigit(c))
        {
            numbers_next_to_each_other++;

            constexpr int PHONE_NUMBER_LENGTH = 10;
            if (numbers_next_to_each_other >= PHONE_NUMBER_LENGTH)
                return true;
        }
        else
        {
            numbers_next_to_each_other = 0;
        }
    }

    return false;
}

bool contains_blacklisted_word(const std::string& message)
{
    const std::string blacklisted_words[] = {
        "whatsapp",
        "telegram",

        "correo electronico",
        "correo electrónico",
        "email",
        "@",
        "gmail",
        "hotmail",
        "outlook",

        "uno",
        "dos",
        "tres",
        "cuatro",
        "cinco",
        "seis",
        "siete",
        "ocho",
        "diez",
    };

    for (const std::string& word : blacklisted_words)
    {
        if (message.find(word) != std::string::npos)
        {
            return true;
        }
    }

    return false;
}
