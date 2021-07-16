#include<iostream>
#include "Parser.h"
#include "MySQLChecker.h"

using namespace std;

int main() {

	//int* x;
	//x = new int(10);
	//cout << x << ' ' << *x;

	Parser::printWords("SELECT * FROM TABLE tabel;");
	
	MySQLChecker checker;
	cout<< checker.getTypeOfCommand("CREATE TABLE tabel;");
	cout << checker.getTypeOfCommand("ALTER TABLE tabel DROP TABLE;");


	return 0;
}