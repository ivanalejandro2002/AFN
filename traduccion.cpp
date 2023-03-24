#include "lectura.h"
void reset(vector<int> &mascara){
    for(int i=0;i<mascara.size();i++)mascara[i]=0;
}

int siguiente(vector<int> &mascara, int &indice){
    while(1){
        if(indice>=mascara.size())return 0;
        //cout<<__builtin_ctz(mascara[indice])<<"\n";
        if(mascara[indice]>0){
            int sol = __builtin_ctz(mascara[indice])+30*indice +1;
            mascara[indice]&=~(1<<__builtin_ctz(mascara[indice]));
            //cout<<mascara[indice]<<"\n";
            return sol;
        }
        indice++;
    }
}

void traduce(vector<map<char,vector<int> > > &transiciones,int nodoInicial,map<int,string> &traductor_inverso,map<string,int> &traductor,string &alfabeto,vector<bool> &aceptacion){
    vector<vector<int> > AFD;
    map<vector<int>,int > nodoAFD;
    vector<int> datos((transiciones.size()+29)/30);
    AFD.resize(2);
    datos[0]=1;
    int cantidadNodos=0;
    set<vector<int> > checados;
    queue<vector<int> > bfs;
    bfs.push(datos);
    checados.insert(datos);
    nodoAFD[datos]=++cantidadNodos;
    int indice;
    int actual,objetivo;
    vector<int> estadosAceptados(2);
    if(aceptacion[1])estadosAceptados[1]=1;
    bool esteEsAceptado=0;
    while(!bfs.empty()){
        datos = bfs.front();
        actual = nodoAFD[datos];
        for(char co:alfabeto){
            esteEsAceptado=0;
            datos = bfs.front();
            indice=0;
            vector<int> nuevoConjunto(datos.size());
            int sig;
            do{
                sig=siguiente(datos,indice);
                if(sig){
                    if(!transiciones[sig][co].empty()){
                        for(int z:transiciones[sig][co]){
                            int auxi = z-1;
                            nuevoConjunto[auxi/30]|=(1<<(auxi%30));
                            if(aceptacion[z])esteEsAceptado=1;
                        }
                    }else{
                        transiciones[sig].erase(co);
                    }
                }
            }while(sig);
            if(!checados.count(nuevoConjunto)){
                estadosAceptados.push_back(esteEsAceptado);
                AFD.push_back({});
                checados.insert(nuevoConjunto);
                nodoAFD[nuevoConjunto]=++cantidadNodos;
                bfs.push(nuevoConjunto);
            }
            AFD[actual].push_back(nodoAFD[nuevoConjunto]-1);
        }
        bfs.pop();
    }

    ofstream fout;
    fout.open("AFD.in");
    fout<<AFD.size()-1<<"\n";
    fout<<alfabeto<<"\n";
    for(int i=1;i<=cantidadNodos;i++){
        fout<<"q"<<i-1<<" ";
    }
    fout<<"\n";
    for(int i=1;i<=cantidadNodos;i++){
        fout<<"q"<<i-1<<" ";
        for(int z: AFD[i]){
            fout<<"q"<<z<<" ";
        }
        fout<<"\n";
    }
    for(int i=1;i<=cantidadNodos;i++){
        if(estadosAceptados[i])fout<<"q"<<i-1<<" ";
    }
    fout<<"\nq0\n";
}
