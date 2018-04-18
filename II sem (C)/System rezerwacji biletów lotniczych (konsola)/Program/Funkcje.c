#include "Header.h"

void qpush(struct elq **head, int x)
{
	struct elq *nowy = (struct elq*)malloc(sizeof(struct elq));
	nowy->num = x;
	nowy->next = NULL;
	if ((*head) == NULL)
		*head = nowy;
	else
	{
		struct elq *pom = *head;
		while (pom->next != NULL)
			pom = pom->next;
		pom->next = nowy;
	}
}
int qpop(struct elq **head)
{//pobranie danej i usuniêcie
	if ((*head) == NULL)
	{
		printf("Error Q\n");
		return;
	}
	if ((*head)->next == NULL)
	{
		int tmp = (*head)->num;
		free(*head);
		*head = NULL;
		return tmp;
	}
	else
	{
		struct elq *pom = (*head)->next;
		int tmp = (*head)->num;
		free(*head);
		*head = pom;
		return tmp;
	}
}
int qempty(struct elq **head)
{
	if ((*head) == NULL)
		return 1;
	else
		return 0;
}

int **wypelnij(int **tab, int n, struct baza *head)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tab[i][j] = 0;
	FILE *plik = fopen("POLACZENIA.txt", "r");
	assert(!ferror(plik));
	while (!feof(plik))
	{
		char nazwa_s[15], nazwa_d[15];
		fscanf(plik, "%s %s", &nazwa_s, &nazwa_d);
		for (struct baza *home = head; home != NULL; home = home->next)
		{
			if (strcmp(home->nazwa, nazwa_s) == 0)
			{
				for (struct baza *away = head; away != NULL; away = away->next)
				{
					if (strcmp(away->nazwa, nazwa_d) == 0)
					{

						tab[home->id][away->id] = 1;
						break;
					}
				}
				break;
			}
		}
	}
	fclose(plik);
	return tab;
}

int wcz_baze(struct baza **head, char *nazwa)
{//zwraca ilosc wierzcho³ków grafu po³¹czeñ lub -1 jak nie znajdzie pliku po³¹czeñ
	FILE *plik = fopen(nazwa, "r");
	if (plik == NULL)
	{
		printf("Nie znaleziono podanego pliku.\n");
		return -1;
	}
	assert(!ferror(plik));
	int indx = 0;

	while (!feof(plik))
	{
		char nazwa_n[15], buff[15];
		fscanf(plik, "%s %s", &nazwa_n, &buff);

		if (*head == NULL)
		{
			struct baza *nowy = (struct baza*)malloc(sizeof(struct baza));
			nowy->id = indx++;
			strcpy(nowy->nazwa, nazwa_n);
			nowy->next = NULL;
			*head = nowy;
		}
		else
		{
			struct baza *pom = *head;
			while (pom->next != NULL)
			{
				if (strcmp(pom->nazwa, nazwa_n) == 0)
					break;
				else
					pom = pom->next;
			}
			if (pom->next == NULL)
			{
				if (strcmp(pom->nazwa, nazwa_n) == 0)
				{
					if (getc(plik) == '\n')
						continue;
					else
						break;
				}
				else
				{
					struct baza *nowy = (struct baza*)malloc(sizeof(struct baza));
					nowy->id = indx++;
					strcpy(nowy->nazwa, nazwa_n);
					nowy->next = NULL;
					pom->next = nowy;
				}
			}

		}
		if (getc(plik) == '\n')
			continue;
		else
			break;
	}
	fclose(plik);
	return indx;
}

void m_dod(struct lista **head, int ind, struct baza *g_baza)
{
	struct lista *nowy = (struct lista*)malloc(sizeof(struct lista));
	struct baza *pom = g_baza;
	for (pom; pom != NULL; pom = pom->next)
		if (pom->id == ind)
			break;//mamy wyszukany element o zadanym indeksie
	nowy->element = pom;
	nowy->next = *head;
	nowy->prev = NULL;
	if ((*head) != NULL)
	{
		(*head)->prev = nowy;
	}
	*head = nowy;
}
void s_dod(struct path **head)
{
	struct path *nowy = (struct path*)malloc(sizeof(struct path));
	nowy->m_elem = NULL; //dajemy NULL bo pózniej bêdziemy to dodawaæ funkcj¹ m_dod
						 // musimy dodawaæ na poczatêk bo funckjc¹ m_dod bêdziemy dodawaæ do g³owy
	nowy->s_next = *head;
	*head = nowy;
}

