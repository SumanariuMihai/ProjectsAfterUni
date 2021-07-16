#pragma once
#include<iostream>
#include<fstream>
#include<list>

using namespace std;

class Parser
{
public:
	Parser();
	~Parser();

	static void printWords(string statement) {
		list<string> words = Parse(statement);
		list<string>::iterator it;
		if (!words.empty())
		{
			for (it = words.begin(); it != words.end(); ++it)
			{
				cout << it->c_str() << endl;
			}
		}
	}

	static list<string> Parse(string statement) {
		list<string> words;
		int statementIndex = 0;
		for (int i = 0; i < statement.size() - 1; i++)
		{
			if (statement[i] == ';')
			{
				cout << "Invalid Command! Please try again!"; return words;
			}
		}
		if (statement[statement.size()-1] != ';')
		{
			cout << "Invalid Command! Please try again!"; return words;
		}
		while (statement[statementIndex] != ';')
		{
			IgnoreSpaces(statement, statementIndex);
			ParseWord(statement, statementIndex, words);
			IgnoreSpaces(statement, statementIndex);
			ParseSymbol(statement, statementIndex, words);
		}

		return words;
	}
	

private:

	static void ParseWord(string statement, int& startOfString, list<string>& wordsList) {
		int substringIndex = 0;
		int clone = startOfString;
		while (!isSpaceCommaParanthesisOrEndOfLine(statement[clone]))
		{
			substringIndex++;
			clone++;
			if (statement[clone] == ';')
				break;
		}
		string word = statement.substr(startOfString, substringIndex);
		wordsList.push_back(word);
		startOfString += substringIndex;
	}

	static void ParseSymbol(string statement, int& startOfString, list<string>& wordsList) {
		if (isSpaceCommaParanthesisOrEndOfLine(statement[startOfString]) && statement[startOfString] != ' ')
		{
			string symbol="x";
			symbol[0] = statement[startOfString];
			wordsList.push_back(symbol);
			startOfString+=1;
		}
	}

	static bool isSpaceCommaParanthesisOrEndOfLine(char checked)
	{
		switch (checked) {
		case ' ': return true;
		case ',': return true;
		case '(': return true;
		case ')': return true;
		case '[': return true;
		case ']': return true;
		case '{': return true;
		case '}': return true;
		default: return false;
		}
	}

	static void IgnoreSpaces(string statement, int &startOfString) {
		while (statement[startOfString] == ' ') {
			startOfString++;
		}
		
	}
};

Parser::Parser(){}

Parser::~Parser()
{
}