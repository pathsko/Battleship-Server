Instrucciones para montar y compilar el proyecto:
Estando en la carpeta ./p2 , ejecutar el siguiente comando:
cmake -B build && cd build && make

Posteriormente en la carpeta ./p2/build/ se encontrarán los ejecutables servidor.exe y cliente.exe respectivamente.

Notas: 
-En el fichero ./p2/build/basededatos.txt se encuentran varios usuarios y contraseñas de prueba(a pesar de que se pueda 
registrar con la opción REGISTRAR).

-Si por algún caso se va a borrar la carpeta build y montar de nuevo el proyecto, el fichero basededatos.txt debería ser copiado a la carpeta ./p2/data/
dado que cmake lo copia de ahí y lo añade automáticamente a la carpeta build.