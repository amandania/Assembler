//Name		:	Akshay Mandania
//Course	:	CMPS361 - Software Design
//Project	:	Assembler
//Instructor:	Professor Victor Miller
//Current File	:	Errors.cpp

#include "stdafx.h"
#include "Errors.h"

// Initialize the space for the static variables.
vector<string> Errors::m_errors;
int Errors::m_totalErrors;

/**/
/*
		Errors::InitErrorReporting() Errors::InitErrorReporting()
	NAME
		void Errors::InitErrorReporting

	SYNOPSIS
		void Errors::InitErrorReporting()

	DESCRIPTION
		This function is responsible for clearing out the error message
		vector, and initialize error counting.

	RETURNS
		((void))

*/
/**/
void Errors::InitErrorReporting() {
	m_totalErrors = 0;

	//Clearing out any errors that would possibly be within the Error Class already
	if (m_errors.empty()) {
		return;
	}
	m_errors.clear();
	return;
}
/*void Errors::InitErrorReporting()*/


/**/
/*
		Errors::RecordError() Errors::RecordError()
	NAME
		void Errors::RecordError

	SYNOPSIS
		void Errors::RecordError(string &a_emsg)

	DESCRIPTION
		This function is responsible for adding Error messages (strings) to
		the Error message vector, namely m_errors.

	RETURNS
		((void))

*/
/**/
void Errors::RecordError(string &a_emsg) {
	if (a_emsg.empty()) return;
	m_errors.push_back(a_emsg);
	m_totalErrors ++;
	return;
}
/*void Errors::RecordError(string &a_emsg);*/


/**/
/*
		Errors::DisplayErrors() Errors::DisplayErrors()
	NAME
		void Errors::DisplayErrors

	SYNOPSIS
		void Errors::DisplayErrors()

	DESCRIPTION
		This function is responsible for displaying the error messages,
		if any, acummulated to the user.

	RETURNS
		((void))

*/
/**/
void Errors::DisplayErrors() {
	if (m_errors.empty()) {
		cout << "Translated Successfully!" << endl;
		return;
	}

	cout << m_totalErrors << " ERROR REPORTS::" << endl;
	for (auto it = m_errors.begin(); it != m_errors.end(); ++it) {
		cout << *it << endl;
	}
}
/*void Errors::DisplayErrors();*/


/**/
/*
		Errors::CreateError() Errors::CreateError()
	NAME
		string Errors::CreateError

	SYNOPSIS
		string Errors::CreateError(int a_loc, const string &a_errMsg)

			a_loc		-> the location where the error occurred.
			a_errMsg	-> the message describing the error.

	DESCRIPTION
		This function is responsible for creating an error message string
		and returning it.

	RETURNS
		Returns a string with the error message specified.

*/
/**/
string Errors::CreateError(int a_loc, const string &a_errMsg) {
	string location = to_string(a_loc);

	return ("Error at location " + location + " :: " + a_errMsg + '\n');
}
/*string Errors::CreateError(int a_loc, const string &a_errMsg);*/


/**/
/*
		Errors::CreateError() Errors::CreateError()
	NAME
		string Errors::CreateError

	SYNOPSIS
		string Errors::CreateError(const string &a_errMsg)

			a_errMsg	-> the message describing the error.

	DESCRIPTION
		This function is responsible for creating an error message string
		and returning it.

	RETURNS
		Returns a string with the error message specified.

*/
/**/
string Errors::CreateError(const string &a_errMsg) {
	return ("Error ::" + a_errMsg + '\n');
}
/*string Errors::CreateError(const string &a_errMsg);*/


/**/
/*
		Errors::ReportCurrentError() Errors::ReportCurrentError()
	NAME
		string Errors::ReportCurrentError

	SYNOPSIS
		string Errors::ReportCurrentError()

	DESCRIPTION
		This function is responsible for returning the most recent
		error message produced.

	RETURNS
		Returns a string with the latest error message.

*/
/**/
string Errors::ReportCurrentError() {
	if( !m_errors.empty() ) return m_errors.back();
	else return string("No Errors To Report");
}
/*string Errors::ReportCurrentError();*/