#include "DBfile.h"
#include "screen.h"

dbfile::dbfile(
    string fileprefix, string table,
    int numIntFields, const char** IntFieldsNames,
    int numStrFields, const char** StrFieldsNames
    ) {
	bindbfilename = fileprefix + ".fl";
	txtdbfilename = "Input" + fileprefix + ".txt";
	tablename = table;
	num_intfields = numIntFields;
	intfieldnames = IntFieldsNames;
	num_strfields = numStrFields;
	strfieldnames = StrFieldsNames;
	master_dbfile = nullptr;
	newid = 1;
//	ReadTxt();
	Read();
}

dbfile::~dbfile() {
//	if (DBArray) delete(DBArray);
}

void dbfile::Print() {
	for (int i = 0; i < dbcount; i++) {
		DBArray[i].Print();
	}
}

void dbfile::Read() {
	ifstream fin(bindbfilename, std::ios::binary);
	if (fin.is_open()) {
		fin.read((char *) &dbcount, sizeof(int));
		DBArray.resize(dbcount);
		//DBArray = new db_object[dbcount];
		for (int i = 0; i < dbcount; i++) {
			DBArray[i].Init(num_intfields, intfieldnames, num_strfields, strfieldnames);
			DBArray[i].ReadFromDB(fin);
			int curid = DBArray[i].GetID();
			if (curid >= newid) {
				newid = curid + 1;
			}
		}
	}
	else {
	    cout << "DBRead: Error opening file " << bindbfilename << endl;
	    exit (1);
	}
	fin.close();
}

void dbfile::ReadTxt() {
	ifstream fin(txtdbfilename);
	if (fin.is_open()) {
		fin >> dbcount;
		DBArray.resize(dbcount);
		//DBArray = new db_object[dbcount];
		for (int i = 0; i < dbcount; i++) {
			DBArray[i].Init(num_intfields, intfieldnames, num_strfields, strfieldnames);
			DBArray[i].ReadFromTxtDB(fin);
			int curid = DBArray[i].GetID();
			if (curid >= newid) {
				newid = curid + 1;
			}
		}
	}
	else {
	    cout << "DBReadTxt: Error opening file " << txtdbfilename << endl;
	    exit (1);
	}
	fin.close();
}

void dbfile::Write() {
	int n = dbcount;
	ofstream fout(bindbfilename, std::ios::out|std::ios::binary);
	if (fout.is_open()) {
	    fout.write((char *) &n, sizeof(int));
		for (int i = 0; i < n; i++) {
			DBArray[i].WriteToDB(fout);
		}
	}
	else {
	    cout << "db::Write: Error opening file " << bindbfilename << endl;
	}
	fout.close();
}

void dbfile::WriteTxt() {
	int n = dbcount;
	ofstream fout(txtdbfilename, std::ios::out);
	if (fout.is_open()) {
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			DBArray[i].WriteToTxtDB(fout);
		}
	}
	else {
		cout << "db::Write: Error opening file " << txtdbfilename << endl;
	}
	fout.close();
}

int dbfile::Search() {
	int found = 0;
	if (dbcount <= 0) {
		cout << "DB is empty. Nothing to search";
	} else {
		db_object SearchExample;
		SearchExample.Init(num_intfields, intfieldnames, num_strfields, strfieldnames);
		SearchExample.ReadSearchExample();

		for (int i = 0; i < dbcount; i++) {
			if (DBArray[i].MatchExample(SearchExample)) {
				DBArray[i].Print();
				found = 1;
			}
		}
	}
	return found;
}

void dbfile::Delete() {
	int idDel;
	cout << "Type in the ID of the table row you want to delete: ";
	cin >> idDel;

	int i;
	for (i=0; i<dbcount; i++) {
	    if (DBArray[i].GetID() == idDel) {
		DBArray[i] = DBArray[dbcount - 1];
		dbcount--;
		DBArray.resize(dbcount);

	    }
	}

	Write();
	WriteTxt();
}

void dbfile::Edit() {
	int id;
	cout << "Type in the ID of the table row you want to edit:";
	cin >> id;

	int i;
	for (i=0; i<dbcount; i++) {
	    if (DBArray[i].GetID() == id) {
		DBArray[i].Edit();
	    }
	}
	Write();
	WriteTxt();
}

void dbfile::Add() {
	/*
	db_object* DBArray1 = new db_object[dbcount+1];
	int i;
	for (i=0; i<dbcount; i++) {
	    DBArray1[i] = DBArray[i];
	}
	*/
	dbcount++;
	DBArray.resize(dbcount);
	DBArray[dbcount-1].Init(num_intfields, intfieldnames, num_strfields, strfieldnames);
	DBArray[dbcount-1].ReadSTDIN(newid);
	newid++;
	//delete(DBArray);
	//DBArray = DBArray1;

	Write();
	WriteTxt();
}

