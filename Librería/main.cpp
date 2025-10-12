
#include <iostream>
#include "suma.hpp"

int main()
{
    int a;
    std::cout << "Ingresa un numero: ";
    std::cin >> a;

    int b;
    std::cout << "Ingresa otro numero: ";
    std::cin >> b;
    
    std::cout << a << " + " << b << " = " << add(a, b) << std::endl;
    return 0;
}