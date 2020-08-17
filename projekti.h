// Määrittää kuljettaja-tietotyypin
typedef struct {
  char nimi[20];
  char talli[20];
  int aika;
} kuljettaja;

// Alustaa uuden kuljettajan ja palauttaa osoittimen listaan
// joka sisältää kaikki kuljettajat
kuljettaja *lisaa_kuljettaja(kuljettaja *kokoelma, unsigned int koko, char *nimi, char *talli, int aika);

// Vertailee kuljettajia ajan mukaan, palauttaa positiivisen luvun
// jos a:n aika on suurempi kuin b:n
int aika_vertailu(const void *a, const void *b);

// Vertailee kuljettajia nimen aakkosjärjestyksen mukaan, palauttaa
// positiivisen luvun jos a:n nimi on aakkosjärjestyksessä ennen b:tä
int nimi_vertailu(const void*a, const void *b);

// Tulostaa kaikkien kuljettajien nimen, tallin ja kokonaisajan
void tulosta_tilanne(kuljettaja *kokoelma, unsigned int koko);

// Lisää kuljettajan kokonaisaikaan aikaa ja palauttaa positiivisen
// luvun jos lisääminen onnistui
int lisaa_aikaa(kuljettaja *kokoelma, unsigned int koko, char *nimi, int aika);

// Tallentaa kisatilanteen tiedostoon ja palauttaa positiivisen
// luvun jos tallentaminen onnistui
int tallenna_tiedostoon(kuljettaja *kokoelma, unsigned int koko, char *nimi);

// Lataa kisatilanteen tiedostosta, korvaa sillä edellisen
// ja palauttaa osoittimen listaan kuljettajista
kuljettaja *lataa_tiedostosta(kuljettaja *kokoelma, char *nimi, unsigned int *koko_osoitin);
