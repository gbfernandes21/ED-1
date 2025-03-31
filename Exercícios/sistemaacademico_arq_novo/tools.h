#include <stdio.h>
#include <string.h>

#define INT " %d"
#define FLOAT " %f"
#define CHAR " %c"
#define STR " %[^\n]s"

void input(char* instrucao, char* tipo, void* ponteiro){
	printf("%s", instrucao);
	scanf(tipo, ponteiro);
}

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

void notas(){
	printf("============================================================\n");
	printf("\t\tLANÇAR NOTAS\t\n");
	printf("============================================================\n\n");
}

void cAluno(){
	printf("============================================================\n");
	printf("\t\tCADASTRAR ALUNO\t\n");
	printf("============================================================\n\n");
}


void hAluno(){
	printf("============================================================\n");
	printf("\t\tHISTÓRICO DO ALUNO\t\n");
	printf("============================================================\n\n");
}


void dAluno(){
	printf("==================== DADOS DO ALUNO ===================\n");
}

void mtr(){
	printf("============================================================\n");
	printf("\t\tMATRÍCULA\t\n");
	printf("============================================================\n\n");
}

void dDisc(){
	printf("============================================================\n");
	printf("\t\tDIÁRIO DA DISCIPLINA\t\n");
	printf("============================================================\n\n");
}

void cDisc(){
	printf("============================================================\n");
	printf("\t\tCADASTRAR DISCIPLINA\t\n");
	printf("============================================================\n\n");
}


void dataD(){
	printf("================ DADOS DA DISCIPLINA ================\n\n");
}

