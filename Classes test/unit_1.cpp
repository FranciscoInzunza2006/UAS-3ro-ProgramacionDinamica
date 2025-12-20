//
// Created by Franc on 19/12/2025.
//
#include "unit_1.hpp"

#include <iostream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>
#include <iostream>
#include <limits>
#include <vector>


namespace Calculadora
{
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

                double result = 0;
                bool success = true;
                std::cout << SEPARATOR;
                switch (symbol)
                {
                case '+':
                    result = n1 + n2;
                    break;

                case '-':
                    result = n1 - n2;
                    break;

                case '*':
                    result = n1 * n2;
                    break;

                case '/':
                    if (n2 == 0)
                    {
                        std::cout << "El divisor no puede ser 0!\n";
                        success = false;
                    }
                    result = n1 / n2;
                    break;
                default: ;
                }


                if (success)
                    std::cout << "Resultado: " << result << std::endl;
            }
            std::cout << SEPARATOR;
            char if_continue;
            std::cout << "Continuar(Y/N)? ";
            std::cin >> if_continue;

            if (if_continue != 'y' && if_continue != 'Y')
            {
                std::cout << SEPARATOR;
                break;
            }
        }

        return 0;
    }
}

namespace Menu
{
    // Sobre-ingenieria pura y dura

    void printSeparator();
    void printMenu();
    void selectOption();
    int getIntInRange(const std::string message, const int min, const int max);

    void isEven();
    void toWeekday();
    void toMonth();
    void isPositive();
    void isGreaterThan100();
    void isVowel();
    void isResultOfAdding();
    void isProductOf();

    typedef void (*Action)();

    class Option
    {
    public:
        Action action;
        std::string name;

        Option(Action action, std::string name)
        {
            this->action = action;
            this->name = name;
        }
    };

    const Option* options[]{
        new Option(&isEven, "Es par"),
        new Option(&toWeekday, "Dia de la semana"),
        new Option(&toMonth, "Mes"),
        new Option(&isPositive, "Es positivo"),
        new Option(&isGreaterThan100, "Es mayor a 100"),
        new Option(&isVowel, "Es vocal"),
        new Option(&isResultOfAdding, "Es el resultado de sumar"),
        new Option(&isProductOf, "Es el producto"),
    };
    const int options_length = sizeof(options) / sizeof(options[0]);

    int main()
    {
        while (true)
        {
            system("cls");
            printMenu();
            selectOption();

            char again;
            std::cout << "Continuar(Y/N)? ";
            std::cin >> again;
            if (again != 'y' && again != 'Y')
                break;
        }

        return 0;
    }

    void printSeparator()
    {
        std::cout << "--------------------------------------------\n";
    }

    void printMenu()
    {
        printSeparator();
        std::cout << "\tMenu\n";
        printSeparator();

        for (int i = 0; i < options_length; i++)
        {
            std::cout << '(' << i + 1 << ") " << options[i]->name << '\n';
        }
        printSeparator();
    }

    void selectOption()
    {
        int selected_option = getIntInRange("Selecciona una opcion: ", 1, options_length);

        printSeparator();
        (options[selected_option - 1]->action)();
        printSeparator();
    }

    int getIntInRange(const std::string message, const int min, const int max)
    {
        while (true)
        {
            int x;
            std::cout << '\r' << message;
            std::cin >> x;

            if (x < min || x > max)
            {
                std::cout << "\rFuera de rango!";
                getch();
                std::cout << "\r                         \x1b[A"; // El diablo (mueve el cursor para arriba)
                continue;
            }

            return x;
        }
    }

    void isEven()
    {
        int number;
        std::cout << "Ingresa un numero: ";
        std::cin >> number;

        if (number % 2 == 0)
            std::cout << "Es par.\n";
        else
            std::cout << "Es impar.\n";
    }

    void toWeekday()
    {
        const int weekdays_length = 7;
        const std::string weekdays[weekdays_length] = {
            "Lunes",
            "Martes",
            "Miercoles",
            "Jueves",
            "Viernes",
            "Sabado",
            "Domingo"
        };

        int day_of_the_week = getIntInRange("Ingresa un numero del 1-7: ", 1, weekdays_length);
        std::cout << "Ese dia es " << weekdays[day_of_the_week - 1] << ".\n";
    }

    void toMonth()
    {
        const int months_length = 12;
        const std::string months[months_length] = {
            "Enero",
            "Febrero",
            "Marzo",
            "Abril",
            "Mayo",
            "Junio",
            "Julio",
            "Agosto",
            "Septiembre",
            "Octubre",
            "Noviembre",
            "Diciembre"
        };

        int month_number = getIntInRange("Ingresa un numero del 1-12: ", 1, months_length);
        std::cout << "Ese mes es " << months[month_number - 1] << ".\n";
    }

