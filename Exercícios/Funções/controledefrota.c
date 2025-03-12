#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int codigo, passageiros, manutencao;
	char placa[10];
}Veiculo;

typedef struct {
	char cidade_origem[50], cidade_destino[50];
	int codigo_veiculo, poltronas[100], cont;
	float valor_passagem; 
}Viagem;

void wait();
void zerar(int* p, int cont);
void passagens_vendidas(int cont, int* p, int max);
Veiculo cadastrarVeiculo(int cod);
int buscaVeiculo(int cod, int cont, Veiculo* v);
Viagem cadastrarViagem(int cont, Veiculo* v);
int buscaViagem(Viagem* v, int cont, char* origem, char* destino);
void printPoltronas(int* p, int cont, int alvo);
int checkAssento(int assento, int* p);
int contPoltronas(int* p, int cont, int alvo);
void printViagem(Viagem v);
int checkLotado(int* p, int cont);
void venderPassagem(Viagem* v, int cont);
void printVeiculo(Veiculo v);
void viagensRelacionadas(int cod, Viagem* v, int cont);
void relatorioVeiculos(Veiculo* v, int contv, Viagem* via, int contvia);
void relatorioViagens(Viagem* v, int cont);

int interface(){
	system("clear");
	int op;
	puts("1) CADASTRAR VEÍCULO");
	puts("2) CADASTRAR VIAGEM");
	puts("3) VENDER PASSAGEM");
	puts("4) RELATÓRIO: FROTA DE VEÍCULOS");
	puts("5) RELATÓRIO: VIAGENS");
	puts("0) SAIR X");
	printf("\nOpção: ");
	scanf(" %d", &op);
	while(getchar() != '\n');
	return op;
}

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

void zerar(int* p, int cont){
	for (int i = 0; i < cont; i++)
		p[i] = 0;
}

void passagens_vendidas(int cont, int* p, int max){
	int i = 0;
	do{
		int pos = rand()%max;
		if (p[pos])
			continue;
		else
			p[pos] = 1;
		i++;
	}while(i < cont);
}

Veiculo cadastrarVeiculo(int cod){
	system("clear");
	Veiculo novo;
	
	printf("Placa do Veículo: ");
	scanf("%[^\n]s", novo.placa);
	printf("Capacidade Máxima de Passageiros: ");
	scanf(" %d", &novo.passageiros);
	
	
	novo.codigo = cod;
	printf("O veículo está em Manutenção?\n1 - SIM\n0 - NÃO\n\n");
	scanf(" %d", &novo.manutencao);
	
	printf("Veículo cadastrado com Sucesso!\n");
	wait();
	return novo;
}

int buscaVeiculo(int cod, int cont, Veiculo* v){
	for (int i = 0; i < cont; i++)
		if(i+1 == cod && !v[i].manutencao)
			return i;
	return -1;
}

Viagem cadastrarViagem(int cont, Veiculo* v){
	system("clear");
	Viagem nova;
	
	printf("Origem: ");
	scanf("%[^\n]s", nova.cidade_origem);
	setbuf(stdin, NULL);
	printf("Destino: ");
	scanf("%[^\n]s", nova.cidade_destino);
	
	printf("Digite o Código do Veículo de fará essa Viagem: ");
	scanf(" %d", &nova.codigo_veiculo);
	int valido = buscaVeiculo(nova.codigo_veiculo, cont, v);
	
	while(valido < 0){
		printf("Veículo indisponível.\nTente novamente: ");
		scanf(" %d", &nova.codigo_veiculo);
		valido = buscaVeiculo(nova.codigo_veiculo, cont, v);
	}
	
	nova.cont = v[valido].passageiros;
	int vendidas = nova.cont/2;
	int* poltronas = nova.poltronas;
	
	printf("Informe o valor da passagem: ");
	scanf(" %f", &nova.valor_passagem);
	
	zerar(poltronas, nova.cont);
	passagens_vendidas(vendidas, poltronas, nova.cont);
	
	printf("Viagem cadastrada com Sucesso!\n");
	wait();
	return nova;
}

int buscaViagem(Viagem* v, int cont, char* origem, char* destino){
	for (int i = 0; i < cont; i++)
		if(!strcmp(v[i].cidade_origem, origem) && !strcmp(v[i].cidade_destino, destino))
			return i;
	return -1;
}

void printPoltronas(int* p, int cont, int alvo){
	for (int i = 0; i < cont; i++)
		if(p[i] == alvo)
			printf("[%d] ", i+1);
	printf("\n");
}

int checkAssento(int assento, int* p){
	if(!p[assento-1])
		return 1;
	else
		return 0;
}

