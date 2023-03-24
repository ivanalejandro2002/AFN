#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <queue>
#include "lectura.h"
using namespace std;

bool lectura(vector<int> &cubeta,string &cad,ifstream &fin){
    getline(fin,cad);
    int i=0;
    for(char co:cad){
        if(cubeta[(int)co]){
            cout<<"No puedes tener dos veces la misma letra en el alfabeto\n";
            return 0;
        }
        cubeta[(int)co]=++i;
    }
    return 1;
}

bool conectar(map<string,int> &traductor,string &cad, vector<map<char,vector<int> > > &transiciones,ifstream &fin,int &nnodos,set<pair<char,pair<int,int> > > &insertados,map<int,string> &traductor_inverso,vector<bool>&aceptacion,vector<int> &cubeta){
    while(getline(fin,cad)){
        if(cad=="#")return 1;
        int i=0;
        string aux="";
        while(i<cad.size() && cad[i]==' ')i++;
        if(i==cad.size()){
            cout<<"Debes de poner el nombre del nodo de inicio el nodo final y el caracter de transicion\n";
            return 0;
        }
        while(i<cad.size() && cad[i]!=' ')aux+=cad[i++];
        if(!traductor[aux]){
            traductor[aux]=++nnodos;
            traductor_inverso[nnodos]=aux;
            transiciones.push_back({});
            aceptacion.push_back(0);
        }
        if(i==cad.size()){
            cout<<"Debes de poner el nombre del nodo de inicio el nodo final y el caracter de transicion\n";
            return 0;
        }


        string aux2="";
        while(i<cad.size() && cad[i]==' ')i++;
        if(i==cad.size()){
            cout<<"Debes de poner el nombre del nodo de inicio el nodo final y el caracter de transicion\n";
            return 0;
        }
        while(i<cad.size() && cad[i]!=' ')aux2+=cad[i++];
        if(!traductor[aux2]){
            traductor[aux2]=++nnodos;
            traductor_inverso[nnodos]=aux2;
            transiciones.push_back({});
            aceptacion.push_back(0);
        }
        i++;
        if(i>=cad.size()){
            cout<<"Debes de poner el nombre del nodo de inicio el nodo final y el caracter de transicion\n";
            return 0;
        }
        while(i<cad.size() && cad[i]==' ')i++;
        if(i==cad.size())i--;
        if(i<cad.size()-1){
            cout<<"Debes de poner el nombre del nodo de inicio el nodo final y el caracter de transicion\n";
            return 0;
        }

        char op=cad[i];

        if(!cubeta[(int)op]){
            cout<<"La letra "<<op<<" no pertenece al alfabeto\n";
            return 0;
        }

        if(!insertados.count({op,{traductor[aux],traductor[aux2]}})){
            transiciones[traductor[aux]][op].push_back(traductor[aux2]);
            insertados.insert({op,{traductor[aux],traductor[aux2]}});
        }else{
            cout<<"No puedes repetir dos veces la misma arista\n";
            return 0;
        }
    }
    cout<<"La lista de conecciones debe de terminar con '#'\n";
    return 0;
}
bool aceptaciones(map<string,int> &traductor,string &cad,vector<bool> &aceptacion,ifstream &fin){
    if(!getline(fin,cad)){
        cout<<"Debes de dejar los estados de aceptacion, si no hay deja la linea en blanco\n";
        return 0;
    }
    int i=0;
    while(i<cad.size()){
        while(i<cad.size() && cad[i]==' ')i++;
        if(i==cad.size())return 1;
        string aux = "";
        while(i<cad.size() && cad[i]!=' ')aux+=cad[i++];
        if(!traductor[aux]){
            cout<<"Los estados de aceptacion deben de existir dentro del AFN, no sirve tener nodos aislados del inicio\n";
            return 0;
        }else{
            aceptacion[traductor[aux]]=1;
        }
    }
    return 1;
}
bool inicio(map<string,int> &traductor, string &cad,ifstream &fin,int &nodoInicial){
    if(!getline(fin,cad)){
        cout<<"Debe de haber un estado inicial\n";
        return 0;
    }
    int i=0;
    while(i<cad.size() && cad[i]==' ')i++;
    if(i==cad.size()){
        cout<<"Debe de haber un estado de inicio\n";
        return 0;
    }
    string aux="";
    while(i<cad.size() && cad[i]!=' ')aux+=cad[i++];
    if(!traductor[aux]){
        cout<<"El nodo inicial debe de estar definido en el AFN\n";
        return 0;
    }
    nodoInicial=traductor[aux];
    return 1;
}
