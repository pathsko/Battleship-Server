#include "tablero.hpp"
#include <iostream>
#include <cassert>
using namespace std;

string Tablero::mostrar_tablero(){
    string salida = "";

    // Agregar encabezados de columnas
    salida += "   A  B  C  D  E  F  G  H  I  J\n";
    
    for(int i = 0; i < matriz.size(); i++){
        // Agregar encabezado de fila
        string espacio_extra="";
        if(i!=9){
            espacio_extra=" ";
        }
        salida += espacio_extra+to_string(i + 1) + " ";
        
        for(int j = 0; j < matriz[i].size(); j++){
            
            if(j == matriz[i].size() - 1){
                salida += matriz[i][j] + "  ";
            }
            else{
                salida += matriz[i][j] + "  ";
            }
        }
        if(i != matriz.size() - 1){
            salida += "\n";
        }
    }
    
    return salida;
}

string Tablero::mostrar_tablero_oculto(){
    string salida ="";
    for(int i=0;i<oculto.size();i++){
        for(int j=0;j<oculto[i].size();j++){
            
            if(j==oculto[i].size()-1){
                salida=salida+oculto[i][j]+";";
            }
            else{
                salida=salida+oculto[i][j]+",";
            }
        }
        salida=salida+"\n";
    }
return salida;
}
bool fuera_rango(int y,int x){
    if(y>=10 || y<0 || x>=10 || x<0){
        return true;
    }
    return false;
}
bool Tablero::comprobar_colindante(int y, int x){

    if(fuera_rango(y,x)){
        return true;
    }
    for(int i=y-1;i<=y+1;i++){
        for(int j=x-1;j<=x+1;j++){
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

            if(matriz[i][j]=="B"){
                return true;
            }
            i=valori;
            j=valorj;
        }
    }
    return false;
}
bool Tablero::comprobar_colindante_general(int y, int x,string buscado){

    if(fuera_rango(y,x)){
        return true;
    }
    for(int i=y-1;i<=y+1;i++){
        for(int j=x-1;j<=x+1;j++){
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

            if(matriz[i][j]==buscado){
                return true;
            }
            i=valori;
            j=valorj;
        }
    }
    return false;
}
bool Tablero::comprobar_colindante_tocado(int y, int x){

    if(fuera_rango(y,x)){
        return true;
    }
    matriz[y][x]="R";
    for(int i=y-1;i<=y+1;i++){
        for(int j=x-1;j<=x+1;j++){
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

            if(matriz[i][j]=="B"){
                matriz[y][x]="T";
                return true;
            }
            i=valori;
            j=valorj;
        }
    }
    for(int i=y-1;i<=y+1;i++){
        for(int j=x-1;j<=x+1;j++){
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

            if( matriz[i][j]=="T"){
                if(comprobar_colindante_tocado(i,j)){
                    matriz[y][x]="T";
                    return true;
                }
            }
            i=valori;
            j=valorj;
        }
    }
    matriz[y][x]="T";
    return false;
}
void Tablero::aniadir_barcos(int nBarcos,int tam){

    for(int cont=0;cont<nBarcos;cont++){
        while(true){
            int mode = rand()%4;
            int x=rand()%10;
            int y=rand()%10;
            
            if(mode==0 && x+tam-1<10){
                bool ocupado=false;
                for(int i=0;i<tam;i++){
                    ocupado = ocupado || comprobar_colindante_general(y,x+i,"B");
                }
                if(!ocupado){
                    for(int i=0;i<tam;i++){
                        matriz[y][x+i]="B";
                    
                    }
                    break;
                
                }
                
            }
            if(mode==1 && x-tam+1>=0){
                bool ocupado=false;
                for(int i=0;i<tam;i++){
                    ocupado = ocupado || comprobar_colindante_general(y,x-i,"B");
                }
                if(!ocupado){
                    for(int i=0;i<tam;i++){
                        matriz[y][x-i]="B";
                        
                    }
                    break;
                }
                
            }
            if(mode==2  && y+tam-1<10){
                bool ocupado=false;
                for(int i=0;i<tam;i++){
                    ocupado = ocupado || comprobar_colindante_general(y+i,x,"B");
                }
                if(!ocupado){
                    for(int i=0;i<tam;i++){
                        matriz[y+i][x]="B";
                        
                    }
                    break;
                }
                
            }
            if(mode==3 && y-tam+1>=0){
                bool ocupado=false;
                for(int i=0;i<tam;i++){
                    ocupado = ocupado || comprobar_colindante_general(y-i,x,"B");
                }
                if(!ocupado){
                    for(int i=0;i<tam;i++){
                        matriz[y-i][x]="B";
                    }
                    break;
                
                }
                
            }
    }


    }

}
//1 barco de 4 espacios, 2 de 3 espacios, 2 de 2 espacios
void Tablero::generar_tablero(){
    
    for(int i=0;i<matriz.size();i++){
        for(int j=0;j<matriz[i].size();j++){
            matriz[i][j]="A";
            oculto[i][j]="X";

        }
    }
    //4 espacios
    
    aniadir_barcos(1,4);

    //2 barcos de 3 espacios
    aniadir_barcos(2,3);
    aniadir_barcos(2,2);
    


    
}
string Tablero::disparar(int y, string sx){
    if(y<0 || y>10 || mapaCeldas.count(sx)!=1){
        return "ERROR";
    }
    int x= mapaCeldas[sx];

    if(matriz[y][x]=="A"){
        oculto[y][x]="A";
        return "AGUA";
    }
    else if(matriz[y][x]=="B"){
        matriz[y][x]="T";
        oculto[y][x]="T";
        if(!comprobar_colindante_tocado(y,x)){
            transformar_hundido(y,x);
            return "HUNDIDO";
        }
        else{
            return "TOCADO";
        }
    }
    else{
        return "TOCADO";
    }

}
string Tablero::disparar(string coord){
    if(coord.size()!=2){
        
        return "ERROR";
    }
    int y=coord[1]-'0';
    if(y==0){
        y=10;
    }
    y--;

    string x=coord.substr(0,1);
    return this->disparar(y,x);
}

