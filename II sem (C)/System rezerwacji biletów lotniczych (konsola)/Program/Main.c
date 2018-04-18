#include "Header.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return;
	struct baza *poloczenia = NULL;
	int n = wcz_baze(&poloczenia, argv[1]); // n - ilosc miast w sieci po³¹czeñ
	if (n == -1)
		return;
	printf("|SYSTEM REZERWACJI BILETÓW LOTNICZYCH|\nWitamy w systemie rezeracji biletow lotniczych.\nOto lista dostepnych lotnisk:\n");
	wyp_lotniska(poloczenia);
	//bazê lotnisk wczytujemy tylko raz od razu po uruchomieniu, ona siê nie zmienia
	int on = 1;
	while (on)
	{
		printf("0 - Zakoncz program\n1 - kontynuuj...");
		scanf("%d", &on);
		while (on != 0 && on != 1)
		{
			printf("Blad (wybierz 1 lub 2): ");
			scanf("%d", &on);
		}
		if (on == 0)
		{// przy tym warunku dochodzi tylko do zakoñczenia dzia³ania programu
		 //wtedy ju¿ zwalniamy bazê po³¹czeñ
			zwolnij_poloczenia(&poloczenia);
			return 0;
		}
		// dane pobierane od u¿ytkownika:
		char skad[15], dokad[15];
		int st = 1; //warunek czy lot w dwie strony
		int wd = 1, wm = 1, wr = 1; //data wylotu
		int pd = 1, pm = 1, pr = 1; //data powrotu (opcjonalne)
		int ils = 1; //ilosc pasazerow
		int kls = 1; //wybor klasy rezerwacji
		int end = 0; //warunek napotkania blêdu
		int war_wyl = 0, w_godz = 0, w_min = 0; //warunek i dane godziny wylotu
		int war_pow = 0, p_godz = 0, p_min = 0; //warunek i dane godziny powrotu (opcjonalne)

												//Operacje pobierania danych od u¿ytkownika i eliminacja b³edów z nimi zwi¹zanych
		printf("Wybierz:\n1 - lot w jedna strone\n2 - lot w obie strony\n");
		scanf("%d", &st);
		while (st != 1 && st != 2)
		{//B³edy miêkkie rozstrzygamy pêtl¹ while
			printf("Blad (wybierz 1 lub 2): ");
			scanf("%d", &st);
		}

		printf("Miejsce wylotu: ");
		scanf("%s", &skad);
		printf("Miejsce przylotu: ");
		scanf("%s", &dokad);

		int iska = ntoi(poloczenia, skad, &end);
		int idok = ntoi(poloczenia, dokad, &end);
		if (end)
		{//jeœli napotkamy jakiœ b³¹d twardy to przerywamy bierz¹c¹ rezerwacjê
			continue;
		}
		printf("Data wylotu (dd-mm-rrrr): ");
		scanf("%d-%d-%d", &wd, &wm, &wr);
		while (spr_date(wd, wm, wr, &end) == 2)
		{
			printf("Wprowadz poprawnie date wylotu (dd-mm-rrrr): ");
			scanf("%d-%d-%d", &wd, &wm, &wr);
		}
		if (spr_date(wd, wm, wr, &end) == 1)
		{
			continue;
		}

		printf("Musze byc na dana godzine. Wybierz (0-nie, 1-tak): ");
		scanf("%d", &war_wyl);
		while (war_wyl != 0 && war_wyl != 1)
		{
			printf("Blad (wybierz 0 lub 1): ");
			scanf("%d", &war_wyl);
		}
		if (war_wyl == 1)
		{
			printf("Podaj godzine (gg-mm): ");
			scanf("%d-%d", &w_godz, &w_min);
			while (spr_godz(w_godz, w_min, &end))
			{
				printf("Wprowadz poprawnie godzine (gg-mm): ");
				scanf("%d-%d", &w_godz, &w_min);
			}
		}

		if (st == 2)
		{
			printf("Data powrotu: ");
			scanf("%d-%d-%d", &pd, &pm, &pr);
			while (spr_date(pd, pm, pr, &end) == 2)
			{
				printf("Wprowadz poprawnie date powrotu (dd-mm-rrrr): ");
				scanf("%d-%d-%d", &pd, &pm, &pr);
			}
			if (spr_date(pd, pm, pr, &end) == 1)
			{
				continue;
			}
			if (porownaj_date(wd, wm, wr, pd, pm, pr))
			{
				printf("Data powrotu musi byc pozniejsza od daty wylotu.");
				continue;
			}
			printf("Musze byc na dana godzine. Wybierz (0-nie, 1-tak): ");
			scanf("%d", &war_pow);
			while (war_pow != 0 && war_pow != 1)
			{
				printf("Blad (wybierz 0 lub 1): ");
				scanf("%d", &war_pow);
			}
			if (war_pow == 1)
			{
				printf("Podaj godzine (gg-mm): ");
				scanf("%d-%d", &p_godz, &p_min);
				while (spr_godz(p_godz, p_min, &end))
				{
					printf("Wprowadz poprawnie godzine (gg-mm): ");
					scanf("%d-%d", &p_godz, &p_min);
				}
			}
		}

		printf("Ilosc pasazerow (1-10): ");
		scanf("%d", &ils);
		while (ils < 1)
		{
			printf("Blad wybierz z przedzialu 1-10: ");
			scanf("%d", &ils);
		}
		if (ils > 10)
		{
			printf("Jezeli chca Panstwo wynajac bilet grupowy, prosimy skontaktowac sie z nami telefonicznie.\nNumer infolinii: 688 234 696.\n");
			continue;
		}

		printf("Klasa:\n1 - ekonomiczna\n2 - biznes\n3 - premium:\n");
		scanf("%d", &kls);
		while (kls != 1 && kls != 2 && kls != 3)
		{
			printf("Blad (wybierz 1, 2 lub 3): ");
			scanf("%d", &kls);
		}
		//Koniec pobierania danych wstêpnych rezerwacji

		//macierz po³¹czeñ miêdzy lotniskami
		int **tab = (int**)malloc(sizeof(int)*n);
		for (int i = 0; i < n; i++)
		{
			tab[i] = (int*)malloc(sizeof(int)*n);
		}
		tab = wypelnij(tab, n, poloczenia);

		//lista wszytskich mozliwych sciezek
		struct path *sciezki = NULL;
		//uzupe³niamy przez referencje listê sciezek
		szukaj(tab, n, iska, idok, poloczenia, &sciezki);
		struct path *pom = sciezki;

		// teraz program uzupe³nia liste sciezek o dane godzin i dat						
		int nr_w = 1;//ineksy sciezek wylotu do wyboru
		int nie_akt[5] = { 0,0,0,0,0 };//tablica nieaktualnych sciezek (mo¿e byæ tak ¿e nie wszytskie oferty z mo¿liwych s¹ nieaktualne)
		int rez = 0;//warunek mo¿liwoœci rezerwacji
		if (sciezki == NULL)
		{//ten b³ad wyst¹pi gdy nie bêdzie siê da³o znaleŸæ odpowiedniego po³aczenia
			for (int i = 0; i < n; i++)
				free(tab[i]);
			free(tab);
			continue;
		}
		printf("MOZLIWE PRZELOTY:\n");
		while (pom)
		{
			pom->nr = nr_w++;//przypisujemy indeks sciezki
			if (war_wyl == 0)
			{
				wypisz_przeloty(&pom, wd, wm, wr, dokad, &end, kls);
				if (end == 1)//jak napotkamy b³ad (np. nieaktualnoœæ oferty)
				{// to odrzucamy bierz¹c¹ ofertê i sprawdzamy kolejne
					nie_akt[nr_w - 2] = 1;
					end = 0;
					continue;
				}
				if (end == 2)
				{//powa¿ny b³ad braku pliku
					for (int i = 0; i < n; i++)
						free(tab[i]);
					free(tab);
					s_us(&sciezki);
					zwolnij_poloczenia(&poloczenia);
					return;
				}
			}
			else
			{//analogicznie tylko jak szukamy po³aczenia na dan¹ godzinê
				wypisz_przeloty_wstecz(&pom, wd, wm, wr, dokad, &end, w_godz, w_min, kls);
				if (end == 1)
				{
					nie_akt[nr_w - 2] = 1;
					end = 0;
					continue;
				}
				if (end == 2)
				{//powa¿ny b³ad braku pliku
					for (int i = 0; i < n; i++)
						free(tab[i]);
					free(tab);
					s_us(&sciezki);
					zwolnij_poloczenia(&poloczenia);
					return;
				}
			}
		}

		for (int j = 0; j < (nr_w - 1); j++)
		{//jeœli wszytskie oferty by³y nieaktualne odrzucamy rezerwacje
			if (nie_akt[j] == 0)
				break;
			if (j == (nr_w - 2))
				rez = 2;
		}
		int w_pol = 1;//indeks wybranej przez nas scie¿ki
		if (sciezki->s_next != NULL&&rez != 2)
		{//w przeciwnym wypadku wybór jest jeden
			printf("Wybierz poloczenie: ");
			for (int i = 1; i < nr_w; i++)
				printf("| %d ", i);
			printf("|\n");
			scanf("%d", &w_pol);
			if (nie_akt[w_pol - 1] == 1)
			{
				printf("Nie mo¿na wybrac nieaktualnej oferty.\n");
				w_pol = 0;
			}
			while (w_pol < 1 || w_pol >= nr_w)
			{
				printf("Wybierz istniejace poloczenie z przedzialu 1-%d: ", (nr_w - 1));
				scanf("%d", &w_pol);
				if (nie_akt[w_pol - 1] == 1)
				{
					printf("Nie mozna wybrac nieaktualnej oferty.\n");
					w_pol = 0;
				}
			}
			pom = sciezki;
			while (pom)
			{// do "pom" przypisujemy wybran¹ scie¿kê wylotu
				if (pom->nr == w_pol)
					break;
				pom = pom->s_next;
			}
		}
		else
		{
			pom = sciezki;
		}
		//lista mo¿liwych scie¿ek powrotu
		struct path *sciezki_p = NULL;
		struct path *pom_p = NULL;
		if (st == 2 && rez != 2)
		{//gdy istniej¹ warunki wylotu (czyli rez!=2) i warunek powrotu zosta³ wybrany
		 //analogiczne dzia³anie jak dla wylotu
			printf("POWROT\n");
			szukaj(tab, n, idok, iska, poloczenia, &sciezki_p);
			pom_p = sciezki_p;
			int nr_p = 1;

			while (pom_p) //petla wypisuj¹ca wyniki
			{
				pom_p->nr = nr_p++;//przypisujemy numer sciezki
				if (war_pow == 0)
				{
					wypisz_przeloty(&pom_p, pd, pm, pr, skad, &end, kls);
					if (end == 1)//tutaj problem nieaktualnoœci ju¿ nie powinien wyst¹piæ
					{
						end = 0;
						continue;
					}
					if (end == 2)
					{//powa¿ny b³ad braku pliku
						for (int i = 0; i < n; i++)
							free(tab[i]);
						free(tab);
						s_us(&sciezki);
						s_us(&sciezki_p);
						zwolnij_poloczenia(&poloczenia);
						return;
					}
				}
				else
				{
					wypisz_przeloty_wstecz(&pom_p, pd, pm, pr, skad, &end, p_godz, p_min, kls);
					if (end == 1)
					{
						end = 0;
						continue;
					}
					if (end == 2)
					{//powa¿ny b³ad braku pliku
						for (int i = 0; i < n; i++)
							free(tab[i]);
						free(tab);
						s_us(&sciezki);
						s_us(&sciezki_p);
						zwolnij_poloczenia(&poloczenia);
						return;
					}
				}
			}

			int p_pol = 1;//indeks wybieranej sicie¿ki powrotu
			if (sciezki_p->s_next != NULL)
			{//w przeciwnym wypadku wybór jest jeden
				printf("Wybierz poloczenie: ");
				for (int i = 1; i < nr_p; i++)
					printf("| %d ", i);
				printf("|\n");
				scanf("%d", &p_pol);
				while (p_pol < 1 || p_pol >= nr_p)
				{
					printf("Wybierz istniejace poloczenie z przedzialu 1-%d: ", (nr_p - 1));
					scanf("%d", &p_pol);
				}
				pom_p = sciezki_p;
				while (pom_p)
				{// do "pom_p" przypisujemy wybran¹ scie¿kê powrotu
					if (pom_p->nr == p_pol)
						break;
					pom_p = pom_p->s_next;
				}
			}
			else
			{
				pom_p = sciezki_p;
			}
		}
		while (rez != 1 && rez != 2)
		{
			printf("Wybierz:\n1 - Rezerwuj\n2 - Odrzuc\n");
			scanf("%d", &rez);
		}
		if (rez == 1)
		{
			//mallockujemy tablice pasa¿erów
			struct osoba *tab_osob = (struct osoba*)malloc(sizeof(struct osoba)*ils);
			int calkowita_cena = 0;//podliczamy ca³kowit¹ cenê
								   //Zbieramy dalsz¹ czêœæ danych od u¿ytkownika potrzebnych do dokonania rezerwacji
			printf("Wprowadz dane osobowe wszytskich pasazerow:\n");
			for (int i = 0; i < ils; i++)
			{
				int c = 0;
				if (st == 1)
					c = pom->cena;
				else
					c = pom->cena + pom_p->cena;
				printf("Wprowadz dane %d osoby:\nImie: ", (i + 1));
				scanf("%s", &(tab_osob[i].imie));
				printf("Nazwisko: ");
				scanf("%s", &(tab_osob[i].nazwisko));
				printf("Wiek: ");
				scanf("%d", &(tab_osob[i].wiek));
				if (tab_osob[i].wiek < 18)
				{//zni¿ka dla dzieci
					c = 0.8*c;
				}
				calkowita_cena += c;
			}
			printf("-----------------------------------------\nKOSZT CALKOWITY: %d zl\n", calkowita_cena);
			int tel, plat;
			char em[30];
			printf("Podaj dane kontaktowe:\nTelefon kotaktowy: +48");
			scanf("%d", &tel);
			while (tel < 100000000 || tel>999999999)
			{
				printf("Podaj prawid³owy numer telefonu: +48");
				scanf("%d", &tel);
			}
			printf("Adres e-mail: ");
			scanf("%s", &em);
			printf("Wybierz forme platnosci:\n1 - karta debetowa/kredytowa\n2 - przelew online\n3 - przelew tradycyjny\n");
			scanf("%d", &plat);
			while (plat != 1 && plat != 2 && plat != 3)
			{
				printf("Wybierz 1, 2 lub 3: ");
				scanf("%d", &plat);
			}
			printf("Dalsze informacje dotyczace platnosci zostana przekazane droga mailowa.\nDziekujemy za skorzystanie z naszych uslug.\n");
			//zebrane dane wpisujemy do dokumentu LISTA_REZERWACJI.txt
			wpisz(pom, pom_p, tab_osob, ils, tel, em, calkowita_cena);
			free(tab_osob);
		}
		//zwalniamy to co by³o zaalokowane
		for (int i = 0; i < n; i++)
			free(tab[i]);
		free(tab);
		s_us(&sciezki);
		s_us(&sciezki_p);
	}
}