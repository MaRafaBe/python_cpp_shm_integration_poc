import time
import numpy as np
from multiprocessing import shared_memory

def run_host():
    shm_name = "shmprueba"
    # Tamaño de un int8 es 1 byte
    size = 1 
    shm = None

    try:
        print(f" Creando memoria compartida: {shm_name}")
    
        shm = shared_memory.SharedMemory(create=True, size=size, name=shm_name)
        print(f"[Python] El nombre real interno es: {shm.name}")
        buffer_array = np.ndarray((1,), dtype='int8', buffer=shm.buf)
        buffer_array[0] = -1
        print(f" Valor inicial establecido en memoria: {buffer_array[0]}")

        print(" Esperando cambios... (Pulsa Ctrl+C para cancelar)")

        running = True
        while running:
            current_value = buffer_array[0]
            
            if current_value != -1:
                print(f" ¡Cambio detectado! Nuevo valor leído: {current_value}")
                if current_value == 3:
                    print(" El valor esperado (3) ha sido recibido. Cerrando...")
                    running = False
            
            if running:
                time.sleep(1) 

    except KeyboardInterrupt:
        print("\n Interrupción manual.")
    except Exception as e:
        print(f" Error: {e}")
    finally:
        if shm:
            print("Cerrando y desvinculando memoria compartida...")
            shm.close()
            shm.unlink() 
            print(" Memoria liberada correctamente.")

if __name__ == "__main__":
    run_host()