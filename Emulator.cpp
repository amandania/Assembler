//Name		:	Akshay Mandania
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	Emulator.cpp


#include "stdafx.h"
#include "Emulator.h"


/**/
/*
	Emulator::insertMemory() Emulator::InsertMemory()

	NAME
		bool Emulator::insertMemory - inserts information to mem

	DESCRIPTION
		adds instructions for emulator to use. consists of 
			(1)op cde
			(2)location of op code

	RETURNS
		Returns true or false, true upon successful memory insertion,
		false if the insertion was attempted outside of the memory scope.

*/
/**/
bool Emulator::insertMemory(int a_location, int a_contents) {
	if (a_location > MEMSZ) {
		//THROW ERROR: out of memory.
		return false;
	} 
	m_memory[a_location] = a_contents;
	return true;
}


/**/
/*
	Emulator::runProgram() Emulator::runProgram()

	NAME
		bool Emulator::executeProgram - runs the instructions (in memory at this point)

	DESCRIPTION
		Find respective instruction and execute in order

	RETURNS
		Returns true upon successful execution of the program,
		false upon failure.

*/
/**/
bool Emulator::runProgram() {
	int currentLoc = 0;
	currentLoc = m_memory[currentLoc];
	for (; currentLoc < MEMSZ; ) {
		string contents = to_string(m_memory[currentLoc]);
		string opCode = "";
		string location = "";
		unsigned it = 0;

		// Get contents of the memory location :: Opcode | Location
		if (stoi(contents) > 99999) {

			//opcode is between 10 and 13
			for (; it < 2; ++it) opCode = opCode + contents[it];
			for (; it < contents.size(); ++it) location = location + contents[it];
		}
		else {
			for (; it < 1; ++it) opCode = opCode + contents[it];
			for (; it < contents.size(); ++it) location = location + contents[it];

		}

		int opCodeVal = stoi(opCode);
		int locationVal = stoi(location);

		// Switch statement determining what instruction was at the location and executing the command
		switch (opCodeVal) {
		case MT_ADD:
			m_acceumulator = m_acceumulator + m_memory[locationVal];
			break;
		case MT_SUB:
			m_acceumulator = m_acceumulator - m_memory[locationVal];
			break;
		case MT_MULT:
			m_acceumulator = m_acceumulator * m_memory[locationVal];
			break;
		case MT_DIV:
			if (m_memory[locationVal] == 0) {
				cout << "ERROR:: DIVISION BY ZERO" << endl;
				exit(1);
			}
			else m_acceumulator = m_acceumulator / m_memory[locationVal];
			break;
		case MT_LOAD:
			m_acceumulator = m_memory[locationVal];
			break;
		case MT_STORE:
			m_memory[locationVal] = m_acceumulator;
			break;
		case MT_READ:
			readLocation(locationVal);
			break;
		case MT_WRITE:
			cout << m_memory[locationVal] << endl;
			break;
		case MT_B:
			currentLoc = locationVal;
			continue;
		case MT_BM:
			if (m_acceumulator < 0) {
				currentLoc = locationVal;
				continue;
			}
			break;
		case MT_BZ:
			if (m_acceumulator == 0) {
				currentLoc = locationVal;
				continue;
			}
			break;
		case MT_BP:
			if (m_acceumulator > 0) {
				currentLoc = locationVal;
				continue;
			}
			break;
		case MT_HALT:
			return true;
			break;
		default:
			//Err
			cout << "Unknown Operation Code :: Terminating Failure" <<endl;
			return false;
		}
		currentLoc++;
	}
	return false;
}


/**/
/*
	Emulator::readLocation() Emulator::readLocation()

	NAME
		void Emulator::readLocation

			a_location,	the integer value of the current location

	DESCRIPTION
		The function is responsible for error checking read input from
		the user, and storing it in the accumulator.

	RETURNS
		((void))

*/
/**/
void Emulator::readLocation(int a_location) {
	string input;
	bool isAlpha = true;
	while (isAlpha) {
		cout << "? ";
		cin >> input;
		for (auto it = input.begin(); it != input.end(); ++it) {
			if (isdigit(*it)) {
				isAlpha = false;
				continue;
			}
			else if (*it == '-' && it == input.begin()) {
				continue;
			}
			else {
				isAlpha = true;
				cout << "Error :: Input is not integer." << endl;
				break;
			}
		}
	}
	int value = stoi(input);
	m_memory[a_location] = value;
}