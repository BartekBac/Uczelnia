#ifndef Wire_h
#define Wire_h

class LogicElement;

//Klasa odpowiedzialna za prawidlowe ³¹czenie ze sob¹ elementów
class Wire {
	int value; //wartoœæ logiczna na przewodzie
	int y_begin; //zapamiêtujemy do którego wyjœcia inElem'entu pod³aczyliœmy przewód (numerowane 1-n)
	int y_end; //zapamiêtujemy wejœcie outElem'entu do którego pod³aczyliœmy przewód (numerowane 1-n)
	LogicElement *inElem; //elemnet nadaj¹cy sygna³ przewodu
	LogicElement *outElem; //element odbieraj¹cy sygna³ przewodu
public:
	Wire();
	void selectBegin(LogicElement *_IN, int i); //wybiera wyjœcie elementu (które bêdzie pocz¹tkiem przewodu)
	void selectEnd(LogicElement *_OUT, int o); //wybiera wejœcie elementu (które bêdzie koñcem przewodu), wyrzuca wyj¹tek gdy nie da siê wybraæ wejœcia
	void ResetEnd(); //resetuje stan elemntu koñcowego (gdy neipowiedzie siê dodanie po³¹czenia)

	void RefreshLogic(); //odœwierza stan na przewodzie
	LogicElement *getSuccessor(); //gdy isnieje zwraca wskaŸnik elementu z którym jest po³¹czony
	~Wire();
};

#endif