struct path *pob_sciezki(int *path, int n, int v, int **tab, struct baza *gbaza)
{
	struct path *s_head = NULL;
	int s = path[path[v]];
	if (s == -1)//bez przesiadki
	{
		s_dod(&s_head);
		m_dod(&s_head->m_elem, v, gbaza);
		m_dod(&s_head->m_elem, path[v], gbaza);
		//zwraca sciezke v, path[v]
	}
	else
	{
		if (path[s] == -1)// 1 przesiadka
		{
			for (int i = 0; i < n; i++)
			{
				if (path[i] == s && tab[i][v] == 1) //st¹d trzeba umieæ dolecieæ do v 
				{
					//zwraca sciezke v, i, path[i]
					s_dod(&s_head);
					m_dod(&s_head->m_elem, v, gbaza);
					m_dod(&s_head->m_elem, i, gbaza);
					m_dod(&s_head->m_elem, path[i], gbaza);
				}
			}
		}
		else
		{
			int t = path[path[s]];
			if (t == -1)
			{
				for (int i = 0; i < n; i++)
				{
					if (path[i] == s && tab[i][v] == 1)// st¹d trzeba umieæ dolecieæ do v  
					{
						for (int j = 0; j < n; j++)
						{
							if (path[j] == path[s] && tab[j][path[v]] == 1) // st¹d trzeba umieæ dolecieæ do path[v](st¹d dolatujemy do v)
							{
								//zwróæ sciezke v, i, j, path[j]?
								s_dod(&s_head);
								m_dod(&s_head->m_elem, v, gbaza);
								m_dod(&s_head->m_elem, i, gbaza);
								m_dod(&s_head->m_elem, j, gbaza);
								m_dod(&s_head->m_elem, path[j], gbaza);
							}
						}
					}
				}
			}
			else
			{//wiecej ni¿ 2 przesiadki
				printf("Zalecany wybor innego lotniska startowego.\n");
			}
		}
	}
	return s_head;

}
void szukaj(int **tab, int n, int p, int k, struct baza *hbaza, struct path **l_path)
{
	int *sciezka = (int*)malloc(sizeof(int)*n);
	struct elq *kolejka = NULL;
	int *visited = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
		visited[i] = 0;
	sciezka[p] = -1;
	qpush(&kolejka, p);
	visited[p] = 1;
	int znaleziono = 0;
	int v;
	while (!qempty(&kolejka))
	{
		v = qpop(&kolejka);
		if (v == k)
		{
			znaleziono = 1;
			break;
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (tab[v][i] == 1)//dla ka¿dego s¹siada
				{
					if (visited[i] == 1)//zabezpieczenie przed pêtla
						continue;
					sciezka[i] = v;//info sk¹d przyszliœmy
					qpush(&kolejka, i);
					visited[i] = 1;
				}
			}
		}
	}
	if (znaleziono)
	{
		*l_path = pob_sciezki(sciezka, n, v, tab, hbaza);
	}
	else
	{
		printf("Nie znaleziono poloczen"); //co nie powinno miec miejsca
	}
	//zwolnienie pamiêci
	free(sciezka);
	free(visited);
	while (!qempty(&kolejka))
		qpop(&kolejka);
}

void m_us(struct lista **head)
{
	while (*head)
	{
		struct baza *pom = (*head)->next;
		free(*head);
		*head = pom;
	}
}
void s_us(struct path **head)
{
	while (*head)
	{
		m_us(&(*head)->m_elem);
		struct baza *pom = (*head)->s_next;
		free(*head);
		*head = pom;
	}
}

