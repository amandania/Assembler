//Name		:	Akshay Mandania
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	SymbTab.cpp

#include "stdafx.h"
#include "SymTab.h"

/**/
/*
	SymbolTable::AddSymbol() SymbolTable::AddSymbol()
	NAME
		void SymbolTable::AddSymbol

	DESCRIPTION
		This funciton is responsible for adding a new operand or label along with
		the location to the symbol. Will keep track of arguments defined multiple times.
	RETURN
		((void))
*/
/**/
void SymbolTable::AddSymbol(string &a_symbol, int a_loc) {
	
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end() && !m_symbolTable.empty()) {
		st->second = multiplyDefinedSymbol;
		return;
	}

	m_symbolTable[a_symbol] = a_loc;
	return;
}

/*
	SymbolTable::showSymblTable() SymbolTable::showSymblTable()
	NAME
		void SymbolTable::showSymblTable
	DESCRIPTION
		This function is responsible displaying the Symbol Table
		to the user.
	RETURNS
		((void))
*/
void SymbolTable::showSymblTable() {
	int symNum = 0;
	printf("Symbol # \tSymbol\tLocation\n");
	for ( auto it = m_symbolTable.begin(); it != m_symbolTable.end(); ++it, ++symNum) {
		cout << symNum << "\t\t " << it->first << "\t " << it->second << endl;
	}
	return;
}

/*
	SymbolTable::findSmbl() SymbolTable::findSmbl()
	NAME
		void SymbolTable::findSmbl
	DESCRIPTION
		Responsible to locate smbl based on symbol.
	RETURNS
		((true false based on smbl existing in location))
*/
bool SymbolTable::findSmbl(string &a_symbol, int &a_loc) {
	auto it = m_symbolTable.find(a_symbol);
	if (it != m_symbolTable.end()){
		a_loc = it->second;
		return true;
	}
	else {
		a_loc = undefinedSymbol;
		return false;
	}
}