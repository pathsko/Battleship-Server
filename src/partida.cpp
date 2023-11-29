#include "partida.hpp"

string Partida::disparar(string coord,int sd){
    string salida;
    if(sd == jugador1->get_sd()){
        salida= tablero2->disparar(coord);
        ndisp1++;
    }
    else{
        salida= tablero1->disparar(coord);
        ndisp2++;
    }
    if(salida=="AGUA"){
        this->turno = !this->turno;
    }
    return salida;
}
bool Partida::buscar_jugador(int sd){
    return (jugador1->get_sd()==sd) || (jugador2->get_sd()==sd);
}
bool Partida::te_toca(int sd){
    auto jugador = turno ? jugador1 : jugador2;
    return jugador->get_sd()==sd;
}