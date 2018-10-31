#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sem.h"

int semafor;
int numer;

int main(int argc, char* argv[])
{
  if(argc<2)
  {
    perror("Niewłaściwa liczba argumentów");
    exit(1);
  }
  semafor=atoi(argv[1]);
  numer=atoi(argv[2]);
  printf("Program do obsługi problemu wzajemnego wykluczania. Proces numer: %d\n", numer);

  printf("Znajduję się przed sekcją krytyczną. (Proces %d)\n", numer);
  sleep(1);
  opusc_sem(semafor);
  printf("Jestem w sekcji krytycznej. (Proces %d)\n", numer);
  sleep(numer%4);
  podnies_sem(semafor);
  printf("Wyszedłem z sekcji krytycznej. (Proces %d)\n", numer);
  
  return 0;
}
