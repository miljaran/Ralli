#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projekti.h"


kuljettaja *lisaa_kuljettaja(kuljettaja *kokoelma, unsigned int koko, char *nimi, char *talli, int aika) {

  kuljettaja *uusi_kokoelma;

  if (koko == 0) {
    uusi_kokoelma = malloc(sizeof(kuljettaja));
  } else {
    uusi_kokoelma = realloc(kokoelma, (koko + 1) * sizeof(kuljettaja));
  }

  strcpy(uusi_kokoelma[koko].nimi, nimi);
  strcpy(uusi_kokoelma[koko].talli, talli);
  uusi_kokoelma[koko].aika = aika;

  return uusi_kokoelma;
}

int aika_vertailu(const void *a, const void *b) {

  kuljettaja *k_a = (kuljettaja *) a;
  kuljettaja *k_b = (kuljettaja *) b;

  if (k_a->aika < k_b->aika) {
    return -1;
  } else {
    return 1;
  }
}

int nimi_vertailu(const void*a, const void *b) {

  kuljettaja *k_a = (kuljettaja *) a;
  kuljettaja *k_b = (kuljettaja *) b;

  return strcmp(k_a->nimi, k_b->nimi);
}

void tulosta_tilanne(kuljettaja *kokoelma, unsigned int koko) {

  if (koko == 0) {
    printf("Tietokannassa ei ole vielä yhtäkään kuljettajaa.\n");

  } else {
    qsort(kokoelma, koko, sizeof(kuljettaja), aika_vertailu);
    printf("Tämänhetkinen tilanne:\n");

    for (unsigned int i = 0; i < koko; i++) {
      int sekuntit = kokoelma[i].aika % 60;
      int minuutit = ((kokoelma[i].aika - sekuntit) / 60) % 60;
      int tunnit = (kokoelma[i].aika - sekuntit - (60 * minuutit)) / 3600;
      printf("%s, %s: %d tuntia, %d minuuttia, %d sekuntia\n", kokoelma[i].nimi, kokoelma[i].talli, tunnit, minuutit, sekuntit);
    }
  }
}

int lisaa_aikaa(kuljettaja *kokoelma, unsigned int koko, char *nimi, int aika) {

  kuljettaja k;
  strcpy(k.nimi, nimi);
  qsort(kokoelma, koko, sizeof(kuljettaja), nimi_vertailu);
  kuljettaja *olemassaoleva = bsearch(&k, kokoelma, koko, sizeof(kuljettaja), (int(*)(const void*,const void*)) nimi_vertailu);

  if (olemassaoleva != NULL) {
    olemassaoleva->aika += aika;
    return 1;
  } else {
    return -1;
  }
}

int tallenna_tiedostoon(kuljettaja *kokoelma, unsigned int koko, char *nimi) {

  FILE *tiedosto = fopen(nimi, "w");
  if (!tiedosto) {
    return -1;
  }

  int onnistui = 1;

  for (unsigned int i = 0; i < koko; i++) {
    int sekuntit = kokoelma[i].aika % 60;
    int minuutit = ((kokoelma[i].aika - sekuntit) / 60) % 60;
    int tunnit = (kokoelma[i].aika - sekuntit - (60 * minuutit)) / 3600;
    int kirjoitettu = fprintf(tiedosto, "%s, %s: %d tuntia, %d minuuttia, %d sekuntia\n", kokoelma[i].nimi, kokoelma[i].talli, tunnit, minuutit, sekuntit);

    if (kirjoitettu < 0) {
      onnistui = -1;
    }
  }

  fclose(tiedosto);
  return onnistui;
}

kuljettaja *lataa_tiedostosta(kuljettaja *kokoelma, char *nimi, unsigned int *koko_osoitin) {

  FILE *tiedosto = fopen(nimi, "r");
  if (!tiedosto) {
    printf("Tiedoston avaaminen ei onnistunut.\n");
    return kokoelma;

  } else {
    if (*koko_osoitin > 0) {
      free(kokoelma);
    }

    kuljettaja *uusi_kokoelma;
    unsigned int koko = 0;
    char nimi[20], talli[20], rivi[100];
    int tunnit, minuutit, sekuntit;

    while (fgets(rivi, 101, tiedosto) != NULL) {
      sscanf(rivi, "%20[^,], %20[^:]: %d tuntia, %d minuuttia, %d sekuntia", nimi, talli, &tunnit, &minuutit, &sekuntit);
      int aika = 3600 * tunnit + 60 * minuutit + sekuntit;
      uusi_kokoelma = lisaa_kuljettaja(uusi_kokoelma, koko, nimi, talli, aika);
      koko++;
    }

    fclose(tiedosto);
    *koko_osoitin = koko;
    printf("Tiedoston lataaminen onnistui.\n");
    return uusi_kokoelma;
  }
}

