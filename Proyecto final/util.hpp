//
// Created by Franc on 26/11/2025.
//

#pragma once
#include <iostream>
#include <string>

namespace input
{
    int getInt(const std::string& message = "");
    int getIntRange(int min, int max, const std::string& message = "");

    float getFloat(const std::string& message = "");
    float getFloatRange(float min, float max, const std::string& message = "");

    std::string getString(const std::string& message = "");
    std::string getStringMaxLength(size_t max_length, const std::string& message = "");
    std::string getLine(const std::string& message = "");

    void waitForInput();
}

inline void separator() {
    std::cout << "────────────────────────────────────────────────────────────────\n";
    //std::cout << "-----------------------------------------------" << std::endl;
}

inline void clearScreen()
{
    std::system("cls");
}