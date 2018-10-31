#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

/*typedef struct msgbuf
{
	long typ;
	char wiad[90];
	long idproc;
}t_komunikat;*/

int stw_kol(key_t klucz)
{
	return msgget(klucz, IPC_CREAT|0666);
}

int usun_kol(int kol)
{
	return msgctl(kol, IPC_RMID, NULL);
}

int kol_wyslij(int kol, const void *komunikat)
{
	return msgsnd(kol, komunikat, (101+sizeof(long)), 0);
}

int kol_odbierz(int kol, void *komunikat, long typkom)
{
	return msgrcv(kol, komunikat, (101+sizeof(long)), typkom, 0|MSG_NOERROR);
}

int kol_odbierz_nblok(int kol, void *komunikat, long typkom)
{
	return msgrcv(kol, komunikat, (101+sizeof(long)), typkom, IPC_NOWAIT|MSG_NOERROR);
}
