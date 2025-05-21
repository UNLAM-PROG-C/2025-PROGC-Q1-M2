#ifndef PLANTA_H
#define PLANTA_H

#include "Semaforo.h"
#include <string>

class Planta
{
public:
    std::string nombre;
    Semaforo semaforoCarga;
    Semaforo semaforoDescarga;
    Semaforo semaforoCombustible;
    Planta(std::string nombre_planta);
};

#endif
