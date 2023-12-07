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

#include "tablero.hpp"
#include "heuristica/heuristicastr1.hpp"
using namespace std;

string leer_ip();
int leer_claves(vector<string> &claves);
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
    //Este es el bicho que juega solo
    Heuristicastr1 bot;
	vector<string> claves;
    leer_claves(claves);
    int logit=0;
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
            bool esperamu=true;
            if(sbuff.find("Usuario conectado")!=string::npos || sbuff.find("El usuario ya ha iniciado sesion")!=string::npos){
                if(sbuff.find("El usuario ya ha iniciado sesion")!=string::npos){
                    logit++;
                }
                sbuff = "USUARIO "+claves[logit];
                logit++;
                bzero(buffer,sizeof(buffer));
                strcpy(buffer,sbuff.c_str());
                send(sd,buffer,sizeof(buffer),0);
            }
            else if(sbuff.find("Usuario correcto")!=string::npos){
                sbuff = "PASSWORD "+claves[logit];
                logit++;
                bzero(buffer,sizeof(buffer));
                strcpy(buffer,sbuff.c_str());
                send(sd,buffer,sizeof(buffer),0);
            }
            else if(sbuff.find("Usuario validado")!=string::npos){
                sbuff = "INICIAR-PARTIDA\n";
                bzero(buffer,sizeof(buffer));
                strcpy(buffer,sbuff.c_str());
                send(sd,buffer,sizeof(buffer),0);
            }
            else if(sbuff.find("Empieza la partida.")!= string::npos){
                vector<int> coords(2);
				do{
                    auxfds = readfds;
                    salida = select(sd+1,&auxfds,NULL,NULL,NULL);
                    if(FD_ISSET(sd, &auxfds)){
                        bzero(buffer,sizeof(buffer));
                        recv(sd,buffer,sizeof(buffer),0);
                        sbuff = buffer;
                        cout<<sbuff<<endl;
                        if((sbuff.find("Ok. AGUA")!= string::npos) || (sbuff.find("Ok. TOCADO")!= string::npos) || (sbuff.find("Ok. HUNDIDO")!= string::npos)){
                            
                            string estado = sbuff.substr(sbuff.find(' ')+1,sbuff.find(':')-sbuff.find(' ')-1);
                            //MODIFICAR DISPARAR PARA PODER INTRODUCIRLE LAS COORDENADAS, POR EL TEMA DE LOS NUMEROS ALEATORIOS
                            bot.disparar(estado,coords);
                            
                        }
                        else if(sbuff.find("Turno de partida")!= string::npos){
                            bzero(buffer,sizeof(buffer));
                            string scoord =bot.selec_dirji(coords,1);
                            sbuff = "DISPARO "+scoord;
                            strcpy(buffer,sbuff.c_str());
                            esperamu=true;
                            send(sd,buffer,sizeof(buffer),0);
                        }
                        else if(sbuff.find("ha ganado")!=string::npos){
                            sbuff = "INICIAR-PARTIDA\n";
                            bzero(buffer,sizeof(buffer));
                            strcpy(buffer,sbuff.c_str());
                            bot.reset();
                            send(sd,buffer,sizeof(buffer),0);
                        }
                        else if(sbuff.find("Desconexion servidor")!=string::npos){
                        	fin=1;
                        }
                    }
                    //mensaje desde servidor
                    
                }while(fin == 0);
            
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
            
            
            else if(sbuff.find("Desconexion servidor")!=string::npos){
                fin=1;
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

int leer_claves(vector<string> &claves){
    std::ifstream archivo("usuarios_pruebas.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << "usuarios_pruebas.txt"<< std::endl;
        return 1; // Salir con código de error
    }
    std::string linea;
    while (std::getline(archivo, linea)) {
        // Imprime cada línea en la consola
        claves.push_back(linea);
    }
    archivo.close();
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
