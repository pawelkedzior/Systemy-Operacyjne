#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int id;
int segment;
int semafor_pam_kons, semafor_pam_prod, semafor_kontrol, semafor_plik;
FILE *zapis;
char znak[5];
struct cykliczny_bufor *bufor;
void *dow;

int main(int argc, char* argv[])
{
	if(argc<5)
	{
		perror("Niewłaściwa liczba argumentów");
		exit(1);
	}
	segment=atoi(argv[1]);
	semafor_plik=atoi(argv[2]);
	semafor_pam_kons=atoi(argv[4]);
	semafor_pam_prod=atoi(argv[3]);
	semafor_kontrol=atoi(argv[5]);
	id=atoi(argv[6]);
	dow=pamdziel_dow(segment, 0);
	bufor=(struct cykliczny_bufor *)dow;
	while(1)
	{
		opusc_sem(semafor_pam_kons);
		printf("(Semafor pamięci konsumenta - konsument %d)\n",id);
		opusc_sem(semafor_kontrol);
		printf("(Semafor kontroli dostępu do pamięci dzielonej - konsument %d)\n",id);
		if(bufor->zakonczono>0&&bufor->pocz+1==(bufor->kon!=0?bufor->kon:16))
		{
				printf("Konsument %d: Zakończyłem odczyt.\n", id);
				podnies_sem(semafor_kontrol);
				podnies_sem(semafor_pam_prod);
				podnies_sem(semafor_pam_kons);
				bufor->zakonczono=bufor->zakonczono+1;
				break;
		};
		opusc_sem(semafor_plik);
		printf("(Semafor dostępu do pliku docelowego - konsument %d)\n",id);
		zapis=fopen("cel.txt", "a+");
		if (zapis==NULL)
		{
			perror("Problem z otwarciem pliku");
			podnies_sem(semafor_kontrol);
			exit(1);
		}
		if(bufor->pocz<15)
			bufor->pocz=bufor->pocz+1;
		else
			bufor->pocz=0;
		podnies_sem(semafor_kontrol);
		strcpy(znak, bufor->string[bufor->pocz>0?bufor->pocz-1:15]);
		podnies_sem(semafor_pam_prod);
		printf("Konsument %d: Zakupiłem znaki: \"%s\".\n", id, znak);
		fputs(znak, zapis);
		fclose(zapis);
		podnies_sem(semafor_plik);
		sleep(1);
	}	
	pamdziel_usundow(dow);
	return 0;
}