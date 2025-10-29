
#include "appointment.hpp"

#include <iostream>

#include "util.hpp"

void makeAppointment() {
    bool diabetes = getBool("¿Eres diabetico? (S=1/N=0) : ");
    bool condicion = getBool("¿Cuentas con alguna condicional? (S=1/N=0) : ");
    bool raro = getBool("¿Eres furro? (S=1/N=0) : ");
    bool sida = getBool("¿Tienes sida? (S=1/N=0) : ");
    bool futuro_tieso = getBool("¿Tienes cancer? (S=1/N=0) : ");

    if (futuro_tieso) {
        std::cout << "Lmao, ahí quedaste carnal.\n";
        return;
    }

    if (raro) {
        if (sida) {
            std::cout << "Debiste usar protección.\n";
        } else {
            std::cout << "Usa protección, eres un peligro andante.\n";
        }

        return;
    }

    if (sida) {
        std::cout << "Usa protección siempre, informa a tu pareja y futuras parejas de esta situación\n";
        return;
    }

    if (condicion) {
        std::cout << "Explica más a detalle tu condición para poder recetarte medicamentos acorde.\n";
        return;
    }

    if (diabetes) {
        std::cout << "Pase a la farmacia para darle insulina.\n";
        return;
    }

    std::cout << "Si estabas tan sano, ¿Por qué viniste?\n";
}