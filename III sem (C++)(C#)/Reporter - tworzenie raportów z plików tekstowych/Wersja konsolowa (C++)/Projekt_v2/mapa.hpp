#include "algorytm.hpp"
#include <map>
class MyMap : public Algorithm {
	map<string, int> m;
	int total;
	map<string, int>::iterator max;
public:
	int Read(char *filename);
	void Print();
	void Write();
};