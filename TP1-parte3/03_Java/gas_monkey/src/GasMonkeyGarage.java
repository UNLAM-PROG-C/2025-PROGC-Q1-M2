import java.util.concurrent.Semaphore;

public class GasMonkeyGarage {
  private static final int PARKING_CAPACITY = 6;
  private static final int PIT_CAPACITY = 3;
  private static final int SERVICE_CAPACITY = 2;
  
  private static int totalCars = 0;
  private static int processedCars = 0;
  private static volatile boolean isFinished = false;
  
  private static final Semaphore semParking = new Semaphore(PARKING_CAPACITY);
  private static final Semaphore semPits = new Semaphore(PIT_CAPACITY);
  private static final Semaphore semService = new Semaphore(SERVICE_CAPACITY);
  
  private static final Semaphore semCarsInParking = new Semaphore(0);
  private static final Semaphore semCarsInspected = new Semaphore(0);
  private static final Semaphore semCarsInPits = new Semaphore(0);
  private static final Semaphore semCarsInService = new Semaphore(0);
  private static final Semaphore semCarsWashed = new Semaphore(0);
  private static final Semaphore semCarsReady = new Semaphore(0);

  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Error: Se requiere un argumento.");
      System.out.println("Uso: java GasMonkeyGarage <número_de_autos>");
      return;
    }

    try {
      totalCars = Integer.parseInt(args[0]);
      if (totalCars <= 0) {
        System.out.println("Error: El número de autos debe ser positivo.");
        return;
      }
    } catch (NumberFormatException e) {
      System.out.println("Error: El número de autos debe ser un entero válido.");
      return;
    }

    System.out.println("Iniciando taller con " + totalCars + " autos...");
    
    Thread richard = new Richard();
    Thread aaron = new Aaron();
    Thread charles = new Charles();
    Thread helper1 = new Helper(1);
    Thread helper2 = new Helper(2);
    Thread carWash = new CarWash();
    Thread customer = new Customer();

    richard.start();
    aaron.start();
    charles.start();
    helper1.start();
    helper2.start();
    carWash.start();
    customer.start();

    try {
      richard.join();
      aaron.join();
      charles.join();
      helper1.join();
      helper2.join();
      carWash.join();
      customer.join();
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }

    System.out.println("\n=== RESUMEN DEL TALLER ===");
    System.out.println("Total de autos procesados: " + processedCars);
    System.out.println("Servicio del taller completado exitosamente!");
  }

  public static synchronized void incrementProcessedCars() {
    processedCars++;
    if (processedCars >= totalCars) {
      isFinished = true;
      semCarsInParking.release(PARKING_CAPACITY);
      semCarsInspected.release(PIT_CAPACITY);
      semCarsInPits.release(PIT_CAPACITY);
      semCarsInService.release(SERVICE_CAPACITY);
      semCarsWashed.release(PARKING_CAPACITY);
      semCarsReady.release(PARKING_CAPACITY);
    }
  }

  public static boolean isFinished() {
    return isFinished;
  }

  public static void simulateDelay() {
    try {
      Thread.sleep((long) (Math.random() * 1000));
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }
  }

  static class Richard extends Thread {
    @Override
    public void run() {
      try {
        for (int i = 0; i < totalCars; i++) {
          if (isFinished()) break;
          semParking.acquire();
          System.out.println("Richard: Admitiendo auto #" + i + " al estacionamiento");
          simulateDelay();
          semCarsInParking.release();
        }
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }

  static class Aaron extends Thread {
    private int carCount = 0;

    @Override
    public void run() {
      try {
        while (!isFinished() && carCount < totalCars) {
          semCarsInParking.acquire();
          if (isFinished()) break;
          System.out.println("Aaron: Inspeccionando auto #" + carCount + " en el estacionamiento");
          simulateDelay();
          semCarsInspected.release();
          carCount++;
        }
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }

  static class Charles extends Thread {
    private int carCount = 0;

    @Override
    public void run() {
      try {
        while (!isFinished() && carCount < totalCars) {
          semCarsInPits.acquire();
          if (isFinished()) break;
          semPits.acquire();
          System.out.println("Charles: Reparando auto #" + carCount + " en fosa");
          simulateDelay();
          semPits.release();
          semCarsInService.release();
          carCount++;
        }
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }

  static class Helper extends Thread {
    private final int id;
    private int carCount = 0;

    public Helper(int id) {
      this.id = id;
    }

    @Override
    public void run() {
      try {
        while (!isFinished() && carCount < totalCars) {
          semCarsInspected.acquire();
          if (isFinished()) break;
          System.out.println("Ayudante " + id + ": Moviendo auto #" + carCount + " inspeccionado a fosa disponible");
          simulateDelay();
          semCarsInPits.release();
          semCarsInService.acquire();
          if (isFinished()) break;
          semService.acquire();
          System.out.println("Ayudante " + id + ": Realizando cambio de aceite al auto #" + carCount + " en estación #" + id);
          simulateDelay();
          semService.release();
          semCarsWashed.release();
          carCount++;
        }
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }

  static class CarWash extends Thread {
    private int carCount = 0;

    @Override
    public void run() {
      try {
        while (!isFinished() && carCount < totalCars) {
          semCarsWashed.acquire();
          if (isFinished()) break;
          System.out.println("Lavadero: Lavando y secando auto #" + carCount);
          simulateDelay();
          System.out.println("Lavadero: Devolviendo auto #" + carCount + " al estacionamiento por rodillos");
          simulateDelay();
          semParking.release();
          semCarsReady.release();
          carCount++;
        }
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }

  static class Customer extends Thread {
    @Override
    public void run() {
      try {
        for (int i = 0; i < totalCars; i++) {
          semCarsReady.acquire();
          System.out.println("Cliente: Retirando auto #" + i + " del estacionamiento");
          simulateDelay();
          incrementProcessedCars();
        }
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }
} 