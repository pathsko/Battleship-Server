#!/bin/bash

echo $(./generador_usuarios_pruebas.exe 30 > ../data/usuarios_pruebas.txt)
echo $( cat ../data/usuarios_pruebas.txt >> basededatos.txt)