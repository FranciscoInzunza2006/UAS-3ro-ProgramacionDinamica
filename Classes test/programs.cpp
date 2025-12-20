//
// Created by Franc on 19/12/2025.
//
#include "programs.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <limits>
#include <vector>
#include "util.hpp"

// Unidad 1
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

namespace IMC
{
#define NAME_MAX_LENGTH 64

    struct
    {
        char name[NAME_MAX_LENGTH];
        unsigned int age;
        float weight;
        float height;
    } typedef Patient;

    void printHeader();
    Patient* getPatientInfo();
    void printSeparator();
    void printPatientInfo(Patient* patient);
    float calculateIMC(Patient* patient);
    void printIMCRating(const float imc);
    bool shouldCloseProgram();

    int main()
    {
        while (true)
        {
            printHeader();

            Patient* patient = getPatientInfo();
            printPatientInfo(patient);
            delete patient;

            if (shouldCloseProgram())
                break;
        }

        return 0;
    }

    void printHeader()
    {
        printSeparator();
        std::cout << "\tCalculadora de IMC\n";
        printSeparator();
    }

    Patient* getPatientInfo()
    {
        Patient* patient = new Patient();

        std::cout << "Ingresa el nombre: ";
        std::cin >> patient->name;

        std::cout << "Ingresa la edad: ";
        std::cin >> patient->age;

        std::cout << "Ingresa el peso(kg): ";
        std::cin >> patient->weight;

        std::cout << "Ingresa la estatura(m): ";
        std::cin >> patient->height;

        return patient;
    }

    void printPatientInfo(Patient* patient)
    {
        printSeparator();

        std::cout << "Nombre: " << patient->name << '\n';
        std::cout << "Edad: " << patient->age << '\n';
        std::cout << "Peso: " << patient->weight << "kg\n";
        std::cout << "Estatura: " << patient->height << "m\n";

        printSeparator();

        float imc = calculateIMC(patient);
        std::cout << "\tIMC: " << imc << '\n';
        std::cout << "\t";
        printIMCRating(imc);

        printSeparator();
    }

    float calculateIMC(Patient* patient)
    {
        return patient->weight / (patient->height * patient->height);
    }

    void printIMCRating(const float imc)
    {
        if (imc < 18.5)
        {
            std::cout << "Estas bien seco carnal\n";
        }
        else if (imc < 25)
        {
            std::cout << "Peso normal\n";
        }
        else if (imc < 30)
        {
            std::cout << "Sobrepeso\n";
        }
        else if (imc < 35)
        {
            std::cout << "Obesidad leve\n";
        }
        else if (imc < 40)
        {
            std::cout << "Obesidad media\n";
        }
        else
        {
            std::cout << "Aimep3\n";
        }
    }

    bool shouldCloseProgram()
    {
        char answer;
        std::cout << "Continuar(Y/N)? ";
        std::cin >> answer;
        return (answer != 'Y' && answer != 'y');
    }

    void printSeparator()
    {
        std::cout << "--------------------------------------\n";
    }
}

namespace Figuras
{
    void drawRectangle(const int width, const int height)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                {
                    std::cout << "* ";
                }
                else
                {
                    std::cout << "  ";
                }
            }
            std::cout << std::endl;
        }
    }

    void drawSquare(const int width)
    {
        drawRectangle(width, width);
    }

    int main()
    {
        std::cout << "Cuadrado 5x5:\n";
        drawSquare(5);

        std::cout << "Cuadrado 8x5:\n";
        drawRectangle(8, 5);

        std::cout << "\nHaz tu propio cuadrado: \n";

        int width;
        std::cout << "Ancho: ";
        std::cin >> width;

        int height;
        std::cout << "Alto: ";
        std::cin >> height;
        drawRectangle(width, height);

        return 0;
    }
}

namespace Fibonacci
{
    int main()
    {
        int x = 0;
        int y = 1;
        for (int i = 0; i < 10; i++)
        {
            int z = x + y;
            x = y;
            y = z;

            std::cout << x << " ";
        }

        return 0;
    }
}

