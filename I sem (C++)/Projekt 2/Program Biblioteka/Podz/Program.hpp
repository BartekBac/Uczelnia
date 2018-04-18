#ifndef NAGLOWKI_H
#define NAGLOWKI_H
#include <stdlib.h>
#include <vld.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//definicje struktur ---------

//struktury potrzebne do utworzenia listy list
struct ksiazka {
	string autor;
	string tytul;
	ksiazka* next;//to jest potrzebne tylko w g³ownej liœcie ksi¹zek
};
struct wsk {
	ksiazka* wsk_na_ks;//ksi¹¿ka przynale¿¹ca do etykiety
	wsk* next;
};
struct etykieta {
	string et;
	etykieta* next;
	wsk* lista_wsk_na_ks;// lista wskazników ksi¹¿ek przynale¿¹cych do etykiety
};
//struktura umo¿liwiaj¹ca generowanie listy b³êdów
struct blad {
	int nr_linii;
	blad* next;
};

//definicje funkcji-----------

//funkcje do operowania na strukturach
void dod_ety(etykieta* &head, const string &etyk);
void dod_ks(ksiazka* &head, const string &aut, const string &tyt);
string szykuj_dane(string &slowo);
bool jest_mniejsze(string a[], string b[]);
void dod_ks_do_ety(wsk* &pocz, ksiazka* wsk_ks);
void zwolnij_pamiec(ksiazka* &head);
etykieta* istnieje(etykieta* head, const string ety_t);
//funkcje wyprowadzaj¹ce dane do pliku wyjœciowego
void wyswietl_ks(wsk* glowa, fstream &plik);
void wyswietl(etykieta* glowa, fstream &plik);
//funkcje zwalniaj¹ce pamiêæ
void usun_ks(wsk* &glowa);
void usun_et(etykieta* &glowa);
//funkcje do obs³ugi konsoli
bool za_malo_arg(int n, char*T[]);
void przelacznik(int n, char*T[], string &input, string &output);
//funkcje do obsu³gi operacji wykrywania b³êdów
void dod_bl(blad* &head, int &linia);
void wys_liste_bl_i_usun(blad* &head, fstream &plik);
bool end(fstream &file, char &sign);

#endif