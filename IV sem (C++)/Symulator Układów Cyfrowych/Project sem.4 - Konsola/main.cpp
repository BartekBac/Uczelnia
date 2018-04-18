#include "LogicElement.h"
#include "Gates.h"
#include "Constant.h"
#include "LEexception.h"
#include "Functions.h"
#include <map>
#include "vld.h"

using namespace std;

int LogicElement::globIndex = 0; //index zapewniaj�cy unikalno�� elemntu w mapie

int main()
{
	map<int, LogicElement*> listLE;	//g�owny kontener elemnt�w logicznych
	int action = 0;					//flaga dzia�ania w p�tli g�ownej programu
	//p�tla g��wna programu
	while (1)
	{
		while (action != 1 && action != 2 && action != 3 && action != 4)
		{//wyb�r akcji
			cout << "Wybierz akcje:\n1 - Dodaj element\n2 - Dodaj poloczenie\n3 - Pokaz stany\n4 - Zakoncz program...\n";
			cin >> action;
		}
		switch (action)	
		{//obs�u�enie akcji
		case 1:
		{
			int enumElem = 0;
			while (enumElem != 1 && enumElem != 2)
			{//wyb�r elemntu
				cout << "Wybierz element:\n1 - AND\n2 - CONST_VALUE\n";
				cin >> enumElem;
			}
			switch (enumElem)
			{//dodanie elemntu
			case 1:
			{ 
				int gType = 0;
				while (gType != 1 && gType != 2 && gType != 3)
				{//wyb�r elemntu
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
		{//dodanie po��czenia
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
			{///to bedzie trzeba zmiani� jak dodamy usuwanie, zamieni� na fora z iteratorem
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
			//dodawanie po��cze� na zasadzie wska�nik�w
			Wire *nWire = new Wire();
			try
			{
				MakeWire(nWire, listLE.at(indxIn), listLE.at(indxOut)); //wyrzuca wyj�tki LEexception i CancelEx
				try
				{
					CheckConnectedSeries_start(listLE[indxIn]); //wyrzuca wyj�tek RaceCondition
				}
				catch (RaceCondition &e)
				{//gdy znajdziemy p�tl� w uk�adzie
					listLE[indxIn]->connectList.pop_back(); //usuni�cie wadliwego po��czenia
					nWire->ResetEnd();	//odwieszenie warto�ci na wej�ciu elementu wyj�ciowego
					throw; //reszt� ob�u�y� jeszcze ni�ej
				}
				//jak nie napotkano awarii, zaktualiozwa� seri�
				UpdateConnectedSeries(listLE[indxIn]);
				cout << "Utworzono poloczenie\n";
			}
			catch (LEexception &e) 
			{//MakeWire rzuca wyj�tki: LEexception i CancelEx		
				cout << e.GetMessage() << endl;
				delete nWire;
				cout << "Nie utworzono poloczenia\n";
			}
			break;
		}
		case 3:
		{//pokazanie stan�w
			for (std::map<int, LogicElement*>::iterator it = listLE.begin(); it != listLE.end(); ++it)
			{
				cout << it->second->getName() << endl;
				ShowLogicElementState(it->second->ReturnIOState());
			}
			
			break;
		}
		case 4:
		{//zamkni�cie programu
			int conf = 0; //flaga potwierdzaj�ca zamkni�cie programu
			do
			{
				cout << "Czy na pewno zamknac program?\n0 - Nie\n1 - Tak\n";
				cin >> conf; //pobranie decyzji od u�ytkownika
				if (conf == 1)
				{
					int i = 0;
					while (i < listLE.size())
					{//opr�nienie g��wnego kontenera programu
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