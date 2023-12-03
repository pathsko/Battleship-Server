Requisitos: El proyecto utiliza gestión de puertos del ordenador por lo que se deberá de montar y ejecutar en distribuciones GNU/Linux, además
 deberá de tener instalado "cmake", utilizado para montar el proyecto y un compilador para C/C++, perferiblemente g++ . 

Instrucciones para montar y compilar el proyecto:
Estando en la carpeta raíz, es decir, en la carpeta que contiene el archivo "CMakeLists.txt", ejecutar el siguiente comando:
cmake -B build && cd build && make && chmod u+x script_generador.sh && ./script_generador.sh

Descripción de ejecutables:

servidor.exe : El programa que ejecuta el servidor, para realizar pruebas se recomienda iniciarlo en una terminal y
 ejecutar aparte los clientes, introducir "SALIR" por línea de comandos para cerrarlo, por defecto también cerrará todos los clientes conectados.

cliente.exe :  El cliente que se conecta al servidor, este proyecto no tiene como objeto trabajar con él.

generador_usuarios_pruebas.exe :  Programa que crea cuentas específicas para que los clientes automáticos puedan iniciar sesión, el usuario que desee realizar
 las pruebas no debe se usarlo, al montar el proyecto el script "script_generador.sh" lo utiliza.

script_generador.sh: Script que utiliza el programa anterior para crear las cuentas de usuarios de prueba para que el programa "automatico_cliente.exe" 
 pueda iniciar sesión.

automatico_cliente.exe : Un cliente que simula ser una persona que se conecta al servidor a jugar al juego, inicia sesión y juega de forma automática,
 para utilizarlo basta con ejecutarlo, conforme se inician varios se puedes ver que al principio de la ejecución recibe errores del servidor,
 esto se debe a que intenta iniciar sesión con las cuentas de usuario generadas por "script_generador.sh", que puede que otras instancias del mismo,
 programa ya hallan utilizado.

estres_cliente.exe :  Un cliente que realiza peticiones basura al servidor para estresarlo.

medidor_tiempo_respuesta.exe :  Un programa que reliza continuamente peticiones al servidor y muestra el tiempo que tarda en responder en milisegundos.
 IMPORTANTE: Este programa tiene dos modos, uno muestra el tiempo y el otro no, para alternar entre ellos introducir por línea de comandos "STOP",
 podemos decir que es como un cronómetro virtual.
 NOTAS: Dado que el programa muestra datos sin parar al escribir el comando "STOP" no veremos lo que escribimos.