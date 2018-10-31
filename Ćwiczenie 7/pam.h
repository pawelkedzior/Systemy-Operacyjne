#ifndef PAM_H
#define PAM_H

int pamdziel_stw(key_t klucz, int rozmiar);
void *pamdziel_dow(int segment, int tryb);
int pamdziel_usundow(void *adrdow);
int pamdziel_usunseg(int segment);

#endif