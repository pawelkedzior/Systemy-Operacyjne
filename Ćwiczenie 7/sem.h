#ifndef SEM_H
#define SEM_H
#include <sys/types.h>
#include <sys/ipc.h>

#define CZEKA_PRZED 14
#define CZEKA_POD 15
#define ILE_MOZLIWE 12

int stw_sem(key_t klucz_sem, int typ);

void usun_sem(int sem);

int kontrola_sem(int sem, int zadanie);

void przejdz_pod_sem(int sem);

void opusc_sem(int sem);

void podnies_sem(int sem);

#endif