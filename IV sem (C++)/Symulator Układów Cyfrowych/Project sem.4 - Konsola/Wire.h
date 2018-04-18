#ifndef Wire_h
#define Wire_h

class LogicElement;

//Klasa odpowiedzialna za prawidlowe ��czenie ze sob� element�w
class Wire {
	int value; //warto�� logiczna na przewodzie
	int y_begin; //zapami�tujemy do kt�rego wyj�cia inElem'entu pod�aczyli�my przew�d (numerowane 1-n)
	int y_end; //zapami�tujemy wej�cie outElem'entu do kt�rego pod�aczyli�my przew�d (numerowane 1-n)
	LogicElement *inElem; //elemnet nadaj�cy sygna� przewodu
	LogicElement *outElem; //element odbieraj�cy sygna� przewodu
public:
	Wire();
	void selectBegin(LogicElement *_IN, int i); //wybiera wyj�cie elementu (kt�re b�dzie pocz�tkiem przewodu)
	void selectEnd(LogicElement *_OUT, int o); //wybiera wej�cie elementu (kt�re b�dzie ko�cem przewodu), wyrzuca wyj�tek gdy nie da si� wybra� wej�cia
	void ResetEnd(); //resetuje stan elemntu ko�cowego (gdy neipowiedzie si� dodanie po��czenia)

	void RefreshLogic(); //od�wierza stan na przewodzie
	LogicElement *getSuccessor(); //gdy isnieje zwraca wska�nik elementu z kt�rym jest po��czony
	~Wire();
};

#endif