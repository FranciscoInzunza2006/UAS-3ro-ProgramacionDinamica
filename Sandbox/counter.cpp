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
