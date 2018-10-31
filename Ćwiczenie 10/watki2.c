#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int licznik;

int liczbawatkow;
pthread_t watki[24];
int i;
int znak;
static int wybieranie[24];
static int numer[24];
int *l;

int maksimum()
{
	int maks=numer[0];
	for(i=1;i<liczbawatkow;i++)
	{
		if(numer[i]>maks)
			maks=numer[i];
	}
	return maks;
}

void piekarnia(int num)
{
	int j;
	wybieranie[num]=1;
 	numer[num]=maksimum()+1;
 	wybieranie[num]=0;
 	for (j=0;j<liczbawatkow;j++)
 	{
 		while (wybieranie[j]==1)
 		{/*printf("Wątek %d: Wybieranie %d\n",num,j);*/}
 		while ((numer[j]!=0)&&((numer[j]<numer[num])||((numer[j]==numer[num])&&(j<num))))
 		{printf(" \b");/*printf("Wątek %d: Czekanie na j %d o numerze %d\n",num,j,numer[j]);*/
 		/*sleep(1);*/}
 	}
}

void *watek(void *numerek)
{
	int licznikwatku;
	int *nr= numerek;
	int num=*nr;
	sleep(liczbawatkow-num);
	while(1)
	{
		printf("\033[%d;%dH                       \033[%d;%dHPrzed sekcją krytyczną.", num, 12, num, 12);
		piekarnia(num);	
		printf("\033[%d;%dH                       \033[%d;%dHW sekcji krytycznej.", num, 12, num, 75);
		licznikwatku=licznik;
		licznikwatku++;
		sleep(2+rand()%3);
		licznik=licznikwatku;
		printf("\033[%d;%dH                    \033[%d;%dHPo sekcji krytycznej.", num, 75, num, 12);
		numer[num]=0;
		sleep(2+rand()%3);
		licznikwatku=0;
	}
}

int main(void)
{
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
	
	for(i=0;i<liczbawatkow;i++) 
	{
      printf("\033[1m");
      printf(" Wątek ");
      if(i<9)
      	printf("0");
      printf("%d:",i+1);
      printf("\033[0m");
		printf(" Przed sekcją krytyczną.\n");
		wybieranie[i]=0;
		numer[i]=0;
   }
   printf("\033[0m");
	for(i=0;i<liczbawatkow;i++) 
	{
		if(pthread_create(&watki[i],NULL,watek,&i)!=0) 
		{
      	perror("Błąd tworzenia wątku");
      	exit(1);
      }
      sleep(1);
   }
   
   getchar();
   znak=0;
   while(znak!=10)
   {
   	znak=getchar();
   }
   system("clear");
   printf("Wartość licznika: %d\n",licznik);
	printf("\033[%d;%dH", 2, 1);
	return 0;
}