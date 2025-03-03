#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

typedef struct{
	char nome[50];
	int matricula;
	int notas[2][10];
	float cr;
	int cont;
}Discente;

typedef struct{
	char nome[50], professor[50];
	int codigo;
	int ch;
	int cont;
	Discente discentes[50];
}Disciplina;

int buscarMateria(char* nome, Disciplina* m, int tam);
int buscarAluno(char* nome, Discente* a, int tam);

int interface(){
	int op;
	system("clear");
	puts("------------------------------------");
	puts("         SISTEMA ACADÊMICO");
	puts("------------------------------------");
	puts("\n\t1 - CADASTRAR DISCIPLINA");
	puts("\t2 - CADASTRAR ALUNO");
	puts("\t3 - MATRICULAR ALUNO");
	puts("\t4 - LANÇAR NOTAS");
	puts("\t5 - DIÁRIO DA DISCIPLINA");
	puts("\t6 - HISTÓRICO DO ALUNO");
	puts("\t7 - RANKING DE CR");
	puts("\t0 - SAIR\n");
	puts("------------------------------------");
	input("\nOpção: ", INT, &op);
	
	return op;
}

Discente cadastrarAluno(int cod){
	Discente novo;
	system("clear");
	puts("-----------------------------------");
	puts("         CADASTRO DE ALUNO");
	puts("-----------------------------------");
	input("\nNome do Aluno: ", STR, novo.nome);
	novo.matricula = cod;
	novo.cont = 0;
	
	for (int i = 0; i < 10; i++){
		novo.notas[0][i] = 0;
		novo.notas[1][i] = 0;
	}
	
	printf("Aluno Cadastrado com Sucesso!\n");
	wait();
	return novo;
}

Disciplina cadastrarMateria(int cod){
	Disciplina nova;
	system("clear");
	puts("-----------------------------------------------");
	puts("            CADASTRO DE DISCIPLINA");
	puts("-----------------------------------------------");
	input("\nNome da Disciplina: ", STR, nova.nome);
	input("Professor da Disciplina: ", STR, nova.professor);
	input("Carga Horária: ", INT, &nova.ch);
	nova.codigo = cod;
	nova.cont = 0;
	
	printf("Disciplina Cadastrada com Sucesso!\n");
	wait();
	return nova;
}

int buscarAluno(char* nome, Discente* a, int tam){
	for (int i = 0; i < tam; i++)
		if(!strcmp(nome, a[i].nome)){
			return i;
			break;
		}
		
	return -1;
}

int buscarMateria(char* nome, Disciplina* m, int tam){
	for (int i = 0; i < tam; i++)
		if(!strcmp(nome, m[i].nome)){
			return i;
			break;
		}
		
	return -1;
}

void matriculaAluno(Discente* a, int cont_a, Disciplina* m, int cont_m){
	system("clear");
	char nome[50], disciplina[50];
	int i, j;
	puts("---------------------------------------------------------------");
	puts("                          MATRÍCULA");
	puts("---------------------------------------------------------------");
	
	while(1){
		input("\nDigite o Nome do Aluno [exit para ENCERRAR]: ", STR, nome);
		if(!strcmp(nome, "exit")) return;
		i = buscarAluno(nome, a, cont_a);
		if(i<0){
			printf("Aluno Não Encontrado! Tente Novamente...");
			wait();
		}else
			break;
	}
	
	while(1){
		input("Digite o Nome da Disciplina [exit para ENCERRAR]: ", STR, disciplina);
		if(!strcmp(disciplina, "exit")) return;
		j = buscarMateria(disciplina, m, cont_m);
		if(j<0){
			printf("Disciplina Não Encontrada! Tente Novamente...");
			wait();
		}else if(buscarAluno(nome, m[j].discentes, m[j].cont) >= 0){
			printf("O Aluno já está Matriculado nesta Disciplina!");
			wait();
		}else
			break;
	}
	
	m[j].discentes[m[j].cont] = a[i];
	m[j].cont++;
	printf("Matrícula Realizada com Sucesso!\n");
	wait();
}

float calculaCr(Discente a){
	float soma = 0, cr;
	int qnt = 0;
	
	for (int i = 0; i < a.cont; i++){
		soma += a.notas[1][i];
		qnt++;
	}
	
	cr = (float)soma/qnt;
	
	 return cr;
}

void ordenar(Discente* a, int cont_a){
	for (int i = 0; i < cont_a; i++)
		for (int j = 0; j < cont_a-i-1; j++)
			if(a[j].cr < a[j+1].cr){
				Discente aux = a[j];
				a[j] = a[j+1];
				a[j+1] = aux;
			}
}

