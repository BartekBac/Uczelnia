#include "mapa.hpp"

int MyMap::Read(char *filename)
{
	fstream file;
	file.open(filename, ios_base::in);
	if (!file.good())
	{
		cerr << "Blad obsugi pliku" << endl;
		return 0;
	}
	fname = filename;
	string w;
	while (file >> w)
	{
		//sprawdzamy i obcinamy s�owo z niepotrzebnych znak�w
		char lastSign = w.at(w.size() - 1);
		if (lastSign == ',' || lastSign == '.' || lastSign == ':' || lastSign == ';' || lastSign == '!' || lastSign == '?' || lastSign == '\"' || lastSign == '\'' || lastSign == ')' || lastSign == ']' || lastSign == '}')
		{
			w.erase(w.size() - 1);
			if (w == "")
				continue;
		}
		char firstSign = w[0];
		if (firstSign == '\'' || firstSign == '\"' || firstSign == '(' || firstSign == '[' || firstSign == '{' || firstSign == '~' || firstSign == '-')
		{
			w.erase(0, 1);
			if (w == "")
				continue;
		}
		total++; //zwi�kszamy ca�kowit� ilo�� s��w
		w = prepareWord(w); // ujednolicamy s�owa do ma�ych znak�w, aby zapobiec traktowaniu jako inne s�owo np. zaczynaj�cego si� z du�ej litery
		map<string, int>::iterator elem = m.find(w); //szukamy podanego s�owa w mapie
		if (elem == m.end())
		{//gdy jeszcze go nie ma to dodajemy je
			m.insert(pair<string, int>(w, 1));
			if (total == 1)//zainicjalizowanie maxymalnego elementu do iteratora max
				max = m.begin();
		}
		else
		{//gdy ju� jest, zwiekszamy jego licznik
			elem->second++;
			if (elem->second > max->second && elem!=max) //sprawdzamy czy to nowe max
				max = elem;
		}
	}
	file.close();
	return 1;
}
void MyMap::Print()
{
	cout << "Total: " << total << endl;
	cout << "Max: " << max->first << " (" << max->second << ")" << endl;
	cout << "Words:" << endl;
	for (map<string, int>::iterator i = m.begin(); i != m.end(); i++)
		cout << i->first << " (" << i->second << ")" << endl;
}
void MyMap::Write()
{
	fstream new_file;
	string name = fname;
	name.erase(name.size() - 4);
	name += "-raport(mapa).txt";
	new_file.open(name, ios_base::out);
	if (!new_file.good())
	{
		cerr << "Blad obslugi pliku." << endl;
		return;
	}
	new_file << "Total: " << total << endl;
	new_file << "Max: " << max->first << " (" << max->second << ")" << endl;
	new_file << "Words:\n";
	for (map<string, int>::iterator i = m.begin(); i != m.end(); i++)
		new_file << i->first << " (" << i->second << ")" << endl;
	new_file.close();
}