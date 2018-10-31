#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
Ćwiczenie numer 2. Systemy Operacyjne. (program wykonywany przez program główny)
Autor: Paweł Kędzior
*/

void wypisz(void) /*Funkcja wypisująca identyfikatory bieżącego procesu, procesu macierzystego oraz grupy procesów na trzy sposoby*/
{
   printf("Identyfikator bieżącego procesu(PID): %d\n",getpid());
   printf("Identyfikator procesu macierzystego(PPID): %d\n",getppid());
   printf("Identyfikator grupy procesów(PGID - getpgid(PID)): %d\n",getpgid(getpid()));
   printf("Identyfikator grupy procesów(PGID - getpgid(0)): %d\n",getpgid(0));
   printf("Identyfikator grupy procesów(PGID - getpgrp()): %d\n",getpgrp());
   printf("\n");
}

int main(void)
{
	wypisz();
   return 0;
}
