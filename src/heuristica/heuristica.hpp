#ifndef HEURIST_H
#define HEURIST_H
#include "../partida.hpp"
#include <random>
using namespace std;
class Heuristica{
    private:
        mutable vector<vector<float>> matriz;
        int size;
        std::random_device rd;  
        std::mt19937 generador{rd()}; 
    public:
    Heuristica(){
        matriz= vector<vector<float>>(10, vector<float>(10));
        size=10;
    }
    Heuristica(vector<vector<float>> matriz_entrada,int new_size){
            matriz= matriz_entrada;
            size=new_size;
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    matriz[j][i]=0;
                }
            }
    }
    
    vector<vector<float>> get_matriz() const{
        return matriz;
    }
    int get_size(){
        return size;
    }
    void set_matriz(vector<vector<float>> matriz_entrada){
        matriz=matriz_entrada;
    }
    void set_matrizpos(int j,int i, float value) const{
        matriz[j][i]=value;
    }
    void set_size(int new_size){
        size=new_size;
    }

    int selec_dirji(vector<int> &v);
    string selec_dirji();
    virtual int actualizar_tocado(vector<int> coords) const = 0;
    virtual int actualizar_hundido_recursivo(vector<int> coords) const = 0;
    virtual int actualizar_agua(vector<int> coords) const = 0;
    int actualizar_euristica(vector<int> &coords,string resultado);
    string mostrar_mapa_euristico();
    bool comprobar_limite(int j, int i) const;

    string disparar(string resultado);
};

#endif