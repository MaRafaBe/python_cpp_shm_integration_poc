cmake_minimum_required(VERSION 3.10)
project(PruebaMemoriaCompartida)

# Usar el estándar C++11 o superior
set(CMAKE_CXX_STANDARD 11)

# Crear el ejecutable
add_executable(cliente_cpp ./src/cliente_cpp.cpp)

# --- MAGIA DE CMAKE PARA LINUX ---
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Busca la librería 'rt' en el sistema
    target_link_libraries(cliente_cpp rt)
endif()
# En macOS no entrará en el 'if' y compilará normal