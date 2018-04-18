#include "drzewo.hpp"
#include "mapa.hpp"

int main(int argc, char **argv) {
	char alg;
	char *fname;
	if (argc != 3)
	{
		cerr << "Blad argumentow.";
		//system("PAUSE");
		return 0;
	}
	else
	{
		fname = argv[1];
		alg = argv[2][0];
		if (alg != 'd' && alg != 'm')
		{
			cerr << "Bladny algorytm";
			//system("PAUSE");
			return 0;
		}

	}
	Algorithm *A;
	Tree T;
	MyMap M;
	if (alg == 'd')
	{
		A = &T;
	}
	else
	{
		A = &M;
	}
	if(A->Read(fname))
		A->Write();
	else
	{
		cerr << "Blad odczytu danych." << endl;
		//system("PAUSE");
		return 0;
	}
	//system("PAUSE");
	return 1;
}