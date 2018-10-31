#ifndef KOL_H
#define KOL_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*typedef struct msgbuf
{
	long typ;
	long idproc;
	char wiad[100];
}t_komunikat;*/

int stw_kol(key_t klucz);

void usun_kol(int kol);

int kol_wyslij(int kol, void *komunikat);

int kol_odbierz(int kol, void *komunikat, long typkom);

int kol_odbierz_nblok(int kol, void *komunikat, long typkom);

#endif