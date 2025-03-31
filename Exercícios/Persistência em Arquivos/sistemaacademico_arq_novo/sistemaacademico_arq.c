#include <stdio.h>
#include <stdlib.h>
#include "matriculas.h"

#define FILE_DISCENTE "discentes.dat"
#define FILE_DISCIPLINA "disciplinas.dat"
#define FILE_MATRICULA "matriculas.dat"

FILE* abrirArquivo(char* arq){
	FILE* a = fopen(arq, "rb+");
	
	if(!a)
		a = fopen(arq, "wb+");
	if(!a)
		printf("Não foi possível abrir o arquivo!\n");
	return a;
}

void fecharArquivos(FILE* a1, FILE* a2, FILE* a3){
	fclose(a1);
	fclose(a2);
	fclose(a3);
}

int interface(){
	system("clear");
	int op;
	printf("1 - CADASTRAR DISCENTE\n2 - CADASTRAR DISCIPLINA\n3 - MATRICULAR DISCENTE\n4 - HISTÓRICO DO DISCENTE\n5 - DIÁRIO DA DISCIPLINA\n\n0 - SAIR\n\n");
	input("Opção: ",INT, &op);
	getchar();
	return op;
}

int main(){
	FILE* arq_discentes = abrirArquivo(FILE_DISCENTE);
	FILE* arq_disciplinas = abrirArquivo(FILE_DISCIPLINA);
	FILE* arq_matriculas = abrirArquivo(FILE_MATRICULA);
	
	do{
		switch(interface()){
			case 0: fecharArquivos(arq_discentes, arq_disciplinas, arq_matriculas);
			return 0;
			case 1: setDiscente(arq_discentes);
			break;
			case 2: setDisciplina(arq_disciplinas);
			break;
			case 3: matricularDiscente(arq_matriculas, arq_discentes, arq_disciplinas);
			break;
			case 4: historicoDiscente(arq_discentes, arq_disciplinas, arq_matriculas);
			break;
			case 5: diarioDisciplina(arq_disciplinas, arq_discentes, arq_matriculas);
			break;
			default: printf("Opção inválida!\n");
			wait();
			break;
		}
	}while(1);
}
