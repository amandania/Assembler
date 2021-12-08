//Name		:	Akshay Mandania
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	FileAccess.cpp

#include "stdafx.h"
#include "FileAccess.h"

FileAccess::FileAccess(int argc, char *argv[])
{
	// Check that there is exactly one run time parameter.
	if (argc != 2) {
		cerr << "Usage: Assem <FileName>" << endl;
		exit(1);
	}

	//do i even need this?
	m_sfile.open(argv[1], ios::in);

	// report errot and terminate if i fail to open file
	if (!m_sfile) {
		cerr << "Source file could not be opened, assembler terminated."
			<< endl;
		exit(1);
	}
}
FileAccess::~FileAccess()
{
	m_sfile.close();
}

bool FileAccess::GetNextLine(string &a_buff)
{
	//Reached end-of-file | there's no more data to be read
	if (m_sfile.eof()) {
		return false;
	}
	getline(m_sfile, a_buff);

	//Return true if a new line exists.
	return true;
}
void FileAccess::Rewind()
{
	// Clean tall file flags and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
}