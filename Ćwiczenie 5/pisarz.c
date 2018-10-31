#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int deskryptor;
FILE *zapis;
FILE *fifoodczyt;
char znak[5];
ssize_t spr;

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		perror("Niewłaściwa liczba argumentów");
		exit(1);
	}
	if(strcmp(argv[1],"0")==0)
	{
		deskryptor=open("./fifokonsola",O_RDONLY,NULL);
		if(deskryptor<0)
		{
			perror("Fifo nie istnieje");
			exit(1);
		}
	}
	else if(strcmp(argv[1],"1")==0)
	{
		fifoodczyt=fopen("fifoprogram", "rb");
		if(fifoodczyt==NULL)
		{
			if(mkfifo("fifoprogram", 0644)!=0)
			{
				perror("Błąd tworzenia FIFO");
				exit(1);
			}
		}
		else 
		{
			fclose(fifoodczyt);
		}
		deskryptor=open("./fifoprogram",O_RDONLY,NULL);
	}
	else 
	{
		perror("Niewłaściwy argument");
		exit(1);
	}
	zapis=fopen("cel.txt", "wb");
	if (zapis==NULL)
	{
		perror("Problem z otwarciem pliku");
		exit(1);
	}
	
	while(1)
	{
		spr=read(deskryptor, znak, 5);
		if(spr<1)
		{
			if(spr==0)
			{
				printf("Zakończyłem odczyt.\n");
				break;
			}
			else
				perror("Problem z odczytem z potoku");
		};
		printf("Konsument: Zakupiłem znak: \"%s\".\n", znak);
		fputs(znak, zapis);
	}	
	close(deskryptor);
	if(strcmp(argv[1],"1")==0)
		unlink("./fifoprogram");
	fclose(zapis);
	return 0;
}