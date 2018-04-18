#include<iostream>
#include<fstream>
#include<string>
using namespace std;
bool sprawdzenie(int n, char*T[])// W przypadku braku podania jakichkolwiek danych
{
	if (n < 2) 
	{
		cerr << "Uzyj: -> " << T[0] << " -h <- w celu uzyskania pomocy" << endl;
		return true;
	}
	else
		return false;
}
bool pomoc(int n, char*T[])//wyswietla pomoc po przelaczniku -h
{
	for (int i = 1; i < n; i++) 
	{
		if (string(T[i]) == "-h")
		{
			cout << "POMOC: \nProgram sluzy do wyszukiwania Najdluzszego Wspolnego Podciagu dwoch wyrazow.\n\nAby program wykonal poprawnie swoje zadanie w kazdej\nlini pliku wejsciowego musza znajdowac sie 2 wyrazy\ndo porownania, w przypadku nieprawidlowo wprowadzonych\ndanych w pliku zostaniesz poinformowany o tym co jest\nnie tak.\n\nProgram korzysta z pliku wejsciowego ktory powinien\nzawierac slowa do porownania zapisane w jednej lini\nLini w pliku moze byc dowolna ilosc.\n\nPraca programu zostaje zapisana do pliku wyjsciowego\n\nAby program zadzialal zastosuj sie do ponizszej reguly\n";
			cout << endl;
			cerr << "Uzyj: -> " << T[0] << " -i <nazwa_pliku_do_otwarcia> -o <nazwa_pliku_do_zapisu>" << endl;
			return true;
		}
		else
			return false;
	}
}
bool za_malo_arg(int n, char*T[])// wy�witlanie pomoc gdy podano za ma�� ilo�� danych wej�ciowych
{
	if (n < 5) 
	{
		cerr << "Uzyj: -> " << T[0] << " -i <nazwa_pliku_do_otwarcia> -o <nazwa_pliku_do_zapisu>" << endl;
		return true;
	}
	else
		return false;
}
string przelacznik(int n, char*T[],string symbol)//pobieranie pliku wejsciowego/wyjsciowego z konsoli 
{
	string nazwa;
	for (int i = 1; i < n; i++)
	{
		if (string(T[i]) == symbol) 
		{
			if (i + 1 < n)
			{
				nazwa = T[++i];
			}
			else
			{
				cout << "Podaj nazwe pliku do otwarcia po przelaczniku: -> "<<symbol<<" <nazwa_pliku_do_otwarcia>" << endl;
				nazwa = "quit";
			}
			break;
		}
		else
			if ((i + 1) == n)
			{
				cout << "Uzyj przelacznika wejscia: -> "<<symbol<<" <nazwa_pliku_do_odczytu>" << endl;
				nazwa = "quit";
			}
	}
	return nazwa;
}
void wykonanie_algorytmu(const string &X, const string &Y,fstream &nowy)
{
	/*WYKONANIE ALGORYTMU:
	Zasada dzia�ania algorytmu polega na tym, �e tworzymy tak jakby tablic� dwuwymiarow�
	z dw�ch s�ow do por�wnania, "g��wny" rz�d tworz� znaki pierwszego s�owa a "g��wn�"
	kolumn� znaki drugiego s�owa. Natomiast tablica b�dzie wype�aniana liczbami. Je�eli
	w kt�rym� momencie element kolumny i rz�du bed� sobie r�wne dojdzie do zasygnalizowania,
	�e istnieje element Najd�u�szego Wsp�lnego Podci�gu, sygnalizowane to odb�dzie si� za
	pomoc� inkrementacji, gdy� tak najlepiej zrobi� to w tablicy liczbowej. Inkrementowana
	b�dzie kom�rka po�o�ona na prawo-w d� od tej w kt�rej odbywa si� akcja, gdy� po
	kom�rkach b�dziemy si� porusza� w prawo i w d�. W ten spos�b otrzymamy d�ugo�� NWP.
	Odczytanie jego warto�ci odb�dzie si� w analogiczny spos�b tylko od ty�u. Ustawimy
	si� na samym dole po prawej stronie tablicy i zaczniemy zczytywa� elementy. Je�eli
	element z "g��wnej" kolumny b�dzie si� r�wna� elementowi z "g�ownego" rz�du spiszemy
	jego warto��, natomiast, je�eli nie b�d� sobie r�wne to b�dziemy si� poruszali w lewo
	lub w g�r�. W ten spos�b otrzymamy warto�� NWP, a w niekt�rych przypadkach nawet 2 r�ne
	warto�ci, gdy� zale�e� to b�dzie od tego czy naszym g�ownym kierunkiem przy zczytywaniu
	b�dzie g�ra czy lewo. Wi�cej szczeg��w opisanych jest przy poszczeg�lnych etapach.*/

	//zmienne pomocnicze do wykonania algorytmu, nadanie im wartosci zczytanych z pliku wejsciowego
	string A, B;
	A = X; //slowo[0];
	B = Y; // slowo[1];

	// utworzenie dynamicznej tablicy dwuwymiarowej

	int m = A.size();
	int n = B.size();
	int **T = new int *[m + 1];
	for (int g = 0; g < (m + 1); g++)
		T[g] = new int[n + 1];

	/*[m+1] i [n+1] te +1 wzie�y si� z tego powodu,
	�e musimy doda� na pocz�tek po jednym wersie i kolumnie wype�nionych zerami*/

	/*Teraz wype�animy pierwszy wers i pierwsz� kolumn� zerami,
	Jest to nam potrzebne gdy� p�zniej b�dziemy zwi�kszali kolejne
	kratki o 1 je�li znak b�dzie si� r�wna�, dlatego potrzebujemy tych 0
	�eby mie� do czego dodawa�*/

	for (int i = 0; i < (m + 1); i++)
		T[i][0] = 0;
	for (int j = 0; j < (n + 1); j++)
		T[0][j] = 0;

	/*Reszt� tablicy wype�niamy d�ugo�ciami Najd�u�szego Wspolnego Dzielnika,
	tak jak by�o to opisane powy�ej. Je�eli znak z "g��wnej" kolumny i znak z
	"g��wnego" rzedu nie r�wnaj� si� to spisujemy warto�� wi�ksz� z lewego lub
	g�rnego s�siedztwa (wi�ksz� gdy� szukamy najd�uzszego wsp�lnego podci�gu),
	lecz nie zwi�kszamy warto�ci NWP bo znaki nie by�y takie same (po prostu
	zapamietujemy sobie jego warto�� w danym momencie, aby m�c p�zniej dodawa�
	do tej warto�ci	kolejne jedynki gdy znaki b�d� takie same)*/

	for (int i = 0; i<m; i++)				//Tu jak i linijk� ni�ej pracujemy na  indeksach ci�g�w A i B
		for (int j = 0; j<n; j++)		//wi�c ich rozmiary wygl�daj� nast�pujaco [0,1,...,m-1]
		{
			if (A[i] == B[j])
				T[i + 1][j + 1] = T[i][j] + 1;					 //Tutaj znowu s� +1 bo parcujemy na indeksach tablicy T
			else											 //kt�re wygl�daj� nast�puj�co [0,1,...,m]:[0,1,...n]
			{
				if (T[i + 1][j] >= T[i][j + 1])
					T[i + 1][j + 1] = T[i + 1][j];
				else
					T[i + 1][j + 1] = T[i][j + 1];
			}
		}

	//w ten spos�b uzyskali�my w kom�rce T[m][n] d�ugo�c NWP

	//Zczytywanie warto�ci NWP

	//Post�pujemy analogicznie tylko �e od ty�u

	string wynik1 = "", wynik2 = "";		//Trzeba nada� warto�� pocz�tkow� �eby mie� do czego dodawa�
	int i = (m - 1), j = (n - 1);	//Zczytywanie nast�pi od ty�u wi�c rozpoczynamy od ostatnich indeks�w
	while ((i >= 0) && (j >= 0))	//-1 wyst�pi�y dlatego �e znow pracujemy na indeksach A i B a nie T.
	{
		if (A[i] == B[j])
		{
			wynik1 = A[i] + wynik1; // Przypisuj� warto�� elementu gdzy znaki si� zgadzaj� i przesuwamy si� 
			i--;				  // Po skosie do g�ry w lewo gdy� tak zapisywali�my warot�ci NWP
			j--;				  // Tam musi znajdowa� si� warto�� NWP o jeden mniejsza
		}
		else
		{
			if (T[i + 1][j + 1] == T[i][j + 1]) // Gdy znaki sie nie zgadzaj� przesuwam si� tam gdzie wyst�pi ta sama
				i--;					  // warto�� co do elementu w kt�rym si� znajdujemy (gdy� wtedy w�drujemy
			else						  // tym samym (najd�uzszym) podci�giem. St�d wynika �e moga wystepowa� wi�cej
				j--;					  // ni� jeden najd�u�szy wsp�lny podci�g
		}
	}
	i = (m - 1), j = (n - 1);
	while ((i >= 0) && (j >= 0))		  // Dla drugiego przypadku NWP
	{
		if (A[i] == B[j])
		{
			wynik2 = A[i] + wynik2;
			i--;
			j--;
		}
		else
		{
			if (T[i + 1][j + 1] == T[i + 1][j])
				j--;
			else
				i--;
		}
	}
	if (wynik1 == "")//przypadek w kt�rym dla dw�ch pobranych s�ow nie wyst�pi NWP
	{
		nowy << "Podane wyrazy nie maja wspolnego podciagu" << endl;
	}
	else
	{
		if (wynik1 == wynik2)
		{
			nowy << "Najdluzszy wspolny podciag ma postac: " << wynik1 << endl; //przypadek gdy NWP b�dzie mia� tylko jedn� posta�
		}
		else
			nowy << "Najdluzszy wspolny podciag ma postaci: " << wynik1 << ", " << wynik2 << endl; //przypadek gdy NWP b�dzie mia� 2 r�ne postacie
	}
}
int main(int argc, char*argv[])
{
	if (sprawdzenie(argc, argv))
		return 1;

	if (pomoc(argc, argv))
		return 1;

	if (za_malo_arg(argc, argv))
		return 1;
		
	// pobieranie danych z konsoli

	string input, output; //nazwy plik�w kolejno do odczytu i zapisu
	
	if (przelacznik(argc, argv, "-i") == "quit")
		return 1;
	else
		input = przelacznik(argc, argv, "-i");

	if (przelacznik(argc, argv, "-o") == "quit")
		return 1;
	else
		output = przelacznik(argc, argv, "-o");

	
	if (input == output) // wyeliminowanie przypadku gdzy podamy ten sam plik jako do odczytu i zapisu
	{
		cout << "Nie mozna zapisac wyniku do pliku wejscia!";
		return 1;
	}

	//operacje na plikach

	fstream plik, nowy; //zadaklarowanie plik�w na ktorych bedziemy pracowac
	plik.open(input, ios::in);
	if (plik.good() == 1) //sprawdzenie czy uzyskali�my dostep do pliku wejsciowego
		cout << "Uzyskano dostep" << endl;
	else
	{
		cout << "Nie znaleziono pliku o nazwie: " << input << endl;
		return 1;
	}
	nowy.open(output, ios::out);
	if (nowy.good() != 1) //sprawdzenie czy mamy wystarczaj�c� ilo�� pami�ci do utworzenia pliku wyj�ciowego
	{
		cout << "Blad z alokacja pamieci dla pliku wyjsciowego" << endl;
		return 1;
	}

	//zmienne pomocnicze przy przeszukiwaniu pliku wejsciowego
	string slowo[3]; //tablica s��w kt�re b�dziemy por�wnywa�
	string dane = ""; //s�u�y tylko do przemieszczania sie po pliku (gdy chccemy przejsc do nastepnej lini a nie wiemy ile jeszcze jest s��w w lini, a jak sprawdzili�my �e jest ich wi�cej ni� 2 to getline'ujemy ca�� lini� i przechodzimy do nast�pnej
	char znak; //g��wna jednostka poruszania sie po tekscie pliku
	int p = 0; //zmienna liczbowa b�dzie nam sygnalizowa�a czy mamy juz odpowiedni� ilo�� s��w do por�wnania

	//p�tla wybierajaca do kt�rej lini w pliku wykona� algorytm

	while (plik >> noskipws >> znak) //korzystamy z takiej funkcji gdyz eof mi nie dzia�a� zawsze :(
	{
		if (p < 2)
		{
			if (znak == '\n') //przypadek gdy w lini jest za ma�o s��w
			{
				nowy << "Za malo slow w lini" << endl;
				p = 0;
				for (int k = 0; k < 3; k++)
					slowo[k] = "";
				continue;
			}
			else
			{
				if (znak == ' ') // spacje uwzgl�dniamy ale przy sczytywaniu znak�w s�owa pomijamy
				{
					continue;
				}
				else
				{
					plik.seekg(-1, ios_base::cur); //pobranie s��w
					plik >> slowo[p++];
				}
			}
		}
		else
		{

			if (znak == '\n') //przypadek gdy w lini sa 2 s�owa, czyli odpowiednia ilo��
			{
				wykonanie_algorytmu(slowo[0], slowo[1], nowy);
				p = 0;
				for (int k = 0; k < 3; k++)
					slowo[k] = "";
				continue; // je�eli znale�li�my jeden wsp�lny podci�g umo�liwiamy programowi znalezienie kolejnych
			}
			else
			{
				if (znak == ' ')
					continue;
				else //w lini po dw�ch znalezionych s�owach wyst�pi kolejny znak nie bed�cy ani spacj� ani przej�ciem do nowej lini, co oznacza wyst�pienie kolejnego wyrazu, tak�e paramerty programu nie zosta�y spe�nione, wi�c informujemy u�ytkownika co zrobi� nie tak
				{
					nowy << "Za duzo slow w lini" << endl;
					getline(plik, dane); //przesuwamy si� do ko�ca lini
					p = 0;
					dane = "";
					for (int j = 0; j < 3; j++)
						slowo[j] = "";
					continue;
				}
			}

		}
	}
	if (p > 0) // wykonanie dla ostatniej lini jezeli w takowej co� wyst�pi�o
	{		   // gdy� funkcja sczyta�a nam te warto�ci ale gdy dosz�a do ko�ca pliku zako�czy�a p�tl�
		if (p == 2) //wykonanie algorytmu
		{
			wykonanie_algorytmu(slowo[0], slowo[1], nowy);
		} 
		else // gdy sczytano tylko jedno s�owo
			nowy << "Za malo slow w lini" << endl;
	}
	plik.close();//zamkniecie plik�w
	nowy.close();
	return 0;
}