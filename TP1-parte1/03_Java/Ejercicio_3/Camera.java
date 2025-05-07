package Ejercicio_3;

public class Camera {
    private String zone;
    private Event event;
    private Integer id;
    private Integer frecuency_time;
    private Integer duration_time;
    private Integer event_ocurrencyes = 0;

    public Camera(Integer id, String zone, Integer frecuency_time, Integer duration_time) {
        this.frecuency_time = frecuency_time * 1000;
        this.duration_time = duration_time * 1000;
        this.zone = zone;
        this.id = id;
        this.event = new Event();
    }

    public static void main(String[] args) {
        if (args.length != 4) {
            System.out.println("Error: Debe ingresar una zona, frecuencia y tiempo de duración positivos.");
            return;
        }
        Integer id = Integer.parseInt(args[0]);
        String zone = args[1];
        Integer frecuency_time = Integer.parseInt(args[2]);
        Integer duration_time = Integer.parseInt(args[3]);
        Camera camera = new Camera(id, zone, frecuency_time, duration_time);
        camera.start();
    }

    private void print_observation(int id, String zone, String event) {
        String msj = "Id: " + id + "\nZona: " + zone + "\nObservacion: " + event;
        String to_print = "";
        int max_len = get_max_len(msj);
        String borde = "-".repeat(max_len + 4);
        to_print += borde + "\n";
        to_print += formated_tex(msj, max_len);
        to_print += borde;
        System.out.println(to_print);
    }

    private String formated_tex(String msj, int max_len) {
        String[] lineas = msj.split("\n");
        String text = "";
        for (String linea : lineas) {
            text += "| " + String.format("%-" + max_len + "s", linea) + " |" + "\n";
        }
        return text;
    }

    private int get_max_len(String msj) {
        String[] lineas = msj.split("\n");
        int max_len = 0;
        for (String linea : lineas) {
            if (linea.length() > max_len) {
                max_len = linea.length();
            }
        }
        return max_len;
    }

    public void start() {
        while (this.duration_time > 0) {
            String eventMessage = event.getEvent();
            event_ocurrencyes += !eventMessage.equals("Sin actividad") ? 1 : 0;
            print_observation(this.id, this.zone, eventMessage);
            try {
                Thread.sleep(frecuency_time);
                duration_time -= frecuency_time;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        print_observation(id, zone, this.event_ocurrencyes.toString());
    }
}
