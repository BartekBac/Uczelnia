#pragma once
#include <string>
#include <iostream>
//G£OWNA KLASA WYJ¥TKÓW
class LEexception {
	std::string message_text;
public:
	LEexception(const std::string &msg = "Wykryto nieznany wyj¹tek") : message_text(msg) {}
	std::string GetMessage() { return message_text; }
	~LEexception() {}
};

//KLASY POCHODNE WYJ¥TKÓW
class CancelEx : public LEexception { //klasa anulowania jakiegoœ wyboru
public:
	CancelEx() : LEexception("Anulowano wybor") {}
};

class RaceCondition : public LEexception { //klasa wyj¹tku wykrycia pêtli w uk³adzie
public:
	RaceCondition() : LEexception("Wykryto petle w ukladzie\n") {}
};

class WrongConstructorParameter : public LEexception {
public:
	WrongConstructorParameter() : LEexception("Podany argument w knstruktorze jest niepoprawny\n") {}
};

class IO_OutOfRange : public LEexception {
public:
	IO_OutOfRange() : LEexception("Przekroczono zakres wejsc/wyjsc elemntu logicznego\n") {}
};