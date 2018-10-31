#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int deskryptor;
FILE *zapis;
char znak[5];
ssize_t spr;

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		perror("Niewłaściwa liczba argumentów");
		exit(1);
	}
	deskryptor=atoi(argv[1]);
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
	fclose(zapis);
	return 0;
}