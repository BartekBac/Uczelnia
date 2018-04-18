#include "Wire.h"
#include "Gates.h"
#include "Constant.h"
#include "LEexception.h"

Wire::Wire()
{
	value = 0;
	y_begin = 0;
	y_end = 0;
	inElem = nullptr;
	outElem = nullptr;
}
void Wire::RefreshLogic()
{
	value = inElem->getOUT(y_begin);
	outElem->setIN(value, y_end);
}
void Wire::selectBegin(LogicElement *_IN, int i)
{
	inElem = _IN;
	y_begin = i;
}
void Wire::selectEnd(LogicElement *_OUT, int o)
{
	outElem = _OUT;
	y_end = o;
	this->RefreshLogic();
}

void Wire::ResetEnd()
{
	if (outElem != nullptr)
	{//odœwierzenie wartoœci na elemencie koñcowym
		outElem->setIN(outElem->getDefaultValue(), y_end);
		outElem->UpdateInputState(y_end, State::off);
		outElem = nullptr;
	}
}
LogicElement* Wire::getSuccessor()
{
	return outElem; //jak nullptr, to zwróci nullptr
}
Wire::~Wire()
{
	std::cout << "Destruktor Wire\n";
	outElem = nullptr;
	inElem = nullptr;
}