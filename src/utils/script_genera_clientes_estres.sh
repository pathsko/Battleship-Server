#!/bin/bash

# Número de veces que se lanzará el servidor
num_veces=$1

# Bucle para lanzar el servidor en nuevas terminales
for ((i = 1; i <= num_veces; i++)); do
    gnome-terminal -e "./estres_cliente.exe && exit"
done
