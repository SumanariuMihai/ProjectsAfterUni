#pragma once
#include <iostream>

class Var
{
	int* number=nullptr;
	long* bigint = nullptr;
	double* numberwithcomma = nullptr;
	char* varchar2 = nullptr;
	char* datetime = nullptr;
	bool* boolean = nullptr;

public:

	Var(int* number);
	Var(long* bigint);
	Var(double* numberwithcomma);
	Var(char* varchar2);
	Var(char* datetime);
	Var(bool* boolean);
	Var(Var* v);
	~Var();

	int* getNumber() { return this->number; }
	long* getBigint() { return this->bigint; }
	double* getNumberWithComma() { return this->numberwithcomma; }
	char* getVarchar2() { return this->varchar2; }
	char* getDateTime() { return this->datetime; }
	bool* getBoolean() { return this->boolean; }

	void setNumber(int* number) {	this->number = new int(*number);  }
	void setBigint(long* bigint) {	this->bigint = new long(*bigint);  }
	void setNumberWithComma(double* comma) {	this->numberwithcomma = new double(*comma);	}
	void setBoolean(bool* boolean) { this->boolean = new bool(*boolean); }
	void setVarchar2(char* varchar) {
		this->varchar2 = new char[sizeof(varchar) + 1];
		for (int i = 0; i < sizeof(varchar); i++)
			this->varchar2[i] = varchar[i];
	}
	void setDateTime(char* varchar) {
		if (sizeof(varchar) == 10) 
		{
			this->datetime = new char[sizeof(varchar) + 1];
			for (int i = 0; i < sizeof(varchar); i++)
				this->datetime[i] = varchar[i];
		}
		else {
			std::cout << "Please input a valid Date type!";
		}
	}



private:

};

Var::Var(int* number) {
	this->setNumber(number);
}

Var::Var(long* bigint) {
	this->setBigint(bigint);
}

Var::Var(double* numberwithcomma) {
	this->setNumberWithComma(numberwithcomma);
}

Var::Var(char* varchar2) {
	this->setVarchar2(varchar2);
}

Var::Var(char* datetime) {
	this->setDateTime(datetime);
}

Var::Var(bool* boolean) {
	this->setBoolean(boolean);
}

Var::Var(Var* v) {
	this->setNumber(v->getNumber());
	this->setBigint(v->getBigint());
	this->setNumberWithComma(v->getNumberWithComma());
	this->setVarchar2(v->getVarchar2());
	if (v->datetime != nullptr) this->setDateTime(v->getDateTime());
}

Var::~Var()
{
	delete[] number;
	delete[] bigint;
	delete[] numberwithcomma;
	delete[] datetime;
	delete[] varchar2;
	delete[] boolean;
}