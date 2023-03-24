#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <queue>
using namespace std;
///Funciones de lectura
bool lectura(vector<int> &,string &,ifstream &);
bool conectar(map<string,int> &,string &, vector<map<char,vector<int> > > &,ifstream &,int &,set<pair<char,pair<int,int> > > &,map<int,string> &,vector<bool>&,vector<int> &);
bool aceptaciones(map<string,int> &,string &,vector<bool> &,ifstream &);
bool inicio(map<string,int> &, string &,ifstream &,int &);

///Funciones traductoras
void reset(vector<int> &);
int siguiente(vector<int> &, int &);
void traduce(vector<map<char,vector<int> > > &,int,map<int,string> &,map<string,int> &,string &,vector<bool> &);
