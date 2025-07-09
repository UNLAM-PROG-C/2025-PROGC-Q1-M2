JC = javac
JFLAGS = -encoding UTF-8
JVM = java
MAIN = GasMonkeyGarage

all: compile

compile:
	$(JC) $(JFLAGS) src/$(MAIN).java

run:
	$(JVM) -cp src $(MAIN) $(filter-out $@,$(MAKECMDGOALS))

clean:
	rm -f src/*.class

help:
	@echo "Comandos disponibles:"
	@echo "  make compile    - Compila el programa"
	@echo "  make run N      - Ejecuta el programa con N autos"
	@echo "  make clean      - Elimina los archivos compilados"
	@echo "  make help       - Muestra esta ayuda"
	@echo ""
	@echo "Ejemplo de uso:"
	@echo "  make compile"
	@echo "  make run 10"

%:
	@:

.PHONY: all compile run clean help 