
#include "clinic.hpp"
#include <cstdlib>

int main()
{
    system("chcp 65001 && cls");

    auto simi = Clinic();
    simi.loadUsers();
    if (!simi.login()) return -1;

    simi.loadPatients();
    simi.saveAppointments();

    simi.mainMenu();

    simi.saveAppointments();
    simi.savePatients();
    simi.saveUsers();

    return 0;
}