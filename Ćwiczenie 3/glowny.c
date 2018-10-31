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

int a,i; /*Zmienne iteracyjne do pętli for*/
int liczba;
char opcja[15];
char reszta[60];
char *lista[5];

int main(void)
{
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
		   			for(i=0;i<5;i++)
		   			{
		   				lista[i]=NULL;
		   			}
				  		printf("Wybierz opcję obsługi programu. Jeśli wpiszesz \"pomoc\" wyświetlą się możliwe sposoby działania.\n");
				  		scanf("%s",opcja);
				   	if(0==strcmp(opcja,"moje"))
				   	{
				    		printf("Jak chcesz zadziałać po swojemu? Tu też możesz wpisać \"pomoc\".\n");
				    		scanf("%s",reszta);
				    	}
				      if(0==strcmp(opcja,"pomoc")||0==strcmp(reszta,"pomoc"))
						{
							switch (fork())
							{
								case -1:
		   					{
		     						perror("Nie mogę dostać się do pomocy!");
		     						exit(1);
		   					}
		   					case 0:
		   					{
					  				execl("./obsluga.out","obsluga.out","pomoc",NULL);/*Wywołanie funkcji execl*/
					  				perror("Nie mogę dostać się do pomocy!");/*Instrukcja w przypadku błędu*/
					  				_exit(2);
					  			}
					  			default:
					  			{
					  				wait(0);
					  				if(0==strcmp(opcja,"pomoc"))
				      				scanf("%s",&*opcja);
				      			else
				      				scanf("%s",&*reszta);
				      		}
					  		}
						}
		   		}
	         default:
		        	{
	         		wait(0);
	         	}
	       }
	   }
   return 0;
}