void lancaNotas(Discente* a, int cont_a, Disciplina* m, int cont_m){
	system("clear");
	char nome[50], disciplina[50];
	int id,jd;
	puts("-------------------------------------------------------------");
	puts("                        LANÇAR NOTAS");
	puts("-------------------------------------------------------------");
	while(1){
		input("Digite o Nome do Aluno [exit para ENCERRAR]: ", STR, nome);
		if(!strcmp(nome, "exit")) return;
		id = buscarAluno(nome, a, cont_a);
		if(id<0){
			printf("Aluno Não Encontrado! Tente Novamente");
			wait();
		}else
			break;
	}
	
	while(1){
		input("Nome da Disciplina: ", STR, disciplina);
		jd = buscarMateria(disciplina, m, cont_m);
		if(jd<0){
			printf("Disciplina Não Encontrada!");
			wait();
		}else 
			break;
	}
	
	int mat = 0;
	
	for(int i = 0; i < m[jd].cont; i++)
		if(a[id].matricula == m[jd].discentes[i].matricula){
			mat = 1;
			break;
		}
		
	if(!mat){
		printf("O Aluno Não está Matriculado nesta Disciplina!\n");
		wait();
		return;
	}
	
	for (int j = 0; j < a[id].cont; j++)
		if(a[id].notas[0][j] == m[jd].codigo){
			printf("A Nota do Aluno já foi Lançada!\n");
			wait();
			return;
		}
	
	int nota;
	
	input("Informe a Nota do aluno: ", INT, &nota);
	
	a[id].notas[0][a[id].cont] = m[jd].codigo;
	a[id].notas[1][a[id].cont] = nota;
	a[id].cont++;
	a[id].cr = calculaCr(a[id]);
	ordenar(a, cont_a);
	printf("Nota Lançada com Sucesso!\n");
	wait();
}

void diarioDisciplina(Disciplina* m, int cont_m, Discente* a, int cont_a){
	system("clear");
	char disciplina[50];
	int id;
	puts("------------------------------------------------------------------------------------------------------------------------");
	puts("                                             DIÁRIO DA DISCIPLINA");
	puts("------------------------------------------------------------------------------------------------------------------------");
	
	while(1){
		input("\nInforme a Disciplina: ", STR, disciplina);
		id = buscarMateria(disciplina, m, cont_m);
		if(id<0){
			printf("Disciplina Não Encontrada!\n");
			wait();
		}else
			break;
	}
	
	printf("\nDisciplina: %s\t\tCódigo: %02d\t\tCarga Horária: %dH\t\tProfessor(a): %s\n\n", 
	m[id].nome, m[id].codigo, m[id].ch, m[id].professor);
	
	for (int i = 0; i < m[id].cont; i++){
		int id_a = m[id].discentes[i].matricula;
		for (int j = 0; j < cont_a; j++)
			if(a[j].matricula == id_a){
				printf("\n| ALUNO: %s | CÓD. MATRÍCULA: %03d | NOTA: "
				, a[j].nome, a[j].matricula);
				for (int k = 0; k < a[j].cont; k++)
					if(a[j].notas[0][k] == m[id].codigo)
						printf("%d |\n------", a[j].notas[1][k]);
			}
	}
	wait();
}

void historicoAluno(Discente* a, int cont_a, Disciplina* m, int cont_m){
	system("clear");
	char nome[50];
	int id;
	
	puts("----------------------------------------------------------------------");
	puts("                        HISTÓRICO DO ALUNO");
	puts("----------------------------------------------------------------------");
	
	while(1){
		input("Informe o Nome do aluno [exit para ENCERRAR]: ", STR, nome);
		if(!strcmp(nome, "exit")) return;
		id = buscarAluno(nome, a, cont_a);
		if(id<0){
			printf("Aluno Não Encontrado!\n");
			wait();
		}else
			break;
	}
	
	printf("\nAluno: %s\tCódigo de Matrícula: %03d\tCoef. de Rendimento: %.2f\n\n",
	 a[id].nome, a[id].matricula, a[id].cr);
	 
	for (int i = 0; i < a[id].cont; i++)
		for(int j = 0; j < cont_m; j++)
			if(a[id].notas[0][j] == m[j].codigo){
				printf("\n| DISCIPLINA: %s | PROFESSOR(a): %s | NOTA: %d |\n------",
				m[i].nome, m[i].professor, a[id].notas[1][i]);
				break;
			}
	wait();
}

void ranking(Discente* a, int cont_a){
	system("clear");
	puts("---------------------------------------------------------------------------------------");
	puts("                                       RANKING");
	puts("---------------------------------------------------------------------------------------");
	
	for (int i = 0; i < cont_a; i++)
		printf("\n| ALUNO: %s | CÓDIGO DE MATRÍCULA: %03d | COEF. DE RENDIMENTO: %.2f |\n------"
		,a[i].nome, a[i].matricula, a[i].cr);
	wait();
}	

int main(){
	Disciplina materias[50];
	Discente alunos[100];
	int cont_a = 0, cont_m = 0;
	
	while(1){
		switch(interface()){
			case 0: return 0;
			case 1: materias[cont_m] = cadastrarMateria(cont_m+1);
			cont_m++;
			break;
			case 2: alunos[cont_a] = cadastrarAluno(cont_a+1);
			cont_a++;
			break;
			case 3: matriculaAluno(alunos, cont_a, materias, cont_m);
			break;
			case 4: lancaNotas(alunos, cont_a, materias, cont_m);
			break;
			case 5: diarioDisciplina(materias, cont_m, alunos, cont_a);
			break;
			case 6: historicoAluno(alunos, cont_a, materias, cont_m);
			break;
			case 7: ranking(alunos, cont_a);
			break;
			default: printf("Opção Inválida! Tente Novamente...");
			wait();
			break;
		}
	}
}
