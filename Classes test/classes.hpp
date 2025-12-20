//
// Created by Franc on 19/12/2025.
//

#pragma once
#include <functional>
#include <string>

class Program
{
public:
    std::string name;
    std::function<int()> entry_point;

    Program(const std::string& name, const std::function<int()>& entry_point)
        : name(name),
          entry_point(entry_point)
    {
    }
};

class Unidad
{
public:
    std::string name;
    std::vector<Program> programs;


    Unidad(const std::string& name, const std::vector<Program>& programs)
        : name(name),
          programs(programs)
    {
    }
};

