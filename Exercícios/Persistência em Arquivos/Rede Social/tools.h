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

void print_line(int cont){
	for (int i = 0; i < cont; i++)
		printf("-");
	printf("\n");
}

FILE* abrir_arquivo(char* arq){
	FILE* file = NULL;
	
	file = fopen(arq, "rb+");
	if(!file)
		file = fopen(arq, "wb+");
	if(!file)
		printf("Algo deu errado!\n");
	return file;
}

void fechar_arquivos(FILE** arquivos, int cont){
	for (int i = 0; i < cont; i++)
		fclose(arquivos[i]);
}
