#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "kol.h"

typedef struct msgbuf
{
	long typ;
	char wiad[90];
	long idproc;
}t_komunikat;

int kolejka;
key_t klucz;
void *komun;
void *komun2;
struct msgbuf *komunikat=NULL;
struct msgbuf *komunikat2=NULL;
int i,j;
int c;
long idproc;

int main(void)
{
	sleep(2);
	klucz=ftok("./",'A');
	kolejka=stw_kol(klucz);
	if(kolejka==-1)
	{
		perror("Błąd tworzenia kolejki");
		exit(1);
	}
	idproc=(long) getpid();
	
	while(c!=27)
	{
		struct msgbuf kom={0,"                             ",0};
		//kom.wiad=(char*)malloc(101-2*sizeof(/*pid_t*/long));
		komunikat=&kom;
		//printf("Podaj wiadomość, jaką chcesz wysłać. Uważaj na długość!\n");
		//scanf("%s",komunikat->wiad);
		for (j=1;j<90;j++)
			kom./*komunikat->*/wiad[j]='0';
		strcpy(komunikat->wiad,"Jakaś wiadomość.");
		komunikat->idproc=idproc;
		komunikat->typ=1;
		printf("Klient: Wysyłam wiadomość: \"%s\" typu %ld mój pid %ld\n",komunikat->wiad, komunikat->typ, komunikat->idproc);
		komun=(void *) komunikat;
		kol_wyslij(kolejka, komun);
		komun2=malloc(sizeof(long)*2+101);
		komunikat2=(t_komunikat *)komun2;
		kol_odbierz(kolejka, komun2, idproc);
		printf("Klient: Odebrałem wiadomość: \"%s\" typu %ld od %ld\n",komunikat2->wiad, komunikat2->typ, komunikat2->idproc);
		printf("\nJeśli chcesz kontynuować wciśnij ENTER, jeśli nie wciśnij ESC\n");
		c=getchar();
	}	
	free(komun2);
	printf("Koniec.\n");
	return 0;
}
