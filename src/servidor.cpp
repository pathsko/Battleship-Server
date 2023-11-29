#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include <queue> 
#define MSG_SIZE 250
#define MAX_CLIENTS 30

#include "usuario.hpp"
#include "tablero.hpp"
#include "partida.hpp"
using namespace std;



void salirCliente(int socket, fd_set * readfds, vector<int> clientes);
int main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	socklen_t from_len;
	fd_set readfds, auxfds;
	vector<Usuario> usuarios;
	cargar_usuarios(usuarios,"basededatos.txt");
	vector<Partida> partidas;
	vector<int> clientes;
	int salida;
	int recibidos;
	int j,i;
	char identificador[MSG_SIZE];
	queue<Usuario> cola_partida;
	int salir = 0;
	int on, ret;

	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}

	on=1;
    ret = setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2065);
	sockname.sin_addr.s_addr =  INADDR_ANY;

	if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}
	

   	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
		from_len = sizeof (from);


		if(listen(sd,1) == -1){
			perror("Error en la operación de listen");
			exit(1);
		}

		printf("El servidor está esperando conexiones...\n");
   		FD_ZERO(&readfds);
    	FD_ZERO(&auxfds);
    	FD_SET(sd,&readfds);
    	FD_SET(0,&readfds);
	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
		while(1){
			auxfds = readfds;
            
            salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);
			if(salida > 0){
                
                
                for(i=0; i<FD_SETSIZE; i++){
                    
                    //Buscamos el socket por el que se ha establecido la comunicación
                    if(FD_ISSET(i, &auxfds)) {
                        if( i == sd){
                            
                            if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                                perror("Error aceptando peticiones");
                            }
                            else
                            {
                                if(clientes.size() < MAX_CLIENTS){
                                    clientes.push_back(new_sd);
                                    FD_SET(new_sd,&readfds);
									
									bzero(buffer,sizeof(buffer));
                                    sprintf(buffer, "+0k. Usuario conectado");
									if(send(new_sd, buffer, sizeof(buffer), 0) == -1){
										perror("Error en la operación de send");
										exit(1);
									}
	
                                    
                                
                                
                                }
                                else
                                {

                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"Demasiados clientes conectados");
                                    send(new_sd,buffer,sizeof(buffer),0);
                                    close(new_sd);
                                }
                                
                            }
                            
                            
                        }
                        else if (i == 0){
                            //Se ha introducido información de teclado
                            bzero(buffer, sizeof(buffer));
                            fgets(buffer, sizeof(buffer),stdin);
                            
                            //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                            if(strcmp(buffer,"SALIR\n") == 0){
                             
                                for (j = 0; j < clientes.size(); j++){
									bzero(buffer, sizeof(buffer));
									strcpy(buffer,"Desconexión servidor"); 
                                    send(clientes[j],buffer , sizeof(buffer),0);
                                    close(clientes[j]);
                                    FD_CLR(clientes[j],&readfds);
                                }
									volcar_usuarios(usuarios,"basededatos.txt");
                                    close(sd);
                                    exit(-1);
                                
                                
                            }
							
                            //Mensajes que se quieran mandar a los clientes (implementar)
                            
                        } 
                        else{
                            bzero(buffer,sizeof(buffer));
                            
                            recibidos = recv(i,buffer,sizeof(buffer),0);
                            string sbuff(buffer);
                            if(recibidos > 0){
								
								if(sbuff.substr(0,sbuff.find(" "))=="USUARIO"){
									char nick[100];
									sscanf(sbuff.c_str(),"USUARIO %s",nick);
									
									string snick= nick;
									strcpy(buffer,"-Err. Usuario incorrecto");
									bool continuar=true;
									for(int j=0;j<usuarios.size() && continuar;j++){
										if(usuarios[j].get_sd()==i){
											strcpy(buffer,"-Err. Usted ya ha iniciado sesion.");
											continuar=false;
										}
									}
									for (int j=0;j<usuarios.size() && continuar;j++){
										if(usuarios[j].get_nick()==snick){
											if(usuarios[j].get_sd()!=-1){
												strcpy(buffer,"-Err. El usuario ya ha iniciado sesion.");
											}
											else{
												strcpy(buffer,"+0k. Usuario correcto");
												usuarios[j].set_sd(i);
											}
											continuar=false;
											
										}
										
									}
									send(i, buffer, sizeof(buffer), 0);
								}
								else if(sbuff.substr(0,sbuff.find(" "))=="PASSWORD"){
									char passwd[100];
									sscanf(sbuff.c_str(),"PASSWORD %s",passwd);
									string spasswd= passwd;
									
									strcpy(buffer,"-Err. Error en la validación");
									for (int j=0;j<usuarios.size();j++){
										if(usuarios[j].get_sd()==i){
											if(usuarios[j].get_valid()){
												strcpy(buffer,"-Err. Usted ya ha validado su usuario");
											}
											else if(usuarios[j].get_passwd()==spasswd){
												usuarios[j].set_valid(true);
												strcpy(buffer,"+0k. Usuario validado");
												break;
											}
											
											break;
										}
										
									}
									
									send(i, buffer, sizeof(buffer), 0);
								}
								else if(sbuff.substr(0,sbuff.find(" "))=="REGISTRO"){
									
									char nick[250],passwd2[250];
									if(sscanf(sbuff.c_str(),"REGISTRO -u %s -p %s",nick,passwd2)!=2){
										strcpy(buffer,"-Err. estructura de comando incorrecta");
									}
									else{
										string snick=nick;
										string spasswd2=passwd2;


										bool ocupado=false;
										for(int i=0;i<usuarios.size() && !ocupado;i++){
											ocupado = ocupado || (usuarios[i].get_nick()==nick);
										}
										
										string aux;
										if(ocupado){
											aux="-Err. Nombre de usuario ya ocupado";
											
										}
										else{
											Usuario aux_us(nick,passwd2);
											usuarios.push_back(aux_us);
											aux="+Ok. Se ha registrado correctamente";
										}
										strcpy(buffer,aux.c_str());
									}

									

									
									send(i, buffer, sizeof(buffer), 0);
								}
								else if(sbuff == "INICIAR-PARTIDA\n"){
									for(int j=0;j<usuarios.size();j++){
										if(usuarios[j].get_sd()==i ){
											
											if(usuarios[j].get_valid()){
												
												if(cola_partida.empty()){
													sbuff="+Ok. Esperando jugadores";
													cola_partida.push(usuarios[j]);
												}
												else{
													
													
													Usuario j2= cola_partida.front();
													//Buscar usuario que estaba en la cola
													int a=0;
													for(a=0;a<usuarios.size();a++){
														if(usuarios[a].get_nick()==j2.get_nick()){
															Partida p(usuarios[a],usuarios[j]);
															partidas.push_back(p);
															sbuff="+Ok. Empieza la partida."+p.get_tablero_jugador(usuarios[a].get_sd())->fold();
															strcpy(buffer,sbuff.c_str());
															send(usuarios[a].get_sd(),buffer,sizeof(buffer),0);

															bzero(buffer,sizeof(buffer));
															sbuff="+Ok. Turno de partida";
															strcpy(buffer,sbuff.c_str());
															send(usuarios[a].get_sd(),buffer,sizeof(buffer),0);

															bzero(buffer,sizeof(buffer));
															sbuff="+Ok. Empieza la partida."+p.get_tablero_jugador(usuarios[j].get_sd())->fold();
															
															cola_partida.pop();
															
															break;
														}
													}
													
												}
											}
											else{
												sbuff="-Err. Usuario no validado";
											}
											break;
										}
									}
									
									strcpy(buffer,sbuff.c_str());
									send(i,buffer,sizeof(buffer),0);
								}
								else if(sbuff.substr(0,sbuff.find(" "))=="DISPARO"){
                                    char c;
									int n;
									string coord;
									if(sscanf(sbuff.c_str(),"DISPARO %c,%d",&c,&n)!=2){
										sbuff="-Err. Coordenada incorrecta";
										strcpy(buffer,sbuff.c_str());
										send(i,buffer,sizeof(buffer),0);
										break;
									}
								
									coord = c + (n==10 ? "0" : to_string(n));
									
									int ipartida=0;
									bool encontrado=false;
									while(ipartida<partidas.size() && !encontrado){
										if(partidas[ipartida].buscar_jugador(i)){
											encontrado=true;
										}
										else{
											ipartida++;
										}
										
									}
									if(!encontrado){
										sbuff="-Err. Usted no se encuentra en ninguna partida.";
										strcpy(buffer,sbuff.c_str());
										send(i,buffer,sizeof(buffer),0);
									}
									else if(!partidas[ipartida].te_toca(i)){
										sbuff="-Err. Debe esperar su turno";
										strcpy(buffer,sbuff.c_str());
										send(i,buffer,sizeof(buffer),0);
									}
									else{
										//Disparas
										string respuesta_oponente;
										respuesta_oponente= sbuff.substr(sbuff.find(" ")+1,sbuff.size());
										respuesta_oponente= "+Ok. Disparo en: "+respuesta_oponente;
										strcpy(buffer,respuesta_oponente.c_str());
										int sd_oponente=partidas[ipartida].get_oponente()->get_sd();
										send(sd_oponente,buffer,sizeof(buffer),0);
										sbuff="+Ok. ";
										string disparo_salida = partidas[ipartida].disparar(coord,i);
										if(disparo_salida=="ERROR"){
											sbuff="-Err. Coordenada incorrecta";
											strcpy(buffer,sbuff.c_str());
											send(i,buffer,sizeof(buffer),0);
											
										}
										else{
											if(disparo_salida=="AGUA"){
												string sturno="+Ok. Turno de partida";
												bzero(buffer,sizeof(buffer));
												strcpy(buffer,sturno.c_str());
												send(sd_oponente,buffer,sizeof(buffer),0);
											}
											sbuff=sbuff+disparo_salida;
											sbuff=sbuff+": "+c+","+to_string(n);
											strcpy(buffer,sbuff.c_str());
											send(i,buffer,sizeof(buffer),0);
											
											if(partidas[ipartida].get_tablero_oponente()->comprobar_finalizado()){
												//gana el otro jugador
												sbuff="+Ok. "+partidas[ipartida].get_jugador()->get_nick()+" ha ganado, número de disparos "+to_string(partidas[ipartida].get_ndisp_jugador());
												strcpy(buffer,sbuff.c_str());
												send(partidas[ipartida].get_jugador()->get_sd(),buffer,sizeof(buffer),0);
												send(partidas[ipartida].get_oponente()->get_sd(),buffer,sizeof(buffer),0);
												partidas.erase(partidas.begin()+ipartida);

											}
											else if(partidas[ipartida].get_tablero_jugador()->comprobar_finalizado()){
												//gana el jugador i
												sbuff="+Ok."+partidas[ipartida].get_oponente()->get_nick()+" ha ganado, número de disparos "+to_string(partidas[ipartida].get_ndisp_oponente());
												strcpy(buffer,sbuff.c_str());
												send(partidas[ipartida].get_oponente()->get_sd(),buffer,sizeof(buffer),0);
												send(partidas[ipartida].get_jugador()->get_sd(),buffer,sizeof(buffer),0);
												partidas.erase(partidas.begin()+ipartida);
											}
											else if(disparo_salida!="AGUA"){
												string sturno="+Ok. Turno de partida";
												bzero(buffer,sizeof(buffer));
												strcpy(buffer,sturno.c_str());
												send(i,buffer,sizeof(buffer),0);
											}
										}
										

									}
									
									
									

                                    
                                    
                                }
                                else if(strcmp(buffer,"SALIR\n") == 0){
                                    int j=0;
									bool encontrado=false;
									while(j<usuarios.size() && !encontrado){
										if(usuarios[j].get_sd()==i){
											encontrado=true;
										}	
										else{
											j++;
										}
									}
									if(encontrado){
										//encontrado, asi que por lo menos está logueado
										if(usuarios[j].get_valid()){
											//puede ser que esté en una partida
											int ipartida=0;
											encontrado=false;
											while(ipartida<partidas.size() && !encontrado){
												if(partidas[ipartida].buscar_jugador(i)){
													encontrado=true;
												}
												else{
													ipartida++;
												}
											}

											if(encontrado){
												sbuff="+Ok. Tu oponente ha terminado la partida";
												strcpy(buffer,sbuff.c_str());
												send(partidas[ipartida].get_oponente(i)->get_sd(),buffer,sizeof(buffer),0);
												partidas.erase(partidas.begin()+ipartida);
												
											}
											else{
												//puede ser que esté en la cola.
												if(!cola_partida.empty() && cola_partida.front().get_nick()==usuarios[j].get_nick()){
													cola_partida.pop();
												}
											}
											usuarios[j].set_valid(false);
										}
										usuarios[j].set_sd(-1);
										
									}
									

									salirCliente(i,&readfds,clientes);
									

                                    
                                    
                                }
                                else{
                                    string aux = "-Err. Orden desconocida.";
                                    

                                    strcpy(buffer,aux.c_str());

                                    
									send(i,buffer,sizeof(buffer),0);

                                    
                                }
                                                                
                                
                            }
                            
                        }
                    }
                }
            }
			
            



			
			
			
		}
		printf("Servidor cerrado\n");
		close(sd);
		volcar_usuarios(usuarios,"basededatos.txt");
		return 0;
	
}

void salirCliente(int socket, fd_set * readfds, vector<int> clientes){
  
    char buffer[250];
    int j;

    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"+Ok. Se ha desconectado correctamente");
	send(socket,buffer,sizeof(buffer),0);
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de clientes
    for (j = 0; j < clientes.size() - 1; j++)
        if (clientes[j] == socket)
            break;
    for (; j < clientes.size() - 1; j++)
        (clientes[j] = clientes[j+1]);
    
    
    
    

            


}