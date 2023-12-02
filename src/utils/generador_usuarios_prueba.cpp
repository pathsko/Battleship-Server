#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(int argc, char ** argv){
    srand(time(NULL));
    int nusuarios= atoi(argv[1]);
    vector<long int> datos;
    for(int i=0;i<nusuarios;i++){
        //usuario
        datos.push_back(rand()%100000000);
        //contrasenia
        datos.push_back(rand()%100000000);
    }
    for(int i=0;i<datos.size();i++){
        cout<<datos[i]<<endl;
    }
}