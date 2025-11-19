
#include "clinic.hpp"
#include <cstdlib>

int main()
{
    system("chcp 65001 && cls");

    auto simi = Clinic();
    //if (!simi.login()) return -1;



    simi.loadPatients();
    simi.mainMenu();
    simi.savePatients();

    return 0;
}