#ifndef CAMIONERO_H
#define CAMIONERO_H

#include <thread>
#include <random>
#include <memory>
#include "Planta.h"
#include <string>

#define TIEMPO_DE_CARGA 2
#define TIEMPO_DE_DESCARGA 2
#define TIEMPO_CARGA_DE_COMBUSTIBLE 1

class Camionero
{
public:
    Camionero(int id, Planta &tapiales, Planta &fernandez, Semaforo &mutex, int &viajes);
    void iniciar();
    void esperar();
    int tiempo_total = 0;

private:
    int id;
    int tiempo_de_viaje;
    std::thread hilo;
    Planta &plantaTapiales;
    Planta &plantaFernandez;
    Semaforo &mutexViajes;
    int &viajesDisponibles;

    void rutina();
    int generarTiempoDeViaje(int min, int max);
    void iniciarViaje(std::string destino);
    void cargar(Planta &planta);
    void descargar(Planta &planta);
    void recargarCombustible(Planta &planta);
    void print(Planta &planta, std::string mensaje);
};

#endif
