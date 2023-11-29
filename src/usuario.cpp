#include "usuario.hpp"

using namespace std;

int volcar_usuarios(vector<Usuario> v,string fn){
    ofstream f( fn );
    if(!f.is_open()){
        cerr<<"Error al abrir el archivo"<<endl;
        return -1;
    }
    for(int i=0;i<v.size();i++){
        f<<v[i].get_nick()<<endl;
        f<<v[i].get_passwd()<<endl;
    }
    f.close();
   
    return 0;
}
int cargar_usuarios(vector<Usuario> &v,string fn){
    ifstream f( fn );
    if(!f.is_open()){
        cerr<<"Error al abrir el archivo"<<endl;
        return -1;
    }
    string entrada;
    while(getline(f,entrada)){
        
        Usuario u;
        
        u.set_nick(entrada);
        getline(f,entrada);
        u.set_passwd(entrada);
        v.push_back(u);
    }
    f.close();
    return 0;
}