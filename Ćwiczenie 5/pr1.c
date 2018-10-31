#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int wybor;

int main(void)
{
	wybor=1;
	while(wybor!=0) {
		printf("Wybierz sposób działania.\n");
		printf("1. Producent-konsument z wykorzystaniem FIFO utworzonego w konsoli (nazwa: fifokonsola).\n");
		printf("2. Producent-konsument z wykorzystaniem FIFO utworzonego w czasie działania programu (nazwa: fifoprogram).\n");
		printf("0. Wyjście.\n");
		scanf("%d",&wybor);
		switch(wybor)
		{
			case 1:
				switch(fork())
				{
					case -1:
						perror("Błąd funkcji fork");
						exit(1);
					break;
					case 0:
						execl("./pisarz.out","pisarz.out","0",NULL);
						perror("Błąd funkcji exec");
						_exit(2);
					break;
					default:
						execl("./czytacz.out","czytacz.out","0",NULL);
						perror("Błąd funkcji exec");
						_exit(2);
					break;
				}
			break;
			case 2:
				switch(fork())
				{
					case -1:
						perror("Błąd funkcji fork");
						exit(1);
					break;
					case 0:
						execl("./pisarz.out","pisarz.out","1",NULL);
						perror("Błąd funkcji exec");
						_exit(2);
					break;
					default:
						execl("./czytacz.out","czytacz.out","1",NULL);
						perror("Błąd funkcji exec");
						_exit(2);
					break;
				}
			break;
			case 0:
				printf("Do widzenia.\n");
			break;
			default:
				printf("Niewłaściwy wybór.\n");
			break;
		}	
	}
	return 0;
}