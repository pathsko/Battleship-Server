#ifndef HEURIST2_H
#define HEURIST2_H
#include "heuristica.hpp"
using namespace std;
class Heuristicastr2 : public Heuristica {
public:
    Heuristicastr2() : Heuristica(){}
    Heuristicastr2(vector<vector<float>> matriz_entrada,int new_size,int new_id,Partida &partida_n) : Heuristica(matriz_entrada,new_size,new_id,partida_n){}
    Heuristicastr2(vector<vector<float>> matriz_entrada,int new_size,int new_id,std::shared_ptr<Partida> &partida_n) : Heuristica(matriz_entrada,new_size,new_id,partida_n){}
        public:
        int actualizar_agua(vector<int> coords) const override{
            set_matrizpos(coords[0],coords[1],-1);
            for(int i=coords[0]-1;i<=coords[0]+1;i++){
                for(int j=coords[1]-1;j<=coords[1]+1;j++){
                    int valorj=j,valori=i;
                    if(i>=10){
                        i=9;
                    }
                    else if(i<0){
                        i=0;
                    }

                    if(j>=10){
                        j=9;
                    }
                    else if(j<0){
                        j=0;
                    }
                    if((i!=j && get_matriz()[j][i]>=0 && get_matriz()[j][i]<1.0) ){
                        set_matrizpos(j,i,0.5);
                    }
                    i=valori;
                    j=valorj;
                }
            }
            return 1;
        }
        int actualizar_tocado(vector<int> coords) const override {
            int j=coords[0];
            int i=coords[1];
        
            for(int a=-1;a<2;a+=2){
                try{
                        if(comprobar_limite(j+a,i) && get_matriz()[j+a][i]>=0){
                            set_matrizpos(j+a,i,1);
                        }
                    }
                catch (...){

                }
                try{
                        if(comprobar_limite(j,i+a) && get_matriz()[j][i+a]>=0){
                            set_matrizpos(j,i+a,1);
                        }
                    }
                catch (...){

                }
            }
        
            set_matrizpos(j,i,-2);




            for(int a=-1;a<2;a+=2){
                for(int b=-1;b<2;b+=2){
                    try{
                        if(comprobar_limite(j+a,i+b) && get_matriz()[j+a][i+b]>=0){
                            set_matrizpos(j+a,i+b,-1);
                        }
                    }
                    catch (...){

                    }
                }
            }
        
            return 1;
        }
        int actualizar_hundido_recursivo(vector<int> coords) const override{


            set_matrizpos(coords[0],coords[1],-1);
            for(int i=coords[1]-1;i<coords[1]+2;i++){
                for(int j=coords[0]-1;j<coords[0]+2;j++){
                    if(comprobar_limite(j,i)){
                        if(get_matriz()[j][i]==-2){
                        vector<int> coords2;
                        coords2.push_back(j);
                        coords2.push_back(i);
                        actualizar_hundido_recursivo(coords2);
                    }
                    else{
                        set_matrizpos(j,i,-1);
                    }
                    }
                    
                    
                    
                }
            }
            return 1;

        }
};


#endif