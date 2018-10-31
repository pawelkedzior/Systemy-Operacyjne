#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
Ćwiczenie numer 1. Systemy Operacyjne.
Autor: Paweł Kędzior
*/

int a; /*Zmienna iteracyjna do pętli for*/
int wybor; /*Zmienna wykorzystywana w pętli switch wykorzystanej do wyboru trybu wywoływania funkcji fork*/

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

   /*Wypisanie identyfikatorów użytkownika oraz grupy użytkownika*/
   printf("Identyfikator użytkownika(UID): %d\n",getuid());
   printf("Identyfikator grupy użytkownika(GID): %d\n",getgid());

   /*Użycie funkcji wypisz dla procesu pierwotnego*/
   printf("\nProces pierwotny\n\n");
   wypisz();

   /*Pętla switch służąca do wyboru trybu wywoływania funkcji fork*/
   printf("Wybierz tryb w jakim chcesz działać:\n");
   printf("1. Tworzenie procesu potomnego i zamykanie go po tym.\n");
   printf("2. Tworzenie drzewa procesów.\n\n");
   scanf("%d",&wybor);
   switch(wybor)
     {
       case 1:
	 {
	 /*Pętla, w której trzykrotnie uruchamiany jest proces fork (Powstają trzy procesy!)*/
	 for (a=0;a<3;a++)
	   {
	     switch (fork())
	       {
	         case -1: /*Instrukcja, w przypadku braku powodzenia funkcji fork*/
		   {
		     perror("fork error");
		     exit(1);
		   }

	         case 0: /*Instrukcja dla procesu potomnego: użycie funcji wypisz i zakończenie procesu */
		   {
		     printf("Proces potomny o a=%d\n\n",a);
		     wypisz();
		     exit(0);

		   }
	         default: /*Instrukcja dla procesu macierzystego: Oczekiwanie na zakończenie procesu potomnego*/
		   {
		     wait(0);
		   }
	       };

	   }
	 }
	 break;
       case 2:
         {
	 /*Przypadek użycia powyższych instrukcji z pominięciem kończenia procesu potomnego zaraz po jego utworzeniu*/
	 for (a=0;a<3;a++)
	   {
	     switch (fork())
	       {
	         case -1: /*Instrukcja, w przypadku braku powodzenia funkcji fork*/
		   {
		     perror("fork error");
		     exit(1);
		   }

	         case 0: /*Instrukcja dla procesu potomnego: użycie funcji wypisz*/
		   {
		     printf("Proces potomny o a=%d\n\n",a);
		     wypisz();
		     sleep(5+5*a);/*oczekiwanie na wypisanie starszych procesów*/
		   }

	         default: /*Instrukcja dla procesu macierzystego: Oczekiwanie na zakończenie procesu potomnego*/
		   {
		     sleep(1);/*Oczekiwanie na wypisanie wszystkich procesów*/
		   }
	       };
	   }
	 }
	 break;
     };
   sleep(30);
   return 0;
}
