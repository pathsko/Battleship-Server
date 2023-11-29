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

#include "tablero.hpp"
using namespace std;

int main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd;
	struct sockaddr_in sockname;
	char buffer[250];
	Tablero tablero;
	Tablero tablero_oponente;
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
	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2065);
	sockname.sin_addr.s_addr =  inet_addr("127.0.0.1");

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
            if(sbuff.find("+Ok. Empieza la partida.")!= string::npos){
				string mensaje=sbuff.substr(sbuff.find('.')+1,sbuff.size());
				string stablero = mensaje.substr(mensaje.find('.')+1,mensaje.size());
				tablero.unfold(stablero);
				vector<vector<string>> matriz_opo(10, vector<string>(10, "X"));
				tablero_oponente = Tablero(matriz_opo);
				cout<<"\n\n"+mostrar_tableros(tablero,tablero_oponente)<<"\n";

			}
			else if(sbuff.find("+Ok. Disparo en: ") != string::npos){
				char c;
				int n;
				string coords = sbuff.substr(sbuff.find(':')+2,sbuff.size());
				sscanf(coords.c_str(),"%c,%d",&c,&n);
				coords = c + to_string(n);
				tablero.disparar(coords);

				cout<<"\n\n"+mostrar_tableros(tablero,tablero_oponente)<<"\n";
			}
			else if((sbuff.find("+Ok. AGUA")!= string::npos) || (sbuff.find("Ok. TOCADO")!= string::npos) || (sbuff.find("Ok. HUNDIDO")!= string::npos)){
				string estado = sbuff.substr(sbuff.find(' ')+1,sbuff.find(':')-sbuff.find(' ')-1);
				string coords = sbuff.substr(sbuff.find(':')+2,sbuff.size());
				char c;
				int n;
				sscanf(coords.c_str(),"%c,%d",&c,&n);
				coords = c + to_string(n-1);
				if(estado == "AGUA"){
					tablero_oponente.set_celda(coords,"A");
				}
				else if(estado == "TOCADO"){
					tablero_oponente.set_celda(coords,"T");
				}
				else if(estado == "HUNDIDO"){
					tablero_oponente.set_celda(coords,"H");
				}
				cout<<"\n\n"+mostrar_tableros(tablero,tablero_oponente)<<"\n";
			}
            else if(strcmp(buffer,"Demasiados clientes conectados") == 0)
                fin =1;
            
            else if(strcmp(buffer,"Desconexión servidor") == 0){
				fin =1;
				
			}
                

            
        }
        else
        {
            
            //He introducido información por teclado
            if(FD_ISSET(0,&auxfds)){
                bzero(buffer,sizeof(buffer));
                
                fgets(buffer,sizeof(buffer),stdin);
                
                if(strcmp(buffer,"SALIR\n") == 0){
                        fin = 1;
                
                }
                
                send(sd,buffer,sizeof(buffer),0);
                
            }
            
            
        }
        
        
				
    }while(fin == 0);
	
    close(sd);
	

    return 0;
		
}