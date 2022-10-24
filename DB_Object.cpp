#include "DB_Object.h"
#include <cstring>

#define STR_FIELD_SIZE 256
static char STR_FIELD_BUFFER[STR_FIELD_SIZE];

db_object::db_object() {
	ID = 0;
	num_intfields = 0;
	num_strfields = 0;
}

db_object::~db_object() {
}

void db_object::Init(int num_intf, const char** intnames, int num_strf, const char** strnames) {
	ID = 0;
	num_intfields = num_intf;
	intfieldname = intnames;
	intfield = NULL;
	if (num_intf > 0)
		intfield = new int[num_intf];
	num_strfields = num_strf;
	strfieldname = strnames;
	strfield = NULL;
	if (num_strf > 0)
		strfield = new string[num_strf];
}

void db_object::Print() {
	if (ID != 0) {
		cout << "ID: " << ID << endl;
		for (int i = 0; i < num_intfields; i++) {
			cout << intfieldname[i] << " " << intfield[i] << endl;
		}
		for (int i = 0; i < num_strfields; i++) {
			cout << strfieldname[i] << " " << strfield[i] << endl;
		}
		cout << "************************" << endl;
	}
}

void db_object::WriteToTxtDB(ofstream& fout) {
	if (fout.is_open()) {
		if (ID != 0) {
			fout << ID << endl;
			for (int i = 0; i < num_intfields; i++) {
				fout << intfield[i] << endl;
			}
			for (int i = 0; i < num_strfields; i++) {
				fout << strfield[i] << endl;
			}
		}
	}
	else {
		cout << "Error opening file \n";
	}
}

void db_object::WriteToDB(ofstream& fout) {
	if (fout.is_open()) {
		if (ID != 0) {
			fout.write((char *) &ID, sizeof(int));
			for (int i = 0; i < num_intfields; i++) {
				fout.write((char*) &intfield[i], sizeof(int));
			}
			for (int i = 0; i < num_strfields; i++) {
				memset(STR_FIELD_BUFFER, 0, STR_FIELD_SIZE);
				memcpy(STR_FIELD_BUFFER, strfield[i].c_str(), strfield[i].length());
				fout.write(STR_FIELD_BUFFER, STR_FIELD_SIZE);
			}
		}
	}
	else {
		cout << "Error opening file \n";
	}
}

void db_object::Edit() {
	ReadSTDIN(ID);
}

void db_object::ReadSTDIN(int Id) {
	for (int i = 0; i < num_intfields; i++) {
		cout << "Type in " << intfieldname[i] << ": ";
		cin >> intfield[i];
	}
	for (int i = 0; i < num_strfields; i++) {
		cout << "Type in " << strfieldname[i] << ": ";
		cin >> strfield[i];
	}
	ID = Id;
}

void db_object::ReadFromTxtDB(ifstream& fin) {
	if (fin.is_open()) {
		fin >> ID;
		for (int i = 0; i < num_intfields; i++) {
			fin >> intfield[i];
		}
		for (int i = 0; i < num_strfields; i++) {
			fin >> strfield[i];
		}
	}
	else {
		cout << "ReadFromTxtDB: Error opening filehandle\n";
	}
}

void db_object::ReadFromDB(ifstream& fin) {
	if (fin.is_open()) {
		fin.read((char *) &ID, sizeof(int));
		for (int i = 0; i < num_intfields; i++) {
			fin.read((char *) &intfield[i], sizeof(int));
		}
		for (int i = 0; i < num_strfields; i++) {
			fin.read(STR_FIELD_BUFFER, STR_FIELD_SIZE);
			strfield[i] = STR_FIELD_BUFFER;
		}
	}
	else {
		cout << "ReadFromDB: Error opening filehandle\n";
	}
}

void db_object::ReadSearchExample() {
	cout << "Type in object ID (press 0 to skip): ";
	cin >> ID;
	for (int i = 0; i < num_intfields; i++) {
		cout << "Type in " << intfieldname[i] << " (type - to skip): ";
		cin >> intfield[i];
	}
	for (int i = 0; i < num_strfields; i++) {
		cout << "Type in " << strfieldname[i] << " (type - to skip): ";
		cin >> strfield[i];
	}
	cout << "************************\n";
}


int db_object::MatchExample(db_object db_objectS) {

	int IdS = db_objectS.GetID();

	if (ID == IdS) {
		cout << "Id matches" << endl;
	} else if (IdS != 0) {
		return 0;
	}

	for (int i = 0; i < num_intfields; i++) {
		int matchval = db_objectS.intfield[i];
		if (intfield[i] == matchval) {
			if (matchval != 0) {
				cout << intfieldname[i] <<  " are equal " << endl;
			}
		} else if (matchval != 0) {
			return 0;
		}
	}

	for (int i = 0; i < num_strfields; i++) {
		if ((strfield[i].compare(db_objectS.strfield[i])) == 0) {
			cout << strfieldname[i] <<  " matches" << endl;
		} else if (db_objectS.strfield[i] != "-") {
			return 0;
		}
	}

	return 1;

}

//for debugging
void db_object::Print_intfield(int index) {
	if (ID != 0) {
		cout << "ID: " << ID << endl;
		cout << intfieldname[index] << " " << intfield[index] << endl;
		cout << "************************" << endl;
	}
}

bool db_object::Check_if_intfield_matches(int value_to_check,int intfield_index) {
	if (intfield[intfield_index] == value_to_check) {
		return 1;
	}
	else {
		return 0;
	}
}