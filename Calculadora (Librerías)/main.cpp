#include <iostream>
#include <cstdlib>
#include "math.hpp"

#define SEPARATOR "===================================\n"
int main()
{
    while (true)
    {
        system("cls");
        std::cout << SEPARATOR;
        std::cout << "  Calculadora\n";
        std::cout << SEPARATOR;

        std::cout << "\t(+) Suma\n";
        std::cout << "\t(-) Resta\n";
        std::cout << "\t(*) Multiplicacion\n";
        std::cout << "\t(/) Division\n";
        std::cout << SEPARATOR;
        std::cout << "Selecciona tu operacion: ";
        char symbol;
        std::cin >> symbol;
        std::cout << SEPARATOR;
        if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/')
        {
            std::cout << "Operacion invalida!\n";
        }
        else
        {

            double n1;
            std::cout << "Ingrese el primer valor: ";
            std::cin >> n1;

            double n2;
            std::cout << "Ingrese el segundo valor: ";
            std::cin >> n2;

            double result;
            bool success = true;
            std::cout << SEPARATOR;
            switch (symbol)
            {
            case '+':
                result = add(n1, n2);
                break;

            case '-':
                result = substract(n1, n2);
                break;

            case '*':
                result = multiply(n1, n2);
                break;

            case '/':
                if (n2 == 0) {
                    std::cout << "El divisor no puede ser 0!\n";
                    success = false;
                }
                result = divide(n1, n2);
                break;
            }


            if (success)
                std::cout << "Resultado: " << result << std::endl;
        }
        std::cout << SEPARATOR;
        char if_continue;
        std::cout << "Continuar(Y/N)? ";
        std::cin >> if_continue;

        if (if_continue != 'y' && if_continue != 'Y') {
            std::cout << SEPARATOR;
            break;
        }
    }

    return 0;
}
