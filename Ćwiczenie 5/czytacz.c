#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int deskryptor;
FILE *odczyt;
FILE *fifozapis;
char znak[5];

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		perror("Niewłaściwa liczba argumentów");
		exit(1);
	}
	if(strcmp(argv[1],"0")==0)
	{
		deskryptor=open("./fifokonsola",O_WRONLY,NULL);
		if(deskryptor<0)
		{		
			perror("Fifo nie istnieje");
			exit(1);
		}
	}
	else if(strcmp(argv[1],"1")==0)
	{
		fifozapis=fopen("fifoprogram", "rb");
		if(fifozapis==NULL)
		{
			if(mkfifo("fifoprogram", 0644)!=0)
			{
				perror("Błąd tworzenia FIFO");
				exit(1);
			}
		}
		else 
		{
			fclose(fifozapis);
		}
		deskryptor=open("./fifoprogram",O_WRONLY,NULL);
	}
	else 
	{
		perror("Niewłaściwy argument");
		exit(1);
	}
	odczyt=fopen("zrodlo.txt", "rb");
	if (odczyt==NULL)
	{
		perror("Problem z otwarciem pliku");
		exit(1);
	}
	while(feof(odczyt)==0)
	{
		fgets((char *)znak,6,odczyt);
		printf("Producent: Produkuję znak: \"%s\" i przekazuję go do potoku.\n", znak);
		sleep(((float)(rand()%300))/100);
		if((write(deskryptor, znak, 5))==-1)
		{
			perror("Problem z zapisem do potoku");
		};
		printf("Producent: Produkcja zakończona.\n");
	}	
	close(deskryptor);
	fclose(odczyt);
	return 0;
}