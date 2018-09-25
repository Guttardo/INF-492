#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

#define getlinha      prob.getline(linha,256)
#define getespaco     prob.getline(linha,256,' ')
#define getdoispontos prob.getline(linha,256,':')

typedef struct{
	double x, y;
}ponto;

typedef struct{
	double valor, peso;
}item;

//arquivo do problema e de solução
fstream prob, sol;

//parâmetros do problema
int tam, n_itens, cap;
double max_time, min_speed, max_speed, speed_atual;
vector<int> itens_ind[1001];
int dist[1001][1001];
ponto p[1001];
item  v[10001];
vector<int> plano_rota, plano_coleta;
int score=0, peso=0;
double tempo = 0.0, reducao_vel;
bool inviavel = false;

//cursores para leitura dos arquivos
char linha[256], filter[256];

int get_int(){
	getdoispontos;
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

double get_double(){
	getdoispontos;
	getlinha;
	int ind = -1;
	double decimal = 1.0;
	double num=0.0;
	for(int i=0; i<strlen(linha); i++)
		if(linha[i]=='.') ind = i;
	if(ind==-1){
		ind = strlen(linha);
	}

	for(int i=ind-1; i>=0; i--){
		if(linha[i]!=' '){
			num += (int(linha[i])-48)*decimal;
			
			decimal*=10.0;
		}
	}
	decimal = 0.1;
	for(int i=ind+1; i<strlen(linha); i++){
		if(linha[i]!=' '){
			num += (int(linha[i])-48)*decimal;
			decimal/=10.0;
		}
	}

	return num;
}

void le_prob(){
	getlinha;
	getlinha;
	tam = get_int();
	n_itens = get_int();
	cap = get_int();
	max_time = get_double();
	min_speed = get_double();
	
	max_speed = get_double();
	getlinha;
	getlinha;
	int ind;
	for(int i=1; i<=tam; i++){
		getespaco;
		ind = atoi(linha);
		getespaco;
		p[ind].x = atof(linha);
		getlinha;
		p[ind].y = atof(linha);
	}
	getlinha;
	for(int i=1; i<=n_itens; i++){
		getespaco;
		ind = atoi(linha);
		getespaco;
		v[ind].valor = atoi(linha);
		getespaco;
		v[ind].peso = atoi(linha);
		getlinha;
		itens_ind[atoi(linha)].push_back(ind);
	}
}

void le_sol(){
	char c;
	int i = 0;
	c = sol.get(); c = sol.get();
	while(c!=']'){
		if(c!=','){
			filter[i] = c;
			i++;
		}
		else{
			filter[i] = '\0';
			plano_rota.push_back(atoi(filter));
			i = 0;
		}
		c = sol.get();
	}
	filter[i] = '\0';
	plano_rota.push_back(atoi(filter));
	i = 0;
	c = sol.get(); c = sol.get(); c = sol.get();
	while(c!=']'){
		if(c!=','){
			filter[i] = c;
			i++;
		}
		else{
			filter[i] = '\0';
			plano_coleta.push_back(atoi(filter));
			i = 0;
		}
		c = sol.get();
	}
	filter[i] = '\0';
	plano_coleta.push_back(atoi(filter));

}

void calcula_dist(){
	double real;
	int inteiro;
	for(int i=1; i<=tam; i++)
		for(int j=1; j<=tam; j++){
			real = sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y));
			inteiro = floor(real);
			if(real==inteiro)
				dist[i][j] = inteiro;
			else
				dist[i][j] = inteiro+1;
		}
}

void verifica_solucao(){
	tempo+=dist[1][plano_rota[0]]/speed_atual;
	for(int i=1; i<plano_rota.size(); i++){
		if(tempo>max_time){
			inviavel = true;
			return;
		}
		for(int j=0; j<plano_coleta.size(); j++){
			for(int k=0; k<itens_ind[plano_rota[i-1]].size(); k++){
				if(plano_coleta[j]==itens_ind[plano_rota[i-1]][k]){
					peso+=v[plano_coleta[j]].peso;
					score+=v[plano_coleta[j]].valor;
					if(peso>cap){
						inviavel = true;
						return;
					}
					speed_atual-= v[plano_coleta[j]].peso*reducao_vel;
				}
			}
		}
		tempo+=dist[plano_rota[i-1]][plano_rota[i]]/speed_atual;
	}
	if(tempo>max_time){
		inviavel = true;
		return;
	}
	
	for(int j=0; j<plano_coleta.size(); j++){
		for(int k=0; k<itens_ind[plano_rota[plano_rota.size()-1]].size(); k++){
			if(plano_coleta[j]==itens_ind[plano_rota[plano_rota.size()-1]][k]){
				peso+=v[plano_coleta[j]].peso;
				score+=v[plano_coleta[j]].valor;
				if(peso>cap){
					inviavel = true;
					return;
				}
				speed_atual-= v[plano_coleta[j]].peso*reducao_vel;
			}
		}
	}
	
	tempo+=dist[plano_rota[plano_rota.size()-1]][tam]/speed_atual;
	
	if(tempo>max_time){
		inviavel = true;
		return;
	}
}


int main(int argc, char *argv[ ]){
	
	prob.open(argv[1], fstream::in);
	sol.open(argv[2], fstream::in);
	fstream dis;
	
	le_prob();
	le_sol();
	prob.close();
	sol.close();
	calcula_dist();
	reducao_vel = (max_speed-min_speed)/cap;
	speed_atual = max_speed;
	verifica_solucao();
	if(inviavel)
		cout << "Inviavel\n";
	else
		cout << score << " - " << tempo;
	/*
	dis.open("saida.txt", fstream::out);
	for(int i=1; i<=tam; i++){
		for(int j=1; j<=tam; j++)
			dis << dist[i][j] << " ";
		dis << endl;
	}
	/*
	for(int i=0; i<plano_rota.size(); i++)
		cout << plano_rota[i] << " -> ";
	cout << endl;

	for(int i=0; i<plano_coleta.size(); i++)
		cout << plano_coleta[i] << " -> ";
	cout << endl;
	/*
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
	}*/
	
	return 0;
}
