#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include <time.h>

typedef struct{
	int hr, min, seg;
}Tempo;

typedef struct{
	char nome[50];
	int numero_inscricao, categoria, sexo;
	Tempo chegada;
}Corredor;

#define PM 1
#define AM 2
#define PF 1
#define AF 2
#define MASC 1
#define FEM 2

void calculaTempo(Corredor* c);
void ordena(Corredor* c, int cont);
void mostraCorredor(Corredor c);
void mostraCategoria(Corredor* c, int cont, int modalidade, int sexo);

int interface(){
	system("clear");
	int op;
	printf("--------------------------------\n");
	printf("             MENU\n");
	printf("--------------------------------\n");
	printf("\n1 - CADASTRAR MARATONISTA\n");
	printf("2 - RANKING DA MARATONA\n");
	printf("0 - ENCERRAR\n");
	printf("\n--------------------------------\n");
	input("\nOpção: ", INT, &op);
	
	return op;
}

Corredor cadastrarMaratonista(int c){
	system("clear");
	Corredor novo;
	input("Nome do Corredor: ", STR, novo.nome);
	input("Sexo [1 - (Masc) / 2 - (Fem)]: ", INT, &novo.sexo);
	while(novo.sexo != MASC && novo.sexo != FEM){
		input("Dígito Inválido!\nTente Novamente: ",
		 INT, &novo.sexo);
	}
	
	if(novo.sexo == MASC){
		input("Digite a Categoria\n1 - Profissional Masc.\n2 - Amador Masc.\n"
		, INT, &novo.categoria);
		while(novo.categoria != PM && novo.categoria != AM){
			input("Dígito Inválido!\nTente Novamente: "
			, INT, &novo.categoria);
		}
	}
	
	if(novo.sexo == FEM){
		input("Digite a Categoria\n1 - Profissional Fem.\n2 - Amador Fem.\n"
		, INT, &novo.categoria);
		while(novo.categoria != PF && novo.categoria != AF){
			input("Dígito Inválido!\nTente Novamente: "
			, INT, &novo.categoria);
		}
	}
		
	novo.numero_inscricao = c;
	calculaTempo(&novo);
	printf("Cadastro Realizado com Sucesso!\n");
	wait();
	return novo;
}

void calculaTempo(Corredor* c){
	c->chegada.hr = 1 + rand() % 4;
	c->chegada.min = rand() % 60;
	c->chegada.seg = rand() % 60;
}

void ordena(Corredor* c, int cont){
	for (int i = 0; i < cont; i++)
		for (int j = 0; j < cont-i-1; j++)
			if(c[j].chegada.hr > c[j+1].chegada.hr ||
			(c[j].chegada.hr == c[j+1].chegada.hr &&
			(c[j].chegada.min > c[j+1].chegada.min ||
			(c[j].chegada.min == c[j+1].chegada.min &&
			c[j].chegada.seg > c[j+1].chegada.seg)))){
				 Corredor aux =c[j];
				 c[j] = c[j+1];
				 c[j+1] = aux;
			}
}

void mostraCorredor(Corredor c){
	printf("%s\t%02d\t[%02dh %02dm %02ds]\n"
	, c.nome, c.numero_inscricao
	, c.chegada.hr, c.chegada.min
	, c.chegada.seg);
}

void mostraCategoria(Corredor* c, int cont, int modalidade, int sexo){
	for (int i = 0; i < cont; i++)
		if(c[i].sexo == sexo && c[i].categoria == modalidade)
			mostraCorredor(c[i]);
}

void ranking(Corredor* c, int cont){
	system("clear");
	printf("--------------------------------------------\n");
	printf("                  RANKING\n");
	printf("--------------------------------------------\n");
	printf("\nResultado: Profissional Masc.\n");
	mostraCategoria(c, cont, PM, MASC);
	printf("\nResultado: Amador Masc.\n");
	mostraCategoria(c, cont, AM, MASC);
	printf("\nResultado: Profissional Fem.\n");
	mostraCategoria(c, cont, PF, FEM);
	printf("\nResultado: Amador Fem.\n");
	mostraCategoria(c, cont, AF, FEM);
	wait();
}

int main(){
	srand(time(NULL));
	Corredor maratonistas[50];
	int cont = 0;
	
	do{
		switch(interface()){
			case 0: return 0;
			case 1: maratonistas[cont] = cadastrarMaratonista(cont+1);
			cont++;
			ordena(maratonistas, cont);
			break;
			case 2: ranking(maratonistas, cont);
			break;
			default: printf("Opção Inválida!\n");
			wait();
			break;
		}
	}while(1);
}
