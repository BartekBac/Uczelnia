#include "Program.hpp"

void dod_ety(etykieta* &head, const string &etyk)
{//dodajemy na pocz¹tek bo bêdziemy z tego korzystaæ przy dodawaniu ksi¹¿ek do poszczególnych etykiet
	head = new etykieta{ etyk,head,nullptr };
}
void dod_ks(ksiazka* &head, const string &aut, const string &tyt)
{//dodaje ksia¿ki na pocz¹tek listy wszytskich ksi¹¿ek
	head = new ksiazka{ aut, tyt, head };
}
string szykuj_dane(string &slowo)//zmienjasza wszytsko na ma³e litery
{
	for (int i = 0; i < slowo.size(); i++)
	{
		if (slowo[i] >= 65 && slowo[i] <= 90)
			slowo[i] = slowo[i] + 32;
	}
	return slowo;
}
bool jest_mniejsze(string a[], string b[])
{
	string A1 = szykuj_dane(a[0]), A2 = szykuj_dane(a[1]), B1 = szykuj_dane(b[0]), B2 = szykuj_dane(b[1]);
	if (A1 == B1)//gdy autor ten sam;
	{//porównuje tytu³y od razu
		if (A2 < B2)
			return true;
		else
			return false;
	}
	else
	{
		if (A1 < B1)
			return true;
		else
			return false;
	}
}
void dod_ks_do_ety(wsk* &pocz, ksiazka* wsk_ks)
{
	wsk* nowy = new wsk;
	nowy->wsk_na_ks = wsk_ks;
	//nowy->wsk_na_ks->next = nullptr;
	if (!pocz)
	{
		pocz = nowy;
		nowy->next = nullptr;
	}
	else
	{
		wsk* pom = pocz;
		int i = 0;
		string dane_wej[2] = { wsk_ks->autor, wsk_ks->tytul };
		string dane_lis[2] = { pom->wsk_na_ks->autor , pom->wsk_na_ks->tytul };
		bool end = true;

		if (jest_mniejsze(dane_wej, dane_lis))//sprawdza czy jest mniejsze od pierwszego elementu
		{//dodanie na pocz¹tek
			nowy->next = pom;
			pocz = nowy;
		}
		else
		{
			while (pom->next&&end)//pêtla szukaj¹ca miejsca do wstawienia nowego elementu
			{
				//przemianowanie danych
				dane_lis[0] = pom->next->wsk_na_ks->autor;
				dane_lis[1] = pom->next->wsk_na_ks->tytul;

				if (jest_mniejsze(dane_wej, dane_lis))
				{//jak znajdzie odpowiednie miejsce to wstawia
					nowy->next = pom->next;
					pom->next = nowy;
					end = false;
				}
				else
					pom = pom->next;
			}
			if (pom->next == nullptr)
			{//dodanie na koniec
				pom->next = nowy;
				nowy->next = nullptr;
			}
		}
	}
}
void zwolnij_pamiec(ksiazka* &head)
{// ta funkcja musi byc oddzielnie bo sama lista ksi¹¿ek nie jest wyœwietlana, totez nie mo¿e byæ wtedy na bierz¹co usuwana jak reszta elementów struktur
	while (head)
	{
		ksiazka* pom = head->next;
		delete head;
		head = pom;
	}
	head = nullptr;
}
etykieta* istnieje(etykieta* head, const string ety_t)
{//funkcja zwraca wskaŸnik na etykietê, do której ma byæ dodana ksi¹¿ka,
	while (head&&head->et != ety_t)
		head = head->next;
	return head;
}

void wyswietl_ks(wsk* glowa, fstream &plik)
{
	while (glowa)
	{
		plik << glowa->wsk_na_ks->autor << "; " << glowa->wsk_na_ks->tytul << endl;
		glowa = glowa->next;
	}
	plik << endl;
}
void wyswietl(etykieta* glowa, fstream &plik)
{
	while (glowa)
	{
		plik << glowa->et << ":" << endl;
		wyswietl_ks(glowa->lista_wsk_na_ks, plik);
		glowa = glowa->next;
	}
	plik << endl;
}
void usun_ks(wsk* &glowa)
{
	while (glowa)
	{
		wsk* pom = glowa->next;
		delete glowa;
		glowa = pom;
	}
	glowa = nullptr;
}
void usun_et(etykieta* &glowa)
{
	while (glowa)
	{
		usun_ks(glowa->lista_wsk_na_ks);
		etykieta* pom = glowa->next;
		delete glowa;
		glowa = pom;
	}
	glowa = nullptr;
}

bool za_malo_arg(int n, char*T[])
{// wyœwitlanie pomoc gdy podano za ma³¹ iloœæ danych wejœciowych
	if (n < 5)
	{
		cerr << "Uzyj: -> " << T[0] << " -i <nazwa_pliku_do_otwarcia> -o <nazwa_pliku_do_zapisu>" << endl;
		return true;
	}
	else
		return false;
}
void przelacznik(int n, char*T[], string &input, string &output)
{//pobieranie nazw pliku wejsciowego/wyjsciowego z konsoli
	for (int i = 1; i < n; i++)
	{
		if (string(T[i]) == "-i")
		{
			if (i + 1 < n)
				input = T[++i];
			else
			{
				cout << "Podaj nazwe pliku do otwarcia po przelaczniku: -> " << "-i" << " <nazwa_pliku_do_otwarcia>" << endl;
				return;
			}
		}
		if (string(T[i]) == "-o")
		{
			if (i + 1 < n)
				output = T[++i];
			else
			{
				cout << "Podaj nazwe pliku wyjsciowego po przelaczniku: -> " << "-o" << " <nazwa_pliku_do_zapisu>" << endl;
				return;
			}
		}
	}
}

void dod_bl(blad* &head, int &linia)
{
	blad* element = new blad;

	if (!head)
		head = element;
	else
	{
		blad* pom;
		pom = head;
		while (pom->next)
		{
			pom = pom->next;
		}
		pom->next = element;
	}
	element->nr_linii = linia;
	element->next = nullptr;
}
void wys_liste_bl_i_usun(blad* &head, fstream &plik)
{
	while (head)
	{
		plik << "Blad danych w lini(" << head->nr_linii << ")" << endl;
		blad* pom = head->next;
		delete head;
		head = pom;
	}
	head = nullptr;
}
bool end(fstream &file, char &sign)
{
	if (file >> noskipws >> sign)
	{
		file.seekg(-2, ios_base::cur);
		file >> noskipws >> sign;
		//dlaczego nie moze sie cofn¹æ gdy pobierze znak '\n'?
		return false;
	}
	else
		return true;
}
