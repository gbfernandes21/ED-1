#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"
#include <time.h>

#define SEMANA 7

int main(){
	srand(time(NULL));
	int n;
	printf("Quantas pessoas tem na festa? ");
	scanf(" %d", &n);
	system("clear");
	
	Datetime a[n];
	int sem[SEMANA] = {0}, maior = 0;
	
	for (int i = 0; i < n; i++){
		a[i] = dt_rand_birth(25);
		sem[a[i].wday]++;
	}
	
	printf("Datas em que mais de uma pessoa faz aniversário\n\n");	
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if(a[i].day == a[j].day && a[i].mon == a[j].mon){
				printf("%02d/%02d\n", a[i].day, a[i].mon);
				break;
			}
				
	for (int i = 0; i < SEMANA; i++)
		if(sem[maior] < sem[i])
			maior = i;
			
	switch(maior){
		case 0 : printf("\nDia da semana em que mais pessoas nasceram: Domingo\n"); break;
		case 1 : printf("\nDia da semana em que mais pessoas nasceram: Segunda-feira\n"); break;
		case 2 : printf("\nDia da semana em que mais pessoas nasceram: Terça-feira\n"); break;
		case 3 : printf("\nDia da semana em que mais pessoas nasceram: Quarta-feira\n"); break;
		case 4 : printf("\nDia da semana em que mais pessoas nasceram: Quinta-feira\n"); break;
		case 5 : printf("\nDia da semana em que mais pessoas nasceram: Sexta-feira\n"); break;
		case 6 : printf("\nDia da semana em que mais pessoas nasceram: Sábado\n"); break;
	}

	return 0;
}
