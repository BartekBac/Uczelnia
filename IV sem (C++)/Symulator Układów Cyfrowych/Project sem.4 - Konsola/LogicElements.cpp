#include "LogicElement.h"
#include "Functions.h"
#include "Gates.h"

LogicElement::LogicElement() { indx = globIndex++; }
Element LogicElement::getElemFlag()
{
	return elemFlag;
}
int LogicElement::getIndex()
{
	return indx;
}
std::string LogicElement::getName()
{
	return name;
}
int LogicElement::getDefaultValue()
{
	return defaultValue;
}
LogicElement::~LogicElement()
{//usuni�cie vectora po��cze�
	for (int i = 0; i < connectList.size(); i++)
		delete connectList[i];
	connectList.clear();
	std::cout << "Destruktor LogicElement\n";
}
