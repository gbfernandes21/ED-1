#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING 100

typedef struct {
	char username[STRING];
	char nome[STRING];
	char senha[STRING];
}Usuario;

int menu_do_usuario(char* nome);
int usuario_duplicado(FILE* users, Usuario u); //CHECA SE NÃO HÁ USUARIOS COM MESMO NOME, USER E SENHA.
int buscar_conta(char* username, char* senha, FILE* users, Usuario* user); //BUSCA A CONTA NO ARQUIVO COM BASE NOS DADOS INFORMADOS NA INTERFACE DE LOGIN.
void login(FILE** files);
void criar_usuario(FILE* arq_users);
void alterar_senha(Usuario user, FILE* users);
void perfil_do_usuario(Usuario user, FILE** files);

void criar_usuario(FILE* arq_users){
	Usuario u;
	
	do{
		system("clear");
		print_line(70);
		printf("\t\tNOVO USUÁRIO\n");
		print_line(70);
		input("Nome completo: ", STR, u.nome);
		input("Nome de usuário: ", STR, u.username);
		input("Senha: ", STR, u.senha);
		
		if(usuario_duplicado(arq_users, u)){
			printf("Esse usuário já existe!\n");
			wait();
			continue;
		}
		break;
	}while(1);
	
	fseek(arq_users, 0, SEEK_END);
	fwrite(&u, sizeof(Usuario), 1, arq_users);
	printf("Conta criada com sucesso!\n");
	wait();
}

int usuario_duplicado(FILE* users, Usuario u){
	fseek(users, 0, SEEK_SET);
	Usuario user;
	
	while(fread(&user, sizeof(Usuario), 1, users))
		if(!strcmp(user.nome, u.nome) && !strcmp(user.username, u.username) && !strcmp(user.senha, u.senha))
			return 1;
	return 0;
}

void login(FILE** files){
	char username[STRING];
	char senha[STRING];
	Usuario user;
	
	do{
		system("clear");
		print_line(70);
		printf("\n\t\t\t\tLOGIN\n\n");
		print_line(70);
		
		input("\nUsername [exit para VOLTAR]: ", STR, username);
		if(!strcmp(username, "exit")) return;
		input("Senha: ", STR, senha);
		
		if(!buscar_conta(username, senha, files[USER], &user)){
			printf("Usuário ou senha incorretos!\nTecle ENTER para tentar novamente...\n");
			wait();
			continue;
		}
		break;
	}while(1);
	
	perfil_do_usuario(user, files);
	wait();
}

int menu_do_usuario(char* nome){
	int op;
	system("clear");
	print_line(70);
	printf("\n\tSEJA BEM-VINDO(a) << %s >>\n\n", nome);
	print_line(70);
	printf("\n1 - NOVO POST\n2 - LISTAR TODOS OS POSTS\n3 - EXCLUIR POST\n4 - ALTERAR SENHA\n0 - LOGOUT\n\n");
	print_line(70);
	input("Opção: ", INT, &op);
	getchar();
	return op;
}

void perfil_do_usuario(Usuario user, FILE** files){
	char* usuario = user.username;
	char* nome = user.nome;
	
	do{
		switch(menu_do_usuario(nome)){
			case 0: return;
			case 1: criar_post(usuario, files[POST]);
			break;
			case 2:
			if (!listar_posts(files[POST], usuario, -1))
				printf("Nenhum post foi encontrado!\n");
			wait();
			break;
			case 3: delete_post(files[POST], usuario);
			break;
			case 4: alterar_senha(user, files[USER]);
			break;
			default: printf("Opção inválida!\n");
			wait();
			break;
		}
	}while(1);
}

int buscar_conta(char* username, char* senha, FILE* users, Usuario* user){
	fseek(users, 0, SEEK_SET);
	Usuario u;
	while(fread(&u, sizeof(Usuario), 1, users))
		if(!strcmp(username, u.username) && !strcmp(senha, u.senha)){
			strcpy(user->nome, u.nome);
			strcpy(user->username, u.username);
			strcpy(user->senha, u.senha);
			return 1;
		}
	return 0;
}

void alterar_senha(Usuario user, FILE* users){
	system("clear");
	char* usuario = user.username;
	char* atual = user.senha;
	char nova[STRING];
	
	print_line(70);
	printf("\n\t\tALTERAR SENHA\n\n");
	print_line(70);
	input("\nDigite a nova senha [exit para SAIR] : ", STR, nova);
	if(!strcmp(nova, "exit")) return;
	
	Usuario u;
	
	fseek(users, 0, SEEK_SET);
	while(fread(&u, sizeof(Usuario), 1, users))
		if(!strcmp(usuario, u.username) && !strcmp(atual, u.senha)){
			strcpy(u.senha, nova);
			fseek(users, -sizeof(Usuario), SEEK_CUR);
			fwrite(&u, sizeof(Usuario), 1, users);
		}
	printf("Senha atualizada com sucesso!\n");
	wait();
}
