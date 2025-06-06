#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
string leer_ip();
int main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd;
	struct sockaddr_in sockname;
	char buffer[250];
	socklen_t len_sockname;
    	fd_set readfds, auxfds;
    	int salida;
    	int fin = 0;
	
    
	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}

   
    
	/* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
	string ip= leer_ip();
	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2065);
	sockname.sin_addr.s_addr =  inet_addr(ip.c_str());

	/* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
	len_sockname = sizeof(sockname);
	
	if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
	{
		perror ("Error de conexión");
		exit(1);
	}
    
    //Inicializamos las estructuras
    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);
    
    FD_SET(0,&readfds);
    FD_SET(sd,&readfds);

	/* ------------------------------------------------------------------
		Se transmite la información
	-------------------------------------------------------------------*/
	do
	{
        auxfds = readfds;
        salida = select(sd+1,&auxfds,NULL,NULL,NULL);
        
        //Tengo mensaje desde el servidor
        if(FD_ISSET(sd, &auxfds)){
            
            bzero(buffer,sizeof(buffer));
            int a=recv(sd,buffer,sizeof(buffer),0);
			string sbuff = buffer;
            
            printf("\n%s\n",buffer);
			if(sbuff.find("Desconexion servidor")!=string::npos){
                fin=1;
            }
                

            
        }
        bzero(buffer,sizeof(buffer));
        string sbuff="ESTRESAU";
        strcpy(buffer,sbuff.c_str());
        send(sd,buffer,sizeof(buffer),0);
        
        
				
    }while(fin == 0);
	
    close(sd);
	

    return 0;
		
}
string leer_ip(){
    std::ifstream archivo("IP.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << "usuarios_pruebas.txt"<< std::endl;
        return ""; // Salir con código de error
    }
    std::string linea;
    std::getline(archivo, linea);
    return linea;
}