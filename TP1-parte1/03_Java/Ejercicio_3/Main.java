package Ejercicio_3;

import java.util.ArrayList;
import java.util.List;

public class Main {
     public static boolean validate_parameters(String[] args)
    {
        if (args.length != 2) {
            System.out.println("Error: Se esperaban 2 argumentos: frecuencia y duracion.");
            return false;
        }
        if (!args[0].matches("\\d+") || !args[1].matches("\\d+")) {
            System.out.println("Error: La frecuencia y la duracion deben ser numeros enteros.");
            return false;
        }

        return true;
    }
    private static List<Process> start_processes(List<String> zones, String frequency, String duration) {
        List<Process> processes = new ArrayList<>();
        String command = "java", file = "Camera";
        int id = 0;

        for (String zone : zones) {
            ProcessBuilder pb = new ProcessBuilder(command, file, String.valueOf(id++), zone, frequency, duration);
            pb.inheritIO();
            try {
                processes.add(pb.start());
            } catch (Exception e) {
                System.out.println("Error starting camera in zone " + zone + ": " + e.getMessage());
            }
        }

        return processes;
    }

    private static void wait_for_processes(List<Process> processes) {
        for (Process process : processes) {
            try {
                process.waitFor();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public static void main(String[] args) {
        if(validate_parameters(args)==false)
           return;
        List<String> zones = List.of("Sotano", "Atico", "Cocina", "Dormitorio", "Jardin", "Mausoleo");
        List<Process> cameras = new ArrayList<>();
        String frecuency = args[0], duration = args[1];
        cameras=start_processes(zones,frecuency,duration);
        wait_for_processes(cameras);
        System.out.println("Todas las camaras han terminado su trabajo.");
    }
}