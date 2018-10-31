#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "sem.h"

key_t klucz;
int semafor;
int liczba;
int i;
char przekaz[12];
char przekaznr[2];

int main()
{
  printf("Tworzę semafor.\n");
  klucz=ftok(".",'A');
  semafor=stw_sem(klucz, 1);
  sprintf(przekaz,"%d",semafor);
  printf("\nUkończyłem tworzenie.\nIle chcesz procesów, żeby zademonstrować działanie programu?\n(Liczba musi być większa niż 1)\n");
  scanf("%d", &liczba);
  while(liczba<2)
  {
    printf("Niewłaściwa liczba. Podaj kolejną.\n");
    scanf("%d", &liczba);     
  }
  for(i=0;i<liczba;i++)
  {
    switch(fork())
    {
      case -1:
	perror("Błąd funkcji fork");
	exit(1);
      break;
      case 0:
   sprintf(przekaznr,"%d",i);
	execl("./dostep.out","dostep.out",przekaz,przekaznr,NULL);
	perror("Błąd funkcji exec");
	_exit(2);
      break;
      default:
      break;
    }
    /*sleep(1);*/
  }
  for(i=0;i<liczba;i++)
    wait(0);
  usun_sem(semafor);
  return 0;
}
