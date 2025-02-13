#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHEGADA 60
#define LIMITE 10

typedef struct{
	char nome[LIMITE], simbolo;
	int pontos;
}Player;

int main(){
	system("clear");
	srand(time(NULL));
	int n;

	do{
		printf("Quantos competidores? ");
		scanf(" %d", &n);
		system("clear");
		if(n > 1) break;
	}while(1);
	
	Player corrida[n];
	int cont = 0;
	char vencedor[LIMITE];

	for (int i = 0; i < n; i++){
		do{
			printf("Digite o nome e o símbolo do Competidor %02d: ", i+1);
			scanf(" %s %c", corrida[i].nome, &corrida[i].simbolo);
			
			if(strlen(corrida[i].nome) > LIMITE){
				printf("Nome muito grande...\nDigite um nome menor.\n");
				system("sleep 1");
				system("clear");
				continue;
			}
			system("clear");
			break;
		}while(1);
		
		corrida[i].pontos = 0;
	}
		
	for (int i = n; i > 0 ; i--){
		printf("A corrida começa em %d\n", i);
		system("sleep 1");
		system("clear");
	}
		
	do{
		for (int i = 0; i < n; i++){
			printf("%-10s", corrida[i].nome);
			for (int j = 0; j < CHEGADA+1; j++)
				((j < corrida[i].pontos) && (j < CHEGADA)) ? printf("%c", corrida[i].simbolo) : 
				(j < CHEGADA) ? printf(" ") : printf("|");
			printf("\n");	
		}
		
		if(cont) break;
		system("sleep 1"); system("clear");
		
		for (int i = 0; i < n; i++){
			corrida[i].pontos += 1+rand()%3;
			if(corrida[i].pontos >= CHEGADA){
				cont++;
				strcpy(vencedor, corrida[i].nome);
			}
		}
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n-i-1; j++)
				if(corrida[j].pontos < corrida[j+1].pontos){
					Player aux = corrida[j];
					corrida[j] = corrida[j+1];
					corrida[j+1] = aux;
				}		
	}while(1);
	
	(cont > 1) ? printf("\nEMPATE!\n") : printf("\nPARABÉNS, %s! VOCÊ VENCEU!!\n", vencedor);
	
	return 0;
}
