
#include "patient.hpp"

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "appointment.hpp"

Id Patient::next_id = 0;

Patient::Patient() {
    // TODO: Registrar todos los valores

    std::string name;
    std::cin >> name;

    this->name = name;
    std::cout << "Hello, World!";
}

Patient::~Patient() {
}