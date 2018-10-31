#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pam.h"
#include "sem.h"

struct cykliczny_bufor
{
	char string[16][5];
	int pocz;
	int kon;
	int zakonczono;
	long pozycjaodczytu;
};

int identyfikator;
key_t klucz_pam;
key_t klucz_sem_producent;
key_t klucz_sem_konsument;
key_t klucz_sem_kontrol;
key_t klucz_sem_odczyt;
key_t klucz_sem_zapis;
int semafor_pam_producent, semafor_pam_konsument, semafor_kontrol;
int semafor_odczyt, semafor_zapis;
char przekaz[8][12];
int lprod, lkons;
int i,j;
void *dow;
struct cykliczny_bufor *bufor;
FILE *zapis, *odczyt;

int main(void)
{
	klucz_sem_producent=ftok("./",'R');
	klucz_sem_konsument=ftok("./",'K');
	klucz_sem_kontrol=ftok("./",'N');
	klucz_pam=ftok("./",'P');
	klucz_sem_odczyt=ftok("./",'O');
	klucz_sem_zapis=ftok("./",'Z');
	identyfikator=pamdziel_stw(klucz_pam, 1024);	
	if(identyfikator<0)
	{
		perror("Błąd tworzenia segmentu pamięci dzielonej");
		exit(1);
	}	
	dow=pamdziel_dow(identyfikator,0);	
	bufor=(struct cykliczny_bufor *)dow;
	
	bufor->pocz=0;
	bufor->kon=0;
	bufor->zakonczono=0;
	bufor->pozycjaodczytu=0;
	zapis=fopen("cel.txt", "w");
	if (zapis==NULL)
	{
		perror("Problem z otwarciem pliku");
		exit(1);
	}
	fclose(zapis);
	
	semafor_pam_producent=stw_sem(klucz_sem_producent, 16);
	semafor_pam_konsument=stw_sem(klucz_sem_konsument, 16);
	for(i=0;i<16;i++)
		opusc_sem(semafor_pam_konsument);
	semafor_kontrol=stw_sem(klucz_sem_kontrol, 1); 
   semafor_odczyt=stw_sem(klucz_sem_odczyt, 1);
   semafor_zapis=stw_sem(klucz_sem_zapis, 1);
   sprintf(przekaz[0],"%d",identyfikator);
   sprintf(przekaz[1],"%d",semafor_odczyt);
   sprintf(przekaz[2],"%d",semafor_zapis);
   sprintf(przekaz[3],"%d",semafor_pam_producent);
   sprintf(przekaz[4],"%d",semafor_pam_konsument);
   sprintf(przekaz[5],"%d",semafor_kontrol);
	printf("Ukończyłem tworzenie semaforów i uzyskałem dostęp do pamięci dzielonej.\nIlu ma być producentów?\n");
	scanf("%d",&lprod);
	printf("Ilu ma być konsumentów?\n");
	scanf("%d",&lkons);
   
	switch(fork())
	{
		case -1:
			perror("Błąd funkcji fork");
			exit(1);
		break;
		case 0:
			switch(fork())
			{
				case -1:
					perror("Błąd funkcji fork");
					exit(1);
				break;
				case 0:
					for (i=0;i<lprod;i++)
						switch(fork())
						{
							case -1:
								perror("Błąd funkcji fork");
								exit(1);
							break;
							case 0:
							{
								sprintf(przekaz[6],"%d",i);
								execl("./producent.out","producent.out",przekaz[0],przekaz[1],przekaz[3],przekaz[4],przekaz[5],przekaz[6],NULL);
								perror("Błąd funkcji exec");
								_exit(2);
							}
							break;
							default:
								
							break;
						}
					exit(0);
				break;
				default:
					sleep(2);
					for (j=0;j<lkons;j++)
						switch(fork())
						{
							case -1:
								perror("Błąd funkcji fork");
								exit(1);
							break;
							case 0:
							{
								sprintf(przekaz[7],"%d",j);
								execl("./konsument.out","konsument.out",przekaz[0],przekaz[2],przekaz[3],przekaz[4],przekaz[5],przekaz[7],NULL);
								perror("Błąd funkcji exec");
								_exit(2);
							}
							break;
							default:
								
							break;
						}
					exit(0);
				break;
			}
		break;
		default:
		break;
	}
	while(bufor->zakonczono<lkons+1)
		sleep(1);
	usun_sem(semafor_pam_producent);
	usun_sem(semafor_pam_konsument);
	usun_sem(semafor_kontrol);
	usun_sem(semafor_odczyt);
	usun_sem(semafor_zapis);
	pamdziel_usundow(dow);
	pamdziel_usunseg(identyfikator);	
	return 0;
}