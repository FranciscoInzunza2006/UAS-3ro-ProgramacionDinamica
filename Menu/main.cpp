
#include <iostream>
#include <string>
#include <conio.h>

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

const Option *options[]{
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

int getIntInRange(const std::string message, const int min, const int max) {
    while (true) {
        int x;
        std::cout << '\r' << message;
        std::cin >> x;

        if (x < min || x > max)  {
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
        "Domingo"};

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
        "Diciembre"};

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
        std::cout << "El tercer numero no es el resultado de sumar los otros dos... " << n1 << " + " << n2 << "= " << n1 + n2 << '\n';
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
        std::cout << "El tercer numero no es el producto de sumar los otros dos... " << n1 << " * " << n2 << "= " << n1 * n2 << '\n';
}