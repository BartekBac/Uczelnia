#ifndef Constant_h
#define Constant_h

#include "LogicElement.h"

class Constant : public LogicElement {
	int value;
public:
	Constant(int IN=0);

	void setIN(int value, int i = 1);
	int getOUT(int o = 1);
	std::vector<int> ReturnAccessibleInputs();
	std::vector<int> ReturnAccessibleOutputs();
	void UpdateInputState(int i, State s);
	void RefreshLogic();
	std::map<std::string, std::vector<int>> ReturnIOState();

	~Constant();
};


#endif // !Constant_h