    void isPositive()
    {
        double number;
        std::cout << "Ingresa un numero: ";
        std::cin >> number;

        if (number > 0)
        {
            std::cout << "Es positivo.\n";
        }
        else if (number < 0)
        {
            std::cout << "Es negativo.\n";
        }
        else
        {
            std::cout << "Es cero(sin signo).\n";
        }
    }

    void isGreaterThan100()
    {
        double number;
        std::cout << "Ingresa un numero: ";
        std::cin >> number;

        if (number > 100)
        {
            std::cout << "Es mayor a 100.\n";
        }
        else
        {
            std::cout << "No es mayor a 100.\n";
        }
    }

    void isVowel()
    {
        char letter;
        std::cout << "Ingresa una letra: ";
        std::cin >> letter;

        letter = tolower(letter);
        if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u')
            std::cout << "Es una vocal.\n";
        else
            std::cout << "No es una vocal.\n";
    }

    void isResultOfAdding()
    {
        double n1;
        std::cout << "Ingresa un numero: ";
        std::cin >> n1;

        double n2;
        std::cout << "Ingresa otro numero: ";
        std::cin >> n2;

        double n3;
        std::cout << "Ingresa un ultimo numero: ";
        std::cin >> n3;

        if (n3 == n1 + n2)
            std::cout << "El tercer numero es el resultado de sumar los otros dos!\n";
        else
            std::cout << "El tercer numero no es el resultado de sumar los otros dos... " << n1 << " + " << n2 << "= "
                << n1 + n2 << '\n';
    }

    void isProductOf()
    {
        double n1;
        std::cout << "Ingresa un numero: ";
        std::cin >> n1;

        double n2;
        std::cout << "Ingresa otro numero: ";
        std::cin >> n2;

        double n3;
        std::cout << "Ingresa un ultimo numero: ";
        std::cin >> n3;

        if (n3 == n1 * n2)
            std::cout << "El tercer numero es el producto de los otros dos!\n";
        else
            std::cout << "El tercer numero no es el producto de sumar los otros dos... " << n1 << " * " << n2 << "= " <<
                n1 * n2 << '\n';
    }
}

namespace Login
{
    struct User
    {
        std::string username;
        std::string password;
    };

    std::vector<User> users;

    bool isUpperCase(char c);
    bool isLowerCase(char c);
    bool isDigit(char c);
    bool isSymbol(char c);

    int testPassword(const std::string& password)
    {
        int numbers = 0;
        int lower = 0;
        int upper = 0;
        int symbols = 0;
        for (const char c : password)
        {
            if (isUpperCase(c))
            {
                upper++;
            }
            else if (isLowerCase(c))
            {
                lower++;
            }
            else if (isDigit(c))
            {
                numbers++;
            }
            else if (isSymbol(c))
            {
                symbols++;
            }
        }

        if (password.length() >= 8 && lower && upper && numbers && symbols)
        {
            return 3;
        }

        if ((lower || upper) && !numbers && !symbols)
        {
            std::cout << "Password is only letters.\n";
            return 1;
        }

        if (numbers && !(lower || upper) && !symbols)
        {
            std::cout << "Password is only numbers.\n";
            return 1;
        }

        if ((lower || upper) && numbers && symbols)
        {
            std::cout << "Missing upper or lower case characters.\n";
            return 2;
        }

        return -1;
    }

    bool usernameExists(const std::string& username)
    {
        for (const User& user : users)
        {
            if (user.username == username)
            {
                std::cout << "Username already registered.\n";
                return true;
            }
        }

        return false;
    }

    int main()
    {
        while (true)
        {
            std::cout << "-----Register a new user-----\n";
            std::cout << "Enter your username: ";
            std::string username;
            std::cin >> username;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (username == "exit")
            {
                break;
            }

            if (usernameExists(username))
                continue;

            std::cout << "Enter a password: ";
            std::string password;

            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::getline(std::cin, password);
            std::cin.clear();

            {
                std::cout << "Confirm your password: ";
                std::string password_confirmation;

                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::getline(std::cin, password_confirmation);
                std::cin.clear();

                if (password != password_confirmation)
                {
                    std::cout << "Passwords do not match.\n";
                    continue;
                }
            }

            const int security_level = testPassword(password);
            if (security_level == 3)
            {
                std::cout << "High security level.\n";
                users.push_back({username, password});
                continue;
            }

            std::cout << "Username wasn't registered because the password is too weak.\n";
            switch (security_level)
            {
            case 1:
                std::cout << "Low security level.\n";
                continue;
            case 2:
                std::cout << "Middle security level.\n";
                break;
            default:
                std::cout << "Unknown security level.\n";
                break;
            }
        }

        return 0;
    }

    bool isUpperCase(const char c)
    {
        return (c >= 'A' && c <= 'Z');
    }

    bool isLowerCase(const char c)
    {
        return (c >= 'a' && c <= 'z');
    }

    bool isDigit(const char c)
    {
        return (c >= '0' && c <= '9');
    }

    bool isSymbol(const char c)
    {
        return !(isLowerCase(c) || isUpperCase(c) || isDigit(c));
    }
}
