#include "lectura.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <queue>

#define LSOne(S) ((S) & (-S))

using namespace std;
int main()
{
    ifstream fin;
    fin.open("AFN.in");
    string alfabeto;
    string cad;
    vector<int> cubeta(256);
    map<string,int> traductor;
    map<int,string> traductor_inverso;
    vector<map<char,vector<int> > >transiciones(1);
    vector<bool> aceptacion(1);
    set<pair<char,pair<int,int> > >insertados;
    int nnodos=0;
    int nodoInicial;
    ///Aqui leemos el diccionario

    if(!lectura(cubeta,alfabeto,fin))return 0;
    if(!conectar(traductor,cad,transiciones,fin,nnodos,insertados,traductor_inverso,aceptacion,cubeta))return 0;
    if(!aceptaciones(traductor,cad,aceptacion,fin))return 0;
    if(!inicio(traductor,cad,fin,nodoInicial))return 0;
    map<char,vector<int> >::iterator it;
    /*for(int i=1;i<=nnodos;i++){
        cout<<traductor_inverso[i]<<":\n";
        for(it=transiciones[i].begin();it!=transiciones[i].end();it++){
            for(int z: it->second){
                cout<<it->first<<"::"<<traductor_inverso[z]<<"\n";
            }
        }
    }*/

    traduce(transiciones,nodoInicial,traductor_inverso,traductor,alfabeto,aceptacion);
    return 0;
}
