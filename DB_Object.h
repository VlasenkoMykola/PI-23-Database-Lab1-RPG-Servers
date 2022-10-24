#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class db_object {
protected:
	int ID;
	int num_strfields;
	string* strfield;
	const char** strfieldname;
	int num_intfields;
	const char** intfieldname;
	int* intfield;

public:

	db_object();
	~db_object();
	int GetID() { return ID; };
	void Init(int numIntFields, const char** IntFieldNames, int numStrFields, const char** StrFieldNames);
	void Print();
	void Edit();
	void WriteToTxtDB(ofstream& fout);
	void WriteToDB(ofstream& fout);
	void ReadFromTxtDB(ifstream& fin);
	void ReadFromDB(ifstream& fin);
	void ReadSTDIN(int Id);
	void ReadSearchExample();
	int MatchExample(db_object example);
	void Print_intfield(int index);
	bool Check_if_intfield_matches(int value_to_check, int intfield_index);
};