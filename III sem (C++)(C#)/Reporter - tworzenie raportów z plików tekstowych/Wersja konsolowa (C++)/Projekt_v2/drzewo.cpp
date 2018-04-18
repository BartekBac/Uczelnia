#include "drzewo.hpp"

//METODY KLASY NodeData
Node::Node(const string &w) : word(w), n(1), left(nullptr), right(nullptr) {};
void Node::operator++() { n++; }
string prepareWord(const string &w)
{
	string tmp = w;
	for (int i = 0; i<w.size(); i++)
	{
		tmp[i] = tolower(tmp[i]);
	}
	return tmp;
}
bool Node::operator==(const string &w)
{//zwraca true gdy to samo s³owo
	if (prepareWord(w) == prepareWord(word))
		return true;
	else
		return false;
}
bool Node::operator>(const string &w)
{//zwraca true gdy s³owo (sk³adnik obiektu) jest wiêksze od s³owa argumentu w rozumieniu porz¹dku s³ownikowego 
	if (prepareWord(word) > prepareWord(w))
		return true;
	else
		return false;
}
bool Node::operator<(const string &w)
{//zwraca true gdy s³owo (sk³adnik obiektu) jest mniejsze od s³owa argumentu w rozumieniu porz¹dku s³ownikowego
	if (prepareWord(word) < prepareWord(w))
		return true;
	else
		return false;
}
void Node::PrintData()
{
	cout << "Pisze z metody Node: " << word << " (" << n << ")" << endl;
}
void Node::WriteData(fstream &file)
{
	file << word << " (" << n << ")\n";
}
Node::~Node()
{
	left = nullptr;
	right = nullptr;
	cout << "Zwalniam Node" << endl;
}


//METODY KLASY Tree
Tree::Tree() : root(nullptr) {};
void Tree::insert(const string &w)
{
	Node *new_node = new Node(w);
	if (!root)
	{
		root = new_node;
		max = new_node;
		return;
	}
	else {
		Node *tmp = root;
		while (tmp)
		{
			while (*tmp>(w))
			{
				if (!tmp->left)
				{//Gdy wêze³ nie ma mniejszego dziecka
					tmp->left = new_node;
					//wstawiamy w to miejsce nowy wêze³
					return;
				}//inaczej siê przesuwamy
				tmp = tmp->left;
			}
			while (*tmp<w)
			{
				if (!tmp->right)
				{//Gdy wêze³ nie ma wiêkszego dziecka
					tmp->right = new_node;
					//wstawiamy w to miejsce nowy wêze³
					return;
				}//inaczej siê przesuwamy
				tmp = tmp->right;
			}
			if (*tmp == w)
			{//Gdy dane s³owo ju¿ jest w drzewie
				tmp->operator++();
				if (tmp->n > max->n&&tmp != max)
					max = tmp;
				delete new_node;
				return;
				//zwiêkszamy jego licznik i zwalniamy zaalokowan¹ niepotrzebnie pamiêæ
			}
		}
	}
}
int Tree::Read(char *filename)
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
		total++;
		insert(w);
	}
	file.close();
	return 1;
}
void Tree::PrintNode(Node *r)
{
	if (!r)
		return;
	if (r->left)
		PrintNode(r->left);
	r->PrintData();
	if (r->right)
		PrintNode(r->right);
}
void Tree::Print()
{
	cout << "Total: " << total << endl;
	cout << "Max: " << max->word << " (" << max->n << ")" << endl;
	PrintNode(root);
}
void Tree::WriteNode(Node *r, fstream &file)
{
	if (!r)
		return;
	if (r->left)
		WriteNode(r->left, file);
	r->WriteData(file);
	if (r->right)
		WriteNode(r->right, file);
}
void Tree::Write()
{
	fstream new_file;
	string name = fname;
	name.erase(name.size() - 4);
	name += "-raport(drzewo).txt";
	new_file.open(name, ios_base::out);
	if (!new_file.good())
	{
		cerr << "Blad obslugi pliku." << endl;
		return;
	}
	new_file << "Total: " << total << endl;
	new_file << "Max: " << max->word << " (" << max->n << ")" << endl;
	new_file << "Words:\n";
	WriteNode(root, new_file);
	new_file.close();
}
void Tree::Clear(Node *r)
{
	if (r->left)
		Clear(r->left);
	if (r->right)
		Clear(r->right);
	delete r;
	r = nullptr;
}
Tree::~Tree()
{
	if (root)
	{
		Clear(root);
		root = nullptr;
		max = nullptr;
	}
}