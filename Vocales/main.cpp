
#include <iostream>
#include <string>

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