//
// Created by Franc on 24/10/2025.
//

#include "../include/menu.hpp"

#include <iostream>

#include "print+.hpp"
#include "input_handler.hpp"

void Menu::show() const
{
    const size_t options_length = options.size();
    while (true)
    {
        cool::clearScreen();

        std::cout << name << '\n';
        for (int option_index = 0; option_index < options_length; option_index++)
        {
            std::cout << "(" << option_index + 1 << ") " << options[option_index].name << '\n';
        }
        std::cout << "(" << options_length + 1 << ") Salir" << '\n';

        const int chosen_option = input_handler::getIntRange(1, options_length + 1) - 1;

        if (chosen_option == options_length)
        {
            break;
        }

        options[chosen_option].action();
        input_handler::waitForInput();
    }
}
