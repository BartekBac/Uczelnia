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
bool za_malo_arg(int n, char*T[])// wyœwitlanie pomoc gdy podano za ma³¹ iloœæ danych wejœciowych
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
	Zasada dzia³ania algorytmu polega na tym, ¿e tworzymy tak jakby tablicê dwuwymiarow¹
	z dwóch s³ow do porównania, "g³ówny" rz¹d tworz¹ znaki pierwszego s³owa a "g³ówn¹"
	kolumnê znaki drugiego s³owa. Natomiast tablica bêdzie wype³aniana liczbami. Je¿eli
	w którymœ momencie element kolumny i rzêdu bed¹ sobie równe dojdzie do zasygnalizowania,
	¿e istnieje element Najd³u¿szego Wspólnego Podci¹gu, sygnalizowane to odbêdzie siê za
	pomoc¹ inkrementacji, gdy¿ tak najlepiej zrobiæ to w tablicy liczbowej. Inkrementowana
	bêdzie komórka po³o¿ona na prawo-w dó³ od tej w której odbywa siê akcja, gdy¿ po
	komórkach bêdziemy siê poruszaæ w prawo i w dó³. W ten sposób otrzymamy d³ugoœæ NWP.
	Odczytanie jego wartoœci odbêdzie siê w analogiczny sposób tylko od ty³u. Ustawimy
	siê na samym dole po prawej stronie tablicy i zaczniemy zczytywaæ elementy. Je¿eli
	element z "g³ównej" kolumny bêdzie siê równa³ elementowi z "g³ownego" rzêdu spiszemy
	jego wartoœæ, natomiast, je¿eli nie bêd¹ sobie równe to bêdziemy siê poruszali w lewo
	lub w górê. W ten sposób otrzymamy wartoœæ NWP, a w niektórych przypadkach nawet 2 ró¿ne
	wartoœci, gdy¿ zale¿eæ to bêdzie od tego czy naszym g³ownym kierunkiem przy zczytywaniu
	bêdzie góra czy lewo. Wiêcej szczegó³ów opisanych jest przy poszczególnych etapach.*/

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

	/*[m+1] i [n+1] te +1 wzie³y siê z tego powodu,
	¿e musimy dodaæ na pocz¹tek po jednym wersie i kolumnie wype³nionych zerami*/

	/*Teraz wype³animy pierwszy wers i pierwsz¹ kolumnê zerami,
	Jest to nam potrzebne gdy¿ pózniej bêdziemy zwiêkszali kolejne
	kratki o 1 jeœli znak bêdzie siê równa³, dlatego potrzebujemy tych 0
	¿eby mieæ do czego dodawaæ*/

	for (int i = 0; i < (m + 1); i++)
		T[i][0] = 0;
	for (int j = 0; j < (n + 1); j++)
		T[0][j] = 0;

	/*Resztê tablicy wype³niamy d³ugoœciami Najd³u¿szego Wspolnego Dzielnika,
	tak jak by³o to opisane powy¿ej. Je¿eli znak z "g³ównej" kolumny i znak z
	"g³ównego" rzedu nie równaj¹ siê to spisujemy wartoœæ wiêksz¹ z lewego lub
	górnego s¹siedztwa (wiêksz¹ gdy¿ szukamy najd³uzszego wspólnego podci¹gu),
	lecz nie zwiêkszamy wartoœci NWP bo znaki nie by³y takie same (po prostu
	zapamietujemy sobie jego wartoœæ w danym momencie, aby móc pózniej dodawaæ
	do tej wartoœci	kolejne jedynki gdy znaki bêd¹ takie same)*/

	for (int i = 0; i<m; i++)				//Tu jak i linijkê ni¿ej pracujemy na  indeksach ci¹gów A i B
		for (int j = 0; j<n; j++)		//wiêc ich rozmiary wygl¹daj¹ nastêpujaco [0,1,...,m-1]
		{
			if (A[i] == B[j])
				T[i + 1][j + 1] = T[i][j] + 1;					 //Tutaj znowu s¹ +1 bo parcujemy na indeksach tablicy T
			else											 //które wygl¹daj¹ nastêpuj¹co [0,1,...,m]:[0,1,...n]
			{
				if (T[i + 1][j] >= T[i][j + 1])
					T[i + 1][j + 1] = T[i + 1][j];
				else
					T[i + 1][j + 1] = T[i][j + 1];
			}
		}

	//w ten sposób uzyskaliœmy w komórce T[m][n] d³ugoœc NWP

	//Zczytywanie wartoœci NWP

	//Postêpujemy analogicznie tylko ¿e od ty³u

	string wynik1 = "", wynik2 = "";		//Trzeba nadaæ wartoœæ pocz¹tkow¹ ¿eby mieæ do czego dodawaæ
	int i = (m - 1), j = (n - 1);	//Zczytywanie nast¹pi od ty³u wiêc rozpoczynamy od ostatnich indeksów
	while ((i >= 0) && (j >= 0))	//-1 wyst¹pi³y dlatego ¿e znow pracujemy na indeksach A i B a nie T.
	{
		if (A[i] == B[j])
		{
			wynik1 = A[i] + wynik1; // Przypisujê wartoœæ elementu gdzy znaki siê zgadzaj¹ i przesuwamy siê 
			i--;				  // Po skosie do góry w lewo gdy¿ tak zapisywaliœmy warotœci NWP
			j--;				  // Tam musi znajdowaæ siê wartoœæ NWP o jeden mniejsza
		}
		else
		{
			if (T[i + 1][j + 1] == T[i][j + 1]) // Gdy znaki sie nie zgadzaj¹ przesuwam siê tam gdzie wyst¹pi ta sama
				i--;					  // wartoœæ co do elementu w którym siê znajdujemy (gdy¿ wtedy wêdrujemy
			else						  // tym samym (najd³uzszym) podci¹giem. St¹d wynika ¿e moga wystepowaæ wiêcej
				j--;					  // ni¿ jeden najd³u¿szy wspólny podci¹g
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
	if (wynik1 == "")//przypadek w którym dla dwóch pobranych s³ow nie wyst¹pi NWP
	{
		nowy << "Podane wyrazy nie maja wspolnego podciagu" << endl;
	}
	else
	{
		if (wynik1 == wynik2)
		{
			nowy << "Najdluzszy wspolny podciag ma postac: " << wynik1 << endl; //przypadek gdy NWP bêdzie mia³ tylko jedn¹ postaæ
		}
		else
			nowy << "Najdluzszy wspolny podciag ma postaci: " << wynik1 << ", " << wynik2 << endl; //przypadek gdy NWP bêdzie mia³ 2 ró¿ne postacie
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

	string input, output; //nazwy plików kolejno do odczytu i zapisu
	
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

	fstream plik, nowy; //zadaklarowanie plików na ktorych bedziemy pracowac
	plik.open(input, ios::in);
	if (plik.good() == 1) //sprawdzenie czy uzyskaliœmy dostep do pliku wejsciowego
		cout << "Uzyskano dostep" << endl;
	else
	{
		cout << "Nie znaleziono pliku o nazwie: " << input << endl;
		return 1;
	}
	nowy.open(output, ios::out);
	if (nowy.good() != 1) //sprawdzenie czy mamy wystarczaj¹c¹ iloœæ pamiêci do utworzenia pliku wyjœciowego
	{
		cout << "Blad z alokacja pamieci dla pliku wyjsciowego" << endl;
		return 1;
	}

	//zmienne pomocnicze przy przeszukiwaniu pliku wejsciowego
	string slowo[3]; //tablica s³ów które bêdziemy porównywaæ
	string dane = ""; //s³u¿y tylko do przemieszczania sie po pliku (gdy chccemy przejsc do nastepnej lini a nie wiemy ile jeszcze jest s³ów w lini, a jak sprawdziliœmy ¿e jest ich wiêcej ni¿ 2 to getline'ujemy ca³¹ liniê i przechodzimy do nastêpnej
	char znak; //g³ówna jednostka poruszania sie po tekscie pliku
	int p = 0; //zmienna liczbowa bêdzie nam sygnalizowa³a czy mamy juz odpowiedni¹ iloœæ s³ów do porównania

	//pêtla wybierajaca do której lini w pliku wykonaæ algorytm

	while (plik >> noskipws >> znak) //korzystamy z takiej funkcji gdyz eof mi nie dzia³a³ zawsze :(
	{
		if (p < 2)
		{
			if (znak == '\n') //przypadek gdy w lini jest za ma³o s³ów
			{
				nowy << "Za malo slow w lini" << endl;
				p = 0;
				for (int k = 0; k < 3; k++)
					slowo[k] = "";
				continue;
			}
			else
			{
				if (znak == ' ') // spacje uwzglêdniamy ale przy sczytywaniu znaków s³owa pomijamy
				{
					continue;
				}
				else
				{
					plik.seekg(-1, ios_base::cur); //pobranie s³ów
					plik >> slowo[p++];
				}
			}
		}
		else
		{

			if (znak == '\n') //przypadek gdy w lini sa 2 s³owa, czyli odpowiednia iloœæ
			{
				wykonanie_algorytmu(slowo[0], slowo[1], nowy);
				p = 0;
				for (int k = 0; k < 3; k++)
					slowo[k] = "";
				continue; // je¿eli znaleŸliœmy jeden wspólny podci¹g umo¿liwiamy programowi znalezienie kolejnych
			}
			else
			{
				if (znak == ' ')
					continue;
				else //w lini po dwóch znalezionych s³owach wyst¹pi kolejny znak nie bed¹cy ani spacj¹ ani przejœciem do nowej lini, co oznacza wyst¹pienie kolejnego wyrazu, tak¿e paramerty programu nie zosta³y spe³nione, wiêc informujemy u¿ytkownika co zrobi³ nie tak
				{
					nowy << "Za duzo slow w lini" << endl;
					getline(plik, dane); //przesuwamy siê do koñca lini
					p = 0;
					dane = "";
					for (int j = 0; j < 3; j++)
						slowo[j] = "";
					continue;
				}
			}

		}
	}
	if (p > 0) // wykonanie dla ostatniej lini jezeli w takowej coœ wyst¹pi³o
	{		   // gdy¿ funkcja sczyta³a nam te wartoœci ale gdy dosz³a do koñca pliku zakoñczy³a pêtlê
		if (p == 2) //wykonanie algorytmu
		{
			wykonanie_algorytmu(slowo[0], slowo[1], nowy);
		} 
		else // gdy sczytano tylko jedno s³owo
			nowy << "Za malo slow w lini" << endl;
	}
	plik.close();//zamkniecie plików
	nowy.close();
	return 0;
}