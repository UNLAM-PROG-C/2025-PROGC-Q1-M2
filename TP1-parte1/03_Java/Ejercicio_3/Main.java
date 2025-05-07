package Ejercicio_3;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Error: Se esperaban 2 argumentos: frecuencia y duracion.");
            return;
        }
        if (!args[0].matches("\\d+") || !args[1].matches("\\d+")) {
            System.out.println("Error: La frecuencia y la duracion deben ser numeros enteros.");
            return;
        }

        List<String> zones = List.of("Sotano", "Atico", "Cocina", "Dormitorio", "Jardin", "Mausoleo");
        List<Process> cameras = new ArrayList<>();
        int id = 0;
        String command = "java";
        String file_path = "TP1.Ejercicio_3.Camera";
        String frecuency = args[0], duration = args[1];

        for (String zone : zones) {
            ProcessBuilder processBuilder = new ProcessBuilder(command, file_path, id++ + "", zone, frecuency,
                    duration);
            processBuilder.inheritIO();
            try {
                Process process = processBuilder.start();
                cameras.add(process);
            } catch (Exception e) {
                System.out.println("Error al iniciar la cámara en la zona " + zone + ": " + e.getMessage());
            }
        }
        for (Process camera : cameras) {
            try {
                camera.waitFor();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("Todas las camaras han terminado su trabajo.");
    }
}