bool Tablero::comprobar_finalizado(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(matriz[i][j]=="B"){
                return false;
            }

        }
    }
    return true;
}
bool Tablero::comprobar_colindante_referencia(int &y,int &x,string buscado){
    if(comprobar_colindante_general(y,x,buscado)){
        for(int i=y-1;i<=y+1;i++){
            for(int j=x-1;j<=x+1;j++){
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

                if(matriz[i][j]==buscado){
                    y=i;
                    x=j;
                    return true;
                }
                i=valori;
                j=valorj;
            }
        }
    }
    return false;
}
bool Tablero::transformar_hundido(int y, int x){
    
    if(fuera_rango(y,x)){
        return true;
    }
    matriz[y][x]="H";
    oculto[y][x]="H";
    for(int i=y-1;i<=y+1;i++){
        for(int j=x-1;j<=x+1;j++){
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

            if(matriz[i][j]=="T"){
                transformar_hundido(i,j);
            }
            i=valori;
            j=valorj;
        }
    }
    return false;
}

string Tablero::fold(){
    string salida ="";
    for(int i=0;i<matriz.size();i++){
        for(int j=0;j<matriz[i].size();j++){
            
            if(j==matriz[i].size()-1 && i==9){
                salida=salida+matriz[i][j]+".";
            }
            else if(j==matriz[i].size()-1){
                salida=salida+matriz[i][j]+";";
            }
            else{
                salida=salida+matriz[i][j]+",";
            }
        }
        
    }
    return salida;
}
void Tablero::unfold(string tablero){
    matriz= vector<vector<string>>(10, vector<string>());
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j+=2){
            char c = tablero[j+20*i];
            string caract(1,c);
            matriz[i].push_back(caract);

        }
    }
}

string mostrar_tableros(Tablero tablero1, Tablero tablero2){
    auto t1= tablero1.get_matriz();
    auto t2= tablero2.get_matriz();
    string salida = "";
    
    // Agregar encabezados de columnas
    salida += "   A  B  C  D  E  F  G  H  I  J         A  B  C  D  E  F  G  H  I  J\n";
    
    for(int i = 0; i < t1.size(); i++){
        // Agregar encabezado de fila
        string espacio_extra="";
        if(i!=9){
            espacio_extra=" ";
        }
        salida += espacio_extra+to_string(i + 1) + " ";
        
        for(int j = 0; j < t1[i].size(); j++){
            
            if(j == t1[i].size() - 1){
                salida += t1[i][j];
            }
            else{
                salida += t1[i][j] + "  ";
            }
        }
        salida+="      "+espacio_extra+to_string(i + 1) + " ";
        for(int j = 0; j < t1[i].size(); j++){
            
            if(j == t2[i].size() - 1){
                salida += t2[i][j];
            }
            else{
                salida += t2[i][j] + "  ";
            }
        }
        if(i != t1.size() - 1){
            salida += "\n";
        }
    }
    
    return salida;
}
 void Tablero::set_celda(string coord, string new_value){
    int y=coord[1]-'0';
    int x=mapaCeldas[coord.substr(0,1)];
    matriz[y][x]=new_value;
    if(new_value=="H"){
        transformar_hundido(y,x);
    }
    
}

