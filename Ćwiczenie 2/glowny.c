#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
Ćwiczenie numer 2. Systemy Operacyjne. (program główny)
Autor: Paweł Kędzior
*/

int a; /*Zmienna iteracyjna do pętli for*/

int main(void)
{
	/*Wypisanie identyfikatorów użytkownika oraz grupy użytkownika*/
   printf("Identyfikator użytkownika(UID): %d\n",getuid());
   printf("Identyfikator grupy użytkownika(GID): %d\n",getgid());

   /*Wypisanie informacji o procesie pierwotnym*/
   printf("\nProces pierwotny\n\n");
   printf("Identyfikator bieżącego procesu(PID): %d\n",getpid());
   printf("Identyfikator procesu macierzystego(PPID): %d\n",getppid());
   printf("Identyfikator grupy procesów(PGID - getpgid(PID)): %d\n",getpgid(getpid()));
   printf("Identyfikator grupy procesów(PGID - getpgid(0)): %d\n",getpgid(0));
   printf("Identyfikator grupy procesów(PGID - getpgrp()): %d\n",getpgrp());
   printf("\n\n");
	
	for (a=0;a<3;a++)/*Pętla, w której wywoływane są funkcje fork oraz execl, ta druga wywołująca wypisanie informacji o procesie potomnym*/
	   {
	     switch (fork())
	       {
	         case -1: /*Instrukcja, w przypadku braku powodzenia funkcji fork*/
		   		{
		     			perror("fork error");
		     			exit(1);
		   		}
	         case 0: /*Instrukcja dla procesu potomnego: użycie funcji exec*/
		   		{
		     			printf("Proces potomny o a=%d\n\n",a);
		     			execl("./wykonywany.out","wykonywany.out",NULL);/*Wywołanie funkcji execl*/
		     			perror("Błąd funkcji execl!\n");/*Instrukcja w przypadku błędu*/
		     			_exit(2);
		   		}
	         default: /*Instrukcja dla procesu macierzystego*/
	         	{
	         		wait(0);
	         	}
	       };
	   }
   return 0;
}