void wyp_lotniska(struct baza *head)
{
	while (head)
	{
		printf("%s\n", head->nazwa);
		head = head->next;
	}
}
int ntoi(struct baza *head, char *nazwa, int *x)
{
	while (head)
	{
		if (strcmp(head->nazwa, nazwa) == 0)
			return head->id;
		head = head->next;
	}
	printf("Nie znaleziono podanego miasta.\n");
	*x = 1;
}

int spr_date(int d, int m, int r, int *end)
{
	if (d < 1 || m < 1 || r < 1)
	{
		*end = 1;
		printf("Blad daty.\n");
		return 2;
	}
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d > 31)
		{
			*end = 1;
			printf("Blad daty.\n");
			return 2;
		}
	}
	else
	{
		if (m == 2 && r % 4 == 0 && r % 100 != 0)
		{
			if (d > 29)
			{
				*end = 1;
				printf("Blad daty.\n");
				return 2;
			}
		}
		else
		{
			if (m == 2)
			{
				if (d > 28)
				{
					*end = 1;
					printf("Blad daty.\n");
					return 2;
				}
			}
			else
			{
				if (d > 30 || m > 12)
				{
					*end = 1;
					printf("Blad daty.\n");
					return 2;
				}
			}
		}
	}

	time_t czas;
	time(&czas); // pobiera czas kalendarzowy
	struct tm *data = localtime(&czas);
	int roznica_r = (r - 1900) - data->tm_year;
	if (data->tm_mon<5)
	{
		if (roznica_r > 0)
		{
			printf("W ofercie nie ma jeszcze lotow do zabukowania na ten okres.\nZa utrudnienia przepraszamy. Po dodatkowa pomoc prosimy dzwonic na numer infolinii: 688 234 696.");
			*end = 1;
			return 1;
		}
	}
	if (data->tm_mon >= 5)
	{
		if (roznica_r > 1 || (roznica_r == 1 && m >= 5)) // na rok do przodu mozna bukowac tylko
		{
			printf("W ofercie nie ma jeszcze lotow do zabukowania na ten okres.\nZa utrudnienia przepraszamy. Po dodatkowa pomoc prosimy dzwonic na numer infolinii: 688 234 696.");
			*end = 1;
			return 1;
		}
	}
	if ((r - 1900) < data->tm_year || ((r - 1900) == data->tm_year && (m - 1) < data->tm_mon) || ((r - 1900) == data->tm_year && (m - 1) == data->tm_mon && d <= data->tm_mday))
	{
		printf("Oferta nieaktualna.\n");
		*end = 1;
		return 1;
	}
	return 0;
}
int spr_godz(int g, int m)
{
	if (g > 23 || g < 0)
	{
		printf("Blad godziny.\n");
		return 1;
	}
	if (m > 59 || m < 0)
	{
		printf("Blad godziny.\n");
		return 1;
	}
	return 0;
}
int conv_data(int d, int m, int r)
{

	time_t czas;
	time(&czas); // pobiera czas kalendarzowy
	struct tm *data = localtime(&czas); // zamienia czas kalendarzowy na lokalny
	if ((r - 1900) < data->tm_year || ((r - 1900) == data->tm_year && (m - 1) < data->tm_mon) || ((r - 1900) == data->tm_year && (m - 1) == data->tm_mon && d <= data->tm_mday))
	{
		printf("Oferta nieaktualna.\n");
		return -1;
	}

	data->tm_year = r - 1900;
	data->tm_mon = m - 1;
	data->tm_mday = d;
	data->tm_isdst = 1;
	mktime(data);
	if (data->tm_wday == 0)
		data->tm_wday = 6;
	else
		data->tm_wday -= 1;

	return data->tm_wday;
}

