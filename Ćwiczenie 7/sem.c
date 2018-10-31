#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

#define CZEKA_PRZED 14
#define CZEKA_POD 15
#define ILE_MOZLIWE 12

union uniasem {
int wart;
struct semid_ds *buf;
ushort *tablica;
} kontrolasem;

int stw_sem(key_t klucz_sem, int typ)
{
	int idsem;
	idsem=semget(klucz_sem, 1, IPC_CREAT|0666);
	if(idsem<0)
	{
		perror("Błąd tworzenia semafora.");
		return -1;
	}
	kontrolasem.wart=typ;
	if(semctl(idsem, 0, SETVAL, kontrolasem)==-1)
	{	
		perror("Błąd inicjacji semafora.");
		return -1;
	}
	return idsem;
}

void usun_sem(int sem)
{
	if(semctl(sem, 0, IPC_RMID)==-1)
		perror("Błąd usuwania semafora.");
}

int kontrola_sem(int sem, int zadanie)
{
	int wart;
	wart=semctl(sem, 0, zadanie);
	if(wart==-1)
		perror("Błąd kontroli semafora.");
	return wart;
}

void opusc_sem(int sem)
{
	struct sembuf corobic={0,-1,0};
	struct sembuf *wsk=&corobic;
	if(semop(sem, wsk, 1)==-1)
		perror("Błąd opuszczania semafora");
	else
	{
		int ile=kontrola_sem(sem, CZEKA_PRZED);
	   printf("Opuszczam semafor. Przed semaforem czeka");
	   if((ile%10>1&&ile%10<5)&&(ile/10!=1))
	     printf("ją");
	   printf(" %d proces", ile);
	   if((ile%10>1&&ile%10<5)&&(ile/10!=1))
	     printf("y");
	   else if(ile!=1)
	     printf("ów");
	   printf(".\n");
   }
}

void przejdz_pod_sem(int sem)
{
	struct sembuf corobic={0,0,0};
	struct sembuf *wsk=&corobic;
	if(semop(sem, wsk, 1)==-1)
		perror("Błąd przechodzenia pod semaforem");
	else
	{
		int ile=kontrola_sem(sem, CZEKA_POD);
	   printf("Przepuszczam proces pod semaforem.\nNa przejście pod semaforem czeka");
	   if((ile%10>1&&ile%10<5)&&(ile/10!=1))
	     printf("ją");
	   printf(" %d proces", ile);
	   if((ile%10>1&&ile%10<5)&&(ile/10!=1))
	     printf("y");
	   else if(ile!=1)
	     printf("ów");
	   printf(".\n");
	}
}

void podnies_sem(int sem)
{
	struct sembuf corobic={0,1,0};
	struct sembuf *wsk=&corobic;
	if(semop(sem, wsk, 1)==-1)
		perror("Błąd podnoszenia semafora");
}