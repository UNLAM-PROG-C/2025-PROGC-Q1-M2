#include <iostream>
#include <vector>
#include "Planta.h"
#include "Camionero.h"

int main(int argc, char const *argv[])
{
    Planta tapiales = Planta("Tapiales");
    Planta fernandez = Planta("Fernandez");
    Semaforo mutexViajes(1);
    int viajes = 4;
    int cantidad_camioneros = 4;
    int tiempo_maximo = 0;
    std::vector<Camionero> camioneros;

    for (int i = 0; i < cantidad_camioneros; ++i)
    {
        camioneros.emplace_back(i + 1, tapiales, fernandez, mutexViajes, viajes);
    }

    for (auto &camionero : camioneros)
    {
        camionero.iniciar();
    }

    for (auto &camionero : camioneros)
    {
        camionero.esperar();
        tiempo_maximo = std::max(tiempo_maximo, camionero.tiempo_total);
    }

    int dias = tiempo_maximo / 24;
    int horas = tiempo_maximo % 24;
    std::cout << "Tiempo total para terminar todos los viajes: " << dias << " dias " << horas << " horas" << std::endl;
    return 0;
}
