cmake_minimum_required(VERSION 3.22)
project(P2)
set(PROJECT_VERSION "1.0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Copia el archivo base_de_datos.txt a la carpeta de construcción
configure_file(${CMAKE_SOURCE_DIR}/data/basededatos.txt ${CMAKE_BINARY_DIR}/basededatos.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/utils/script_generador.sh ${CMAKE_BINARY_DIR}/script_generador.sh COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/utils/script_genera_clientes_auto.sh ${CMAKE_BINARY_DIR}/script_genera_clientes_auto.sh COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/utils/script_genera_clientes_estres.sh ${CMAKE_BINARY_DIR}/script_genera_clientes_estres.sh COPYONLY)

add_executable(cliente.exe src/cliente.cpp src/usuario.cpp src/tablero.cpp src/partida.cpp)
add_executable(automatico_cliente.exe src/cliente_automatico.cpp src/usuario.cpp src/tablero.cpp src/partida.cpp src/cliente_automatico.cpp src/heuristica/heuristica.cpp)
add_executable(estres_cliente.exe src/estres_cliente.cpp)
add_executable(medidor_tiempo_respuesta.exe  src/cliente_medidor.cpp src/utils/ClaseTiempo.cpp)
add_executable(servidor.exe src/servidor.cpp src/usuario.cpp src/tablero.cpp src/partida.cpp)
add_executable(generador_usuarios_pruebas.exe src/utils/generador_usuarios_prueba.cpp)


