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
	int master_connected_id_index;
	dbfile* master_dbfile;

	std::vector<dbfile*> slave_dbfiles;
	//	std::vector<dbfile> connected_dbfiles;
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
	void InsertSlaveDBFile(dbfile* secondtable);
	void SetMasterDBFile(dbfile* secondtable, int connected_id_index);
	void PrintSlaveDBFiles();
	void PrintMasterDBFile();
	void Print_Master_Intfields_at_connected_index();
	void DeleteWhileAffectingMaster();
	void Delete_if_matching_id(int ID_to_delete, int intfield_index);
	void Delete_from_master();
	void Delete_from_master_part2(dbfile master);
	void DeleteWhileAffectingMaster_part2(dbfile master, int ID_to_delete, int intfield_index);
};