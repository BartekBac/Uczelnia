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
//struktura do tworzenia listy podwieszonej scie�ek
struct lista {
	struct baza *element;
	int g_wyl[2];
	int g_prz[2];
	int data[3];
	struct lista *next;
	struct lista *prev;
};
//struktura do tworzenia listy scie�ek
struct path {
	int nr;
	int cena;
	struct lista *m_elem;
	struct path *s_next;
};
//struktura przechowuj�ca dane osobowe klient�w
struct osoba {
	char imie[15];
	char nazwisko[15];
	int wiek;
};
//struktura do obs�ugi kolejki
//(u�ywanej w algorytmie wyszukiwania najkr�tszej scie�ki po��cze� mi�dzy lotniskami)
struct elq {
	int num;
	struct elq *next;
};

//deklaracje funkcji------------------------------------

//funkcje obs�uguj�ce kolejk�
void qpush(struct elq **head, int x);
int qpop(struct elq **head);
int qempty(struct elq **head);
//koniec obs�ugi kolejki

//funkcja wype�niaj�ca miacierz po��cze�
int **wypelnij(int **tab, int n, struct baza *head);
//funkcja wczytuj�ca lotniska do bazy
int wcz_baze(struct baza **head, char *nazwa);
//funkcja dodaj�ca listy podwieszone scie�ek
void m_dod(struct lista **head, int ind, struct baza *g_baza);
//funkcja dodaj�ca scie�ki do listy
void s_dod(struct path **head);
//funkcja pobieraj�ca mo�liwe sice�ki przelotu
struct path *pob_sciezki(int *path, int n, int v, int **tab, struct baza *gbaza);
//funkcja wyszukuj�ca mo�liwych sciezek po��cze�
void szukaj(int **tab, int n, int p, int k, struct baza *hbaza, struct path **l_path);
//funkcja usuwaj�ca listy powieszone scie�ek
void m_us(struct lista **head);
//funkcja usuwaj�ca list� scie�ek
void s_us(struct path **head);
//funkcja wypisuj�ca dost�pne lotniska
void wyp_lotniska(struct baza *head);
//funkcja zamieniajaca nazw� lotniska na id
int ntoi(struct baza *head, char *nazwa, int *x);
//funkcja sprawdzaj�ca czy data jest poprawna i jej aktualno��
int spr_date(int d, int m, int r, int *end);
//funkcja sprawdzaj�ca czy wprowadzona godzina jest poprawna
int spr_godz(int g, int m);
//funckaj zamienia dat� na dzie� tygodnia
int conv_data(int d, int m, int r);
//funkcja s�u��c� do wyszukiwania daty i po�rednio godziny wylotu, zwraca ile doda� dni do daty wylotu (gdy wylot jest niemo�liwy w danym dniu)
int sz_rozk(char *s_nazwa, char *d_nazwa, int dz, int godz, int min, int **godz_wyl, int **godz_prz);
//funkcja wyszukuje dat� i po�rednio godzin� wylotu, w warunku gdy mamy wymuszon� godzin� przylotu (opcjonalnie zwraca ile dni odj�� od daty wylotu)
int sz_rozk_wstecz(char *s_nazwa, char *d_nazwa, int dz, int godz, int min, int **godz_wyl, int **godz_prz);
//funkcja bezpo�rednio wyszukuje w rozkladzie najdogodniejsza godzine wylotu, zwraca 0 jak nie znalezniono w danym dniu odpowiedniej, zwraca 1 jak znaleziono
int sz_godz(FILE *plik, int godz, int min, int *odlot[], int *przylot[]);
//funkcja analogiczna do sz_godz, tylko w warunkach wymuszonej godziny przylotu
int sz_godz_wstecz(FILE *plik, int godz, int min, int *odlot[], int *przylot[]);
//funkcja sprawdza czy data powrotu jest pozniejsza ni� data wylotu
int porownaj_date(int wyl_d, int wyl_m, int wyl_r, int prz_d, int prz_m, int prz_r);
//funkcja zwi�kszaj�ca dat�
int *inc_data(int tab[], int x);
//funkcja zmniejszaj�ca dat�
int *dec_data(int tab[], int x);
//funkcja, kt�ra uzupe�nia list� sciezek o godziny i daty, potrzebne do wypisania i zwr�cenia wybranej sciezki
void uzupelnij(struct lista **element, int gw, int mw, int gp, int mp, int d, int m, int r);
//funkcja wypisuj�ca na ekran mo�liwe �ciezki wylotu do wyboru
void wypisz_przeloty(struct path **sciezki, int d, int m, int r, char *miasto_docelowe, int *zamknij, int kl);
//funkcja wypisuj�ca na ekran mo�liwe �cie�ki wylotu do wyboru, w warunku wymuszonej odpowiedniej godziny przylotu
void wypisz_przeloty_wstecz(struct path **sciezki, int d, int m, int r, char *miasto_docelowe, int *zamknij, int h_p, int m_p, int kl);
//funkcja wpisuj�ca dane dotyczace rezerwacji do pliku wynikowego
void wpisz(struct path *wyl, struct path *pow, struct osoba *tos, int il, int tl, int em, int cn);
//funkcja wypisuje cen� za pojedynczy bilet danej scie�ki
int ustal_cene(struct lista *head, int klasa);
//funkcja zwalniaj�ca list� lotnisk z bazy
void zwolnij_poloczenia(struct baza **head);

#endif