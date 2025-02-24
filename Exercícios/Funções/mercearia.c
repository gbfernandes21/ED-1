#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct{
	int cod, estoque;
	float valor;
	char desc[MAX];
}Produto;

int buscar(Produto* p, int tam, int alvo);
void ordenar(Produto* p, int tam);
void imprimirProduto(Produto p);

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

int interface(){
	system("clear");
	int op;
	printf("========== MERCEARIA ==========\n\n");
	printf("1 - CADASTRAR PRODUTO\n");
	printf("2 - VENDER PRODUTO\n");
	printf("3 - IMPRIMIR RELATÓRIO\n");
	printf("--------------------------------\n");
	printf("0 - SAIR\n\n");
	printf("Digite a Opção Desejada: ");
	scanf(" %d", &op);
	
	return op;
}

Produto cadastrarProduto(Produto* p, int tam){
	system("clear");
	Produto novo;
	printf("========== CADASTRANDO PRODUTO ==========\n\n");
	do{
		printf("Cód. de Barras: ");
		scanf(" %d", &novo.cod);
		if(buscar(p, tam, novo.cod) < 0) break;
		printf("Esse código já existe!\nTente Novamente...\n");
	}while(1);
	setbuf(stdin, NULL);
	printf("Descrição: ");
	scanf("%[^\n]s", novo.desc);
	printf("Valor unitário: ");
	scanf(" %f", &novo.valor);
	printf("Qtde. em Estoque: ");
	scanf(" %d", &novo.estoque);
	
	printf("\nProduto Cadastrado com Sucesso!\n\n");
	imprimirProduto(novo);
	wait();
	return novo;
}

float venderProduto(Produto* p){
	system("clear");
	int qnt;
	printf("========== VENDAS ==========\n");
	printf("Produto: %s\nQtde. em Estoque: %d\nUnidades Solicitadas: "
	, p->desc, p->estoque);
	scanf(" %d", &qnt);
	
	if(qnt > p->estoque){
		printf("Quantidade Indisponível!\n");
		wait();
		return 0;
	}
	
	float valor = qnt*p->valor;
	printf("Venda Concluída com Sucesso!\n");
	p->estoque -= qnt;
	wait();
	return valor;
}

void ordenar(Produto* p, int tam){
	for (int i = 0; i < tam; i++)
		for (int j = 0; j < tam-i-1; j++)
			if(p[j].cod > p[j+1].cod){
				Produto aux = p[j];
				p[j] = p[j+1];
				p[j+1] = aux;
			}
}

int buscar(Produto* p, int tam, int alvo){
	int inicio = 0, fim = tam-1, meio;
	
	while(inicio <= fim){
		meio = (inicio+fim)/2;
		
		if(p[meio].cod == alvo){
			return meio;
			break;
		}else if(p[meio].cod > alvo)
				fim = meio-1;
				else
					inicio = meio+1;
	}
	return -1;
}

void carrinho(Produto* p, int tam){
	system("clear");
	int codigo, ind;
	float total = 0;
	if(!tam){
		printf("Não Há Produtos no Estoque!\n");
		wait();
		return;
	}
	printf("========== CARRINHO ==========\n\n");
	do{
		printf("Cód. de Barras do produto [0 para sair]: ");
		scanf(" %d", &codigo);
		if(!codigo) break;
		do{
			ind = buscar(p, tam, codigo);
			if(ind >= 0) break;
			printf("Código Inexistente!\nTente Novamente...\n");
			scanf(" %d", &codigo);
		}while(1);
		total += venderProduto(&p[ind]);
	}while(1);
	
	printf("Valor total: R$ %.2f\n", total);
	printf("Valor pago: ");
	float pag;
	do{
	scanf(" %f", &pag);
		if(pag >= total) break;
		printf("Valor Insuficiente\nVenda não concluída!\n");
	}while(1);
	printf("\nTroco: R$ %.2f\n", pag-total);
	printf("\nObrigado pela preferência.\nVolte Sempre!!\n");
	wait();
}

void imprimirProduto(Produto p){
	printf("Código: %03d\n\nDesc. do Produto: %s\nValor Unitário: R$ %.2f\nQtde. em Estoque:"
	" %d\n------------------------------------------\n\n"
	, p.cod, p.desc, p.valor, p.estoque);
}

void relatorio(Produto* p, int tam){
	float valor_total = 0;
	int qnt_total = 0;
	system("clear");
	if(!tam){
		printf("Estoque Vazio!\n");
		wait();
		return;
	}
	printf("========== RELATÓRIO ==========\n\n");
	for (int i = 0; i < tam; i++){
		imprimirProduto(p[i]);
		valor_total += p[i].estoque*p[i].valor;
		qnt_total += p[i].estoque;
	}
	
	printf("Qtde. Total de Produtos em Estoque: %d\nValor Total Bruto: R$ %.2f"
	, qnt_total, valor_total);
	wait();
}

int main(){
	Produto estoque[MAX];
	int cont_prod = 0;
	
	do{
		switch(interface()){
			case 1: estoque[cont_prod] = cadastrarProduto(estoque, cont_prod);
			cont_prod++;
			ordenar(estoque, cont_prod);
			break;
			case 2: carrinho(estoque, cont_prod);
			break;
			case 3: relatorio(estoque, cont_prod);
			break;
			case 0: return 0;
		}
	}while(1);
}
