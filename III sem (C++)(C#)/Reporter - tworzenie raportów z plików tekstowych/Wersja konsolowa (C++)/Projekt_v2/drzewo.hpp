#include "algorytm.hpp"

class Node {
	friend class Tree;
protected:
	string word;
	int n;
	Node *left;
	Node *right;
public:
	Node(const string&);
	void operator++();
	bool operator==(const string&);
	bool operator>(const string&);
	bool operator<(const string&);
	void PrintData();
	void WriteData(fstream&);
	virtual ~Node();
};
class Tree : public Algorithm {
	Node *root;
	int total; // ca�kowita liczba s��w
	Node *max;	// element o najwi�kszej ilo�ci wyst�pie�
public:
	Tree();
	void insert(const string&);
	int Read(char *filename);
	void PrintNode(Node*);
	void Print();
	void WriteNode(Node*, fstream&);
	void Write();
	void Clear(Node*);
	~Tree();
};