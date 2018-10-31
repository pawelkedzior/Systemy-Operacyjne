#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int deskryptory[2];
char deskr[2][2];

int main(void)
{
	if(pipe(deskryptory)<0)
	{
		perror("Błąd tworzenia potoku");
		exit(1);
	}
	sprintf(deskr[0],"%d",deskryptory[0]);
	sprintf(deskr[1],"%d",deskryptory[1]);
	switch(fork())
	{
		case -1:
			perror("Błąd funkcji fork");
			exit(1);
		break;
		case 0:
			close(deskryptory[1]);
			execl("./pisarz.out","pisarz.out",deskr[0],NULL);
			perror("Błąd funkcji exec");
			_exit(2);
		break;
		default:
			close(deskryptory[0]);
			execl("./czytacz.out","czytacz.out",deskr[1],NULL);
			perror("Błąd funkcji exec");
			_exit(2);
		break;
	}	
	return 0;
}