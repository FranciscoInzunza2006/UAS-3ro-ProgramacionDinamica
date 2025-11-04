#include <iostream>
#include <limits>
#include <vector>

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

        std::cin.ignore(std::cin.rdbuf()->in_avail() );
        std::getline(std::cin, password);
        std::cin.clear();

        {
            std::cout << "Confirm your password: ";
            std::string password_confirmation;

            std::cin.ignore(std::cin.rdbuf()->in_avail() );
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
