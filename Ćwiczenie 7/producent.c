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
int liczba;
int segment;
int semafor_pam_kons, semafor_pam_prod, semafor_kontrol, semafor_plik;
FILE *odczyt;
char znak[5];
struct cykliczny_bufor *bufor;
void *dow;

int main(int argc, char* argv[])
{
	if(argc<6)
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
	odczyt=fopen("zrodlo.txt","r+");
	if (odczyt==NULL)
	{
			perror("Problem z otwarciem pliku");
			exit(1);
	}
	while(bufor->zakonczono==0)
	{
		opusc_sem(semafor_pam_prod);
		printf("(Semafor dostępu do pamięci producenta)\n");
		opusc_sem(semafor_plik);
		printf("(Semafor dostępu do pliku źródłowego)\n");
		if(bufor->zakonczono==0)
		{
			opusc_sem(semafor_kontrol);
			printf("(Semafor kontroli dostępu do pamięci dzielonej)\n");
			fseek(odczyt,bufor->pozycjaodczytu,SEEK_SET);
			fgets((char *)znak,5,odczyt);
			printf("Producent %d: Produkuję znaki: \"%s\" i przekazuję je do pamięci dzielonej.\n", id, znak);
			strcpy(bufor->string[bufor->kon],znak);
			if(bufor->kon<15)
				bufor->kon=bufor->kon+1;
			else
				bufor->kon=0;
			podnies_sem(semafor_kontrol);
			if(feof(odczyt)==1)
			{
				printf("Producent %d: Produkcja zakończona.\n", id);
				bufor->zakonczono=1;
			}
			bufor->pozycjaodczytu=ftell(odczyt);
		}
		podnies_sem(semafor_plik);
		podnies_sem(semafor_pam_kons);
	}	
	fclose(odczyt);
	pamdziel_usundow(dow);
	return 0;
}