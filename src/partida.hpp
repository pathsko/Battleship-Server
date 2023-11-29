#ifndef PARTIDA_H
#define PARTIDA_H
#include <memory>
#include "usuario.hpp"
#include "tablero.hpp"
using namespace std;

class Partida{
    private:
        shared_ptr<Usuario> jugador1;
        shared_ptr<Usuario> jugador2;
        int ndisp1;
        int ndisp2;
        shared_ptr<Tablero> tablero1;
        shared_ptr<Tablero> tablero2;
        //Indica si le toca al jugador 1
        bool turno=true;

    public:
        Partida(){
            srand(time(NULL));
            jugador1=make_shared<Usuario>();
            jugador2=make_shared<Usuario>();
            tablero1=std::make_shared<Tablero>();
            tablero1->generar_tablero();
            tablero2=std::make_shared<Tablero>();
            ndisp1=0;
            ndisp2=0;
        }
        Partida(Usuario &jugador1_,Usuario &jugador2_){
            srand(time(NULL));
            jugador1=std::make_shared<Usuario>(jugador1_);
            jugador2=std::make_shared<Usuario>(jugador2_);
            tablero1=std::make_shared<Tablero>();
            tablero1->generar_tablero();
            tablero2=std::make_shared<Tablero>();
            ndisp1=0;
            ndisp2=0;
        }
        Partida(shared_ptr<Usuario> jugador1_,shared_ptr<Usuario> jugador2_,shared_ptr<Tablero> tablero1_,
        shared_ptr<Tablero> tablero2_){
            jugador1=jugador1_;
            jugador2=jugador2_;
            tablero1=tablero1_;
            tablero2=tablero2_;
            ndisp1=0;
            ndisp2=0;
        }
        Partida(Usuario &jugador1_,Usuario &jugador2_,Tablero &tablero1_,
        Tablero &tablero2_){
            jugador1=std::make_shared<Usuario>(jugador1_);
            jugador2=std::make_shared<Usuario>(jugador2_);
            tablero1=std::make_shared<Tablero>(tablero1_);
            tablero2=std::make_shared<Tablero>(tablero2_);
            ndisp1=0;
            ndisp2=0;
        }

        shared_ptr<Usuario> get_jugador1(){
            return jugador1;
        }
        shared_ptr<Usuario> get_jugador2(){
            return jugador2;
        }
        shared_ptr<Tablero> get_tablero1(){
            return tablero1;
        }
        shared_ptr<Tablero> get_tablero2(){
            return tablero2;
        }

        void set_jugador1(shared_ptr<Usuario> jugador1_){
            jugador1=jugador1_;
        }
        void set_jugador2(shared_ptr<Usuario> jugador2_){
            jugador2=jugador2_;
        }
        void set_tablero1(shared_ptr<Tablero> tablero1_){
            tablero1=tablero1_;
        }
        void set_tablero2(shared_ptr<Tablero> tablero2_){
            tablero2=tablero2_;
        }
        shared_ptr<Usuario> get_jugador(int sd){
            if(sd==jugador1->get_sd()){
                return jugador1;
            }
            else if(sd==jugador2->get_sd()){
                return jugador2;
            }
            else{
                return nullptr;
            }
        }
        shared_ptr<Usuario> get_oponente(int sd){
            if(sd==jugador1->get_sd()){
                return jugador2;
            }
            else if(sd==jugador2->get_sd()){
                return jugador1;
            }
            else{
                return nullptr;
            }
        }
        shared_ptr<Usuario> get_jugador(){
            return turno ? jugador1 : jugador2;
        }
        shared_ptr<Usuario> get_oponente(){
            return !turno ? jugador1 : jugador2;
        }
        shared_ptr<Tablero> get_tablero_jugador(){
            return turno ? tablero1 : tablero2;
        }
        shared_ptr<Tablero> get_tablero_oponente(){
            return !turno ? tablero1 : tablero2;
        }
        shared_ptr<Tablero> get_tablero_jugador(int sd){
            if(sd==jugador1->get_sd()){
                return tablero1;
            }
            else if(sd==jugador2->get_sd()){
                return tablero2;
            }
            else{
                return nullptr;
            }
        }
        shared_ptr<Tablero> get_tablero_oponente(int sd){
            if(sd==jugador1->get_sd()){
                return tablero2;
            }
            else if(sd==jugador2->get_sd()){
                return tablero1;
            }
            else{
                return nullptr;
            }
        }
        bool get_turno(){
            return turno;
        }
        int get_ndisp_jugador(){ return turno ? ndisp1 : ndisp2; }
        int get_ndisp_oponente(){ return !turno ? ndisp1 : ndisp2; }
        string disparar(string coord,int sd);
        bool buscar_jugador(int sd);
        bool te_toca(int sd);
};

#endif