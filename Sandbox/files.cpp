#include <fstream>
#include <iostream>
#include <string>

#define FILE_PATH "out/people.txt"

struct Person {
    std::string name;
    int age;
};

int main() {
    Person persons[] = {
        {"John Doe", 21},
        {"Paco", 19},
    };

    std::ofstream file_o(FILE_PATH, std::ios::app);
    if (!file_o) {
        std::cout << "The file couldn't be open.\n";
        return 1;
    }

    for (const auto& p : persons) {
        file_o << p.name << ',' << p.age << '\n';
    }
    file_o.close();
    std::cout << "Data saved sucessfully.\n";

    std::ifstream file_i(FILE_PATH);
    std::cout << "Data in file:\n";

    std::string buf;
    while (std::getline(file_i, buf)) {
        std::cout << buf << '\n';
    }
    file_i.close();

    return 0;
}