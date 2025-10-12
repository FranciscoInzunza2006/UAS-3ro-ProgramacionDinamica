#include <iostream>

#define BILLETES_TOTAL 6
#define COINS_TOTAL 5

#define DOLLAR_CONVERSION_RATE 20
#define EURO_CONVERSION_RATE 22

const float billetes_value[BILLETES_TOTAL] = {20, 50, 100, 200, 500, 1000};
const float coins_value[COINS_TOTAL] = {0.50f, 1, 2, 5, 10};

int main()
{
    std::cout << "Contadora de billetes\n";

    while (true)
    {
        int billetes_amount[BILLETES_TOTAL];
        for (int i = 0; i < BILLETES_TOTAL; i++)
        {
            std::cout << "Cuantos billetes de $" << billetes_value[i] << " tienes? ";
            std::cin >> billetes_amount[i];
        }
        std::cout << std::endl;

        int coins_amount[COINS_TOTAL];
        for (int i = 0; i < COINS_TOTAL; i++)
        {
            std::cout << "Cuantas monedas de $" << coins_value[i] << " tienes? ";
            std::cin >> coins_amount[i];
        }
        std::cout << std::endl;

        float billetes_total = 0;
        for (int i = 0; i < BILLETES_TOTAL; i++)
        {
            billetes_total += billetes_value[i] * billetes_amount[i];
        }
        float coins_total = 0;
        for (int i = 0; i < COINS_TOTAL; i++)
        {
            coins_total += coins_value[i] * coins_amount[i];
        }
        const float total = billetes_total + coins_total;

        std::cout << "Total de billetes: $" << billetes_total << std::endl;
        std::cout << "Total de monedas: $" << coins_total << std::endl;
        std::cout << "Total: $" << total << std::endl;

        std::cout << "Deseas convertir esta cantidad a otra moneda?\n";
        std::cout << "(1) Dolares\n";
        std::cout << "(2) Euros\n";

        int c;
        std::cin >> c;
        if (c == 1)
        {
            std::cout << "Total de billetes en dolares: $" << billetes_total / DOLLAR_CONVERSION_RATE << std::endl;
            std::cout << "Total de monedas en dolares: $" << coins_total / DOLLAR_CONVERSION_RATE << std::endl;
            std::cout << "Total en dolares: $" << total / DOLLAR_CONVERSION_RATE << std::endl;
        }
        else if (c == 2)
        {
            std::cout << "Total de billetes en euros: $" << billetes_total / EURO_CONVERSION_RATE << std::endl;
            std::cout << "Total de monedas en euros: $" << coins_total / EURO_CONVERSION_RATE << std::endl;
            std::cout << "Total en euros: $" << total / EURO_CONVERSION_RATE << std::endl;
        }

        std::cout << "Volver a contar(S/N)? ";
        char loop;
        std::cin >> loop;
        if (loop != 'S' && loop != 's')
            break;
    }

    std::cout << "Adios" << std::endl;
    return 0;
}