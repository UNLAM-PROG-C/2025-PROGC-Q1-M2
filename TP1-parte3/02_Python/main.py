import threading
import time
import random
import sys

bun_table_count = threading.Semaphore(0)
bun_table_capacity = threading.Semaphore(20)
pre_bun_count = threading.Semaphore(0)
basket_bread_count = threading.Semaphore(0)
basket_bread_capacity = threading.Semaphore(50)
sales_counter_count = threading.Semaphore(0)
sales_counter_capacity = threading.Semaphore(30)

bun_table_mtx = threading.Lock()
basket_bread_mtx = threading.Lock()
bakery_scale_mtx = threading.Lock()
sales_counter_mtx = threading.Lock()
sales_mtx = threading.Lock()

packages_sold = 0

def P(semaphore):
    semaphore.acquire()

def V(semaphore):
    semaphore.release()

def master():
    while True:
        P(bun_table_capacity)
        P(bun_table_capacity)
        P(bun_table_mtx)
        print("[Maestro]: Depositando 2 bollos de pan.", flush=True)
        time.sleep(0.25)
        V(bun_table_count)
        V(bun_table_count)
        V(bun_table_mtx)

def assistant():
    while True:
        P(bun_table_capacity)
        P(bun_table_mtx)
        print("[Asistente]: Depositando 1 bollo de pan.", flush=True)
        time.sleep(0.25)
        V(bun_table_count)
        V(bun_table_mtx)

def chef():
    while True:
        for _ in range(5):
            P(bun_table_count)

        P(bun_table_mtx)
        print("[Cocinero]: Retirando 5 bollos de pan.", flush=True)
        time.sleep(0.25)
        for _ in range(5):
            V(bun_table_capacity)
        V(bun_table_mtx)

        for _ in range(5):
            V(pre_bun_count)
        
def smart_oven():
    while True:
        for _ in range(5):
            P(basket_bread_capacity)
        
        for _ in range(5):
            P(pre_bun_count)

        P(basket_bread_mtx)
        print("[Horno]: Depositando 5 panes cocinados.", flush=True)
        time.sleep(0.25)
        for _ in range(5):
            V(basket_bread_count)
        V(basket_bread_mtx)
        
def packer():
    while True:
        for _ in range(3):
            P(basket_bread_count)

        P(basket_bread_mtx)
        print("[Empaquetador]: Retirando 3 panes cocinados.", flush=True)
        time.sleep(0.25)
        for _ in range(3):
            V(basket_bread_capacity)
        V(basket_bread_mtx)

        P(bakery_scale_mtx)
        print("[Empaquetador]: Pesando el paquete.", flush=True)
        time.sleep(0.25)
        V(bakery_scale_mtx)
        
        P(sales_counter_capacity)
        P(sales_counter_mtx)
        print("[Empaquetador]: Depositando 1 paquete en el mostrador.", flush=True)
        time.sleep(0.25)
        V(sales_counter_count)
        V(sales_counter_mtx)

def sales_woman(clients):
    global packages_sold

    for client in range(clients):
        package = random.randint(1, 3)
        print(f"[Cliente N°{client+1}]: Solicitando {package} paquete/s.", flush=True)

        for _ in range(package):
            P(sales_counter_count)
            P(sales_counter_mtx)
            print("[Vendedora]: Retirando 1 paquete del mostrador.", flush=True)
            time.sleep(0.25)
            V(sales_counter_capacity)
            V(sales_counter_mtx)

            P(sales_mtx)
            packages_sold += 1
            print(f"[Vendedora]: Registrando venta de paquete N°{packages_sold} ", flush=True)
            time.sleep(0.25)
            V(sales_mtx)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            clients = int(sys.argv[1])

            if clients <= 0:
                print("La cantidad de clientes debe ser un número positivo.")
                exit()
            
            threds = [
                threading.Thread(target=master, daemon=True),
                threading.Thread(target=assistant, daemon=True),
                threading.Thread(target=chef, daemon=True),
                threading.Thread(target=smart_oven, daemon=True),
                threading.Thread(target=packer, daemon=True),
                threading.Thread(target=packer, daemon=True),
                threading.Thread(target=sales_woman, daemon=True, args=(clients,))
            ]

            for h in threds:
                h.start()

            threds[-1].join()

            print(f"----- Total de paquetes vendidos: {packages_sold} -----")

        except ValueError:
            print("Argumento inválido. Por favor, ingrese un número entero para la cantidad de clientes.")
    else:
        print(f"No se especificó la cantidad de clientes.")
