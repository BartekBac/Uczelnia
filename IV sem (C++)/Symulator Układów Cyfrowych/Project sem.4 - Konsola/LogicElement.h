#ifndef LogicElement_h
#define LogicElement_h

#include <iostream>
#include <vector>
#include <map>
#include "Wire.h"

enum State { off = 0, on = 1 };
enum Element { eAND, eOR, eXOR, eMUX, eLatch, eConstant };


//Klasa bazowa wszytskich element�w logicznych
class LogicElement {
protected:
	Element elemFlag;	//flaga elementu logicznego
	int indx;			//unikalny index elementu
	std::string name;	//nazwa elementu
	int defaultValue;	//domy�lnie ustawione warto�ci logiczne na wej�ciu
public:
	std::vector<Wire*> connectList; //vector wszytskich po��cze� wyj�ciowych bramki
	static int globIndex;			//globalny index gwarantuj�cy unikalno�� elemnt�w
	
	LogicElement();

	virtual void setIN(int value, int i=1) = 0;				//ustawia i-te wejscie na dan� warto��
	virtual int getOUT(int o=1) = 0;						//zwraca warto�� o-tego wyj�cia
	virtual std::vector<int> ReturnAccessibleInputs() = 0;	//zwraca dost�pne wej�cia
	virtual std::vector<int> ReturnAccessibleOutputs() = 0;	//zwraca dost�pne wyj�cia
	virtual void UpdateInputState(int i, State s) = 0;		//aktualizuje dost�pno�� wej��
	virtual void RefreshLogic() = 0;						//od�wie�a logiczny stan bramki
	virtual std::map<std::string, std::vector<int>> ReturnIOState() = 0;	//zwraca map� stan�w na wej�ciach/wyj�ciach dowolnego elementu logicznego

	Element getElemFlag();				//zwraca flag� jaki to jest element
	int getIndex();						//zwraca index elementu
	std::string getName();				//zwraca nazw� elementu
	int getDefaultValue();				//zwraca domy�ln� warto�� logiczn� na wej�ciu

	virtual ~LogicElement();
};


#endif