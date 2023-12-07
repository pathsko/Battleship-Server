#!/bin/bash

echo $(./generador_usuarios_pruebas.exe 1000 > usuarios_pruebas.txt)
echo $( cat usuarios_pruebas.txt >> basededatos.txt)
