//Name		:	Akshay
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	: Assembler.h	


#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"
#include "Errors.h"


class Assembler {

public:
	Assembler(int argc, char *argv[]);

	// Pass I - establish the locations of the symbols
	void PassI();

	// Pass II - generate a translation
	void PassII();

	// Display the symbols in the symbol table.
	void DisplaySymbolTable() { m_symtab.showSymblTable(); }

	// Run Emulator on the translation.
	void RunEmulator();

	// Structure that can information the Emulator will need.
	struct InstructionInfo {
		int location;
		int contents;
	};

private:
	
	// Output details of the line to the user, as well as the instruction itself.
	void convertedOutput(int a_instLocation, int a_operandLocation, int a_opCodeNum, string a_instruction, Instruction::InstructionType a_type);

	FileAccess m_facc;	    // File Access object
	SymbolTable m_symtab; // Symbol table object
	Instruction m_inst;	    // Instruction object
	Emulator m_emul;        // Emulator object
	vector <InstructionInfo> m_instructions;	// Vector of instruction information
};
