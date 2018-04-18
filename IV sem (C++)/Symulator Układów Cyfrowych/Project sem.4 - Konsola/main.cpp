#include "LogicElement.h"
#include "Gates.h"
#include "Constant.h"
#include "LEexception.h"
#include "Functions.h"
#include <map>
#include "vld.h"

using namespace std;

int LogicElement::globIndex = 0; //index zapewniaj¹cy unikalnoœæ elemntu w mapie

int main()
{
	map<int, LogicElement*> listLE;	//g³owny kontener elemntów logicznych
	int action = 0;					//flaga dzia³ania w pêtli g³ownej programu
	//pêtla g³ówna programu
	while (1)
	{
		while (action != 1 && action != 2 && action != 3 && action != 4)
		{//wybór akcji
			cout << "Wybierz akcje:\n1 - Dodaj element\n2 - Dodaj poloczenie\n3 - Pokaz stany\n4 - Zakoncz program...\n";
			cin >> action;
		}
		switch (action)	
		{//obs³u¿enie akcji
		case 1:
		{
			int enumElem = 0;
			while (enumElem != 1 && enumElem != 2)
			{//wybór elemntu
				cout << "Wybierz element:\n1 - AND\n2 - CONST_VALUE\n";
				cin >> enumElem;
			}
			switch (enumElem)
			{//dodanie elemntu
			case 1:
			{ 
				int gType = 0;
				while (gType != 1 && gType != 2 && gType != 3)
				{//wybór elemntu
					cout << "Wybierz typ bramki:\n1 - dwu-wejsciowa\n2 - trzy-wejsciowa\n3-cztero-wejsciowa\n";
					cin >> gType;
				}
				AND *nElem = new AND(gateType(gType-1));
				listLE.insert(pair<int, LogicElement*>(nElem->getIndex(), nElem));
				cout << "Dodano bramke: " << nElem->getName() << endl;
				break;
			}
			case 2:
				int val = 0;
				std::cout << "Podaj wartosc stalej: ";
				std::cin >> val;
				Constant *nElem = new Constant(val);
				listLE.insert(pair<int, LogicElement*>(nElem->getIndex(), nElem));
				cout << "Dodano stala: " << nElem->getName() << endl;
				break;
			}
			break;
		}
		case 2:
		{//dodanie po³¹czenia
			if (listLE.size() < 2)
			{
				cout << "Niewystarczajaca ilosc elementow\n";
				break;
			}
			int indxIn = -1;
			int indxOut = -1;
			cout << "Lista dostepnych elementow:\n";
			int i = 0;
			while (i < listLE.size())
			{///to bedzie trzeba zmianiæ jak dodamy usuwanie, zamieniæ na fora z iteratorem
				cout << listLE[i]->getName() << ": " << listLE[i]->getIndex() << endl;
				i++;
			}
			cout << "Wybierz poczatek poloczenia (wpisz to co po dwukropku): ";
			while (indxIn < 0 || indxIn >= i)
			{
				cin >> indxIn;
			}
			cout << "Wybierz koniec poloczenia: ";
			while (indxOut < 0 || indxOut >= i || indxOut == indxIn)
			{
				cin >> indxOut;
			}
			//dodawanie po³¹czeñ na zasadzie wskaŸników
			Wire *nWire = new Wire();
			try
			{
				MakeWire(nWire, listLE.at(indxIn), listLE.at(indxOut)); //wyrzuca wyj¹tki LEexception i CancelEx
				try
				{
					CheckConnectedSeries_start(listLE[indxIn]); //wyrzuca wyj¹tek RaceCondition
				}
				catch (RaceCondition &e)
				{//gdy znajdziemy pêtlê w uk³adzie
					listLE[indxIn]->connectList.pop_back(); //usuniêcie wadliwego po³¹czenia
					nWire->ResetEnd();	//odwieszenie wartoœci na wejœciu elementu wyjœciowego
					throw; //resztê ob³u¿yæ jeszcze ni¿ej
				}
				//jak nie napotkano awarii, zaktualiozwaæ seriê
				UpdateConnectedSeries(listLE[indxIn]);
				cout << "Utworzono poloczenie\n";
			}
			catch (LEexception &e) 
			{//MakeWire rzuca wyj¹tki: LEexception i CancelEx		
				cout << e.GetMessage() << endl;
				delete nWire;
				cout << "Nie utworzono poloczenia\n";
			}
			break;
		}
		case 3:
		{//pokazanie stanów
			for (std::map<int, LogicElement*>::iterator it = listLE.begin(); it != listLE.end(); ++it)
			{
				cout << it->second->getName() << endl;
				ShowLogicElementState(it->second->ReturnIOState());
			}
			
			break;
		}
		case 4:
		{//zamkniêcie programu
			int conf = 0; //flaga potwierdzaj¹ca zamkniêcie programu
			do
			{
				cout << "Czy na pewno zamknac program?\n0 - Nie\n1 - Tak\n";
				cin >> conf; //pobranie decyzji od u¿ytkownika
				if (conf == 1)
				{
					int i = 0;
					while (i < listLE.size())
					{//opró¿nienie g³ównego kontenera programu
						delete listLE[i];
						i++;
					}
					listLE.clear();
					return 0;
				}
				else { break; }
			} while (conf != 0 || conf != 1);
			break;
		}
		}
		action = 0;
	}
	system("PAUSE");
	return 0;
}