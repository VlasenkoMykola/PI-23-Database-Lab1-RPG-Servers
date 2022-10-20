using namespace std;
#include <iostream>

#if defined(_WIN64) || defined(_WIN32)
void cls() {
	system("cls");
}

void pause() {
	system("pause");
}
#else
void cls() {
	system("clear");
}

void pause() {
	cout << "Press any key to continue..." << std::endl;
	system("read -s -N 1");
}
#endif
