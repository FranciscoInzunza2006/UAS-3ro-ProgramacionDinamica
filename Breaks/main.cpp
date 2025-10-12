
#include <iostream>

#define MAX_NUMBERS 10

int main() {
    int numbers[MAX_NUMBERS];
    int numbers_entered = 0;
    for (; numbers_entered < MAX_NUMBERS; numbers_entered++) {
        int n;
        std::cout << "Ingrese un numero, ingresa un numero negativo para finalizar, #"<< numbers_entered+1 << " = ";        
        std::cin >> n;

        if (n < 0)
            break;

        numbers[numbers_entered] = n;
    }

    if (numbers_entered > 0) {
        std::cout << "\nEntered values:\n";
        for (int i = 0; i < numbers_entered; i++)
        {
            std::cout << "#" << i+1 << " = " << numbers[i] << std::endl;
        }
        
    } else {
        std::cout << "\nNo values entered.\n";
    }
}