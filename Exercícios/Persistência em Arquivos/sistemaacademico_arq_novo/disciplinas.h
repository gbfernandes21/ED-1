#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "discentes.h"

typedef struct{
	int cod;
	char disciplina[30];
	char professor[100];
	int ch;
}Disciplina;

int printDiscentes(int cod, FILE* discentes, FILE* matriculas);
void atribuirNota(int cod, FILE* discentes, FILE* matriculas);

int contDisciplinas(FILE* arq_disciplinas, Disciplina* d){
	int i = 0;
	fseek(arq_disciplinas, 0, SEEK_SET);
	while(fread(&d[i], sizeof(Disciplina), 1, arq_disciplinas))
		i++;
	return i;
}


int existeDisciplina(char* disciplina, FILE* arq_disciplina){
	Disciplina d[1000];
	int cont = contDisciplinas(arq_disciplina, d);
	
	for (int i = 0; i < cont; i++)
		if(!strcmp(disciplina, d[i].disciplina)) return 1;
	return 0;
}



void setDisciplina(FILE* arq_disciplina){
	system("clear");
	Disciplina d;
	fseek(arq_disciplina,0, SEEK_END);
	cDisc();
	d.cod = (ftell(arq_disciplina)/sizeof(Disciplina))+1;
	input("Disciplina [exit para SAIR]: ",STR, d.disciplina);
	getchar();
	
	if(existeDisciplina(d.disciplina, arq_disciplina)){
		printf("Essa disciplina já foi cadastrada!\n");
		wait();
		return;
	}
	if(!strcmp(d.disciplina, "exit")) return;
	
	input("Professor: ",STR, d.professor);
	input("Carga Horária: ",INT, &d.ch);
	fwrite(&d, sizeof(Disciplina), 1, arq_disciplina);
	fflush(arq_disciplina);
	printf("Disciplina cadastrada com Sucesso!\n");
	wait();
}

//AVALIA SE RESPECTIVA DISCIPLINA EXISTE

int buscaDisciplina(FILE* arq_disciplinas, int alvo){
	Disciplina d[1000];
	int cont = contDisciplinas(arq_disciplinas, d);
	
	for (int i = 0; i < cont; i++)
		if(alvo == d[i].cod) return 1;
	return 0;
}
//////


void getDisciplina(Disciplina d, int total){

	(!total) ? printf("| CÓDIGO: %d\t| DISCIPLINA: %s\t |\n", d.cod, d.disciplina):
	printf("| CÓDIGO: %d\t| DISCIPLINA: %s\t|\n| CH: %dh\t| PROFESSOR(a): %s\t|\n", d.cod, d.disciplina, d.ch, d.professor);
}

void ordenarDisciplinas(Disciplina* d, int cont){
	for (int i = 0; i < cont; i++)
		for (int j = 0; j < cont-i-1; j++)
			if(strcmp(d[j].disciplina, d[j+1].disciplina) > 0){
				Disciplina aux = d[j];
				d[j] = d[j+1];
				d[j+1] = aux;
			}
}

void relatorioDisciplinas(FILE* arq_disciplinas){
	Disciplina d[1000];
	int cont = contDisciplinas(arq_disciplinas, d);
	ordenarDisciplinas(d, cont);
	
	for (int i = 0; i < cont; i++)
		getDisciplina(d[i], 0);

}

//BUSCA DISCIPLINAS QUE TENHA UM RESPECTIVO PADRÃO (STRING) EM SEU NOME

int buscaPadraoDisciplina(int tam_alvo, char* alvo, FILE* arq_disciplinas, int total){
	fseek(arq_disciplinas, 0, SEEK_SET);
	Disciplina d[1000];
	int cont = contDisciplinas(arq_disciplinas, d);
	int achou = 0;
	ordenarDisciplinas(d, cont);
	
	for (int i = 0; i < cont; i++){
		char* disc= d[i].disciplina;
		int tam_disc = strlen(disc);
		for (int j = 0; j <= tam_disc-tam_alvo; j++){
			int tam = 0;
			while(tam < tam_alvo && disc[j+tam] == alvo[tam]){
				tam++;
			}
			
			if(tam == tam_alvo){
				achou = 1;
				getDisciplina(d[i], total);
				break;
			}
		}
	}
	
	if(!achou){
		printf("Disciplina não encontrada!\n");
		return 0;
	}
	return 1;
}

void pesquisaDisciplinas(FILE* disciplinas){
	char padrao[20];
	input("Pesquisar: ", STR, padrao);
	getchar();
	while(!buscaPadraoDisciplina(strlen(padrao), padrao, disciplinas, 0)){
		input("\nTente novamente: ", STR, padrao);
		getchar();
	}
}

//MOSTRA TODOS OS DADOS DE UMA RESPECTIVA DISCIPLINA, SEUS ALUNOS, NOTA E SE FOI APROVADO / REPROVADO

void printDadosDisciplina(FILE* arq_discentes, FILE* arq_disciplinas, FILE* arq_matriculas, int cod){
	system("clear");
	fseek(arq_disciplinas, 0, SEEK_SET);
	Disciplina d; 
	while(fread(&d, sizeof(Disciplina), 1, arq_disciplinas))
		if(d.cod == cod) break;
	dataD();
	getDisciplina(d, 1);
	
	printf("\n");
	if (!printDiscentes(cod, arq_discentes, arq_matriculas)){
		wait();
		return;
	}
	char esc;
	input("\nDeseja atribuir nota aos discentes? [s/n]: ", CHAR, &esc);
	if(esc == 'n') return;
	
	if(esc == 's')
		atribuirNota(cod, arq_discentes, arq_matriculas);
}
//


void diarioDisciplina(FILE* arq_disciplinas, FILE* arq_discentes, FILE* arq_matriculas){
	system("clear");
	fseek(arq_disciplinas,0, SEEK_END);
	if(!ftell(arq_disciplinas)){
		printf("(Vazio)\n");
		wait();
		return;
	}
	int cod;
	dDisc();
	relatorioDisciplinas(arq_disciplinas);
	input("\nDigite o código da Disciplina [0 para SAIR e -1 para PESQUISAR discente]: ", INT, &cod);
	while(cod > 0 && !buscaDisciplina(arq_disciplinas, cod))
		input("Disciplina não encontrada!\nTente novamente [0 para SAIR e -1 para PESQUISAR discente]: ", INT, &cod);
	
	if(!cod) return;
	
	if(cod < 0){
		pesquisaDisciplinas(arq_disciplinas);
		input("\nDigite o código do disciplina: ", INT, &cod);
		while(!buscaDisciplina(arq_disciplinas, cod))
			input("Opção inválida!\nTente novamente: ", INT, &cod);
	}
	
	printDadosDisciplina(arq_discentes, arq_disciplinas, arq_matriculas, cod);
}
