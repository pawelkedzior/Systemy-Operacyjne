#ifndef SEM_H
#define SEM_H
#include <sys/types.h>
#include <sys/ipc.h>

int stw_sem(key_t klucz_sem, int typ);

void usun_sem(int sem);

int kontrola_sem(int sem, int zadanie);

void przejdz_pod_sem(int sem);

void opusc_sem(int sem);

void podnies_sem(int sem);

#endif