#pragma once

#include <iostream>
#include <string>

#include "DB_Object.h"
#include <vector>

using namespace std;

class dbfile {
private:
	string txtdbfilename;
	string bindbfilename;
	string tablename;
	int num_strfields;
	const char** strfieldnames;
	int num_intfields;
	const char** intfieldnames;
	int dbcount;
	int newid;
	//db_object* DBArray;
	std::vector<db_object> DBArray;
public:
	dbfile(string fileprefix, string table,
	       int numIntFields, const char** IntFieldsNames,
	       int numStrFields, const char** StrFieldsNames);
	~dbfile();

	void Print();
	void Read();
	void ReadTxt();
	void Write();
	void WriteTxt();
	void Delete();
	void Edit();
	void Add();
	int Search();
	string DBMenu();
	void DBApp();
	void PrintFromAnotherTable(dbfile secondtable);
	void DeleteFromAnotherTable(dbfile secondtable);
};
