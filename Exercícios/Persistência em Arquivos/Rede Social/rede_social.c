/*GABRIEL FERNANDES DOS SANTOS
 * 07/04/2025*/

enum ARQUIVOS {USER = 0, POST};

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tools.h"
#include "posts.h"
#include "users.h"

#define MAX_FILES 2

#define FILE_USERS "users.dat"
#define FILE_POSTS "posts.dat"

int interface(){
	system("clear");
	int op;
	print_line(70);
	printf("\n\t\t\t= REDE SOCIAL =\n\n");
	print_line(70);
	printf("\n1 - NOVO USUÁRIO\n\n2 - FAZER LOGIN\n\n0 - FECHAR APLICAÇÃO\n\n");
	print_line(70);
	input("\nOpção: ", INT, &op);
	getchar();
	return op;
}

int main(){
	srand(time(NULL));
	FILE* files[MAX_FILES];
	files[USER] = abrir_arquivo(FILE_USERS);
	files[POST] = abrir_arquivo(FILE_POSTS);
	
	do{
		switch(interface()){
			case 0:  fechar_arquivos(files, MAX_FILES);
			return 0;
			case 1: criar_usuario(files[USER]);
			break;
			case 2: login(files);
			break;
			default: printf("Opção inválida!\n");
			wait();
			break;
		}
	}while(1);
}