int sz_rozk(char *s_nazwa, char *d_nazwa, int dz, int godz, int min, int **godz_wyl, int **godz_prz)
{
	int dod = 0;
	char *sn = (char*)malloc(sizeof(char) * 15);
	strncpy_s(sn, 15, s_nazwa, 15); //uwa¿ac na wyciek
	strncat_s(sn, 15, ".txt", 4);
	FILE *plik = fopen(sn, "r");
	if (plik == NULL)
	{
		printf("Nie znaleziono rozkladu dla miasta: %s\n", s_nazwa);
		free(sn);
		return -1;
	}
	assert(!ferror(plik));
	int *odlot;
	int *przylot;

	//to bedziemy przez referencje zwracac funkcja sz_godz
	int g_prog = godz, m_prog = min; //ten prog czasowy jest tylko dla dnia w którym bedziemy wylatywaæ, na przysz³y dzien mo¿emy lecieæ pierwszym
	while (1)
	{
		char name[15];
		fscanf(plik, "%s", &name);
		if (strcmp(name, d_nazwa) == 0) //sprawdzamy dokad lecimy
		{
			int dzen[7]; // wype³niamy tablice dni tygodnia, w których samolot kursuje
			int x = getc(plik);
			for (int i = 0; i < 7; i++)
				dzen[i] = 0;
			while (1)
			{
				x = getc(plik);
				if (x == 44)
					continue;
				if (x == 32)
					break;
				dzen[x - 48 - 1] = 1;
			}
			while (dz < 7)
			{
				if (dzen[dz] == 1)
				{
					if (sz_godz(plik, g_prog, m_prog, &odlot, &przylot) == 1)//znaleziono godziny odlotu
					{
						*godz_wyl = odlot;
						*godz_prz = przylot;
						fclose(plik);
						free(sn);
						return dod;
					}

				}// jak powyzsze warunki nie sa spe³nione to pêtla
				 //tutaj juz mamy pewne ze na przyszly dzien bedziemy leciec stad progi na 0
				g_prog = 0;
				m_prog = 0;
				dod++; // trzeba dodaæ kolejny dzieñ do daty wylotu
				if (dz == 6)
					dz = 0;
				else
					dz++;
			}
		}
		else
		{// przechodzimy do koñca linii aby sczytaæ nastêpn¹ nazwê miasta
			char c = getc(plik);
			while (c != '\n')
			{
				if (feof(plik))
				{
					fclose(plik);
					free(sn);
					printf("Nie znaleziono poloczenia.");// co nie powinno mieæ miejsca
					return 0;
				}
				c = getc(plik);
			}
		}
	}
}
int sz_rozk_wstecz(char *s_nazwa, char *d_nazwa, int dz, int godz, int min, int **godz_wyl, int **godz_prz)
{//funkcja zwraca ile dodaæ dni do dnia wylotu przy wyszukanej godzinie wylotu
	int ode = 0;
	char *sn = (char*)malloc(sizeof(char) * 15);
	strncpy_s(sn, 15, s_nazwa, 15); //uwa¿ac na wyciek
	strncat_s(sn, 15, ".txt", 4);
	FILE *plik = fopen(sn, "r");
	if (plik == NULL)
	{
		printf("Nie znaleziono rozkladu dla miasta: %s\n", s_nazwa);
		free(sn);
		return -1;
	}
	assert(!ferror(plik));
	int *odlot;
	int *przylot;

	// to bedziemy przez referencje zwracac funkcja sz_godz
	int g_prog = godz, m_prog = min; // ten prog czasowy jest tylko dla dnia w którym bedziemy wylatywaæ, na przysz³y dzien mo¿emy lecieæ pierwszym
	while (1)
	{
		char name[15];
		fscanf(plik, "%s", &name);
		if (strcmp(name, d_nazwa) == 0) //sprawdzamy dokad lecimy
		{
			int dzen[7];
			int x = getc(plik);
			for (int i = 0; i < 7; i++)
				dzen[i] = 0;
			while (1)
			{
				x = getc(plik);
				if (x == 44)
					continue;
				if (x == 32)
					break;
				dzen[x - 48 - 1] = 1;
			}
			while (dz >= 0)
			{
				if (dzen[dz] == 1)
				{
					if (sz_godz_wstecz(plik, g_prog, m_prog, &odlot, &przylot) == 1)//znaleziono godziny odlotu
					{
						*godz_wyl = odlot;
						*godz_prz = przylot;
						fclose(plik);
						free(sn);
						return ode;
					}

				}// jak powyzsze warunki nie sa spe³nione to pêtla
				 //tutaj juz mamy pewne ze na poprzedni dzien bedziemy leciec stad progi na 0
				g_prog = 23;
				m_prog = 59;
				ode++;
				if (dz == 0)
					dz = 6;
				else
					dz--;
			}
		}
		else
		{
			char c = getc(plik);
			while (c != '\n')
			{
				if (feof(plik))
				{
					fclose(plik);
					free(sn);
					printf("Nie znaleziono poloczenia.");
					return 0;
				}
				c = getc(plik);
			}
			//tutaj mamy c==\n czyli w nastepnym przejsciu petli sczytamy now¹ nazwê
		}
	}
}
int sz_godz(FILE *plik, int godz, int min, int *odlot[], int *przylot[])
{
	int wsk = 0; //zmienna która poinformuje nas o ile siê trzeba cofn¹æ zeby móc od nowa sczytywaæ godziny w nastepnym dniu
	int *odl = (int*)malloc(sizeof(int) * 2);
	int *prz = (int*)malloc(sizeof(int) * 2);
	char znak = getc(plik);
	while (znak != '\n')
	{
		if (isdigit(znak))
			fseek(plik, -1, SEEK_CUR);
		fscanf_s(plik, "%d:%d-%d:%d", &odl[0], &odl[1], &prz[0], &prz[1]);
		if (odl[0] > godz || (odl[0] == godz&&odl[1] > min))
		{
			*odlot = odl;
			*przylot = prz;
			return 1;
		}
		else
		{
			wsk++;
		}
		if (getc(plik) == EOF)
		{
			//jak siê nie znajdzie godziny to trzeba zwolnic zaalokowan¹ pamiêæ i cofn¹æ wskaŸnik
			fseek(plik, -(wsk * 12), SEEK_CUR);
			free(odl);
			free(prz);
			return 0;
		}
		fseek(plik, -1, SEEK_CUR);
		znak = getc(plik);
	}
	fseek(plik, -(1 + wsk * 12), SEEK_CUR);
	free(odl);
	free(prz);
	return 0;
}
int sz_godz_wstecz(FILE *plik, int godz, int min, int *odlot[], int *przylot[])
{
	int flaga = 0;
	int *odl = (int*)malloc(sizeof(int) * 2);
	int *prz = (int*)malloc(sizeof(int) * 2);
	char znak = getc(plik);
	while (1)
	{
		znak = getc(plik);
		//przejechalismy na koniec linijki
		if (feof(plik) != 0)
		{
			fseek(plik, -12, SEEK_END);
			znak = getc(plik);// jak jest tylko jedna godzina w linijce
			if (znak == ' ')
				flaga = 1;
			break;
		}
		if (znak == '\n')
		{
			fseek(plik, -14, SEEK_CUR);
			znak = getc(plik);
			if (znak == ' ')
				flaga = 1;
			break;
		}
	}
	while (1)
	{
		//sczytujemy od konca
		fscanf_s(plik, "%d:%d-%d:%d", &odl[0], &odl[1], &prz[0], &prz[1]);
		if (prz[0] < godz || (prz[0] == godz&&prz[1] < min))
		{
			*odlot = odl;
			*przylot = prz;
			return 1;
		}
		if (flaga)
			break;
		fseek(plik, -24, SEEK_CUR);//po sczytaniu cofiemy sie do kolejnego sczytania
		znak = getc(plik);
		if (znak == ' ')// jak dojdziemy do spacji to znaczy ze nie ma juz wiecej godzi wylotu
			flaga = 1; // ale musimy jeszcze sprawdziæ ostatni¹ wartoœæ, st¹d flaga
	}
	fseek(plik, -2, SEEK_CUR);
	free(odl);// jak nie znajdziemy trzeba zwolnic pamiec
	free(prz);
	return 0;
}

