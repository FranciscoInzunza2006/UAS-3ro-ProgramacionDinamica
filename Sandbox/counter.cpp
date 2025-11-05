//
// Created by Franc on 03/11/2025.
//

#include <iostream>
#include <string>

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

    return 0;
}
