#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

/*
Ćwiczenie numer 3. Systemy Operacyjne. (program główny)
Autor: Paweł Kędzior
*/

int a; /*Zmienna iteracyjna do pętli for*/
int liczba; /*Zmienna przechowująca liczbę procesów potomnych*/
int numer; /*Zmienna przechowująca numer sygnału do przeciążenia*/
char sygnal[2];
pid_t potomny;

int main(void)
{
	printf("To numer grupy: %d\n\n",getpgid(0));
	printf("Podaj numer sygnału, który chcesz przeciążyć.\n");
	scanf("%d",&numer);
	if(numer>10)
		sygnal[0]=numer/10+48;
	else 	
   	sygnal[0]=0+48;
   sygnal[1]=numer%10+48;
   printf("Ile chcesz procesów potomnych?\n");
   scanf("%d",&liczba);
	for (a=0;a<liczba;a++)
	   {
	     switch (fork())
	       {
	         case -1:
		   		{
		     			perror("Błąd funkcji fork!");
		     			exit(1);
		   		}
	         case 0:
		   		{
		   			if(liczba==1)
		   			{
		   				a=3;
		   				potomny=getpid();
		   			}
				      switch (a%6)
				      {
				      	case 0:
				      		execl("./obsluga.out","obsluga.out","zwyczajne",NULL);/*Wywołanie funkcji execl*/
					  			perror("Nie mogę dostać się do pomocy!");/*Instrukcja w przypadku błędu*/
					  			_exit(2);
				      	break;
				      	case 1:
				      		execl("./obsluga.out","obsluga.out","olane",sygnal,NULL);/*Wywołanie funkcji execl*/
					  			perror("Nie mogę dostać się do pomocy!");/*Instrukcja w przypadku błędu*/
					  			_exit(2);
				      	break;
				      	case 2:
				      		execl("./obsluga.out","obsluga.out","moje",sygnal,"UJ",NULL);/*Wywołanie funkcji execl*/
					  			perror("Nie mogę dostać się do pomocy!");/*Instrukcja w przypadku błędu*/
					  			_exit(2);
				      	break;
				      	case 3:
				      		execl("./obsluga.out","obsluga.out","moje",sygnal,"Licz",NULL);/*Wywołanie funkcji execl*/
					  			perror("Nie mogę dostać się do pomocy!");/*Instrukcja w przypadku błędu*/
					  			_exit(2);
				      	break;
				      	case 4:
				      		execl("./obsluga.out","obsluga.out","moje",sygnal,"Zniewaz",NULL);/*Wywołanie funkcji execl*/
					  			perror("Nie mogę dostać się do pomocy!");/*Instrukcja w przypadku błędu*/
					  			_exit(2);
				      	break;
				      	case 5:
				      		execl("./obsluga.out","obsluga.out","moje",sygnal,"Podlizsie",NULL);/*Wywołanie funkcji execl*/
					  			perror("Nie mogę dostać się do pomocy!");/*Instrukcja w przypadku błędu*/
					  			_exit(2);
				      	break;				      	
				      }
		   		}
	         default:
		        	{
		        		sleep(1);
		        		if (signal(numer,SIG_IGN) == SIG_ERR)
			        		{
								perror("Funkcja signal ma problem z wybranym sygnałem.");
								exit(EXIT_FAILURE);
							}
						if(a==liczba-1)
						{
							if(liczba==1)
							{
								kill(potomny,numer);
		        				sleep(5);
		        				kill(potomny,SIGKILL);
							}
							else 
							{
		        				killpg(getpgid(0),numer);
		        				sleep(5);
		        				killpg(getpgid(0),SIGKILL);
		        			}
		        		}
	         	}
	       }
	   }
	sleep(60);
   return 0;
}
