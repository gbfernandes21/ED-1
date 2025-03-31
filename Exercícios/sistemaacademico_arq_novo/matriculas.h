#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplinas.h"

typedef struct{
	int cod_discente;
	int cod_disciplina;
	float nota;
}Matricula;

int contMatriculas(FILE* matriculas, Matricula* mtr){
	int i = 0;
	fseek(matriculas, 0, SEEK_SET);
	while(fread(&mtr[i], sizeof(Matricula), 1, matriculas))
		i++;
	return i;
}


int existeMatricula(int discente, int disciplina, FILE* matriculas){
	Matricula m[1000];
	int cont = contMatriculas(matriculas, m);
	for (int i = 0; i < cont; i++)
		if(m[i].cod_discente == discente && m[i].cod_disciplina == disciplina)
			return 1;
	return 0;
}




void matricularDiscente(FILE* matriculas, FILE* discentes, FILE* disciplinas){
	system("clear");
	Matricula m;
	mtr();
	relatorioDiscentes(discentes);
	input("\nDigite o código do discente a ser matriculado[0 para SAIR -1 para PESQUISAR discente]: ", INT, &m.cod_discente);
	while(getchar() != '\n');
	while(m.cod_discente > 0 && !buscaDiscente(m.cod_discente, discentes)){
			input("\nOpção inválida!\nTente novamente[0 para SAIR]: ", INT, &m.cod_discente);
			while(getchar() != '\n');
	}
	if(!m.cod_discente)return;
	
	if(m.cod_discente < 0){
		pesquisaDiscentes(discentes);
		input("\nDigite o código do discente: ", INT, &m.cod_discente);
		while(!buscaDiscente(m.cod_discente, discentes)){
			input("\nOpção inválida!\nTente novamente: ", INT, &m.cod_discente);
		}
	}
	
	printf("\n");
	relatorioDisciplinas(disciplinas);
	input("Digite o código da disciplina onde o discente será matriculado[0 para PESQUISAR]: ", INT, &m.cod_disciplina);
	while(m.cod_disciplina != 0 && !buscaDisciplina(disciplinas, m.cod_disciplina)){
			input("\nOpção inválida!\nTente novamente: ", INT, &m.cod_disciplina);
	}
	
	if(!m.cod_disciplina){
		pesquisaDisciplinas(disciplinas);
		input("\nDigite o código da disciplina: ", INT, &m.cod_disciplina);
		while(!buscaDisciplina(disciplinas, m.cod_disciplina)){
			input("\nOpção inválida!\nTente novamente: ", INT, &m.cod_disciplina);
		}
	}
	
	if(existeMatricula(m.cod_discente, m.cod_disciplina, matriculas)){
		printf("\nO discente já está cadastrado nessa disciplina!\n");
		wait();
		return;
	}
	
	m.nota = -1;
	fseek(matriculas,0, SEEK_END);
	fwrite(&m, sizeof(Matricula), 1, matriculas);
	printf("\nMatrícula realizada com Sucesso!\n");
	wait();
}

//MOSTRA DISCIPLINAS EM QUE UM RESPECTIVO ALUNO ESTÁ MATRICULADO

void printDisciplinas(int cod, FILE* disciplinas, FILE* matriculas){
	fseek(matriculas,0, SEEK_END);
	int cont = ftell(matriculas)/sizeof(Matricula);
	Matricula m[cont];
	int achou = 0;
	
	fseek(matriculas,0, SEEK_SET);
	for (int i = 0; i < cont; i++)
		fread(&m[i], sizeof(Matricula), 1, matriculas);
		
	Disciplina disciplina[1000];
	int cont_disc = contDisciplinas(disciplinas, disciplina);
	ordenarDisciplinas(disciplina, cont_disc);
	
	for (int i = 0; i < cont_disc; i++){
		char disc[50] = {" "};
		for (int j = 0; j < cont; j++)
			if(disciplina[i].cod == m[j].cod_disciplina){
				achou = 1;
				strcpy(disc, disciplina[i].disciplina);
				printf("| %s\t| Nota: %.2f\t|\t%s\t|\n", disc, m[j].nota, 
				(m[j].nota >= 60 ? "APROVADO" : m[j].nota < 0 ? "-" : "REPROVADO"));
				break;
			}
	}
	if (!achou)
		printf("O discente não está matriculado em nenhuma disciplina!\n");
}

//MOSTRA OS ALUNOS MATRICULADOS EM UMA DETERMINADA DISCIPLINA

