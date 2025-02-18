#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	char descricao[100];
	int codigo, estoque;
	float preco;
}Produto;

void atualizarEstoque(Produto *a, int b){
	a->estoque -= b;
}

Produto cadastrarProduto(){
	Produto novo;
	printf("=============== CADASTRANDO PRODUTO ===============\n");
	printf("Produto: ");
	scanf("%[^\n]s", novo.descricao);
	printf("Preço: ");
	scanf(" %f", &novo.preco);
	printf("Estoque: ");
	scanf(" %d", &novo.estoque);
	novo.codigo = 10000+rand()%99999;
	
	printf("Produto cadastrado com sucesso!\n");
	return novo;
}
	
void mostrarProduto(Produto a){
	printf("\nProduto castrado: %s\n", a.descricao);
	printf("Código de barras: %d\n", a.codigo);
	printf("Estoque: %02d\n", a.estoque);
	printf("Valor: R$ %.2f\n\n", a.preco);
}

void venderProduto(Produto *a){
	int quantidade;
	float total, pago, troco;
	
	do{
		printf("Quantas unidades deseja adquirir? ");
		scanf(" %d", &quantidade);
		
		if(quantidade > a->estoque){
			printf("Não temos essa quantidade em nosso estoque!\n");
			system("sleep 1.5"); system("clear"); continue;
		}
		break;
	}while(1);
	
	total = (float)a->preco*quantidade;
	
	do{
		printf("Total a pagar: R$ %.2f\n", total);
		printf("Pagamento: ");
		scanf(" %f", &pago);
		
		if(pago < total){
			printf("Valor insuficiente!\n");
			system("sleep 1.5"); system("clear"); continue;
		}
		break;
	}while(1);
	
	troco = pago-total;
	
	printf("\n*** VENDA REALIZADA COM SUCESSO! ***\n\n");
	printf("Produto: %s\nQtde.: %d\nTotal compra: R$ %.2f\n", a->descricao, quantidade, total);
	if(troco > 0)
		printf("Total pago pelo cliente: R$ %.2f\nTroco: R$ %.2f\n", pago, troco);
	atualizarEstoque(a, quantidade);
}

int main(){
	Produto p = cadastrarProduto();
	mostrarProduto(p);
	venderProduto(&p);
	mostrarProduto(p);
	
	return 0;
}
