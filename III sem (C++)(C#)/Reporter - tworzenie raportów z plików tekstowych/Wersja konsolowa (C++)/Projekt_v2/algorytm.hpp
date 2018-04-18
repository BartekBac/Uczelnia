#ifndef algorytm
#define algorytm

#include <iostream>
#include <string>
#include <vld.h>
#include <fstream>

using namespace std;

class Algorithm {
protected:
	string fname;
public:
	Algorithm() {};
	virtual int Read(char *filename) = 0; //zwraca 1 gdy pomyœlnie wczyta dane, inaczej zwraca 0
	virtual void Print() = 0;
	virtual void Write() = 0;
};
string prepareWord(const string&); // ta funkcja jest zadeklarowana tutaj, bo jest
								   // u¿ywana i w pliku drzewo.cpp (gdzie jest zdefiniowana)
								   // i w pliku mapa.cpp

#endif algorytm