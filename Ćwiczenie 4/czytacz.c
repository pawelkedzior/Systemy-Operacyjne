#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int deskryptor;
FILE *odczyt;
char znak[5];

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		perror("Niewłaściwa liczba argumentów");
		exit(1);
	}
	deskryptor=atoi(argv[1]);
	printf("czytacz: %d\n", deskryptor);
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