#include "Constant.h"
#include "Functions.h"
#include <string>

Constant::Constant(int IN)
{
	defaultValue = 1;
	value = ParseLogic(IN);
	elemFlag = eConstant;
	name = "CONST_VALUE_";
	name += std::to_string(indx);
}
void Constant::setIN(int value, int i)
{//nie zaistnieje taka sytuacja
	;
}
int Constant::getOUT(int o)
{
	return value;
}
std::vector<int> Constant::ReturnAccessibleInputs()
{//nie zaistnieje taka sytuacja
	return std::vector<int>();
}
std::vector<int> Constant::ReturnAccessibleOutputs()
{
	vector<int> retVector;
	retVector.push_back(1);
	return retVector;
}
void Constant::UpdateInputState(int i, State s)
{//nie zaistnieje taka sytuacja
	;
}
void Constant::RefreshLogic()
{//wartoœæ sta³ej siê nie zmienia
	;
}
std::map<string, vector<int>> Constant::ReturnIOState()
{
	std::map<string, vector<int>> retMap;
	std::vector<int> vec1;
	vec1.push_back(value);
	retMap.insert(pair<string, vector<int>>("output", vec1));
	return retMap;
}
Constant::~Constant()
{
	std::cout << "Destruktor stalej\n";
}