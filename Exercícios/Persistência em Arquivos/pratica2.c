#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PRODUCTS "products.txt"
#define MAX_PRODUCTS 100
#define STRING 50

typedef struct{
	char descricao[STRING];
	int quantidade, cod;
	float preco;
}Produto;

int interface();
int carregarEstoque(Produto* p);
int busca(int alvo, Produto* p, int cont);
void wait();
void limite();
void printProduto(Produto p);
void relatorio(Produto* p, int cont);
void carrinho(Produto* p, int* cont);
void salvaProduto(Produto* p, int cont);
void cadastrarProduto(Produto* p, int* cont);
float venderProduto(Produto* p);

int interface(){
	system("clear");
	int op;
	printf("1 - CADASTRAR PRODUTO\n2 - VENDER PRODUTO\n3 - ESTOQUE\n0 - SAIR\n\nOpção: ");
	scanf(" %d", &op);
	getchar();
	return op;
}

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

void limite(){
	system("clear");
	printf("Limite de cadastros atingido!\n");
	wait();
}

int carregarEstoque(Produto* p){
	FILE* file = fopen(FILE_PRODUCTS, "r");
	
		if(file == NULL) return 0;
		int i = 0;
		while(i < MAX_PRODUCTS && fscanf(file, "%s %d %d %f", p[i].descricao, &p[i].cod, &p[i].quantidade, &p[i].preco) == 4)
			i++;
	fclose(file);
	return i;
}

void salvaProduto(Produto* p, int cont){
	FILE* file = fopen(FILE_PRODUCTS, "w");
	
		if(file == NULL){
			printf("ERRO!\n");
			return;
		}
		
		for (int i = 0; i < cont; i++)
			fprintf(file, "%s %d %d %f\n", p[i].descricao, p[i].cod, p[i].quantidade, p[i].preco);
	fclose(file);
}

void printProduto(Produto p){
	printf("| CÓDIGO: %03d | PRODUTO: %s\t| QTDE. EM ESTOQUE : %d\t| VALOR UN.: R$ %.2f\t|\n", p.cod, p.descricao, p.quantidade, p.preco);
}

void relatorio(Produto* p, int cont){
	system("clear");
	if(!cont){
		printf("(Estoque vazio)\n");
		wait();
		return;
	}
	
	float valor_prod = 0;
	int qnt_prod = 0;
	
	for (int i = 0; i < cont; i++){
		printProduto(p[i]);
		qnt_prod += p[i].quantidade;
		valor_prod += p[i].quantidade*p[i].preco;
	}
	
	printf("--------------------------------------------------------------------------------\n");
	printf("Produtos em Estoque: %d\nValor Total(bruto): R$ %.2f\n", qnt_prod, valor_prod);
	printf("--------------------------------------------------------------------------------\n");
	wait();
}

int busca(int alvo, Produto* p, int cont){
	for (int i = 0; i < cont; i++)
		if(alvo == p[i].cod) return i;
	return -1;
}

float venderProduto(Produto* p){
	if(!p->quantidade){
		printf("\nProduto indisponível\n\n");
		return 0;
	}
	
	int qnt;
	float valor;
	
	printf("\n");
	printProduto(*p);
	printf("\nDigite a quantidade desejada [0 para SAIR]: ");
	scanf(" %d", &qnt);
	if(qnt<=0) return 0;
	
	while(qnt > p->quantidade){
		printf("\nQuantidade indisponível para venda!\nTente novamente ou digite 0 para SAIR: ");
		scanf(" %d", &qnt);
		if(qnt<=0) return 0;
	}
	
	printf("\n");
	valor = qnt*p->preco;
	p->quantidade -= qnt;
	return valor;
}

void carrinho(Produto* p, int* cont){
	system("clear");
	if(!*cont){
		printf("Não há produtos cadastrados no sistema!\n");
		wait();
		return;
	}
	
	float total = 0, pag, troco;
	int cod, i;
	
	do{
		printf("[0 para fechar carrinho]\n[-1 para CANCELAR compra]\nDigite o Código do produto: ");
		scanf(" %d", &cod);
		if(!cod) break;
		if(cod<0) return;
		
		while((i = busca(cod, p, *cont)) < 0){
			printf("\nCódigo inválido!\nTente novamente ou digite -1 para CANCELAR a compra: ");
			scanf(" %d", &cod);
			if(cod<0) return;
		}
		
		total += venderProduto(&p[i]);
	}while(1);
	
	printf("\nValor total da compra: R$ %.2f\n", total);
	printf("\nValor pago [0 para CANCELAR compra]: ");
	scanf(" %f", &pag);
	if(!pag) return;
	
	while(pag<total){
		printf("\nValor insuficiente!\nTente novamente ou digite 0 para CANCELAR a compra: ");
		scanf(" %f", &pag);
		if(!pag) return;
	}
	
	troco = pag-total;
	if(troco)
		printf("\nTroco: %.2f", troco);
	printf("\nVenda realizada com Sucesso!\nObrigado pela preferência!!\n");
	salvaProduto(p, *cont);
	wait();
}

void cadastrarProduto(Produto* p, int* cont){
		system("clear");
		printf("Nome do produto [exit para SAIR]: ");
		scanf("%[^\n]s", p[*cont].descricao);
		getchar();
		if(!strcmp(p[*cont].descricao, "exit")) return;
		
		printf("Qtde. em Estoque: ");
		scanf(" %d", &p[*cont].quantidade);
		printf("Valor Unitário: ");
		scanf(" %f", &p[*cont].preco);
		
		p[*cont].cod = *cont+1;
		(*cont)++;
		printf("Produto Cadastrado com Sucesso!\n");
		salvaProduto(p, *cont);
		wait();
}

int main(){
	Produto estoque[MAX_PRODUCTS];
	int cont = carregarEstoque(estoque);
	
	do{
		switch(interface()){
			case 0: return 0;
			case 1: cont < MAX_PRODUCTS ? cadastrarProduto(estoque, &cont) : limite();
			break;
			case 2: carrinho(estoque, &cont);
			break;
			case 3: relatorio(estoque, cont);
			break;
		}
	}while(1);
}
