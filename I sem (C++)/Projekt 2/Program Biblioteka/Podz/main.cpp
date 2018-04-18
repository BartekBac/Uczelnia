#include "Program.hpp"

int main(int argc, char*argv[])
{
	string wej, wyj;//nazwy plik�w wej�ciowego i wyj�ciowego

	if (za_malo_arg(argc, argv))
		return 1;

	przelacznik(argc, argv, wej, wyj);

	if (wej == wyj)
	{// wyeliminowanie przypadku gdzy podamy ten sam plik jako do odczytu i zapisu
		cout << "Nie mozna zapisac wyniku do pliku wejscia!";
		return 1;
	}

	fstream plik, nowy;
	plik.open(wej, ios::in);
	if (!plik.good())
	{
		cerr << "Blad pliku wejsciowego." << endl;
		return 1;
	}
	nowy.open(wyj, ios::out);
	if (!nowy.good())
	{
		cerr << "Blad pliku wyjsciowego" << endl;
		return 1;
	}

	etykieta* lista_et = nullptr; //g��wna lista wszytskich etykiet
	ksiazka* lista_ks = nullptr; //g�owna lista wszystkich ksi��ek
	blad* lista_bl = nullptr;// g�owna lista napotkanych b��d�w

							 //dane pomocnicze do poruszania si� po pliku wejsciowym
	char znak;
	int licznik = 1;
	string aut_t, tyt_t, ety_t;

	//P�tla sczytuj�ca dane z pliku wej�ciowego
	while (plik >> noskipws >> znak)
	{
		bool new_line = true;
		while (znak != ';')
		{//sczytanie nazwy autora
			if (znak == '\n' || end(plik, znak))
			{
				dod_bl(lista_bl, licznik);
				new_line = false;
				break;
			}
			aut_t += znak;
			plik >> noskipws >> znak;
		}
		if (new_line)
		{
			plik >> znak;//pobiera spacje
			while (znak != ';')
			{//zczytuje tytu� (a� do napotkania ";"<- jest to wymuszone przez specyfikacje programu)
				if (znak == '\n' || end(plik, znak))
				{
					dod_bl(lista_bl, licznik);
					new_line = false;
					break;
				}
				if (znak != '\n')//dziwny przypadek gdy powy�szy if zwraca '\n' jak nie dostaje go na wejsciu, opisane jeszcze w funkcji end
					plik >> noskipws >> znak;
				tyt_t += znak;
			}
			if (new_line)
			{
				if (end(plik, znak))//sprawdzenie czy nie koniec pliku (gdyby ostatnia ksia�ka nie mia�a etykiet i po �redniku nie b�dzie spacji
					dod_bl(lista_bl, licznik);
				else
				{
					tyt_t.erase((tyt_t.size() - 1), 1);//gumuje ";"
					dod_ks(lista_ks, aut_t, tyt_t);//dodaje ksi�zk� do g�ownej listy ksi��ek
				}
				while (plik >> noskipws >> znak)
				{//wyemilinowanie b�edu, gdy nie podano �adnych etykiet
					if (end(plik, znak))//sprawdzenie czy nie ma konca pliku gdy po �redniku sa spacje
						dod_bl(lista_bl, licznik);
					if (znak == ' ')
						continue;
					else
					{
						if (znak == '\n')
						{
							dod_bl(lista_bl, licznik);
							break;
						}
						else
						{
							plik.seekg(-2, ios_base::cur);
							break;
						}
					}
				}
				//teraz nast�puje sczytanie nazw etykiet
				while (znak != '\n'&&plik >> noskipws >> znak)//zczytuje do momentu przejscia do nowej linii
				{
					while (znak != ','&& plik >> noskipws >> znak)//pojedy�cz� nazw� etykiety zczytuj� do momentu napotkania przecinka
					{
						ety_t += znak;
						if (znak == '\n')break;//w przypadku gdy jest tylko jedna etykieta przypisana do ksiazki
					}
					if (!end(plik, znak))//sprawdza czy to nie koniec pliku
						ety_t.erase((ety_t.size() - 1), 1);//gumuje ","
					if (ety_t!="")//gdy kto� po ostatnim przecinku(kt�rego w og�le powinno nie by� wpisze spacj�)
					{
						if (ety_t[ety_t.size() - 1] == '\n' || ety_t[ety_t.size() - 1] == ',')// dla wyeliminowaniu bledu gdy po ostatniej linii kto� wpisze jeszcze enter lub ','
							ety_t.erase((ety_t.size() - 1), 1);
					}
					//Sprawdzamy gdzie wstawi� now� ksi��k�
					etykieta* nowa;
					nowa = istnieje(lista_et, ety_t);
					if (nowa == nullptr)
					{//je�li taka nie istnieje to zwr�ci nullptr, czyli trzeba doda� now� etykiet�
						dod_ety(lista_et, ety_t);
						dod_ks_do_ety(lista_et->lista_wsk_na_ks, lista_ks);
					}
					else
						dod_ks_do_ety(nowa->lista_wsk_na_ks, lista_ks);

					ety_t = "";
				}
			}
		}
		//trzeba wyczyscic dane, �eby m�c na nowo dopisywa� do nich znaki
		aut_t = "";
		tyt_t = "";
		ety_t = "";
		licznik++;
	}
	wyswietl(lista_et, nowy);
	wys_liste_bl_i_usun(lista_bl, nowy);
	usun_et(lista_et);
	zwolnij_pamiec(lista_ks);
	cout << "Wykonano." << endl;
	
	return 0;
}