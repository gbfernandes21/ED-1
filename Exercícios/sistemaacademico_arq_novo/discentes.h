#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

typedef struct{
	char nome[100];
	char email[100];
	int cod;
}Discente;

void printDisciplinas(int cod, FILE* disciplinas, FILE* matriculas);

int buscaPosDiscente(int cod, Discente* d, int cont){
	for (int i = 0; i < cont; i++)
		if(cod == d[i].cod) return i;
	return -1;
}

int contDiscentes(FILE* arq_discentes, Discente* d){
	int i = 0;
	fseek(arq_discentes, 0, SEEK_SET);
	while(fread(&d[i], sizeof(Discente), 1, arq_discentes))
		i++;
	return i;
}

void setDiscente(FILE* arq_discente){
	system("clear");
	Discente d;
	fseek(arq_discente,0, SEEK_END);
	cAluno();
	d.cod = (ftell(arq_discente)/sizeof(Discente))+1;
	input("Nome [exit para SAIR]: ",STR, d.nome);
	getchar();
	if(!strcmp(d.nome, "exit")) return;
	
	input("E-mail: ",STR, d.email);
	fwrite(&d, sizeof(Discente), 1, arq_discente);
	fflush(arq_discente);
	printf("Discente cadastrado com Sucesso!\n");
	wait();
}

void getDiscente(Discente d, int total){
	(!total) ? printf("| CÓDIGO: %d\t| DISCENTE: %s\t |\n", d.cod, d.nome):
	printf("| CÓDIGO: %d\t| DISCENTE: %s\t|\n| E-MAIL: %s\t|\n", d.cod, d.nome, d.email);
}

void ordenarDiscentes(Discente* d, int cont){
	for (int i = 0; i < cont; i++)
		for (int j = 0; j < cont-i-1; j++)
			if(strcmp(d[j].nome, d[j+1].nome) > 0){
				Discente aux = d[j];
				d[j] = d[j+1];
				d[j+1] = aux;
			}
}

void relatorioDiscentes(FILE* arq_discentes){
	Discente d[1000];
	int cont = contDiscentes(arq_discentes, d);
	ordenarDiscentes(d, cont);
			
	for (int i = 0; i < cont; i++)
		getDiscente(d[i], 0);
}

//BUSCA ALUNOS CUJO NOME CONTENHA UM RESPECTIVO PADRÃ0 (STRING)

int buscaPadraoDiscente(int tam_alvo, char* alvo, FILE* arq_discentes, int total){
	fseek(arq_discentes, 0, SEEK_SET);
	Discente d[1000];
	int cont = contDiscentes(arq_discentes, d);
	int achou = 0;
	
	ordenarDiscentes(d, cont);
	
	for (int i = 0; i < cont; i++){
		char* nome = d[i].nome;
		int tam_nome = strlen(nome);
		for (int j = 0; j <= tam_nome-tam_alvo; j++){
			int tam = 0;
			while(tam < tam_alvo && nome[j+tam] == alvo[tam]){
				tam++;
			}
			
			if(tam == tam_alvo){
				achou = 1;
				getDiscente(d[i], total);
				break;
			}
		}
	}
	
	if(!achou){
		printf("Discente não encontrado!\n");
		return 0;
	}
	return 1;
}

int buscaDiscente(int alvo, FILE* arq_discentes){
	Discente d[1000];
	int cont = contDiscentes(arq_discentes, d);
	for (int i = 0; i < cont; i++)
		if(alvo == d[i].cod) return 1;
	return 0;
}

void pesquisaDiscentes(FILE* discentes){
	char padrao[20];
	input("\nPesquisar: ", STR, padrao);
	while(!buscaPadraoDiscente(strlen(padrao), padrao, discentes, 0)){
		input("\nTente novamente: ", STR, padrao);
	}
}

void printDadosDiscente(FILE* arq_discentes, FILE* arq_disciplinas, FILE* arq_matriculas, int cod){
	system("clear");
	fseek(arq_discentes, 0, SEEK_SET);
	Discente d; 
	while(fread(&d, sizeof(Discente), 1, arq_discentes))
		if(d.cod == cod) break;
	dAluno();
	getDiscente(d, 1);
	printf("\n");
	printDisciplinas(cod, arq_disciplinas, arq_matriculas);
	wait();
}

void historicoDiscente(FILE* arq_discentes, FILE* arq_disciplinas, FILE* arq_matriculas){
	system("clear");
	fseek(arq_discentes,0, SEEK_END);
	if(!ftell(arq_discentes)){
		printf("(Vazio)\n");
		wait();
		return;
	}
	int cod;
	hAluno();
	relatorioDiscentes(arq_discentes);
	input("\nDigite o código do Discente [0 para SAIR e -1 para PESQUISAR discente]: ", INT, &cod);
	while(cod > 0 && !buscaDiscente(cod, arq_discentes))
		input("Discente não encontrado!\nTente novamente [0 para SAIR e -1 para PESQUISAR discente]: ", INT, &cod);
	
	if(!cod) return;
	
	if(cod < 0){
		pesquisaDiscentes(arq_discentes);
		input("\nDigite o código do discente: ", INT, &cod);
		while(!buscaDiscente(cod, arq_discentes))
			input("Opção inválida!\nTente novamente: ", INT, &cod);
	}
	
	printDadosDiscente(arq_discentes, arq_disciplinas, arq_matriculas, cod);
}
