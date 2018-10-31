#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
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
t_komunikat *komunikat;
int i;
char znak[2];
char c;

int main(void)
{	
	klucz=ftok("./",'A');
	kolejka=stw_kol(klucz);
	if(kolejka==-1)
	{
		perror("Błąd tworzenia kolejki");
		exit(1);
	}
	while(1)
	{
		komun=malloc(sizeof( t_komunikat )*2+101);
		komunikat=(t_komunikat *) komun;
		if(kol_odbierz(kolejka,komun,1)>=0)
		{
			i=0;
			printf("Serwer: Otrzymałem wiadomość: \"");
			while(komunikat->wiad[i])
			{
				printf("%c",komunikat->wiad[i]);
				i++;
			}
			printf("\" od %d\n",komunikat->idproc);
			i=0;
			while(komunikat->wiad[i]!=0)
			{
				if(komunikat->wiad[i]<0)
				{
					znak[0]=komunikat->wiad[i];
					znak[1]=komunikat->wiad[i+1];
					char a1[]="Ą";
					char a4[]="Ć";
					char a2[]="Ę";
					char a3[]="Ł";
					char a5[]="Ń";
					char a6[]="Ó";
					char a7[]="Ś";
					char a8[]="Ź";
					char a9[]="Ż";
					switch(znak[0])
					{
						case -61:
							znak[0]=a6[0];
							znak[1]=a6[1];
						break;
						case -60:
							switch(znak[1])
							{
								case -103:
									znak[0]=a2[0];
									znak[1]=a2[1];
								break;
								case -121:
									znak[0]=a4[0];
									znak[1]=a4[1];
								break;
								case -123:
									znak[0]=a1[0];
									znak[1]=a1[1];
								break;
							}
						break;
						case -59:
							switch(znak[1])
							{
								case -126:
									znak[0]=a3[0];
									znak[1]=a3[1];
								break;
								case -124:
									znak[0]=a5[0];
									znak[1]=a5[1];
								break;
								case -101:
									znak[0]=a7[0];
									znak[1]=a7[1];
								break;
								case -70:
									znak[0]=a8[0];
									znak[1]=a8[1];
								break;
								case -68:
									znak[0]=a9[0];
									znak[1]=a9[1];
								break;
							}
						break;						
					}
					komunikat->wiad[i]=znak[0];
					komunikat->wiad[i+1]=znak[1];
					i++;
				}
				else 
				{
					if(komunikat->wiad[i]<=122&&komunikat->wiad[i]>=97)
						//komunikat->wiad[i]=komunikat->wiad[i]-32;
						komunikat->wiad[i]=toupper(komunikat->wiad[i]);
				}
				i++;
			}
			t_komunikat kom2;
			kom2.typ=komunikat->idproc;
			kom2.idproc=0;
			strcpy(kom2.wiad,komunikat->wiad);
			komunikat=&kom2;
			kol_wyslij(kolejka, &kom2);
			printf("Serwer: Wysłałem przetworzoną wiadomość: \"%s\".\n",kom2.wiad);
		}
		else {puts("Błąd");}
		printf("\nJeśli chcesz kontynuować wciśnij ENTER, jeśli nie wciśnij ESC\n");
		free(komun);
		c=getchar();
		if(c==27)
			break;
	}	
	usun_kol(kolejka);
	printf("Koniec.\n");
	return 0;
}
