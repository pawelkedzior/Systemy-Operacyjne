#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

/*
Ćwiczenie numer 3. Systemy Operacyjne. (program do obsługi sygnałów)
Autor: Paweł Kędzior
*/

int a; /*Zmienna iteracyjna do pętli for*/
int wybor; /*Zmienna do pętli switch odpowiadająca za wybór trybu działania programu*/
int numer; /*Zmienna opisująca numer sygnału*/

/*Funkcje definiujące reakcje na sygnał*/
void pochlebstwo (int kod)
{
	printf("\n\nAle sprawnie posługujesz się konsolą!\n\n");
}

void zniewaga (int kod)
{
	printf("\n\nTwoja wiedza z dziedziny mechaniki kwantowej jest tak mała, jak prawdopodobieństwo pobicia przez Ciebie rekordowego czasu ułożenia kostki rubika!\n\n");
}

void uczelnia (int kod)
{
	printf("\n\nKOCHAM UJ!\n\n");
}

void liczymy (int kod)
{
	printf("\n");
	for (a=10;a>-1;a--)
		{
			printf("%d\n",a);
			sleep(1);
		}
	printf("\n");
}

/*Funkcja główna*/
int main(int argc, char *argv[])
{
		  printf("\n\nProgram obsługujący sygnały.\n\n");
		  /*Sprawdzenie wybranego sposobu reakcji na sygnał*/
	     if (argc>1)
		 		if (0==strcmp(argv[1],"zwyczajne"))
		     		wybor=1;
		 		else
		     		if(0==strcmp(argv[1],"olane"))
			 			wybor=2;
		     		else
			 			if(0==strcmp(argv[1],"moje"))
			     			wybor=3;
			 			else
			     			if(0==strcmp(argv[1],"pomoc"))
				 				wybor=4;
			     			else
				 				wybor=6654;
	     else
	       wybor=6655;
	     switch (wybor)
	       {
	         case 1:/*Domyślna reakcja na sygnał*/
		   		{
		   			printf("Domyślna obsługa sygnału\n\n");
				      printf("Wykonaj kombinację klawiszy lub wykorzystaj polecenie kill w innym terminalu\n\n");
		   		}
		 		break;
	         case 2:/*Ignorowanie otrzymanego sygnału*/
		   		{
		   			printf("Ignorowanie sygnału\n\n");
		        		printf("Możesz wprowadzić kombinację klawiszy, ale ja i tak nic nie zrobię :D\n");
		        		printf("Jeśli dodatkowo podałeś numer sygnału do przeciążenia to możesz mi go wysyłać przez polecenie kill, ale tego też nie posłucham.");
		        		if (signal(SIGQUIT,SIG_IGN) == SIG_ERR)
			        		{
								perror("Funkcja signal ma problem z SIGQUIT");
								exit(EXIT_FAILURE);
							}
		        		if (signal(SIGINT,SIG_IGN) == SIG_ERR)
			        		{
								perror("Funkcja signal ma problem z SIGINT");
								exit(EXIT_FAILURE);
							}
				  		if (signal(SIGTSTP,SIG_IGN) == SIG_ERR)
			        		{
								perror("Funkcja signal ma problem z SIGTSTP");
								exit(EXIT_FAILURE);
							}
				        		
				  		if(!(argc<3))/*Sprawdzenie poprawności wypisania argumentów wywołania: numer sygnału*/
		   				{
				        		sscanf(argv[2],"%d",&numer);
		   					if (signal(numer,SIG_IGN) == SIG_ERR)
				        		{
									perror("Funkcja signal ma problem z tym sygnałem");
									exit(EXIT_FAILURE);
								}
				        		printf("A nie mówiłem?\n"); 
				    		}
		   		}
		 		break;
		 		case 3:/*Własne oddziaływanie na sygnał*/
		   		{
		   			  printf("Własna obsługa sygnału\n");
		   			  if(argc<3)/*Sprawdzenie poprawności wypisania argumentów wywołania: numer sygnału*/
		   					{
									printf("Nie podałeś numeru sygnału.\n\n");
									wybor=6656;
		   					}
		   			  else 
		   					{
		   						if (argc<4)/*Sprawdzenie poprawności wypisania argumentów wywołania: akcja*/
				        				{
									  		printf("Nie zdefiniowałeś akcji\n\n");
									  		wybor=6656;
										}
									else/*Obsługa sygnału*/
										{
											sscanf(argv[2],"%d",&numer);
											if (strcmp(argv[3],"Zniewaz")==0)
												{
													if (signal(numer,zniewaga) == SIG_ERR)
				        								{
															perror("Funkcja signal ma problem z sygnałem");
															exit(EXIT_FAILURE);
														}
												}
											else
													if (strcmp(argv[3],"Podlizsie")==0)
														{
															if (signal(numer,pochlebstwo) == SIG_ERR)
				        										{
																	perror("Funkcja signal ma problem z sygnałem");
																	exit(EXIT_FAILURE);
																}
														}
													else
														if (strcmp(argv[3],"UJ")==0)
															{
															if (signal(numer,uczelnia) == SIG_ERR)
				        										{
																	perror("Funkcja signal ma problem z sygnałem");
																	exit(EXIT_FAILURE);
																}
															}
														else 
															if (strcmp(argv[3],"Licz")==0)
															{
																if (signal(numer,liczymy) == SIG_ERR)
				        											{
																		perror("Funkcja signal ma problem z sygnałem");
																		exit(EXIT_FAILURE);
																	}
															}
															else 
																printf("Nie ma takiej opcji, program zareaguje domyślnie na wskazany sygnał.");
											printf("\n");
										}
		   					}
		   		}
		 		break;
		 		case 4:/*Informacje o sposobie obsługi programu*/
				  {
				        printf("Aby wywołać odpowiedni sposób oddziaływania na sygnał wpisz:\n");
						  printf("\"zwyczajne\" - domyślna reakcja na sygnał\n");
						  printf("\"olane\" - ignorowanie sygnału\n");
						  printf("\"moje\" - wybrany sposób oddziaływania na sygnał - dostępne są następujące sposoby reakcji:\n");
						  printf("\t\"UJ\" - Wypisuje na ekran tekst: \"KOCHAM UJ!\"\n");
						  printf("\t\"Licz\" - Wykonuje odliczanie od 10 do 0 co sekundę.\n");
						  printf("\t\"Zniewaz\" - Obraża obsługującego program.\n");
						  printf("\t\"Podlizsie\" - Wypisuje tekst ociekający słodyczą.\n");
						  printf("Sposoby oddziaływania należy podać jako drugi argument wywołania programu.\n");
						  printf("Numer sygnału należy podać jako trzeci argument wywołania programu (należy uważać, żeby wpisać liczbę,\n");
						  printf("w innym wypadku można doprowadzić do niepożądanych skutków).\n");
						  printf("W przypadku wyboru możliwości \"moje\" jako czwarty argument należy podać odpowiedni sposób reakcji.\n");
						  printf("\n");
					}
				break;
	         default:/*Informacja o potrzebie skorzystania z pomocy*/
				    {
				      printf("Aby dowiedzieć się, co powinieneś zrobić wpisz \"pomoc\" jako argument wywołania programu.\n\n\n");
				    }
				break;
	       };
	     if (wybor!=6654&&wybor!=6655&&wybor!=4&&wybor!=6656)
	     		while(1)
	     		{
	       		pause();
	       	}
        return 0;
}
