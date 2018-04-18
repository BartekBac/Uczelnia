#include "Functions.h"
#include "LEexception.h"

//FUNCTIONS
int ParseLogic(int x) {
//dla wartoœci ró¿nych od 0 zwraca 1
	if (x == 0)
		return 0;
	else
		return 1;
}

void UpdateConnectedSeries(LogicElement *_elem)
{//rekurencyjne aktualizowanie ca³ej po³¹czonej serii
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
		if (vecLE[i] == elem->getIndex()) //sprawdzamy czy pêtla
		{ // jeœli wykryto pêtle wyrzucamy wyj¹tek
			vecLE.clear(); //usuniêcie vectora?
			throw RaceCondition(); //usuniêcie ostatniego Wire?
		}
	}
	
	for (int i = 0; i < elem->connectList.size(); i++)
	{//dla wszytsko po³aczonych elementów do aktualnego
		vecLE.push_back(elem->getIndex()); //dajemy do vectora index aktualnego elementu, jak ma dalsze przewody
		//elem->connectList[i]->RefreshLogic(); //zaktualizowanie stanu
		CheckConnectedSeries(elem->connectList[i]->getSuccessor(), vecLE); //wywo³anie rekurencyjne dla nastêpnych elemntów po³¹czonej serii
		vecLE.pop_back(); //po rekurencyjnym powrocie zwalniamy wrzucon¹ wartoœæ
	}
}
void MakeWire(Wire *_wire, LogicElement* inLE, LogicElement* outLE)
{
	//pobieramy z list dostêpne wejscia i wyjscia wybranych elemntów
	std::vector<int> accessibleOutputs = inLE->ReturnAccessibleOutputs(); 
	std::vector<int> accessibleInputs = outLE->ReturnAccessibleInputs(); //wyrzuca wyj¹tek LEexception gdy nie ma dostêpnych wejœæ
	//ustawiamy za pomoc¹
	bool mustSelectBegin = true;	//flaga poprawnoœci wyboru pocz¹tku przeowdu
	bool mustSelectEnd = true;		//flaga poprawnoœci wyboru koñca przewodu
	int selectedBegin = 0;			//numer wybranego przewodu wyjœcia elemntu pocz¹tkowego
	int selectedEnd = 0;			//numer wybranego przewodu wejœcia elemntu koñcowego
	int countOfAccessibleOutputs = accessibleOutputs.size();	
	int countOfAccessibleInputs = accessibleInputs.size();
	//sprawdzanie koniecznoœci wyboru pocz¹tku przewodu
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

	if (inLE->getElemFlag() == Element::eConstant) /// dodaæ pozosta³e flagi
	{
		selectedBegin = accessibleOutputs[0];
		mustSelectBegin = false;
	}
	//wybieranie pocz¹tku przewodu
	while (mustSelectBegin)
	{
		std::cout << "Wybierz pocz¹tek poloczenia (wpisz to co po dwukropku):\n";
		//wypisanie wszytskich dostêpnych wyjœæ
		for (int i = 0; i < countOfAccessibleOutputs; i++)
		{
			std::cout << "wyjscie " << accessibleOutputs[i] << ":" << accessibleOutputs[i] << std::endl;
		}
		std::cout << "anuluj: 0\n";
		std::cin >> selectedBegin;
		if (selectedBegin == 0) throw CancelEx();
		//sprawdzenie poprawnoœci wybrania przez u¿ytkownika
		for (int i = 0; i < countOfAccessibleOutputs; i++)
		{
			if (selectedBegin == accessibleOutputs[i])
			{
				mustSelectBegin = false;
			}
		}
	}
	//sprawdzanie koniecznoœci/poprawnoœci wyboru koñca przewodu
	if (outLE->getElemFlag() == Element::eConstant)
	{
		throw LEexception("Nie mozna podlaczyc przewodu do stalej");
	}
	//wybieranie koñca przewodu
	while (mustSelectEnd)
	{
		std::cout << "Wybierz koniec poloczenia (wpisz to co po dwukropku):\n";
		//wypisanie wszytskich dostêpnych wejœæ
		for (int i = 0; i < countOfAccessibleInputs; i++)
		{
			std::cout << "wejscie " << accessibleInputs[i] << ":" << accessibleInputs[i] << std::endl;
		}
		std::cout << "anuluj: 0\n";
		std::cin >> selectedEnd;
		if (selectedEnd == 0) throw CancelEx();
		//sprawdzenie poprawnoœci wybrania przez u¿ytkownika
		for (int i = 0; i < countOfAccessibleInputs; i++)
		{
			if (selectedEnd == accessibleInputs[i])
			{
				mustSelectEnd = false;
			}
		}
	}
	//utworzenie w³asciwgo po³¹czenia
	_wire->selectBegin(inLE, selectedBegin);
	_wire->selectEnd(outLE, selectedEnd);
	//zaktualizowanie informacji o utworzonym po³¹czeniu
	inLE->connectList.push_back(_wire);
	outLE->UpdateInputState(selectedEnd, State::on);
}
void ShowLogicElementState(std::map<string, vector<int>> _map)
{
	for (std::map<string, vector<int>>::iterator it = _map.begin(); it != _map.end(); ++it)
	{
		std::cout << it->first << ": "; //wypisanie rodziaju wejœæ/wyjœæ
		for (int i = 0; i < it->second.size(); i++)
		{
			std::cout << it->second.at(i) << " "; //wypisanie wartoœci wszytskich elemntów tego rodzaju
		}
		std::cout << std::endl;
	}
}