#ifndef Gates_h
#define Gates_h

#include "LogicElement.h"

using namespace std;

enum gateType {two_input, three_input, four_input};

struct GateIO {
	vector<int> input;
	vector<State> input_status;
	int output;
	int input_count;
	GateIO(gateType _type);
	~GateIO();
};

//struktura statusu wejœæ bramki
struct GateConnectionStatus {
	State in1;
	State in2;
};
///TO DO
/*
-dodaæ do ka¿dego elementu strukturê wejœæ/wyjœæ
-ka¿dy element ma obiekt wybranej struktury wejœæ/wyjœæ
-indywidualny enum struktur IO, przyjmowany przez konstruktor przekazywany w mainie przy tworzeniu
-metoda ShowState zwraca strukturê wejœæ/wyjœæ
*/

//KLASA BAZOWA BRAMEK
class Gate : public LogicElement {
protected:
	/*int input1;
	int input2;
	int output;*/
	GateIO IO;
	//GateConnectionStatus currentState;
public:
	Gate(gateType _type);

	void setIN(int value, int i = 1);
	int getOUT(int o=1);
	vector<int> ReturnAccessibleInputs(); //wyrzuca wyj¹tek LEexception gdy nie ma ju¿ dostepnych wejœæ
	vector<int> ReturnAccessibleOutputs();
	void UpdateInputState(int i, State s);
	map<string, vector<int>> ReturnIOState();

	virtual ~Gate();
};

//KLASY POSZCZEGÓLNYCH BRAMEK
class AND : public Gate {
public:
	AND(gateType _type);
	void RefreshLogic();
	~AND();
};

#endif