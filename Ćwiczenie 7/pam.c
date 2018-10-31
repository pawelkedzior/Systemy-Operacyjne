#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

const int ZWYKLY=0;
const int ODCZYT=SHM_RDONLY;

int pamdziel_stw(key_t klucz, int rozmiar)
{
	return shmget(klucz, rozmiar, IPC_CREAT|0666);
}

void *pamdziel_dow(int segment, int tryb)
{
	return shmat(segment, (void *) 0, tryb);
}

int pamdziel_usundow(void *adrdow)
{
	return shmdt(adrdow);
}

int pamdziel_usunseg(int segment)
{
	return shmctl(segment, IPC_RMID, (struct shmid_ds *)0);
}