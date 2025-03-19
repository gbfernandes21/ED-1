#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nome[50], carro[50], placa[50];
	int estacionado, cont;
}Cliente;

#define MAX_VEICULOS 100

int interface();
int estacionar(Cliente* e, int cont);
int existe(char* alvo, Cliente* e, int cont);
void wait();
void limite();
void print_cliente(Cliente e);
void sair(Cliente* e, int cont);
void relatorio(Cliente* e, int cont);
void cadastro_estacionamento(Cliente* e, int cont);
Cliente cadastrar_cliente(Cliente* e, int cont);

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

void limite(){
	system("clear");
	printf("Limite de cadastros atingido!\n");
	wait();
}

int interface(){
	system("clear");
	int op;
	printf("1 - CADASTRAR CLIENTE\n2 - ESTACIONAR VÉICULO\n3 - RETIRAR VEÍCULO\n4 - RELATÓRIO\n\n");
	printf("--------------------------\n\n0 - SAIR\n\n");
	printf("Opção: ");
	scanf(" %d", &op);
	while(getchar() != '\n');
	return op;
}

int existe(char* alvo, Cliente* e, int cont){
	for (int i = 0; i < cont; i++)
		if(!strcmp(alvo, e[i].placa)) return i;
	return -1;
}

Cliente cadastrar_cliente(Cliente* e, int cont){
	system("clear");
	Cliente novo;
	
	printf("Nome do cliente: ");
	scanf("%[^\n]s", novo.nome);
	while(getchar() != '\n');
	printf("Placa: ");
	scanf("%[^\n]s", novo.placa);
	while(getchar() != '\n');
	while(existe(novo.placa, e , cont) >= 0){
		printf("Esse véiculo já está cadastrado!\nTente novamente: ");
		scanf("%[^\n]s", novo.placa);
		while(getchar() != '\n');
	}
	printf("Veículo: ");
	scanf("%[^\n]s", novo.carro);
	while(getchar() != '\n');
	novo.cont = 0;
	novo.estacionado = 0;
	printf("Cliente cadastrado com Sucesso!\n");
	wait();
	return novo;
}

void cadastro_estacionamento(Cliente* e, int cont){
	printf("Olá! Para estacionar, realize seu cadastro primeiro.\n[Tecle ENTER]\n");
	wait();
	e[cont] = cadastrar_cliente(e, cont);
}

int estacionar(Cliente* e, int cont){
	system("clear");
	char placa[50];
	int var = 0, pos;
	
	if(!cont){
		var = 1;
		cadastro_estacionamento(e, cont);
	}else{
		printf("Placa [exit para sair]: ");
		scanf("%[^\n]s", placa);
		if(!strcmp(placa, "exit")) return 1;
		
		pos = existe(placa, e, cont);
		if(pos < 0){
			if(cont < MAX_VEICULOS){
				var = 1;
				cadastro_estacionamento(e, cont);
			}else{
				limite();
				return 1;
			}
		}
	}
	
	if(!var){
		if(e[pos].estacionado){
			printf("Este veículo já está estacionado!\n");
			wait();
			return 1;
		}
		
		e[pos].estacionado = 1;
		e[pos].cont++;
		printf("Veículo estacionado com Sucesso!\n");
		wait();
		return 1;
	}else{
		e[cont].estacionado = 1;
		e[cont].cont++;
		printf("Veículo estacionado com Sucesso!\n");
		wait();
		return 0;
	}
}

void sair(Cliente* e, int cont){
	system("clear");
	
	if(!cont){
		printf("(Estacionamento vazio)\n");
		wait();
		return;
	}
	
	char placa[50];
	printf("Placa: ");
	scanf("%[^\n]s", placa);
	if(!strcmp(placa, "exit")) return;
	
	int pos = existe(placa, e, cont);
	if(pos < 0){
		printf("Este veículo não está cadastrado em nosso sistema.\n");
		wait();
		return;
	}
	
	if(!e[pos].estacionado){
		printf("Este veículo não se encontra no estacionamento!");
		wait();
		return;
	}
	
	e[pos].estacionado = 0;
	e[pos].cont++;
	printf("Saída realizada com Sucesso\n");
	wait();
}

void print_cliente(Cliente e){
	printf("| CLIENTE: %s\t| VEÍCULO: %s\t| PLACA: %s\t| SITUAÇÃO:%s\t| QTDE. DE INTERAÇÕES: %d |\n", e.nome, e.carro, e.placa, (e.estacionado? " Estacionado" : " \t-"), e.cont);
}

void relatorio(Cliente* e, int cont){
	system("clear");
	
	if(!cont){
		printf("(Vazio)\n");
		wait();
		return;
	}
	
	printf("CLIENTES CADASTRADOS\n\n");
	for (int i = 0; i < cont; i++)
		print_cliente(e[i]);
	wait();
}

int main(){
	Cliente estacionamento[MAX_VEICULOS];
	int cont = 0;
	
	do{
		switch(interface()){
			case 0: return 0;
			case 1:
			if(cont < MAX_VEICULOS){
				estacionamento[cont] = cadastrar_cliente(estacionamento, cont);
				cont++;
			}else{
				limite();
			} break;
			case 2: if(!estacionar(estacionamento, cont)) cont++;
			break;
			case 3: sair(estacionamento, cont);
			break;
			case 4: relatorio(estacionamento, cont);
			break;
			default: printf("Opção Inválida!\n");
			wait();
			break;
		}	
	}while(1);
}
