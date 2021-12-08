//Name		:	Akshay Mandania
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	Errors.h


#ifndef _ERRORS_H
#define _ERRORS_H

class Errors {

public:

	// Initializes error reports.
	static void InitErrorReporting();

	// Records an error message.
	static void RecordError(string &a_emsg);

	// Displays the collected error message.
	static void DisplayErrors();

	// Detailing the messages
	static string CreateError( int a_loc, const string &a_errMsg );
	static string CreateError(const string &a_errMsg);

	// Display the most recent error recorded
	static string ReportCurrentError();

	// Checks if the Error array is empty or not
	static inline bool isError() {
		return !m_errors.empty();
	};

private:
	static int m_totalErrors; 
	static vector <string> m_errors;
};
#endif