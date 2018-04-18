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

//struktura statusu wej�� bramki
struct GateConnectionStatus {
	State in1;
	State in2;
};
///TO DO
/*
-doda� do ka�dego elementu struktur� wej��/wyj��
-ka�dy element ma obiekt wybranej struktury wej��/wyj��
-indywidualny enum struktur IO, przyjmowany przez konstruktor przekazywany w mainie przy tworzeniu
-metoda ShowState zwraca struktur� wej��/wyj��
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
	vector<int> ReturnAccessibleInputs(); //wyrzuca wyj�tek LEexception gdy nie ma ju� dostepnych wej��
	vector<int> ReturnAccessibleOutputs();
	void UpdateInputState(int i, State s);
	map<string, vector<int>> ReturnIOState();

	virtual ~Gate();
};

//KLASY POSZCZEG�LNYCH BRAMEK
class AND : public Gate {
public:
	AND(gateType _type);
	void RefreshLogic();
	~AND();
};

#endif