int printDiscentes(int cod, FILE* discentes, FILE* matriculas){
	fseek(matriculas,0, SEEK_END);
	int cont = ftell(matriculas)/sizeof(Matricula);
	Matricula m[cont];
	int achou = 0;
	
	fseek(matriculas,0, SEEK_SET);
	for (int i = 0; i < cont; i++)
		fread(&m[i], sizeof(Matricula), 1, matriculas);
	
	Discente discente[1000];
	int cont_disc = contDiscentes(discentes, discente);
	ordenarDiscentes(discente, cont_disc);
	
	for (int i = 0; i < cont_disc; i++){
		char disc[50] = {" "};
		for (int j = 0; j < cont; j++)
			if(discente[i].cod == m[j].cod_discente){
				achou = 1;
				strcpy(disc, discente[i].nome);
				printf("| %d | %s\t| Nota: %.2f\t|\t%s\t|\n", m[j].cod_discente, disc, m[j].nota, 
				(m[j].nota >= 60 ? "APROVADO" : m[j].nota < 0 ? "-" : "REPROVADO"));
				break;
			}
	}
	
	if (!achou)
		printf("Não há alunos matriculados nesta disciplina!\n");
	return achou;
}

int getMatriculas(int cod, Matricula* mtr, FILE* matriculas){
	Matricula m;
	int i = 0;
	fseek(matriculas, 0, SEEK_SET);
	while(fread(&m, sizeof(Matricula), 1, matriculas))
		if(m.cod_disciplina == cod){
			mtr[i] = m;
			i++;
		}
	return i;
}

//BUSCA MATRÍCULA PARA ATRIBUIR NOTA

int getMatricula(int cod, Matricula* m, int cont){
	int id = -1;
	for (int i = 0; i < cont; i++)
		if(m[i].cod_discente == cod) id = i;
	return id;
}

int discenteMatriculado(Matricula* m, int cont, int cod){
	int achou = 0;
	for (int i = 0; i < cont; i++)
		if(cod == m[i].cod_discente){
			achou = 1;
			break;
		}
	return achou;
}

void update(Matricula* todos, int cont_t, Matricula* diario, int cont){
	for (int i = 0; i < cont_t; i++)
		for (int j = 0; j < cont; j++)
			if(todos[i].cod_disciplina == diario[j].cod_disciplina && todos[i].cod_discente == diario[j].cod_discente)
				todos[i].nota = diario[j].nota;
}

void atribuirNota(int cod, FILE* discentes, FILE* matriculas){
	Matricula mtr[1000];
	int cont_mtr = contMatriculas(matriculas, mtr);
	
	Matricula diario[1000];
	int cont_mt = getMatriculas(cod, diario, matriculas);
	
	Discente disc[1000];
	int cont_disc = contDiscentes(discentes, disc);
	ordenarDiscentes(disc, cont_disc);
	
	int atualizou = 0;
	
	do{
		system("clear");
		int cod_d;
		notas();
		printDiscentes(cod, discentes, matriculas);
		input("\nDigite o código do discente que deseja atribuir nota.\n[0 para SAIR -1 para PESQUISAR]: ", INT, &cod_d);
		while(cod_d > 0 && !discenteMatriculado(diario, cont_mt, cod_d))
			input("\nDiscente não encontrado no diário da disciplina!\nTente novamente[0 para SAIR -1 para PESQUISAR]: ", INT, &cod_d);
		if(!cod_d) return;
		
		if(cod_d < 0){
			pesquisaDiscentes(discentes);
			input("\nDigite o código do discente que deseja atribuir nota [0 para SAIR]: ", INT, &cod_d);
			while(cod_d > 0 && !discenteMatriculado(diario, cont_mt, cod_d)){
				input("\nDiscente não encontrado no diário da disciplina!\nTente novamente[0 para SAIR]: ", INT, &cod_d);
				if(!cod) return;
			}
		}
		
		int pos = getMatricula(cod_d, diario, cont_mt);
		
		if(diario[pos].nota >= 0){
			char op;
			printf("\nA nota do discente já foi atribuída.\n");
			do{
				input("Deseja atualizar nota? [s/n]: ", CHAR, &op);
			}while(op != 's' && op != 'n');
			if(op == 'n') continue;
		}
		
		char opt;
		
		int posd = buscaPosDiscente(cod_d, disc, cont_disc);
		
		printf("\nNota para %s: ", disc[posd].nome);
		scanf(" %f", &diario[pos].nota);
		while(diario[pos].nota < 0)
			input("\nOpção inválida!\nTente novamente: ", FLOAT, &diario[pos].nota);
		atualizou = 1;
		printf("\nNota lançada para %s", disc[posd].nome);
		do{
			input("\nDeseja atribuir mais notas? [s/n]: ", CHAR, &opt);
		}while(opt != 's' && opt != 'n');
		
		if(opt == 'n') break;
	}while(1);
	
	if(!atualizou) return;
	
	fseek(matriculas, 0, SEEK_SET);
	update(mtr, cont_mtr, diario, cont_mt);
	for (int i = 0; i < cont_mtr; i++)
		fwrite(&mtr[i], sizeof(Matricula), 1,matriculas);
	fflush(matriculas);
	printf("Notas lançadas com sucesso!\n");
	wait();
}