namespace CosoConPalabras
{
    int main()
    {
        std::string name;
        std::cout << "Ingresa tu nombre: ";
        std::cin >> name;

        int a = 0;
        int e = 0;
        int i = 0;
        int o = 0;
        int u = 0;
        int invalid_character = 0;
        const int len = name.length();
        for (int ci = 0; ci < len; ci++)
        {
            switch (name[ci])
            {
            case 'A':
            case 'a':
                a++;
                break;
            case 'E':
            case 'e':
                e++;
                break;
            case 'I':
            case 'i':
                i++;
                break;

            case 'O':
            case 'o':
                o++;
                break;

            case 'U':
            case 'u':
                u++;
                break;

            case ' ':
                invalid_character++;
                break;
            }
        }

        std::cout << "Tu nombre tiene " << len - invalid_character << " letras, de las cuales " << a + e + i + o + u << " son vocales.\n";
        std::cout << "A: " << a << '\n';
        std::cout << "E: " << e << '\n';
        std::cout << "I: " << i << '\n';
        std::cout << "O: " << o << '\n';
        std::cout << "U: " << u << '\n';

        return 0;
    }
}

// Unidad 2
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

namespace Counter
{
    //
    // Created by Franc on 03/11/2025.
    //

#include <iostream>
#include <string>

    int countAppearances(const std::string& str, const char search_char)
    {
        int appearances = 0;
        for (const auto c : str)
        {
            if (c == search_char)
                appearances++;
        }

        return appearances;
    }

    int main()
    {
        std::cout << "Enter some phrase: ";
        std::string sample;
        std::getline(std::cin, sample);

        int letters = 0;
        int numbers = 0;
        int words = 0;

        bool in_word = false;
        for (const auto c : sample)
        {
            if (isspace(c))
            {
                in_word = false;
                continue;
            }

            if (!in_word)
            {
                words++;
                in_word = true;
            }

            if (isdigit(c))
            {
                numbers++;
            }
            else if (!ispunct(c))
            {
                letters++;
            }
        }

        std::cout << "Stats:\n";
        std::cout << "Words: " << words << "\n";
        std::cout << "Letters: " << letters << "\n";
        std::cout << "Numbers: " << numbers << "\n";

        std::cout << "\nEnter a letter:";
        char c;
        std::cin >> c;
        std::cout << "That characters appears in the string " << countAppearances(sample, c) << " times.\n";

        return 0;
    }
}

namespace ChatFilter
{
    bool is_valid_message(const std::string& message);

    bool contains_email(const std::string& message);
    bool contains_phone_number(const std::string& message);
    bool contains_blacklisted_word(const std::string& message);

    int main()
    {
        std::cout << "Mensajeria de Mercado Libre\n";

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
        std::transform(sample.begin(), sample.end(), sample.begin(),
                       [](const unsigned char c) { return std::tolower(c); });

        return !(contains_phone_number(sample) || contains_blacklisted_word(sample));
        //return !(contains_email(sample) || contains_phone_number(sample) || contains_blacklisted_word(sample));
    }

