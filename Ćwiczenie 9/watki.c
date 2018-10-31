#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int licznik;
pthread_mutex_t muteks=PTHREAD_MUTEX_INITIALIZER;
int liczbawatkow;
pthread_t *watki;
int i;
int znak;

void *watek(void *numer)
{
	int licznikwatku;
	int nr=*(int*) numer;
	sleep(5);
	while(1)
	{
		printf("\033[%d;%dH                       \033[%d;%dHPrzed sekcją krytyczną.\n", nr, 11, nr, 11);
		pthread_mutex_lock(&muteks);
		printf("\033[%d;%dH                       \033[%d;%dHW sekcji krytycznej.\n", nr, 11, nr, 75);
		licznikwatku=licznik;
		licznikwatku++;
		sleep(3);
		licznik=licznikwatku;
		pthread_mutex_unlock(&muteks);
		printf("\033[%d;%dH                    \033[%d;%dHPo sekcji krytycznej.\n", nr, 75, nr, 11);
		sleep(2);
	}
}

int main(void)
{
	/*if(pthread_mutex_init(&muteks, NULL)!=0);
	{
		perror("Błąd inicjacji muteksu");
		exit(1);
	}*/
	
	printf("Ile chcesz stworzyć wątków? Liczba ta nie może przekraczać 23 i musi być większa od 0.\n");
	scanf("%d",&liczbawatkow);
	if(liczbawatkow>23&&liczbawatkow<1)
	{
		do
		{
			printf("Podałeś niewłaściwą liczbę. Podaj inną.");
			scanf("%d",&liczbawatkow);
		}
		while(liczbawatkow>23&&liczbawatkow<1);
	}
	system("clear");
	printf("\033[%d;%dH", 24, 1);
	printf("\033[5;7m");
	printf("Nacisnij klawisz [Enter], aby zakończyć!");
	printf("\033[0m");
	printf("\033[%d;%dH", 1, 1);
	
	watki=(pthread_t*) malloc((liczbawatkow+1)*sizeof(pthread_t));
	for(i=0;i<liczbawatkow;i++) 
	{
      printf("\033[1m");
      printf("Wątek ");
      if(i<9)
      	printf("0");
      printf("%d:",i+1);
      printf("\033[0m");
		printf(" Przed sekcją krytyczną.\n");
   }
   printf("\033[0m");
	for(i=0;i<liczbawatkow;i++) 
	{
		if(pthread_create(&watki[i],NULL,watek,&i)!=0) 
		{
      	perror("Błąd tworzenia wątku");
      	exit(1);
      }
   }
   getchar();
   while(znak!=10)
   {
   	znak=getchar();
   }
   system("clear");
	printf("Wartość licznika: %d\n",licznik);
	pthread_mutex_destroy(&muteks);
	free(watki);
	return 0;
}