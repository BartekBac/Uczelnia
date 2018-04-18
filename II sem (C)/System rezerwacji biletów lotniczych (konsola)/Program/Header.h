#ifndef Header_h
#define Header_h
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<time.h>
#include<vld.h>

//definicje struktur -------------------------------
//strutura do tworzenia listy lotnisk
struct baza {
	char nazwa[15];
	int id;
	struct baza *next;
};
//struktura do tworzenia listy podwieszonej scie¿ek
struct lista {
	struct baza *element;
	int g_wyl[2];
	int g_prz[2];
	int data[3];
	struct lista *next;
	struct lista *prev;
};
//struktura do tworzenia listy scie¿ek
struct path {
	int nr;
	int cena;
	struct lista *m_elem;
	struct path *s_next;
};
//struktura przechowuj¹ca dane osobowe klientów
struct osoba {
	char imie[15];
	char nazwisko[15];
	int wiek;
};
//struktura do obs³ugi kolejki
//(u¿ywanej w algorytmie wyszukiwania najkrótszej scie¿ki po³¹czeñ miêdzy lotniskami)
struct elq {
	int num;
	struct elq *next;
};

//deklaracje funkcji------------------------------------

//funkcje obs³uguj¹ce kolejkê
void qpush(struct elq **head, int x);
int qpop(struct elq **head);
int qempty(struct elq **head);
//koniec obs³ugi kolejki

//funkcja wype³niaj¹ca miacierz po³¹czeñ
int **wypelnij(int **tab, int n, struct baza *head);
//funkcja wczytuj¹ca lotniska do bazy
int wcz_baze(struct baza **head, char *nazwa);
//funkcja dodaj¹ca listy podwieszone scie¿ek
void m_dod(struct lista **head, int ind, struct baza *g_baza);
//funkcja dodaj¹ca scie¿ki do listy
void s_dod(struct path **head);
//funkcja pobieraj¹ca mo¿liwe sice¿ki przelotu
struct path *pob_sciezki(int *path, int n, int v, int **tab, struct baza *gbaza);
//funkcja wyszukuj¹ca mo¿liwych sciezek po³¹czeñ
void szukaj(int **tab, int n, int p, int k, struct baza *hbaza, struct path **l_path);
//funkcja usuwaj¹ca listy powieszone scie¿ek
void m_us(struct lista **head);
//funkcja usuwaj¹ca listê scie¿ek
void s_us(struct path **head);
//funkcja wypisuj¹ca dostêpne lotniska
void wyp_lotniska(struct baza *head);
//funkcja zamieniajaca nazwê lotniska na id
int ntoi(struct baza *head, char *nazwa, int *x);
//funkcja sprawdzaj¹ca czy data jest poprawna i jej aktualnoœæ
int spr_date(int d, int m, int r, int *end);
//funkcja sprawdzaj¹ca czy wprowadzona godzina jest poprawna
int spr_godz(int g, int m);
//funckaj zamienia datê na dzieñ tygodnia
int conv_data(int d, int m, int r);
//funkcja s³u¿¹c¹ do wyszukiwania daty i poœrednio godziny wylotu, zwraca ile dodaæ dni do daty wylotu (gdy wylot jest niemo¿liwy w danym dniu)
int sz_rozk(char *s_nazwa, char *d_nazwa, int dz, int godz, int min, int **godz_wyl, int **godz_prz);
//funkcja wyszukuje datê i poœrednio godzinê wylotu, w warunku gdy mamy wymuszon¹ godzinê przylotu (opcjonalnie zwraca ile dni odj¹æ od daty wylotu)
int sz_rozk_wstecz(char *s_nazwa, char *d_nazwa, int dz, int godz, int min, int **godz_wyl, int **godz_prz);
//funkcja bezpoœrednio wyszukuje w rozkladzie najdogodniejsza godzine wylotu, zwraca 0 jak nie znalezniono w danym dniu odpowiedniej, zwraca 1 jak znaleziono
int sz_godz(FILE *plik, int godz, int min, int *odlot[], int *przylot[]);
//funkcja analogiczna do sz_godz, tylko w warunkach wymuszonej godziny przylotu
int sz_godz_wstecz(FILE *plik, int godz, int min, int *odlot[], int *przylot[]);
//funkcja sprawdza czy data powrotu jest pozniejsza ni¿ data wylotu
int porownaj_date(int wyl_d, int wyl_m, int wyl_r, int prz_d, int prz_m, int prz_r);
//funkcja zwiêkszaj¹ca datê
int *inc_data(int tab[], int x);
//funkcja zmniejszaj¹ca datê
int *dec_data(int tab[], int x);
//funkcja, która uzupe³nia listê sciezek o godziny i daty, potrzebne do wypisania i zwrócenia wybranej sciezki
void uzupelnij(struct lista **element, int gw, int mw, int gp, int mp, int d, int m, int r);
//funkcja wypisuj¹ca na ekran mo¿liwe œciezki wylotu do wyboru
void wypisz_przeloty(struct path **sciezki, int d, int m, int r, char *miasto_docelowe, int *zamknij, int kl);
//funkcja wypisuj¹ca na ekran mo¿liwe œcie¿ki wylotu do wyboru, w warunku wymuszonej odpowiedniej godziny przylotu
void wypisz_przeloty_wstecz(struct path **sciezki, int d, int m, int r, char *miasto_docelowe, int *zamknij, int h_p, int m_p, int kl);
//funkcja wpisuj¹ca dane dotyczace rezerwacji do pliku wynikowego
void wpisz(struct path *wyl, struct path *pow, struct osoba *tos, int il, int tl, int em, int cn);
//funkcja wypisuje cenê za pojedynczy bilet danej scie¿ki
int ustal_cene(struct lista *head, int klasa);
//funkcja zwalniaj¹ca listê lotnisk z bazy
void zwolnij_poloczenia(struct baza **head);

#endif