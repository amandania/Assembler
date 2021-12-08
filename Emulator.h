//Name		:	Akshay Mandania
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	Emulator.h


#ifndef _EMULATOR_H
#define _EMULATOR_H

class Emulator {

public:

	const static int MEMSZ = 10000;	// The size of the memory of the VC3600.
	Emulator() {
		m_acceumulator = 0;
		memset(m_memory, 0, MEMSZ * sizeof(int));
	}
	// Records instructions and data into VC3600 memory.
	bool insertMemory(int a_location, int a_contents);

	// Runs the program recorded in memory.
	bool runProgram();

	enum MachineOpCode {
		MT_ADD = 1,
		MT_SUB = 2,
		MT_MULT = 3,
		MT_DIV = 4,
		MT_LOAD = 5,
		MT_STORE = 6,
		MT_READ =  7,
		MT_WRITE = 8,
		MT_B = 9,
		MT_BM = 10,
		MT_BZ = 11,
		MT_BP = 12,
		MT_HALT = 13
	};

private:
	void readLocation(int a_location);
	
	int m_memory[MEMSZ];       // The memory of the VC3600.
	int m_acceumulator;			// The accumulator for the VC3600
};

#endif
