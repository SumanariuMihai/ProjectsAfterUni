#pragma once
#include<vector>
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
		vector<string> words = Parser::Parse(statement);
		vector<string>::iterator it = words.begin();;
		vector<string>::iterator previousIt = words.begin();
		bool endChecker;
		bool onlyOneCheckerAlter = true;
		bool onlyOneCheckerTable = true;
		bool alterChecker = false;
		bool tableChecker = false;
		int wordsChecker = 0;

		ifSameAndOnlyChangeCheckers(words[0], "ALTER", alterChecker, onlyOneCheckerAlter);
		ifSameAndOnlyChangeCheckers(words[1], "TABLE", tableChecker, onlyOneCheckerTable);
		if (alterChecker == true && tableChecker == true)
		{
			it += 2;
			for (it; it != words.end(); ++it)
			{
				if (tableChecker == true) wordsChecker++;
				ifSameAndOnlyChangeCheckers(it, "ALTER", alterChecker, onlyOneCheckerAlter);
				if(strcmp(previousIt->c_str(),"DROP")!=0)
					ifSameAndOnlyChangeCheckers(it, "TABLE", tableChecker, onlyOneCheckerTable);
				previousIt = it;
			}

			if (onlyOneCheckerAlter == true &&
				onlyOneCheckerTable == true &&
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
		else
		{
			endChecker = false;
			return endChecker;
		}
	}
	
	bool isCreateTable(string statement)
	{
		vector<string> words = Parser::Parse(statement);
		vector<string>::iterator it;
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

	void ifSameAddToCounter(vector<string>::iterator word1, const char* word2, int &counter){
		if (strcmp(word1->c_str(), word2)==0)	counter++;
	}

	void ifSameAndOnlyChangeCheckers(vector<string>::iterator word1, const char* word2, bool &wordChecker, bool &onlyOneChecker) {
		if (strcmp(word1->c_str(), word2)==0)
		{
			if (wordChecker == false)
				wordChecker = true;
			else onlyOneChecker = false;
		}
	}

	void ifSameAndOnlyChangeCheckers(string word1, const char* word2, bool& wordChecker, bool& onlyOneChecker) {
		if (strcmp(word1.c_str(), word2) == 0)
		{
			if (wordChecker == false)
				wordChecker = true;
			else onlyOneChecker = false;
		}
	}
};

MySQLChecker::MySQLChecker()
{
}

MySQLChecker::~MySQLChecker()
{
}