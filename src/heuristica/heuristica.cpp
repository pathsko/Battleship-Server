#include "heuristica.hpp"
int Heuristica::selec_dirji(vector<int> &v){
        map<float,int> conteo;
        
        for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(conteo.count(matriz[j][i])>0){
                        conteo.at(matriz[j][i])++;
                    }
                    else{
                        conteo.insert(make_pair(matriz[j][i],1));
                    }
                }
        }
        //Conteo realizado
        float valor;
        if(conteo.count(1)>0){
            valor=1;
        }
        else if(conteo.count(0.5)>0){
            valor=0.5;
        }
        else if(conteo.count(0)>0){
            valor=0;
        }
        else{
            return -1;
        }
        int nval=0;

        //Ya sabemos que toca

        if(conteo.at(valor)==1){
            //Todo easy as fuck
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(matriz[j][i]==valor){
                        v[0]=j;
                        v[1]=i;
        
                        return 1;
                    }
                }
            }
        }
        else{
            //Hay que elegir amai
            vector<int> coordsj;
            vector<int> coordsi;
            conteo.clear();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(matriz[j][i]==valor){
                        coordsj.push_back(j);
                        coordsi.push_back(i);
                    }
                }
            }
            int cont=0;
            std::uniform_int_distribution<int> distribucion(0, coordsj.size()-1);
            int random = distribucion(generador);
            v[0]=coordsj[random];
            v[1]=coordsi[random];
            
            return 1;

        }
        return 1;
}
string Heuristica::selec_dirji(vector<int> &v, int modo){
    vector<string> alfabeto({ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"});
    selec_dirji(v);
    string res= alfabeto[v[0]]+","+to_string(v[1]+1);
    return res;
}
bool Heuristica::comprobar_limite(int j,int i) const {
    //devuelve true si es valido, sino devuelve false
    return !(j<0 || j>size-1 || i<0 || i>size-1);
}

int Heuristica::actualizar_euristica(vector<int> &coords,string resultado){
    if(resultado=="AGUA"){
        actualizar_agua(coords);
        return 1;
    }
    else if(resultado=="TOCADO"){
        actualizar_tocado(coords);
        return 1;

    }
    else if(resultado=="HUNDIDO"){ 
    
        matriz[coords[0]][coords[1]]=-2;
        actualizar_hundido_recursivo(coords);
        return 1;
    }
    else{
        return -1;
    }
}
string Heuristica::disparar(string resultado){
    if(resultado!="AGUA" && resultado!="TOCADO" && resultado!="HUNDIDO"){
        return "NADA";
    }
    vector<string> alfabeto({ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"});
    vector<int> coords(2);
    selec_dirji(coords);
    string scoords;
    if(coords[1]==9){
        scoords= alfabeto[coords[0]]+to_string(0);
    }
    else{
        scoords= alfabeto[coords[0]]+to_string(coords[1]+1);
    }
  
    string scoords_mostrar= alfabeto[coords[0]]+","+to_string(coords[1]+1);

    //dispara jugador1 que siempre es el "bot"void reset();
    actualizar_euristica(coords,resultado);
    return scoords_mostrar;
}

string Heuristica::disparar(string resultado,vector<int> coords){
    if(resultado!="AGUA" && resultado!="TOCADO" && resultado!="HUNDIDO"){
        return "NADA";
    }
    vector<string> alfabeto({ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"});

    string scoords;
    if(coords[1]==9){
        scoords= alfabeto[coords[0]]+to_string(0);
    }
    else{
        scoords= alfabeto[coords[0]]+to_string(coords[1]+1);
    }
  
    string scoords_mostrar= alfabeto[coords[0]]+","+to_string(coords[1]+1);

    //dispara jugador1 que siempre es el "bot"
    actualizar_euristica(coords,resultado);
    return scoords_mostrar;
}

string Heuristica::mostrar_mapa_euristico(){
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
                salida += to_string(matriz[j][i]) + "  ";
            }
            else{
                salida += to_string(matriz[j][i]) + "  ";
            }
        }
        if(i != matriz.size() - 1){
            salida += "\n";
        }
    }
    
    return salida;

}
void Heuristica::reset(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            matriz[j][i]=0;
        }
    }
}