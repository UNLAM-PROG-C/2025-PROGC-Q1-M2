import os
import random
import time
import sys

# El script siguiente simula un juego de dados en el que varios jugadores lanzan un dado varias veces y suman sus puntos.
# Cada jugador es un proceso hijo que se crea a partir de un proceso padre.
# El proceso padre espera a que todos los procesos hijos terminen antes de finalizar.
# El número de lanzamientos y jugadores se define como constantes al principio del script.
# El script imprime el resultado de cada lanzamiento y la puntuación total de cada jugador al final.

THROWS = 10
PLAYER = 5


def player(id):
    sys.stdout.write(f"Jugador {id} entra al juego.\n")
    points = 0
    for i in range(THROWS):
        dice = random.randint(1, 6)
        points += dice
        sys.stdout.write(f"Jugador {id} - Lanzamiento {i+1}: {dice}\n")
        time.sleep(random.uniform(0.1, 0.3))
    sys.stdout.write(f"Jugador {id} finaliza con {points} puntos\n")


def main():
    procesos = []
    for i in range(PLAYER):
        pid = os.fork()
        if pid == 0:
            player(i + 1)
            sys.exit(0)
        else:
            procesos.append(pid)
    for pid in procesos:
        os.waitpid(pid, 0)
    sys.stdout.write("Todos los jugadores han terminado.\n")


if __name__ == "__main__":
    main()
