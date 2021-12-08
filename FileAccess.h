//Name		:	Akshay Mandania
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	FileAccess.h


#pragma once

#ifndef _FILEACCESS_H
#define _FILEACCESS_H

class FileAccess {

public:

	// Opens the file.
	FileAccess(int argc, char *argv[]);

	// Closes the file.
	~FileAccess();

	// Get the next line from the source file.
	bool GetNextLine(string &a_buff);

	// Put the file pointer back to the beginning of the file.
	void Rewind();

private:

	ifstream m_sfile;		// Source file object.
};
#endif
