#ifndef HEURIST1_H
#define HEURIST1_H
#include "heuristica.hpp"
using namespace std;
class Heuristicastr1 : public Heuristica {
public:
    Heuristicastr1() : Heuristica(){}
    Heuristicastr1(vector<vector<float>> matriz_entrada,int new_size) : Heuristica(matriz_entrada,new_size){}
        public:
        int actualizar_agua(vector<int> coords) const override{
            set_matrizpos(coords[0],coords[1],-1);
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