int porownaj_date(int wyl_d, int wyl_m, int wyl_r, int prz_d, int prz_m, int prz_r)
{
	int rwyl = wyl_r - 2017;
	int rprz = prz_r - 2017;
	int wylot = rwyl * 365;
	int przylot = rprz * 365;
	for (int i = 1; i < wyl_m; i++)
	{
		if (i == 4 || i == 6 || i == 9 || i == 11)
			wylot += 30;
		else
		{
			if (i == 2 && wyl_r % 4 == 0 && wyl_r % 100 != 0)
				wylot += 29;
			else
			{
				if (i == 2)
					wylot += 28;
				else
					wylot += 31;
			}
		}
	}
	for (int i = 1; i < prz_m; i++)
	{
		if (i == 4 || i == 6 || i == 9 || i == 11)
			przylot += 30;
		else
		{
			if (i == 2 && prz_r % 4 == 0 && prz_r % 100 != 0)
				przylot += 29;
			else
			{
				if (i == 2)
					przylot += 28;
				else
					przylot += 31;
			}
		}
	}
	wylot += wyl_d;
	przylot += prz_d;
	if (wylot < przylot)
		return 0;
	else
		return 1;
}
int *inc_data(int tab[], int x)
{
	int dni = tab[0] + x;
	if (tab[1] == 12)//je¿eli koniec roku
	{
		if (dni > 31)
		{
			tab[0] = dni - 31;
			tab[1] = 1;
			tab[2]++;
			return tab;
		}
	}
	if (tab[1] == 4 || tab[1] == 6 || tab[1] == 9 || tab[1] == 11) // miesiace 30-sto dniowe
	{
		if (dni > 30)
		{
			tab[0] = dni - 30;
			tab[1]++;
			return tab;
		}
	}
	else
	{
		if (tab[1] == 2 && tab[2] % 4 == 0 && tab[2] % 100 != 0) //przestepny w lutym
		{
			if (dni > 29)
			{
				tab[0] = dni - 29;
				tab[1]++;
				return tab;
			}
		}
		else
		{
			if (tab[1] == 2)// nie przestepny
			{
				if (dni > 28)
				{
					tab[0] = dni - 28;
					tab[1]++;
					return tab;
				}
			}
			else// miesiace 31-dniowe
			{
				if (dni > 31)
				{
					tab[0] = dni - 31;
					tab[1]++;
					return tab;
				}
			}
		}
	}
	tab[0] = dni;
	return tab;
}
int *dec_data(int tab[], int x)
{
	int dni = tab[0] - x;
	if (tab[1] == 1)//je¿eli poczatek roku
	{
		if (dni < 1)
		{
			tab[0] = 31 + dni;
			tab[1] = 12;
			tab[2]--;
			return tab;
		}
	}
	if (tab[1] == 5 || tab[1] == 7 || tab[1] == 10 || tab[1] == 12) // miesiace 30-sto dniowe
	{
		if (dni < 1)
		{
			tab[0] = 30 + dni;
			tab[1]--;
			return tab;
		}
	}
	else
	{
		if (tab[1] == 3 && tab[2] % 4 == 0 && tab[2] % 100 != 0) //przestepny w lutym
		{
			if (dni < 1)
			{
				tab[0] = 29 + dni;
				tab[1]--;
				return tab;
			}
		}
		else
		{
			if (tab[1] == 3)// nie przestepny
			{
				if (dni < 1)
				{
					tab[0] = 28 + dni;
					tab[1]--;
					return tab;
				}
			}
			else// miesiace 31-dniowe
			{
				if (dni < 1)
				{
					tab[0] = 31 + dni;
					tab[1]--;
					return tab;
				}
			}
		}
	}
	tab[0] = dni;
	return tab;
}
void uzupelnij(struct lista **element, int gw, int mw, int gp, int mp, int d, int m, int r)
{
	(*element)->g_wyl[0] = gw;
	(*element)->g_wyl[1] = mw;
	(*element)->g_prz[0] = gp;
	(*element)->g_prz[1] = mp;
	(*element)->data[0] = d;
	(*element)->data[1] = m;
	(*element)->data[2] = r;
}

