#include "Functions.h"
#include "LEexception.h"

//FUNCTIONS
int ParseLogic(int x) {
//dla warto�ci r�nych od 0 zwraca 1
	if (x == 0)
		return 0;
	else
		return 1;
}

void UpdateConnectedSeries(LogicElement *_elem)
{//rekurencyjne aktualizowanie ca�ej po��czonej serii
	for (int i = 0; i < _elem->connectList.size(); i++)
	{
		_elem->connectList[i]->RefreshLogic();
		UpdateConnectedSeries(_elem->connectList[i]->getSuccessor());
	}
}

void CheckConnectedSeries_start(LogicElement *_elem)
{
	if (_elem->connectList.size() > 0)
	{
		std::vector<int> _vecLE;
		CheckConnectedSeries(_elem, _vecLE);
		_vecLE.clear();
	}
}
void CheckConnectedSeries(LogicElement *elem, std::vector<int> vecLE)
{
	for (int i = 0; i < vecLE.size(); i++) 
	{
		if (vecLE[i] == elem->getIndex()) //sprawdzamy czy p�tla
		{ // je�li wykryto p�tle wyrzucamy wyj�tek
			vecLE.clear(); //usuni�cie vectora?
			throw RaceCondition(); //usuni�cie ostatniego Wire?
		}
	}
	
	for (int i = 0; i < elem->connectList.size(); i++)
	{//dla wszytsko po�aczonych element�w do aktualnego
		vecLE.push_back(elem->getIndex()); //dajemy do vectora index aktualnego elementu, jak ma dalsze przewody
		//elem->connectList[i]->RefreshLogic(); //zaktualizowanie stanu
		CheckConnectedSeries(elem->connectList[i]->getSuccessor(), vecLE); //wywo�anie rekurencyjne dla nast�pnych elemnt�w po��czonej serii
		vecLE.pop_back(); //po rekurencyjnym powrocie zwalniamy wrzucon� warto��
	}
}
void MakeWire(Wire *_wire, LogicElement* inLE, LogicElement* outLE)
{
	//pobieramy z list dost�pne wejscia i wyjscia wybranych elemnt�w
	std::vector<int> accessibleOutputs = inLE->ReturnAccessibleOutputs(); 
	std::vector<int> accessibleInputs = outLE->ReturnAccessibleInputs(); //wyrzuca wyj�tek LEexception gdy nie ma dost�pnych wej��
	//ustawiamy za pomoc�
	bool mustSelectBegin = true;	//flaga poprawno�ci wyboru pocz�tku przeowdu
	bool mustSelectEnd = true;		//flaga poprawno�ci wyboru ko�ca przewodu
	int selectedBegin = 0;			//numer wybranego przewodu wyj�cia elemntu pocz�tkowego
	int selectedEnd = 0;			//numer wybranego przewodu wej�cia elemntu ko�cowego
	int countOfAccessibleOutputs = accessibleOutputs.size();	
	int countOfAccessibleInputs = accessibleInputs.size();
	//sprawdzanie konieczno�ci wyboru pocz�tku przewodu
	try
	{
		Gate *checkIfItsGate = dynamic_cast<Gate*>(inLE);
		if (checkIfItsGate != nullptr)
		{
			selectedBegin = accessibleOutputs[0];
			mustSelectBegin = false;
		}
	}
	catch (std::bad_cast)
	{
		mustSelectBegin=true;
	}

	if (inLE->getElemFlag() == Element::eConstant) /// doda� pozosta�e flagi
	{
		selectedBegin = accessibleOutputs[0];
		mustSelectBegin = false;
	}
	//wybieranie pocz�tku przewodu
	while (mustSelectBegin)
	{
		std::cout << "Wybierz pocz�tek poloczenia (wpisz to co po dwukropku):\n";
		//wypisanie wszytskich dost�pnych wyj��
		for (int i = 0; i < countOfAccessibleOutputs; i++)
		{
			std::cout << "wyjscie " << accessibleOutputs[i] << ":" << accessibleOutputs[i] << std::endl;
		}
		std::cout << "anuluj: 0\n";
		std::cin >> selectedBegin;
		if (selectedBegin == 0) throw CancelEx();
		//sprawdzenie poprawno�ci wybrania przez u�ytkownika
		for (int i = 0; i < countOfAccessibleOutputs; i++)
		{
			if (selectedBegin == accessibleOutputs[i])
			{
				mustSelectBegin = false;
			}
		}
	}
	//sprawdzanie konieczno�ci/poprawno�ci wyboru ko�ca przewodu
	if (outLE->getElemFlag() == Element::eConstant)
	{
		throw LEexception("Nie mozna podlaczyc przewodu do stalej");
	}
	//wybieranie ko�ca przewodu
	while (mustSelectEnd)
	{
		std::cout << "Wybierz koniec poloczenia (wpisz to co po dwukropku):\n";
		//wypisanie wszytskich dost�pnych wej��
		for (int i = 0; i < countOfAccessibleInputs; i++)
		{
			std::cout << "wejscie " << accessibleInputs[i] << ":" << accessibleInputs[i] << std::endl;
		}
		std::cout << "anuluj: 0\n";
		std::cin >> selectedEnd;
		if (selectedEnd == 0) throw CancelEx();
		//sprawdzenie poprawno�ci wybrania przez u�ytkownika
		for (int i = 0; i < countOfAccessibleInputs; i++)
		{
			if (selectedEnd == accessibleInputs[i])
			{
				mustSelectEnd = false;
			}
		}
	}
	//utworzenie w�asciwgo po��czenia
	_wire->selectBegin(inLE, selectedBegin);
	_wire->selectEnd(outLE, selectedEnd);
	//zaktualizowanie informacji o utworzonym po��czeniu
	inLE->connectList.push_back(_wire);
	outLE->UpdateInputState(selectedEnd, State::on);
}
void ShowLogicElementState(std::map<string, vector<int>> _map)
{
	for (std::map<string, vector<int>>::iterator it = _map.begin(); it != _map.end(); ++it)
	{
		std::cout << it->first << ": "; //wypisanie rodziaju wej��/wyj��
		for (int i = 0; i < it->second.size(); i++)
		{
			std::cout << it->second.at(i) << " "; //wypisanie warto�ci wszytskich elemnt�w tego rodzaju
		}
		std::cout << std::endl;
	}
}