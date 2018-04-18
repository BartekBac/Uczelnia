#ifndef Functions_h
#define Functions_h
#include "LogicElement.h"
#include "Gates.h"

int ParseLogic(int x);	//gwarantuje zwrócenie wartoœci tylko 0 lub 1
void CheckConnectedSeries(LogicElement *elem, std::vector<int> vecLE);	//aktualizuje stan serii po³¹czeñ
void CheckConnectedSeries_start(LogicElement *_elem);
void UpdateConnectedSeries(LogicElement *_elem);
void MakeWire(Wire *_wire, LogicElement* inLE, LogicElement* outLE);
void ShowLogicElementState(std::map<std::string, std::vector<int>> _IOmap);
#endif