    bool contains_phone_number(const std::string& message)
    {
        int numbers_next_to_each_other = 0;
        for (const char& c : message)
        {
            if (std::isspace(c) || c == '-' || c == '+' || c == '.')
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
            "trato directo",
            "contactame",
            "contacto directo",

            "whatsapp",
            "telegram",
            "face", // facebook

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
}

// Unidad 3
namespace Exam
{
    //
    // Created by Franc on 03/12/2025.
    //

    std::size_t next_id = 0;

    struct Book
    {
        std::size_t id{};
        std::string title;
        std::string author;
        int release_year{};
        int pages_count{};
        float price{};
    };

    std::vector<Book> books;
    constexpr auto SAVE_PATH = "books.data";

    bool load();
    bool save();

    void registerBook();
    void showBooks();

    void queryBook();
    void bookMenu();

    void modify_book(Book* book);
    void delete_book(Book* book);

    int main()
    {
        load();

        bool running = true;
        while (running)
        {
            std::system("cls");

            separator();
            std::cout << "Biblioteca Paco\n";
            separator();
            std::cout << "  (1) Registrar libro\n";
            std::cout << "  (2) Consultar libros\n";
            std::cout << "  (3) Salir\n";

            separator();
            const int option = input::getIntRange(1, 3);
            separator();

            bool query;
            switch (option)
            {
            case 1:
                registerBook();
                break;

            case 2:
                showBooks();

                query = input::getInt("¿Realizar consulta? (Sí = 1) : ");
                if (query) queryBook();
                break;

            case 3:
                std::cout << "Hasta pronto!\n";
                running = false;
                break;

            default: ;
            }
            separator();
            input::waitForInput();
        }

        if (!save()) return 1;
        return 0;
    }

    void registerBook()
    {
        Book book;

        book.id = ++next_id;

        std::cin.ignore();
        book.title = input::getLine("Titulo: ");
        book.author = input::getLine("Autor: ");

        book.release_year = input::getInt("Año de salida: ");
        book.pages_count = input::getInt("Numero de paginas: ");
        std::cout << "Precio: $";
        std::cin >> book.price;

        books.push_back(book);
    }

    void showBooks()
    {
        if (books.empty())
        {
            std::cout << "No hay hay libros registrados.\n";
            return;
        }

        // Field size
        constexpr int ID_FS = 4;
        constexpr int NAME_FS = 20;
        constexpr int AUTOR_FS = 20;
        constexpr int YEAR_FS = 6;
        constexpr int PAGES_FS = 8;
        constexpr int PRICE_FS = 6;

        std::cout << std::left << std::setw(ID_FS) << "ID" << ' ';
        std::cout << std::setw(NAME_FS) << "Titulo";
        std::cout << std::setw(AUTOR_FS) << "Autor";
        std::cout << std::setw(YEAR_FS) << "Año";
        std::cout << std::setw(PAGES_FS) << "Paginas";
        std::cout << std::setw(PRICE_FS) << "Precio";
        std::cout << std::endl;

        for (const auto& b : books)
        {
            std::cout << std::right << std::setw(ID_FS) << std::setfill('0') << b.id << std::setfill(' ') << std::left
                << ' ';
            std::cout << std::setw(NAME_FS) << b.title;
            std::cout << std::setw(AUTOR_FS) << b.author;
            std::cout << std::setw(YEAR_FS) << b.release_year;
            std::cout << std::setw(PAGES_FS) << b.pages_count;
            std::cout << std::setw(PRICE_FS) << b.price;
            std::cout << '\n';
        }

        std::cout << std::right;
    }

    void queryBook()
    {
        separator();
        std::size_t id = input::getInt("Ingrese la ID del libro: ");

        Book* b = nullptr;
        int i = 0;
        for (auto& book : books)
        {
            if (book.id == id)
            {
                b = &book;
                break;
            }
            i++;
        }

        if (b == nullptr)
        {
            std::cout << "Libro no encontrado.";
            return;
        }

        separator();
        std::cout << "¿Qué deseas realizar?\n"
            "  (1) Modificar\n"
            "  (2) Eliminar\n"
            "  (3) Nada\n";
        int action = input::getIntRange(1, 3);
        if (action == 3) return;

        separator();
        if (action == 1)
        {
            modify_book(b);
            return;
        }

        if (action == 2)
        {
            std::cout << "Borrado.\n";
            books.erase(books.begin() + i);
        }
    }

    void modify_book(Book* book)
    {
        std::cin.ignore();
        const std::string title = input::getLine("Ingrese el titulo (deje en blanco para conservar): ");
        if (!title.empty())
        {
            book->title = title;
        }

        const std::string author = input::getLine("Ingrese el autor (deje en blanco para conservar): ");
        if (!author.empty())
        {
            book->author = author;
        }

        const std::string release_year = input::getLine(
            "Ingrese el año de publicación (deje en blanco para conservar): ");
        if (!release_year.empty())
        {
            book->release_year = std::stoi(release_year);
        }

        const std::string pages_count =
            input::getLine("Ingrese el numero de paginas (deje en blanco para conservar): ");
        if (!pages_count.empty())
        {
            book->pages_count = std::stoi(pages_count);
        }

        const std::string price = input::getLine("Ingrese el precio (deje en blanco para conservar): ");
        if (!price.empty())
        {
            book->price = std::stof(price);
        }
    }

    // region Files In Out
    bool load()
    {
        std::ifstream file(SAVE_PATH);
        if (!file.is_open())
            return false;

        while (file.peek() != std::ifstream::traits_type::eof())
        {
            Book book;

            // Read ID
            {
                std::string id_buf;
                if (!std::getline(file, id_buf, ',')) break;
                book.id = std::stoull(id_buf);

                if (next_id < book.id)
                    next_id = book.id;
            }

            std::getline(file, book.title, ',');
            std::getline(file, book.author, ',');

            {
                std::string int_buffer;
                std::getline(file, int_buffer, ',');
                book.release_year = std::stoi(int_buffer);

                std::getline(file, int_buffer, ',');
                book.pages_count = std::stoi(int_buffer);
            }

            {
                std::string float_buffer;
                std::getline(file, float_buffer);
                book.price = std::stof(float_buffer);
            }

            books.push_back(book);
        }
        return true;
    }

    bool save()
    {
        std::ofstream file(SAVE_PATH);
        if (!file.is_open()) return false;

        for (const auto& book : books)
        {
            file << book.id << ',' << book.title << ',' << book.author << ',' << book.release_year << ','
                << book.pages_count << ',' << book.price << '\n';
        }

        file.close();
        std::cout << "Guardado.\n";
        return true;
    }

    // endregion
}