int main(void) {

  char rivi[80];
  char *osoitin = fgets(rivi, 81, stdin);
  unsigned int koko = 0;
  kuljettaja *kokoelma;

  // Käyttäjältä kysytään syötettä kunnes komentona on 'Q' tai saavutetaan tiedoston loppu
  while (rivi[0] != 'Q' && osoitin != NULL) {

    // Käyttäjä haluaa lisätä uuden kuljettajan
    if (rivi[0]  == 'A' && rivi[1] == ' ') {
      char nimi[80], talli[80];
      int res = sscanf(rivi, "%*s %s %s", nimi, talli);

      if (res == 2 && strlen(nimi) <= 20 && strlen(talli) <= 20) {
        kuljettaja k;
        strcpy(k.nimi, nimi);
        kuljettaja *olemassaoleva = bsearch(&k, kokoelma, koko, sizeof(kuljettaja), (int(*)(const void*,const void*)) strcmp);

        if (olemassaoleva != NULL) {
          printf("Nimi on jo käytössä.\n");
        } else {
          kokoelma = lisaa_kuljettaja(kokoelma, koko, nimi, talli, 0);
          koko++;
          printf("Kuljettajan lisääminen tietokantaan onnistui.\n");
        }
      } else {
        printf("Virheellinen syöte.\n");
      }
      osoitin = fgets(rivi, 81, stdin);

    // Käyttäjä haluaa tulostaa tilanteen
    } else if (rivi[0] == 'L') {
      tulosta_tilanne(kokoelma, koko);
      osoitin = fgets(rivi, 81, stdin);

    // Käyttäjä haluaa päivittää kuljettajan aikaa
    } else if (rivi[0] == 'U' && rivi[1] == ' ') {
      int tunnit, minuutit, sekunnit;
      char nimi[80];
      int res = sscanf(rivi, "%*s %s %2d %2d %2d", nimi, &tunnit, &minuutit, &sekunnit);
      if (strlen(nimi) > 20) {
        printf("Kuljettajaa ei löytynyt tietokannasta, ajan päivittäminen epäonnistui.\n");
      } else if (res == 4) {
        int aika = tunnit * 3600 + minuutit * 60 + sekunnit;
        int ret = lisaa_aikaa(kokoelma, koko, nimi, aika);
        if (ret > 0) {
          printf("Ajan päivittäminen onnistui.\n");
        } else {
          printf("Kuljettajaa ei löytynyt tietokannasta, ajan päivittäminen epäonnistui.\n");
        }
      } else {
        printf("Virheellinen syöte.\n");
      }
      osoitin = fgets(rivi, 81, stdin);

    // Käyttäjä haluaa tallentaa tulokset tiedostoon
    } else if (rivi[0] == 'W' && rivi[1] == ' ') {
      char nimi[80];
      int ret = sscanf(rivi, "%*s %s", nimi);
      if (ret == 1) {
        ret = tallenna_tiedostoon(kokoelma, koko, nimi);
        if (ret < 0) {
          printf("Tiedostoon tallentaminen epäonnistui.\n");
        } else {
          printf("Tiedostoon tallentaminen onnistui.\n");
        }
      } else {
        printf("Virheellinen syöte.\n");
      }
      osoitin = fgets(rivi, 81, stdin);

    // Käyttäjä haluaa ladata tulokset tiedostosta
    } else if (rivi[0] == 'O' && rivi[1] == ' ') {
      char nimi[80];
      int res = sscanf(rivi, "%*s %s", nimi);
      if (res == 1) {
        kokoelma = lataa_tiedostosta(kokoelma, nimi, &koko);
      } else {
        printf("Virheellinen syöte.\n");
      }
      osoitin = fgets(rivi, 81, stdin);

    // Käyttäjä on antanut virheellisen syötteen
    } else {
      printf("Virheellinen syöte.\n");
      osoitin = fgets(rivi, 81, stdin);
    }
  }
  if (koko > 0) {
    free(kokoelma);
  }
  printf("Lopetetaan ohjelma.\n");
  return 0;
}
