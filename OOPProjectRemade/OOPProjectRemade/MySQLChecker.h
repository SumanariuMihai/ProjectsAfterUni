#pragma once
#include "Parser.h"

class MySQLChecker
{
public:
	MySQLChecker();
	~MySQLChecker();

	string getTypeOfCommand(string statement)
	{
		if (isAlterTable(statement)) return "Este de tipul Alter Table";
		else if (isCreateTable(statement)) return "Este de tipul Create Table";
		else return "Nu stiu";
	}

private:

	bool isAlterTable(string statement)
	{
		list<string> words = Parser::Parse(statement);
		list<string>::iterator it;
		bool endChecker;
		bool onlyOneCheckerAlter = true;
		bool onlyOneCheckerTable = true;
		bool alterChecker = false;
		bool tableChecker = true;
		int wordsChecker = 0;
		
		for (it = words.begin(); it != words.end(); ++it)
		{
			if (tableChecker == true) wordsChecker++;
			ifSameAndOnlyChangeCheckers(it, "ALTER", alterChecker, onlyOneCheckerAlter);
			ifSameAndOnlyChangeCheckers(it, "TABLE", tableChecker, onlyOneCheckerTable);
		}

		if (onlyOneCheckerAlter == true &&
			onlyOneCheckerTable==true &&
			alterChecker == true &&
			tableChecker == true &&
			wordsChecker >= 3)
		{
			endChecker = true;
		}
		else
			endChecker = false;

		return endChecker;
	}
	
	bool isCreateTable(string statement)
	{
		list<string> words = Parser::Parse(statement);
		list<string>::iterator it;
		bool endChecker;
		bool onlyOneCheckerCreate=true; 
		bool onlyOneCheckerTable = true;
		bool createChecker = false;
		bool tableChecker = false;
		bool notLastWordTable = false;
		int leftParanthesisCounter = 0;
		int rightParanthesisCounter = 0;
		
		for (it = words.begin(); it != words.end(); ++it)
		{
			if (tableChecker == true) notLastWordTable = true;
			ifSameAndOnlyChangeCheckers(it, "CREATE", createChecker, onlyOneCheckerCreate);
			ifSameAndOnlyChangeCheckers(it, "TABLE", createChecker, onlyOneCheckerTable);
			ifSameAddToCounter(it, "(", leftParanthesisCounter);
			ifSameAddToCounter(it, ")", rightParanthesisCounter);
		}

		if (createChecker == true &&
			tableChecker == true &&
			onlyOneCheckerCreate == true &&
			onlyOneCheckerTable==true &&
			leftParanthesisCounter > 0 &&
			leftParanthesisCounter == rightParanthesisCounter
			&& notLastWordTable==true)
		{
			endChecker = true;
		}
		else endChecker = false;

		return endChecker;
	}

	void ifSameAddToCounter(list<string>::iterator word1, const char* word2, int &counter){
		if (strcmp(word1->c_str(), word2))	counter++;
	}

	void ifSameAndOnlyChangeCheckers(list<string>::iterator word1, const char* word2, bool &wordChecker, bool &onlyOneChecker) {
		if (strcmp(word1->c_str(), word2))
			if (wordChecker == false)
				wordChecker = true;
			else onlyOneChecker = false;
	}
};

MySQLChecker::MySQLChecker()
{
}

MySQLChecker::~MySQLChecker()
{
}