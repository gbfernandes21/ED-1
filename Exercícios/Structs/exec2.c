#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"
#include <time.h>

#define MAX 10

int main(){
	srand(time(NULL));
	Datetime hr[MAX], atual = dt_now();
	
	printf("=========== HORÁRIOS ============\n\n");
	for (int i = 0; i < MAX; i++){
		hr[i] = dt_rand_time();
		printf("[%02d:%02d]\n", hr[i].hour, hr[i].min);
	}
	
	printf("\n** Horário atual do sistema: [%02d:%02d]\n", atual.hour, atual.min);
	
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX-i-1; j++)
			if(hr[j].hour > hr[j+1].hour || 
			(hr[j].hour == hr[j+1].hour && hr[j].min > hr[j+1].min)){
				Datetime aux = hr[j];
				hr[j] = hr[j+1];
				hr[j+1] = aux;
			}
	
	Datetime passado, futuro;
	int encp = 0, encf = 0;
	
	for (int i = 0; i < MAX; i++){
		if(hr[i].hour < atual.hour || 
		(hr[i].hour == atual.hour && hr[i].min < atual.min)){
			passado = hr[i];
			encp = 1;
		}else if(!encf){
				futuro = hr[i];
				encf = 1;
			}
	}
	
	(encp) ? printf("\n** Horário mais próximo (relação ao passado): [%02d:%02d]\n", passado.hour, passado.min) : printf("\n** Não há horário anterior ao atual.\n");
	(encf) ? printf("\n** Horário mais próximo (relação ao futuro): [%02d:%02d]\n", futuro.hour, futuro.min) : printf("\n** Não há horário posterior ao atual.\n");
	
	return 0;
}
