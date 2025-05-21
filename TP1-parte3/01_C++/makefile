# Nombre del ejecutable
TARGET = simulacion

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

# Archivos fuente y objeto
SRC = main.cpp TruckDriver.cpp Plant.cpp Semaphore.cpp
OBJ = $(SRC:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Cómo construir el ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para limpiar archivos objeto y binario
clean:
	rm -f $(OBJ) $(TARGET)
