
/*
    TODO:
    - Menu that looks actually decent

    - Register patients
    - Lookup patients
    - Edit patients
    - Delete patients

    - Same thing for appointments

    - Save patients to file
    - Read patients from file

    - Data that patients must have:
        * Name
        * Last name
        * Birthdate
        * Phone number
        * Email
        * Address
        * Blood type
        * Medical record

    - Appointments:
        * Date
        * Reason
        * Result
*/

#include <cstdlib>

#include "clinic.hpp"
#include "menu.hpp"

int main() {
    loadPatientsData();

    system("chcp 65001 && cls");
    systemMenu();

    savePatientsData();
    return 0;
}