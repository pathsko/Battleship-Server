#ifndef USUARIO_HPP
#define USUARIO_HPP
#

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Usuario{
    private:
    string nick;
    string passwd;
    bool validado;
    int sd;

    public:
        Usuario(string nick_,string passwd_,bool validado_=false,int sd_=-1){
            nick=nick_;
            passwd=passwd_;
            validado= validado_;
            sd=sd_;
        }
        Usuario(){
            nick="";
            passwd="";
            validado=false;
            sd=-1;
        }

        string get_nick(){
            return nick;
        }
        string get_passwd(){
            return passwd;
        }
        bool get_valid(){
            return validado;
        }
        int get_sd(){
            return sd;
        }

        void set_nick(string nnick){
            nick=nnick;
        }
        void set_passwd(string npasswd){
            passwd=npasswd;
        }
        void set_valid(bool isvalid){
            validado=isvalid;
        }
        void set_sd(int nsd){
            sd=nsd;
        }



};

    int volcar_usuarios(vector<Usuario> v,string fn);
    int cargar_usuarios(vector<Usuario> &v,string fn);



#endif