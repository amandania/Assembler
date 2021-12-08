#pragma once

class SymbolTable {

public:

	const int multiplyDefinedSymbol = -999;
	const int undefinedSymbol = -990;

	// Add a new symbol to the symbol table.
	void AddSymbol(string &a_symbol, int a_loc);

	// Display the symbol table.
	void showSymblTable();

	// Lookup a symbol in the symbol table.
	bool findSmbl(string &a_symbol, int &a_loc);

private:

	// This is the actual symbol table.  The symbol is the key to the map.
	map<string, int> m_symbolTable;
};