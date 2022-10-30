#pragma once

#include <iostream>
#include <string>

#include "DB_Object.h"
#include <vector>

using namespace std;

class dbfile {

	struct primary_key_link
	{
		dbfile* db;
		int id_index;
	};

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

	std::vector<primary_key_link> slave_dbfiles;
	std::vector<primary_key_link> master_dbfiles;

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
	void Edit();
	void Add();
	int Search();
	string DBMenu();
	void DBApp();
	void SetMasterForDBFile(dbfile* secondtable, int connected_id_index);
	void PrintSlaveDBFiles();
	void Delete();
	void RawDelete(int idDel);
	void DeleteWhileAffectingSlaves();
	void Delete_if_matching_id(int ID_to_delete, int intfield_index);
};
