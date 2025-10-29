//
// Created by Franc on 24/10/2025.
//

#pragma once
#include <functional>
#include <string>
#include <utility>
#include <vector>

typedef struct
{
    std::string name;
    std::function<void()> action;
} Option;

class Menu
{
    std::string name;
    std::vector<Option> options;

public:
    Menu(std::string name, const std::vector<Option>& options) : name(std::move(name)),
                                                                       options(options)
    {
    }

    void show() const;
};