int contPoltronas(int* p, int cont, int alvo){
	int total = 0;
	for (int i = 0; i < cont; i++)
		if(p[i] == alvo) total++;
	return total;
}

void printViagem(Viagem v){
	printf("Origem: %s\t\tDestino: %s\t\tCód. do Veículo: %03d\t\tValor da Passagem: R$ %.2f\n",
	v.cidade_origem, v.cidade_destino, v.codigo_veiculo, v.valor_passagem);
	
	int* poltronas = v.poltronas;
	int cont = v.cont;
	
	printf("\nPoltronas Ocupadas (%d)\n", contPoltronas(poltronas, cont, 1));
	printPoltronas(poltronas, cont, 1);
	printf("\nPoltronas Livres (%d)\n", contPoltronas(poltronas, cont, 0));
	printPoltronas(poltronas, cont, 0);
}

int checkLotado(int* p, int cont){
	for (int i = 0; i < cont; i++)
		if(!p[i]) return 0;
	return 1;
}

void venderPassagem(Viagem* v, int cont){
	system("clear");
	char origem[50], destino[50];
	
	printf("Origem: ");
	scanf("%[^\n]s", origem);
	setbuf(stdin, NULL);
	printf("Destino: ");
	scanf("%[^\n]s", destino);
	
	int pos = buscaViagem(v, cont, origem, destino);
	
	if(pos < 0){
		printf("Viagem indisponível!\n");
		wait();
		return;
	}
	
	int assento, maximo = v[pos].cont;
	float valor = v[pos].valor_passagem;
	int* assentos = v[pos].poltronas;
	int lotado = checkLotado(assentos, maximo);
	
	if(lotado){
		printf("Assentos esgotados!\n");
		wait();
		return;
	}
	
	printViagem(v[pos]);
	printf("Informe a poltrona desejada: ");
	scanf(" %d", &assento);
	
	int disponivel = checkAssento(assento, assentos);
	
	while(!disponivel){
		printf("Assento indisponível!\nEscolha outro: ");
		scanf(" %d", &assento);
		disponivel = checkAssento(assento, assentos);
	}
	
	printf("Valor pago: ");
	float pagamento;
	scanf(" %f", &pagamento);
	
	while(pagamento < valor){
		printf("Valor insuficiente!\nTente novamente: ");
		scanf(" %f", &pagamento);
	}
	
	float troco = pagamento-valor;
	
	if(troco)
		printf("Troco: R$ %.2f\n\n", troco);
	printf("Obrigado pela preferência, boa viagem!\n");
	assentos[assento-1] = 1;
	wait();
}

void printVeiculo(Veiculo v){
	printf("Placa: %s\tQtde. Máxima de Passageiros: %d\tCódigo: %03d\n",
	v.placa, v.passageiros, v.codigo);
}

void viagensRelacionadas(int cod, Viagem* v, int cont){
	for (int i = 0; i < cont; i++)
		if(v[i].codigo_veiculo == cod)
			printf("%s -> %s\n", v[i].cidade_origem, v[i].cidade_destino);
}

void relatorioVeiculos(Veiculo* v, int contv, Viagem* via, int contvia){
	system("clear");
	for (int i = 0; i < contv; i++){
		printVeiculo(v[i]);
		printf("\nViagens Relacionadas\n\n");
		viagensRelacionadas(v[i].codigo, via, contvia);
		printf("-------------------\n\n");
	}
	wait();
}

void relatorioViagens(Viagem* v, int cont){
	system("clear");
	for (int i = 0; i < cont; i++){
		printViagem(v[i]);
		int* lugares = v[i].poltronas;
		float passagem = v[i].valor_passagem;
		int total_lugares = v[i].cont;
		int qnt = contPoltronas(lugares, total_lugares, 1);
		printf("\nArrecadação Total da Viagem: R$ %.2f\n", passagem*qnt);
		printf("-------------------\n\n");
	}
	wait();
}

int main(){
	srand(time(NULL));
	Veiculo veiculos[100];
	Viagem viagens[20];
	int cont_veiculos, cont_viagens;
	
	do{
		switch(interface()){
			case 0: return 0;
			case 1: veiculos[cont_veiculos] = cadastrarVeiculo(cont_veiculos+1);
			cont_veiculos++;
			break;
			case 2: viagens[cont_viagens] = cadastrarViagem(cont_veiculos, veiculos);
			cont_viagens++;
			break;
			case 3: venderPassagem(viagens, cont_viagens);
			break;
			case 4: relatorioVeiculos(veiculos, cont_veiculos, viagens, cont_viagens);
			break;
			case 5: relatorioViagens(viagens, cont_viagens);
			break;
			default:
			printf("Opção Inválida!\n");
			wait();
			break;
		}
	}while(1);
}
