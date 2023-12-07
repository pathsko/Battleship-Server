#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(int argc, char ** argv){
    int seed = 1000000;
    int nusuarios= atoi(argv[1]);
    vector<long int> datos;
    for(int i=0;i<nusuarios;i++){
        //usuario
        datos.push_back(seed+i);
        //contrasenia
        datos.push_back(seed+i);
    }
    for(int i=0;i<datos.size();i++){
        cout<<datos[i]<<endl;
    }
}