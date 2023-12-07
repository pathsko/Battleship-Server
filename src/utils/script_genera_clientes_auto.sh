#!/bin/bash

# Número de veces que se lanzará el servidor
num_veces=$1 # Cambia este número al número deseado de ejecuciones

# Bucle para lanzar el servidor en nuevas terminales
for ((i = 1; i <= num_veces; i++)); do
    gnome-terminal -e "./automatico_cliente.exe && exit" 
done
