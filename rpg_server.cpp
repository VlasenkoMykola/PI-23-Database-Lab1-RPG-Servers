#include "DBfile.h"
#include "screen.h"

using namespace std;

static const char* players[] = {"name","email","password"};
static const char* servers[] = {"DNS name"};
static const char* sessions[] = { "playerid","serverid"};

int main() {
	dbfile DBPlayers = dbfile("Players","Players", 0, NULL, 3, players);
	dbfile DBServers = dbfile("Servers","Servers", 0, NULL, 1, servers);
	dbfile DBSessions = dbfile("Sessions", "Sessions", 2, sessions, 0, NULL);
	//pointers to previous dbfile variables
    DBSessions.InsertSlaveDBFile(&DBPlayers);
	DBSessions.InsertSlaveDBFile(&DBServers);
	DBPlayers.SetMasterDBFile(&DBSessions,0);
	DBServers.SetMasterDBFile(&DBSessions,1);

	string stateM;
	do {
		cls();
		cout << "    Select Database table:\n"
		     << "(0) Exit menu\n"
		     << "(1) Players table\n"
		     << "(2) Servers table\n"
		     << "(3) Sessions table\n"
		     << "Type a number from 0 to 3 to continue: ";
		cin >> stateM;
		cls();

		if (stateM == "1") {
			DBPlayers.DBApp();
		}
		else if (stateM == "2") {
//			DBServers.PrintFromAnotherTable(DBPlayers);
//			pause();
			DBServers.DBApp();
		}
		else if (stateM == "3") {
			DBSessions.DBApp();
		}
		else if (stateM != "0") {
			cout << "************************\n"
				<< "ERROR: incorrect option. Should be a number from 0 to 3\n"
				<< "************************\n";
		}
		//pause();

	} while (stateM != "0");
}