void wypisz_przeloty(struct path **sciezki, int d, int m, int r, char *miasto_docelowe, int *zamknij, int kl)
{
	//dla ka¿dej nowej sciezki dane sie musz¹ odnowiæ
	int data_w[3];
	data_w[0] = d;
	data_w[1] = m;
	data_w[2] = r;
	int h[2] = { 0,0 }; // to s¹ te co dostaje funkcja na wejscie
	int *h_wyl, *h_prz; // to sa te co oddaje funkcja na wyjsciu
	printf("(%d) ", (*sciezki)->nr);
	struct lista *m_pom = (*sciezki)->m_elem;
	while (m_pom->next)
	{

		int dz_tyg = conv_data(data_w[0], data_w[1], data_w[2]);
		if (dz_tyg < 0)
		{
			*zamknij = 1;
			(*sciezki) = (*sciezki)->s_next;
			return;
		}
		int dod_date = sz_rozk(m_pom->element->nazwa, m_pom->next->element->nazwa, dz_tyg, h[0], h[1], &h_wyl, &h_prz);//podajemy nazwê miasta satrtowego i nastêpnego w sciezce czyli docelowego
		if (dod_date == -1)
		{//powa¿ny b³ad braku pliku rozk³adu dla danego miasta
			*zamknij = 2;
			return;
		}
		inc_data(&data_w, dod_date);
		printf("%s: %02d:%02d - %02d:%02d, %02d-%02d-%d -> ", m_pom->element->nazwa, h_wyl[0], h_wyl[1], h_prz[0], h_prz[1], data_w[0], data_w[1], data_w[2]);
		uzupelnij(&m_pom, h_wyl[0], h_wyl[1], h_prz[0], h_prz[1], data_w[0], data_w[1], data_w[2]);
		free(h_wyl);
		h[0] = h_prz[0];
		h[1] = h_prz[1];
		free(h_prz);
		dz_tyg = conv_data(data_w[0], data_w[1], data_w[2]);
		if (dz_tyg < 0)
		{
			*zamknij = 1;
			(*sciezki) = (*sciezki)->s_next;
			return;
		}
		m_pom = m_pom->next;
	}
	int cn = ustal_cene((*sciezki)->m_elem, kl);
	(*sciezki)->cena = cn;
	printf("%s, cena biletu: %d zl\n", miasto_docelowe, cn);
	(*sciezki) = (*sciezki)->s_next;
}
void wypisz_przeloty_wstecz(struct path **sciezki, int d, int m, int r, char *miasto_docelowe, int *zamknij, int h_p, int m_p, int kl)
{
	//dla ka¿dej nowej sciezki dane sie musz¹ odnowiæ
	int data_w[3];
	data_w[0] = d;
	data_w[1] = m;
	data_w[2] = r;
	int h[2];
	h[0] = h_p;
	h[1] = m_p; // to s¹ te co dostaje funkcja na wejscie
	int *h_wyl, *h_prz; // to sa te co oddaje funkcja na wyjsciu
	printf("(%d) ", (*sciezki)->nr);
	struct lista *m_pom = (*sciezki)->m_elem;
	while (m_pom->next)
		m_pom = m_pom->next;//tutaj jesteœmy na koñcu sciezki
	while (m_pom->prev)
	{

		int dz_tyg = conv_data(data_w[0], data_w[1], data_w[2]);
		if (dz_tyg < 0)
		{
			*zamknij = 1;
			(*sciezki) = (*sciezki)->s_next;
			return;
		}
		int ode_date = sz_rozk_wstecz(m_pom->prev->element->nazwa, m_pom->element->nazwa, dz_tyg, h[0], h[1], &h_wyl, &h_prz);
		if (ode_date == -1)
		{
			*zamknij = 2;
			return;
		}
		dec_data(&data_w, ode_date);
		uzupelnij(&m_pom->prev, h_wyl[0], h_wyl[1], h_prz[0], h_prz[1], data_w[0], data_w[1], data_w[2]); //uzupe³niamy od przedostatniego miasta bo ostatnie nie ma wylotu
																										  //najpierw uzupe³niamy od ty³u a pózniej wypisujemy
		free(h_prz);
		h[0] = h_wyl[0];
		h[1] = h_wyl[1];
		free(h_wyl);
		dz_tyg = conv_data(data_w[0], data_w[1], data_w[2]); // jak siê za bardzo cofnie to wypisze ¿e oferta nieaktualna
		if (dz_tyg < 0)
		{
			*zamknij = 1;
			(*sciezki) = (*sciezki)->s_next;
			return;
		}
		m_pom = m_pom->prev;
	}
	m_pom = (*sciezki)->m_elem;
	while (m_pom->next)//wypisujemy w odpowiedniej kolejnoœci
	{
		printf("%s: %02d:%02d - %02d:%02d, %02d-%02d-%d -> ", m_pom->element->nazwa, m_pom->g_wyl[0], m_pom->g_wyl[1], m_pom->g_prz[0], m_pom->g_prz[1], m_pom->data[0], m_pom->data[1], m_pom->data[2]);
		m_pom = m_pom->next;
	}
	int cn = ustal_cene((*sciezki)->m_elem, kl);
	(*sciezki)->cena = cn;
	printf("%s, cena biletu: %d zl\n", miasto_docelowe, cn);
	(*sciezki) = (*sciezki)->s_next;
}

