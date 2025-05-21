#include "Camionero.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
#define TIEMPO_MINIMO 18
#define TIEMPO_MAXIMO 24

Camionero::Camionero(int id, Planta &tapiales, Planta &fernandez, Semaforo &mutex, int &viajes)
    : id(id), plantaTapiales(tapiales), plantaFernandez(fernandez), mutexViajes(mutex), viajesDisponibles(viajes)
{
    tiempo_de_viaje = generarTiempoDeViaje(TIEMPO_MINIMO, TIEMPO_MAXIMO);
}

void Camionero::iniciar()
{
    hilo = thread(&Camionero::rutina, this);
}

void Camionero::esperar()
{
    if (hilo.joinable())
    {
        hilo.join();
    }
}

int Camionero::generarTiempoDeViaje(int min, int max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void Camionero::rutina()
{
    mutexViajes.esperar();
    while (viajesDisponibles > 0)
    {
        viajesDisponibles--;
        mutexViajes.liberar();
        cargar(plantaTapiales);
        iniciarViaje("Fernandez");
        descargar(plantaFernandez);
        cargar(plantaFernandez);
        recargarCombustible(plantaFernandez);
        iniciarViaje("Tapiales");
        descargar(plantaTapiales);
        mutexViajes.esperar();
    }
    mutexViajes.liberar();
    std::string mensaje = "Camionero " + std::to_string(id) + " ha terminado su turno en " + std::to_string(tiempo_total) + "hs.\n";
    std::cout << mensaje;
}

void Camionero::iniciarViaje(std::string destino)
{
    std::string mensaje = "Camionero " + std::to_string(id) + " viajando a " + destino + ", Tiempo de vieaje: " + std::to_string(tiempo_de_viaje) + "hs.\n";
    std::cout << mensaje;
    tiempo_total += tiempo_de_viaje;
    this_thread::sleep_for(chrono::milliseconds(tiempo_de_viaje));
}

void Camionero::cargar(Planta &planta)
{
    print(planta, "Esperando para cargar");
    auto intento = std::chrono::steady_clock::now();
    planta.semaforoCarga.esperar();
    auto entrada = std::chrono::steady_clock::now();

    print(planta, "Cargando");
    this_thread::sleep_for(chrono::milliseconds(TIEMPO_DE_CARGA));
    print(planta, "Carga completa");
    planta.semaforoCarga.liberar();

    auto tiempo_espera = std::chrono::duration_cast<std::chrono::milliseconds>(entrada - intento).count();
    tiempo_total += TIEMPO_DE_CARGA + tiempo_espera;
}

void Camionero::descargar(Planta &planta)
{
    print(planta, "Esperando para descargar");
    auto intento = std::chrono::steady_clock::now();
    planta.semaforoDescarga.esperar();
    auto entrada = std::chrono::steady_clock::now();

    print(planta, "Descargando");
    this_thread::sleep_for(chrono::milliseconds(TIEMPO_DE_DESCARGA));
    print(planta, "Descarga completa");
    planta.semaforoDescarga.liberar();

    auto tiempo_espera = std::chrono::duration_cast<std::chrono::milliseconds>(entrada - intento).count();
    tiempo_total += TIEMPO_DE_DESCARGA + tiempo_espera;
}

void Camionero::recargarCombustible(Planta &planta)
{
    print(planta, "Esperando para recargar combustible");
    auto intento = std::chrono::steady_clock::now();
    planta.semaforoCombustible.esperar();
    auto entrada = std::chrono::steady_clock::now();

    print(planta, "Recargando Combustible");
    this_thread::sleep_for(chrono::milliseconds(TIEMPO_CARGA_DE_COMBUSTIBLE));
    print(planta, "Recarga de combustible completa");
    planta.semaforoCombustible.liberar();

    auto tiempo_espera = std::chrono::duration_cast<std::chrono::milliseconds>(entrada - intento).count();
    tiempo_total += TIEMPO_CARGA_DE_COMBUSTIBLE + tiempo_espera;
}

void Camionero::print(Planta &planta, std::string accion)
{
    std::string mensaje = "Camionero " + std::to_string(id) + " en planta " + planta.nombre + ": " + accion + ".\n";
    std::cout << mensaje;
}
