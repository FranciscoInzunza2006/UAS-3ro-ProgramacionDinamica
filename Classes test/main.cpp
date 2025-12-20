//
// Created by Franc on 19/12/2025.
//

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "classes.hpp"
#include "unit_1.hpp"
#include "util.hpp"

int main()
{
    const std::vector unidades
    {
        Unidad("Unidad 1", {
                   Program("Calculadora", Calculadora::main),
                   Program("Menu", Menu::main)
               }),
        Unidad("Unidad 2", {
                   Program("Login", Login::main),
               })
    };

    bool running = true;
    std::size_t selected_unit = -1;
    while (running)
    {
        clearScreen();
        if (selected_unit == -1)
        {
            std::cout << "Selecciona una unidad:\n";
            const std::size_t total_units = unidades.size();
            for (std::size_t i = 0; i < total_units; ++i)
            {
                std::cout << "\t(" << i + 1 << ") " << unidades[i].name << "\n";
            }
            std::cout << "\t(" << total_units + 1 << ") " << "Salir" << "\n";

            int choice = input::getIntRange(1, total_units + 1) - 1;
            if (choice == total_units)
            {
                running = false;
            }
            else
            {
                selected_unit = choice;
            }

            continue;
        }

        // Menu de programas
        const Unidad& current_unit = unidades[selected_unit];
        const std::size_t total_programs = current_unit.programs.size();

        std::cout << current_unit.name << '\n';
        std::cout << "Selecciona un programa:\n";
        for (std::size_t i = 0; i < total_programs; ++i)
        {
            std::cout << "\t(" << i + 1 << ") " << current_unit.programs[i].name << "\n";
        }
        std::cout << "\t(" << total_programs + 1 << ") " << "Salir" << "\n";
        const int choice = input::getIntRange(1, total_programs + 1) - 1;
        if (choice == total_programs)
        {
            selected_unit = -1;
            continue;
        }

        clearScreen();
        int exit_code = current_unit.programs[choice].entry_point();
        if (exit_code == 0)
        {
            std::cout << "Program exited successfully\n";
        }
        else
        {
            std::cout << "Program exited with error: " << exit_code << "\n";
        }
        input::waitForInput();
    }

    return 0;
}
