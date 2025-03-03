#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include <time.h>

typedef struct{
	char nome[50];
	float saldo;
	int codigo[5];
}ContaBancaria;

void mostrarConta(ContaBancaria c);

int interface(){
	int op;
	system("clear");
	puts("-------------------------------------------");
	puts("            SISTEMA BANCÁRIO");
	puts("-------------------------------------------");
	puts("\t1 - ABRIR NOVA CONTA");
	puts("\t2 - MOSTRAR DADOS DA CONTA");
	puts("\t3 - REALIZAR SAQUE");
	puts("\t4 - REALIZAR DEPÓSITO");
	puts("\n\t0 - SAIR");
	puts("-------------------------------------------");
	input("\nOpção: ", INT, &op);
	
	return op;
}

void gerarCodigo(int* cod){
	for (int i = 0; i < 4; i++)
		cod[i] = rand()%10;
		
	int v = (cod[0] - cod[1] + cod[2] - cod[3]);
	
	if(v<0) v *= -1;
	
	if(v >= 10) v = (v/10)+(v%10);
		
	cod[4] = v;
}

ContaBancaria abrirConta(){
	ContaBancaria nova;
	system("clear");
	puts("-------------------------------------------");
	puts("               NOVA CONTA");
	puts("-------------------------------------------");
	input("Informe o Nome do Titular da Conta: ", STR, nova.nome);
	gerarCodigo(nova.codigo);
	nova.saldo = 0;
	
	printf("Conta Aberta com Sucesso!\n\nSeja Bem-vindo(a) ao nosso Banco!\n\n");
	mostrarConta(nova);
	wait();
	return nova;
}

void printarCodigo(int* cod){
	for (int i = 0; i < 5; i++)
		printf("%d", cod[i]);
}

void mostrarConta(ContaBancaria c){
	printf("Nome do Titular: %s\n", c.nome);
	printf("Código da Conta: ");
	printarCodigo(c.codigo);
	printf("\nSaldo: R$ %.2f", c.saldo);
}

int buscarConta(ContaBancaria* c, int tam){
	char alvo[50];
	input("Informe o nome do Titular da Conta: ", STR, alvo);
	
	for (int i = 0; i < tam; i++)
		if(!strcmp(alvo, c[i].nome)){
			return i;
			break;
		}
		
	return -1;	
}

void mostrarDados(ContaBancaria* c, int tam){
	system("clear");
	if(!tam){
		puts("Não Há Contas Cadastradas no Sistema!");
		wait();
		return;
	}
	int i;
	puts("========== BUSCAR CONTA ==========\n");
	
	while(1){
		i = buscarConta(c, tam);
		
		if(i<0){
			puts("Conta Inválida! Tente novamente...");
			wait();
		}else 
			break;
	}
	
	mostrarConta(c[i]);
	wait();
}

void sacar(ContaBancaria* c, int tam){
	system("clear");
	if(!tam){
		puts("Não Há Contas Cadastradas no Sistema!");
		wait();
		return;
	}
	int i;
	puts("========== $AQUE ==========");
		while(1){
			i = buscarConta(c, tam);
			
			if(i<0){
				puts("Conta Inválida! Tente novamente...");
				wait();
			}else
				break;
		}
	
	if(!c[i].saldo){
		printf("Conta Vazia.\n");
		wait();
		return;
	}
	
	float saque;
	while(1){
		input("Informe o Valor para Saque: ", FLOAT, &saque);
		if(saque > c[i].saldo){
			puts("Valor Indisponível. Tente novamente.");
			wait();
		}else
			break;
	}
	
	puts("Saque Realizado com Sucesso!");
	c[i].saldo -= saque;
	wait();
}

void depositar(ContaBancaria* c, int tam){
	system("clear");
	if(!tam){
		puts("Não Há Contas Cadastradas no Sistema!");
		wait();
		return;
	}
	int i;
	puts("========== DEPÓ$ITO ==========");
		while(1){
			i = buscarConta(c, tam);
			
			if(i<0){
				puts("Conta Inválida! Tente novamente...");
				wait();
			}else
				break;
		}
		
	float deposito;
	while(1){
		input("Informe o Valor de Depósito: ", FLOAT, &deposito);
		if(deposito <= 0){
			puts("Dígito Inválido! Tente Novamente...");
			wait();
		}else
			break;
	}
	
	puts("Depósito Realizado com Sucesso!");
	c[i].saldo += deposito;
	wait();
	
}

int main(){
	srand(time(NULL));
	ContaBancaria contas[100];
	int cont = 0;
	
	while(1){
		switch(interface()){
			case 0: return 0;
			case 1: contas[cont++] = abrirConta();
			break;
			case 2: mostrarDados(contas, cont);
			break;
			case 3: sacar(contas, cont);
			break;
			case 4: depositar(contas, cont);
			break;
			default: printf("Opção Inválida!\n");
			wait();
			break;
		}
	}
}