void wpisz(struct path *wyl, struct path *pow, struct osoba *tos, int il, int tl, int em, int cn)
{
	struct lista *wylot = wyl->m_elem;
	FILE *plik = fopen("LISTA_REZERWACJI.txt", "a");
	while (wylot->next)
	{
		fprintf(plik, "%s: %02d-%02d-%d, %02d:%02d-%02d:%02d -> ", wylot->element->nazwa, wylot->data[0], wylot->data[1], wylot->data[2], wylot->g_wyl[0], wylot->g_wyl[1], wylot->g_prz[0], wylot->g_prz[1]);
		wylot = wylot->next;
	}
	fprintf(plik, "%s", wylot->element->nazwa);
	if (pow != NULL)
	{
		fprintf(plik, "\n + POWROT\n");
		struct lista *powrot = pow->m_elem;
		while (powrot->next)
		{
			fprintf(plik, "%s: %02d-%02d-%d, %02d:%02d-%02d:%02d -> ", powrot->element->nazwa, powrot->data[0], powrot->data[1], powrot->data[2], powrot->g_wyl[0], powrot->g_wyl[1], powrot->g_prz[0], powrot->g_prz[1]);
			powrot = powrot->next;
		}
		fprintf(plik, "%s", powrot->element->nazwa);
	}
	fprintf(plik, "\n%d osoba/y:", il);
	int i = 0;
	while (i<il)
	{
		fprintf(plik, " %s %s (%d),", tos[i].imie, tos[i].nazwisko, tos[i].wiek);
		i++;
	}
	fprintf(plik, "\nKontakt: tel: %d e-mail: %s KOSZT: %d\n\n", tl, em, cn);
	fclose(plik);
}

int ustal_cene(struct lista *head, int klasa)
{
	int cena = 50; //wartosc bazowa ceny
	int czas = 0, r_min = 0, r_godz = 0, r = 0;
	//wyznaczamy ca³kowity czas lotu, który przeliczamy na cenê
	while (head->next)
	{
		r_godz = head->g_prz[0] - head->g_wyl[0];
		r_min = head->g_prz[1] - head->g_wyl[1];
		r = (r_godz * 60) + r_min;
		czas += r;
		head = head->next;
	}
	cena += czas;
	switch (klasa)
	{
	case 1:
		break;

	case 2:
		cena = 0.89*cena;
		break;
	case 3:
		cena = 1.46*cena;
		break;
	}//innej wartosci nie mo¿e byæ, wyparsowane
	return cena;
}

void zwolnij_poloczenia(struct baza **head)
{
	while (*head)
	{
		struct baza *pom = (*head)->next;
		free(*head);
		*head = pom;
	}
}
