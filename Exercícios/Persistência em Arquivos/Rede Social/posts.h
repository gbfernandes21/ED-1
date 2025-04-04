#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING 100
#define CONTENT 500

typedef struct {
	char username[STRING];
	char conteudo[CONTENT];
	int id;
	int valido;
}Publicacao;

int listar_posts(FILE* posts, char* username, int cod);
void print_post(Publicacao post);
void criar_post(char* username, FILE* posts);
void delete_post(FILE* posts, char* username);

void criar_post(char* username, FILE* posts){
	system("clear");
	fseek(posts, 0, SEEK_END);
	Publicacao post;
	
	input("O que você está pensando agora [exit para SAIR] ? ", STR, post.conteudo);
	if(!strcmp(post.conteudo, "exit")) return;
	strcpy(post.username, username);
	post.id = rand()%1000;
	post.valido = 1;
	
	fwrite(&post, sizeof(Publicacao), 1, posts);
	printf("Post publicado com Sucesso!\n");
	wait();
}

void print_post(Publicacao post){
	printf("%s\tpost: %d\n\n", post.username, post.id);
	printf("%s\n", post.conteudo);
	print_line(70);
}

int listar_posts(FILE* posts, char* username, int cod){
	system("clear");
	Publicacao post;
	int achou = 0;
	fseek(posts, 0, SEEK_SET);
	
	while(fread(&post, sizeof(Publicacao), 1, posts))
		if(!strcmp(username, post.username)){
			if(cod < 0 && post.valido){
				achou = 1;
				print_post(post);
			}else if(cod >= 0)
					if(post.id == cod && post.valido){
						achou = 1;
						print_post(post);
					}
		}
	return achou;
}

void delete_post(FILE* posts, char* username){
	system("clear");
	int cod;
	print_line(70);
	printf("\n\t\tEXLUSÃO DE POST\n\n");
	print_line(70);
	
	input("\nInforme o código do post que você deseja excluir [-1 para SAIR] : ", INT, &cod);
	if(cod < 0) return;
	if(!listar_posts(posts, username, cod)){
		printf("Esse post já foi excluído!\n");
		wait();
		return;
	}
	
	char op;
	do{
		input("\nDeseja excluir esse post? [s/n]: ", CHAR, &op);
	}while(op != 's' && op != 'n');
	
	if (op == 'n') return;
	
	if (op == 's'){
		fseek(posts, 0, SEEK_SET);
		Publicacao post;
		while(fread(&post, sizeof(Publicacao), 1, posts))
			if(!strcmp(username, post.username) && cod == post.id){
				post.valido = 0;
				fseek(posts, -sizeof(Publicacao), SEEK_CUR);
				fwrite(&post, sizeof(Publicacao), 1, posts);
			}
	}
	
	printf("O post foi exluído!\n");
	wait();
}
