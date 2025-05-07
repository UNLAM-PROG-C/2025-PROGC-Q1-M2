package Ejercicio_3;

import java.util.List;

public class Event {
    private List<String> events = List.of("Sin actividad", "Movimiento detectado", "Anomalía térmica", "Sombra extraña",
            "Ruido detectado");

    public Event() {
    }

    public String getEvent() {
        int randomIndex = (int) (Math.random() * events.size());
        return events.get(randomIndex);
    }

}
