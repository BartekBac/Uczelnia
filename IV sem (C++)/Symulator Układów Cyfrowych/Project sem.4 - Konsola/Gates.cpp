#include "Gates.h"
#include "Functions.h"
#include <string>
#include "LEexception.h"
#include <algorithm>
//
//GATE
//

GateIO::GateIO(gateType _type)
{
	if (_type == gateType::two_input)
	{
		input_count = 2;
	}
	else if (_type == gateType::three_input)
	{
		input_count = 3;
	}
	else if (_type == gateType::four_input)
	{
		input_count = 4;
	}
	else
	{
		throw WrongConstructorParameter();
	}

	for (int i = 0; i < input_count; i++)
	{
		input_status.push_back(State::off);
	}
}
GateIO::~GateIO()
{
	input.clear();
	input_status.clear();
}


Gate::Gate(gateType _type) : IO(GateIO(_type)) {}

int Gate::getOUT(int o)
{
	return IO.output;
}
void Gate::setIN(int value, int i)
{
	if (IO.input_count >= i)
	{//gdy wybrane wejœcie istnieje, ustawiamy wybran¹ wartoœæ
		IO.input[i - 1] = ParseLogic(value);
	}
	else
	{//inaczej wyrzucamy wyj¹tek
		throw IO_OutOfRange();
	}
	//automatycznie oœwierzamy wartoœæ na wyjœciu
	this->RefreshLogic(); //!!!WA¯NE
}
vector<int> Gate::ReturnAccessibleInputs()
{
	//parsowanie wyboru wejœcia
	int countOfAccesibleInputs = count_if(IO.input_status.begin(), IO.input_status.end(), [](State s) { return s == State::off;  });
	if(countOfAccesibleInputs==0)
		throw LEexception("Wejscia sa juz zajete");

	vector<int> retVector;

	for (int i = 0; i < IO.input_count; i++)
	{
		if (IO.input_status[i] == State::off)
		{
			retVector.push_back(i + 1);
		}
	}

	return retVector;
}
vector<int> Gate::ReturnAccessibleOutputs()
{
	vector<int> retVector;
	
	retVector.push_back(1);

	return retVector;
}
void Gate::UpdateInputState(int i, State s)
{
	if (IO.input_count >= i)
	{
		IO.input_status[i - 1] = s;
	}
	else
	{
		throw IO_OutOfRange();
	}
}

map<string, vector<int>> Gate::ReturnIOState()
{
	map<string, vector<int>> retMap;
	vector<int> outVec;
	outVec.push_back(IO.output);
	retMap.insert(pair<string, vector<int>>("inputs", IO.input));
	retMap.insert(pair<string, vector<int>>("output", outVec));
	return retMap;
}

Gate::~Gate()
{
	std::cout<<"Destruktor Gate\n";
}

//
//AND
//

AND::AND(gateType _type) : Gate(_type) {

	defaultValue = 0;
	elemFlag = eAND;
	name = "AND_";
	name += std::to_string(indx);

	for (int i = 0; i < IO.input_count; i++)
	{
		IO.input.push_back(defaultValue);
	}

	this->RefreshLogic();
}
void AND::RefreshLogic()
{
	int countOfOnes = count_if(IO.input.begin(), IO.input.end(), [](int i) { return i==1; });

	if (countOfOnes == IO.input_count)
	{
		IO.output = 1;
	}
	else
	{
		IO.output = 0;
	}
}
AND::~AND()
{
	std::cout << "Destruktor AND\n";
}