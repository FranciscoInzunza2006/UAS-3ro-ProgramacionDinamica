//
// Created by Franc on 24/10/2025.
//

#pragma once
#include <string>

namespace input_handler
{
    int getInt(const std::string& message = "");
    int getIntRange(int min, int max, const std::string& message = "");

    bool getBool(const std::string& message = "");

    std::string getString(const std::string& message = "");
    std::string getStringMaxLength(size_t max_length, const std::string& message = "");

    void clearInputStream();
    void waitForInput();
}
