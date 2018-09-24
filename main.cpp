#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

#define getlinha cin.getline(linha,256)
#define getspace cin.getline(linha,256,' ')

typedef struct{
	double x, y;
}ponto;

typedef struct{
	int valor, peso;
}item;

int tam, n_itens, cap, max_time, min_speed, max_speed;
vector<int> itens_ind[1000];
int dist[1000][1000];
ponto p[1000];
item  v[10000];
char linha[256], filter[256];

int get_num(){
	getspace;
	getlinha;
	
	int cont = 0;
	for(int i=0; i<strlen(linha); i++){
		if(linha[i]!=' '){
			filter[cont]=linha[i];
			cont++;
		}
	}
	filter[cont] = '\0';
	return atoi(filter);
}

int main(){
	
	getlinha;
	getlinha;
	tam = get_num();
	n_itens = get_num();
	cap = get_num();
	max_time = get_num();
	min_speed = get_num();
	max_speed = get_num();
	getlinha;
	getlinha;
	int ind;
	for(int i=1; i<=tam; i++){
		getspace;
		ind = atoi(linha)
		getspace;
		p[ind].x = atof(linha);
		getlinha;
		p[ind].y = atof(linha);
	}
	
	for(int i=1; i<=n_itens; i++){
		getspace;
		ind = atoi(linha);
		getspace;
		v[ind].valor = atoi(linha);
		getspace;
		v[ind].peso = atoi(linha);
		getspace;
		itens_ind[atoi(linha)].push_back(ind);
	}
	
	for(int i=1; i<=tam; i++){
		cout << i << " : " << p[i].x << '-' << p[i].y << endl;
	}
	
	cout << "-----------" << endl;
	
	for(int i=1; i<=n_itens; i++){
		cout << i << " : " << v[i].valor << '-' << v[i].peso << endl; 
	}
	
	cout << "-----------" << endl;
	
	for(int i=1; i<=tam; i++){
		cout << i << " : ";
		for(int j=0; j<itens_ind[i].size(); j++)
			cout << itens_ind[i][j] << " ";
		cout << endl;
	}
	
	return 0;
}