string dbfile::DBMenu() {
	string stateM;
	cls();
	cout << "    Database table menu [" << tablename << "]\n"
		<< "(0) Exit menu\n"
		<< "(1) Add DB entry\n"
		<< "(2) Delete DB entry (affects master)\n"
		<< "(3) Edit DB entry\n"
		<< "(4) Print DB table\n"
		<< "(5) Search for DB entries\n"
		<< "(6) Import Text file\n"
		<< "(7) Write to Binary DB file\n"
		<< "(8) Export to Text file\n"
		<< "(9) Print Slave Tables\n"
		<< "(10) Print Master Tables\n"
		<< "Type a number from 0 to 9 to continue: ";
	cin >> stateM;
	cls();
	return stateM;
};

void dbfile::DBApp() {
	Read();
	string stateM;
	do {
		stateM = DBMenu();

		if (stateM == "1") {
			Add();
		}
		else if (stateM == "2") {
//			Delete();
//			Delete_from_master();
			DeleteWhileAffectingMaster();
			pause();
		}
		else if (stateM == "3") {
			Edit();
		}
		else if (stateM == "4") {
			Print();
			pause();
		}
		else if (stateM == "5") {
			int found = Search();
			if (!found) {
				cout << "Nothing found." << endl;
			}
			pause();
		}
		else if (stateM == "6") {
			ReadTxt();
			cout << "Import successful." << endl;
			pause();
		}
		else if (stateM == "7") {
			Write();
		}
		else if (stateM == "8") {
			WriteTxt();
		}
		else if (stateM == "9") {
			PrintSlaveDBFiles();
			pause();
		}
		else if (stateM == "10") {
			PrintMasterDBFile();
			pause();
		}
		else if (stateM != "0") {
			cout << "************************\n"
			     << "ERROR: incorrect option. Should be a number from 0 to 7\n"
			     << "************************\n";

		}

	} while (stateM != "0");
}

void dbfile::PrintFromAnotherTable(dbfile secondtable) {
	secondtable.Print();
}

void dbfile::InsertSlaveDBFile(dbfile* secondtable) {
	slave_dbfiles.push_back(secondtable);
}

void dbfile::SetMasterDBFile(dbfile* secondtable,int connected_id_index) {
	master_dbfile = secondtable;
	master_connected_id_index = connected_id_index;//for playerid or serverid
}

void dbfile::PrintSlaveDBFiles() {
	for (int i = 0; i < slave_dbfiles.size(); i++)
	{
		PrintFromAnotherTable(*slave_dbfiles[i]);
	}
}

void dbfile::PrintMasterDBFile() {
//	PrintFromAnotherTable(*master_dbfile);
	dbfile tmp_master = *master_dbfile;
	tmp_master.Print();
}


void dbfile::Print_Master_Intfields_at_connected_index() {
//	*master_dbfile->DBArray.Print();
//	for (int i = 0; i < dbcount; i++) {
//		DBArray[i].Print();
//	}

//	for (int i = 0; i < dbcount; i++) {
//		DBArray[i].Print();
//	}
}

void dbfile::DeleteWhileAffectingMaster() {

//	PrintMasterDBFile();

	int idDel;
	cout << "Type in the ID of the table row you want to delete: ";
	cin >> idDel;

	int i;
	for (i = 0; i < dbcount; i++) {
		if (DBArray[i].GetID() == idDel) {
			DBArray[i] = DBArray[dbcount - 1];
			dbcount--;
			DBArray.resize(dbcount);

		}
	}

	Write();
	WriteTxt();

	if (master_dbfile != nullptr) {
		DeleteWhileAffectingMaster_part2(*master_dbfile, idDel, master_connected_id_index);
//		PrintMasterDBFile();
	}
}

//todo: add to header
void dbfile::Delete_from_master() {
//	dbfile tmp_master = *master_dbfile;
//	tmp_master.Delete_if_matching_id(0, master_connected_id_index);
	Delete_from_master_part2(*master_dbfile);
}

void dbfile::DeleteWhileAffectingMaster_part2(dbfile master, int ID_to_delete, int intfield_index) {
	master.Delete_if_matching_id(ID_to_delete, intfield_index);
}

void dbfile::Delete_from_master_part2(dbfile master) {
	//	dbfile tmp_master = *master_dbfile;
	//	tmp_master.Delete_if_matching_id(0, master_connected_id_index);
	master.Delete();
}

void dbfile::Delete_if_matching_id(int ID_to_delete,int intfield_index) {
	int idDel = ID_to_delete;

	int i;
	bool intfield_matches;
	for (i = 0; i < dbcount; i++) {
		intfield_matches = DBArray[i].Check_if_intfield_matches(ID_to_delete, intfield_index);
		cout << intfield_matches << endl;
		if (intfield_matches = 1) {
			DBArray[i] = DBArray[dbcount - 1];
			dbcount--;
			DBArray.resize(dbcount);
		}
	}

	Write();
	WriteTxt();
}