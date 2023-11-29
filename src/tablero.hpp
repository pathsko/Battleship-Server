#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

class Tablero{
    private:
        vector<vector<string>> matriz;
        map<string,int> mapaCeldas;
        vector<vector<string>> oculto;

    public:
        Tablero(){
            matriz= vector<vector<string>>(10, vector<string>(10));
            oculto= vector<vector<string>>(10, vector<string>(10));
            for(int i=0;i<matriz.size();i++){
                for(int j=0;j<matriz[i].size();j++){
                    matriz[i][j]="A";
                    oculto[i][j]="X";

                }
            }
            vector<string> alfabeto({ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"});
            for(int i=0;i<10;i++){
                mapaCeldas.insert(make_pair(alfabeto[i],i));
            }
            
            generar_tablero();
        }
        Tablero(vector<vector<string>> matriz_entrada){
            matriz= matriz_entrada;
            oculto= vector<vector<string>>(10, vector<string>(10));
            vector<string> alfabeto({ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"});
            for(int i=0;i<10;i++){
                mapaCeldas.insert(make_pair(alfabeto[i],i));
            }
        }
        vector<vector<string>> get_matriz(){
            return matriz;
        }
        vector<vector<string>> get_matriz_oculto(){
            return oculto;
        }
        void set_celda(string coord, string new_value);
        string mostrar_tablero();
        string mostrar_tablero_oculto();
        string fold();
        void unfold(string tablero);
        void generar_tablero();

        bool comprobar_colindante(int y, int x);
        bool comprobar_colindante_general(int y, int x,string buscado);

        void aniadir_barcos(int nBarcos,int tam);
        string disparar(int y, string sx);
        string disparar(string coord);
        bool comprobar_finalizado();
        bool transformar_hundido(int y, int x);
        bool comprobar_colindante_referencia(int &y,int &x,string buscado);
        bool comprobar_colindante_tocado(int y, int x);
};

string mostrar_tableros(Tablero tablero1, Tablero tablero2);


#endif