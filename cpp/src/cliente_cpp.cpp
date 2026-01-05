#include <iostream>
#include <sys/mman.h>   // Para shm_open, mmap
#include <sys/stat.h>   // Constantes de modo
#include <fcntl.h>      // Constantes O_*
#include <unistd.h>     // Para close, ftruncate
#include <cstdint>      // Para int8_t

int main() {
    // Nombre exacto definido en Python
    const char* shm_name = "/shmprueba";
    const int SIZE = 1; // 1 Byte

    std::cout << "[C++] Intentando conectar a memoria compartida: " << shm_name << std::endl;

    // 1. Abrir la memoria compartida existente
    // O_RDWR: Lectura y escritura
    int fd = shm_open(shm_name, O_RDWR, 0666);

    if (fd == -1) {
        std::cerr << "[C++] Error: No se pudo abrir la memoria compartida. " 
                  << "¿Está ejecutándose el script de Python?" << std::endl;
        return 1;
    }

    // 2. Mapear la memoria al espacio de direcciones de este proceso
    // PROT_READ | PROT_WRITE: Permisos de lectura/escritura
    // MAP_SHARED: Los cambios son visibles para otros procesos
    void* ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED) {
        std::cerr << "[C++] Error: Falló el mapeo de memoria (mmap)." << std::endl;
        close(fd);
        return 1;
    }

    // 3. Castear el puntero a int8_t (entero de 8 bits con signo)
    int8_t* data = static_cast<int8_t*>(ptr);

    std::cout << "[C++] Valor actual en memoria: " << (int)*data << std::endl;
    std::cout << "[C++] Escribiendo valor 3..." << std::endl;

    // 4. Escribir el valor
    *data = 3;

    std::cout << "[C++] Escritura completada. Saliendo." << std::endl;

    // 5. Limpieza
    // Deshacemos el mapeo (no hacemos shm_unlink, eso es responsabilidad de Python)
    munmap(ptr, SIZE);
    close(fd);

    return 0;
}