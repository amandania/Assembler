//Name		:	Akshay Mandania
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	Assembler.cpp

#include "stdafx.h"
#include "Assembler.h"

/**/
/*
	Assembler::Assembler() Assembler::Assembler
	NAME
		Assembler::Assembler
	
	DESCRIPTION
		Opening the file in the command line arguments for program use
		using the FileAccess class.
	RETURNS
		((void))
*/
/**/
Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
}
/**/

/*
	Assembler::PassI() Assembler::PassI()
	NAME
		void Assembler::PassI
	DESCRIPTION
		This function is responsible for:
				(1) Identifying the instruction type of a line.
				(2) Filling in the symbol table for the whole text file.
				(3) Error checks, however, no errors are saved in this.

	RETURNS
		((void))
*/
/**/
void Assembler::PassI() {
	Errors::InitErrorReporting(); //required for errors
	int loc = 0;

	// Loop is for gathering each line in a file to the end.
	for ( ; ; ) {

		// Read in a line from the file to be parsed.
		string buff;
		if (!m_facc.GetNextLine(buff)) {
			return;
		}

		// get instruction type of line
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);
		cout << buff << endl;
		
		// end of pass 2
		if (st == Instruction::ST_End) return;

		// Only labels requried languages otherwise skip to new line
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) continue;
		if (m_inst.isLabel()) {
			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		loc = m_inst.LocationNextInstruction(loc);
	}
	system("pause");
}

/**/
/*
	Assembler::PassII() void Assembler::PassII()
	NAME
		void Assembler::PassII
	DESCRIPTION
		This function is responsible for:
				(1) Translating each line into instruction code.
				(2) Finding each error, and reporting them accordingly.
	RETURNS
		((void))
*/
/**/
void Assembler::PassII() {

	Errors::InitErrorReporting();
	m_facc.Rewind();

	int loc = 0;
	int operandLoc = 0;
	cout << "____________________________________________________________" << endl;
	cout << "Translation of Program : " << endl << endl;
	cout << "Location\tContents\tOriginal Instruction" <<endl;
	for (; ; ) {
		string buff;
		if (!m_facc.GetNextLine(buff)) {

			Errors::RecordError(Errors::CreateError(loc, string("[ERROR] missing assembly language END statement. Unable to continue...")));
			return;
		}

		Instruction::InstructionType st = m_inst.ParseInstruction(buff);
		if (st == Instruction::ST_End) {
			if (m_facc.GetNextLine(buff)) {
				Errors::RecordError(Errors::CreateError(loc, string("statement after assembly language END instruction.")));
				Errors::ReportCurrentError();
			}
			return;
		}
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) {
			convertedOutput(loc, operandLoc, m_inst.GetOpCodeNum(), buff, st);
			continue;
		}
		operandLoc = 0;

		if (!m_inst.GetOperand().empty() && !m_inst.isNumericOperand() && !m_symtab.findSmbl(m_inst.GetOperand(), operandLoc)) {

			if (operandLoc == -999) {
				Errors::RecordError(Errors::CreateError(loc, string("multiply defined variable named - " + m_inst.GetOperand())));
				Errors::ReportCurrentError();
			}
			else {
				Errors::RecordError(Errors::CreateError(loc, string("undefined variable named - " + m_inst.GetOperand())));
				m_symtab.AddSymbol(m_inst.GetOperand(), m_symtab.undefinedSymbol);
				Errors::ReportCurrentError();
			}
		}

		// Output the line according to the translated values
		convertedOutput(loc, operandLoc, m_inst.GetOpCodeNum(), buff, st);
		if (loc > Emulator::MEMSZ) {
			Errors::RecordError(Errors::CreateError(loc, "current location exceeds memory."));
			Errors::ReportCurrentError();
		}
		loc = m_inst.LocationNextInstruction(loc);
	}
	system("pause");
}

/**/
/*
	Assembler::convertedOutput() Assembler::convertedOutput()
	NAME
		void Assembler::convertedOutput
	DESCRIPTION
		This function's purpose is to display the line information and
		translation to the user, using the above variables. As well as
		store the required variables into memory.
	RETURNS
		((void))
*/
/**/
void Assembler::convertedOutput(int a_instLocation, int a_operandLocation, int a_opCodeNum, string a_instruction, Instruction::InstructionType a_type) {
	string contents = "";
	Assembler::InstructionInfo temp;
	stringstream stream;
	int location= a_operandLocation;

	
	// If Comment or an END statement then output the contents.
	if (Instruction::ST_Comment == a_type) {
		cout << "\t\t\t   " << a_instruction << endl;
		return;
	}
	if (Instruction::ST_End == a_type) {
		cout << "\t\t\t   " << a_instruction << endl;
		return;
	}

	// If it was an assembler instruction
	if (Instruction::ST_AssemblerInstr == a_type) {
	
		// ORG and DS instructions do not get "contents" ie operandLocation/opCodNum
		if ("ORG" == m_inst.GetOpCode() ||"DS" == m_inst.GetOpCode()) {
			cout << "  " << a_instLocation << "\t\t\t   " << a_instruction << endl;
			if ("ORG" == m_inst.GetOpCode()) {
				stream.str(string());
				stream << setfill('0') << setw(6) << m_inst.GetOperandVal();
				contents = stream.str();
				temp.contents = stoi(contents);
				temp.location = int(a_instLocation);
				Assembler::m_instructions.push_back(temp);
			}
			return;
		}

		// If it was AL :: we are getting the numerical val or location
		location =  m_inst.GetOperandVal();
	}
	stream.str(string());
	stream << setfill('0') << setw(2) << a_opCodeNum << setw(4) << location;
	contents = stream.str();


	temp.contents = stoi(contents);
	temp.location = int(a_instLocation);
	cout << "  " << a_instLocation << "\t\t" << contents << "\t   " << a_instruction << endl;
	Assembler::m_instructions.push_back(temp);
	return;
}
/**/
/*
	Assembler::RunEmulator() Assembler::RunEmulator()
	NAME
		void Assembler::RunEmulator
	DESCRIPTION
		This function will run the Emulator and output the running
		program to the user upon no errors.
	RETURNS
		((void))
*/
/**/
void Assembler::RunEmulator() {
	if (Errors::isError()) {
		Errors::DisplayErrors();
		return;
	}
	else {
	
		for (auto it = Assembler::m_instructions.begin(); it != Assembler::m_instructions.end(); ++it) {
			if (Assembler::m_emul.insertMemory(it->location, it->contents)) continue;
			else {
				Errors::RecordError(string("out of memory."));
				cout << Errors::ReportCurrentError();
				exit(1);
			}
		}
	}

	if (m_emul.runProgram()) {
		cout << "Exit successful" << endl;
	}
	else cout << "Exit failure, unable to complete program." << endl;
	return;
}