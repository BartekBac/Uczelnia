#ifndef LogicElement_h
#define LogicElement_h

#include <iostream>
#include <vector>
#include <map>
#include "Wire.h"

enum State { off = 0, on = 1 };
enum Element { eAND, eOR, eXOR, eMUX, eLatch, eConstant };


//Klasa bazowa wszytskich elementów logicznych
class LogicElement {
protected:
	Element elemFlag;	//flaga elementu logicznego
	int indx;			//unikalny index elementu
	std::string name;	//nazwa elementu
	int defaultValue;	//domyœlnie ustawione wartoœci logiczne na wejœciu
public:
	std::vector<Wire*> connectList; //vector wszytskich po³¹czeñ wyjœciowych bramki
	static int globIndex;			//globalny index gwarantuj¹cy unikalnoœæ elemntów
	
	LogicElement();

	virtual void setIN(int value, int i=1) = 0;				//ustawia i-te wejscie na dan¹ wartoœæ
	virtual int getOUT(int o=1) = 0;						//zwraca wartoœæ o-tego wyjœcia
	virtual std::vector<int> ReturnAccessibleInputs() = 0;	//zwraca dostêpne wejœcia
	virtual std::vector<int> ReturnAccessibleOutputs() = 0;	//zwraca dostêpne wyjœcia
	virtual void UpdateInputState(int i, State s) = 0;		//aktualizuje dostêpnoœæ wejœæ
	virtual void RefreshLogic() = 0;						//odœwie¿a logiczny stan bramki
	virtual std::map<std::string, std::vector<int>> ReturnIOState() = 0;	//zwraca mapê stanów na wejœciach/wyjœciach dowolnego elementu logicznego

	Element getElemFlag();				//zwraca flagê jaki to jest element
	int getIndex();						//zwraca index elementu
	std::string getName();				//zwraca nazwê elementu
	int getDefaultValue();				//zwraca domyœln¹ wartoœæ logiczn¹ na wejœciu

	virtual ~LogicElement();
};


#endif