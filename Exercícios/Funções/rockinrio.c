#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BILHETERIA 1000
#define MAX_DIAS 7

typedef struct {
	char nome[50], cpf[11], headLiner[50], token[25];
	float valor;
}Ingresso;

typedef struct {
	char headLiner[50];
	int cod, cont_ingressos;
	Ingresso ingressos[MAX_BILHETERIA];
	float valor_ingresso;
}Dia;

Dia cadastrar_show(int cod);
int interface();
int busca_ingresso_cpf(char* cpf, Dia* d, int cont);
int busca(int alvo, Dia* d, int cont);
void wait();
void erro(int* op);
void print_info(Ingresso ing);
void print_atracoes(Dia* d, int cont);
void cria_token(char* token);
void vender_ingresso(Dia* d, int cont);
void relatorio_ingressos(Dia* d, int cont);
void print_ingresso(Ingresso ing);
void baixar_ingressos(Dia* d, int cont);

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

void erro(int* op){
	printf("Opção Inválida!\nTente novamente: ");
	scanf(" %d", op);
	while(getchar() != '\n');
}

void print_info(Ingresso ing){
	printf("| Nome: %s\t| Token: %s |\n------\n",
	ing.nome, ing.token);
}

int interface(){
	system("clear");
	int op;
	
	printf("========== ROCK IN RIO ==========\n");
	printf("\n1 - Cadastrar dia no Line-up\n");
	printf("2 - Vender Ingresso\n");
	printf("3 - Baixar Ingresso\n");
	printf("4 - Listar Qtde. e Tokens\n");
	printf("0 - Sair X\n\n");
	printf("Opção: ");
	scanf(" %d", &op);
	while(getchar() != '\n');
	
	return op;
}

Dia cadastrar_show(int cod){
	Dia novo;
	
	printf("Informe a atração principal do dia: ");
	scanf("%[^\n]s", novo.headLiner);
	printf("Informe qual será o valor do ingresso: ");
	scanf(" %f", &novo.valor_ingresso);
	novo.cod = cod;
	novo.cont_ingressos = 0;
	printf("Show cadastrado com Sucesso!\n");
	wait();
	
	return novo;
}

void print_atracoes(Dia* d, int cont){
	for (int i = 0; i < cont; i++)
		printf("Dia %02d - %s\n", d[i].cod, d[i].headLiner);
}

void cria_token(char* token){
	for (int i = 0; i < 24; i++)
		token[i] = '0' + rand()%10;
	token[24] = '\0';
}

int busca(int alvo, Dia* d, int cont){
	for (int i = 0; i < cont; i++)
		if(d[i].cod == alvo) return i;
	return -1;
}

void vender_ingresso(Dia* d, int cont){
	system("clear");
	
	if(!cont){
		printf("Não há shows confirmados no momento\nTente mais tarde...\n");
		wait();
		return;
	}
	
	int op;
	Ingresso novo;
	
	printf("Nome do Comprador: ");
	scanf("%[^\n]s", novo.nome);
	setbuf(stdin, NULL);
	printf("CPF: ");
	scanf("%[^\n]s", novo.cpf);
	setbuf(stdin, NULL);
	printf("\n");
	print_atracoes(d, cont);
	printf("Informe a opção desejada: ");
	scanf(" %d", &op);
	
	int pos = busca(op, d, cont);
	
	while(pos < 0){
		erro(&op);
		pos = busca(op, d, cont);
	}
	
	if(d[pos].cont_ingressos == MAX_BILHETERIA){
		printf("\nBilheteria esgotada!\n");
		wait();
		return;
	}
	
	float valor = d[pos].valor_ingresso, pagamento, troco;
	
	printf("Valor: R$ %.2f\n\n", valor);
	printf("Pagamento: ");
	scanf(" %f", &pagamento);
	
	while(pagamento < valor){
		printf("Valor insuficiente!\nTente novamente: ");
		scanf(" %f", &pagamento);
	}
	
	troco = pagamento-valor;
	
	Ingresso* bilheteria = d[pos].ingressos;
	char* artista = d[pos].headLiner;
	
	if(troco)
		printf("Troco: R$ %.2f", troco);
	printf("\nVenda realizada com sucesso!\nAproveite o show!!\n");
	
	novo.valor = valor;
	cria_token(novo.token);
	strcpy(novo.headLiner, artista);
	bilheteria[d[pos].cont_ingressos] = novo;
	d[pos].cont_ingressos++;
	wait();
}

void relatorio_ingressos(Dia* d, int cont){
	system("clear");
	
	if(!cont){
		printf("(Vazio)\n");
		wait();
		return;
	}
	
	int op;
	print_atracoes(d, cont);
	printf("Digite a opção desejada: ");
	scanf(" %d", &op);
	system("clear");
	
	int pos = busca(op, d, cont);
	
	while(pos < 0){
		erro(&op);
		pos = busca(op, d, cont);
	}
	
	Ingresso* ingressos = d[pos].ingressos;
	int cont_i = d[pos].cont_ingressos;
	
	if(!cont_i){
		printf("(Vazio)\n");
		wait();
		return;
	}
	
	printf("Dia: %02d\t\tHeadliner: %s\tValor do ingresso: R$ %.2f\n\n",
	d[pos].cod, d[pos].headLiner, d[pos].valor_ingresso);
	
	for (int i = 0; i < cont_i; i++)
		print_info(ingressos[i]);
	printf("\nTotal de Ingressos Vendidos: %d\nFaturamento: R$ %.2f",
	cont_i, d[pos].valor_ingresso*cont_i);
	wait();
}

void print_ingresso(Ingresso ing){
	printf("| Nome: %s\t| Headliner: %s\t| Token: %s\t| Valor: R$ %.2f |\n----------\n",
	ing.nome, ing.headLiner, ing.token, ing.valor);
}

int busca_ingresso_cpf(char* cpf, Dia* d, int cont){
	int achou = 0;
	
	for (int i = 0; i < cont; i++){
		Ingresso* ingressos = d[i].ingressos;
		int cont_ing = d[i].cont_ingressos;
		for (int j = 0; j < cont_ing; j++)
			if(!strcmp(cpf, ingressos[j].cpf)){
				achou = 1;
				print_ingresso(ingressos[j]);
				strcpy(ingressos[j].token, "0");
			}
	}
	
	return achou;
}

void baixar_ingressos(Dia* d, int cont){
	system("clear");
	
	if(!cont){
		printf("(Vazio)\n");
		wait();
		return;
	}
	
	char cpf[50];
	printf("Informe o CPF: ");
	scanf("%[^\n]s", cpf);
	
	while(!busca_ingresso_cpf(cpf, d, cont)){
		printf("CPF não encontrado!\n");
		wait();
		return;
	}
	wait();
}

int main(){
	srand(time(NULL));
	Dia dias[MAX_DIAS];
	int cont_dias = 0;
	
	do{
		switch(interface()){
			case 0: return 0;
			case 1: 
			if(cont_dias < MAX_DIAS){
				dias[cont_dias] = cadastrar_show(cont_dias+1);
				cont_dias++;
			} else{
				printf("Todos os Line-ups já foram cadastrados.\n");
				wait();
			} break;
			case 2: vender_ingresso(dias, cont_dias);
			break;
			case 3: baixar_ingressos(dias, cont_dias);
			break;
			case 4: relatorio_ingressos(dias, cont_dias);
			break;
			default: printf("Opção Inválida!\n");
			wait();
			break;
		}
	}while(1);
}
