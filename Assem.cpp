//Name		:	Akshay
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	Assem.cpp

#include "stdafx.h"
#include <stdio.h>

#include "Assembler.h"

int main(int argc, char *argv[])
{
	Assembler assem(argc, argv);

	// Setup Locations and Symbl Tbl
	assem.PassI();
	system("pause");

	// Display the symbol table.
	assem.DisplaySymbolTable();
	system("pause");

	// Output the symbol table and the translation.
	assem.PassII();
	system("pause");

	// Run the emulator
	assem.RunEmulator();
	system("pause");
	
	return 0;
}