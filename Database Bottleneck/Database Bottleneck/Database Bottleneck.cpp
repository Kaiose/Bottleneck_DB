// Database Bottleneck.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"


chrono::system_clock::time_point start;

void Print() {
	cout << "Hello";
}
int main()
{
	
	Database* db = new Database((SQLWCHAR*)L"mysql_game", (SQLWCHAR*)L"root", (SQLWCHAR*)L"kinam1018");
	db->Connect();

	int hashID;
	const char* id = "id";
	const char* password = "password";

	db->Bind_Attribute("number",SQL_INTEGER);
	db->Bind_Attribute("id", SQL_CHAR);
	db->Bind_Attribute("password", SQL_CHAR);
	
	//db->Delete();
#define COUNT 5000
	
	int epoch = 50;
	for (int j = 0; j < epoch; j++) {
		chrono::system_clock::time_point start = chrono::system_clock::now();
		for (int i = 0; i < COUNT; i++) {
			ThreadManager::getInstance().push(Database::Insert, db->hStmt);
		}

		ThreadManager::getInstance().wait();
		chrono::duration<double> sec = chrono::system_clock::now() - start;
		cout << "time out : " << sec.count() << endl;

		string filePath = "result.txt";
		ofstream writeFile;
		writeFile.open(filePath.data(), ios::app);
		writeFile << sec.count() << endl;

		wchar_t deleteCommand[100] = L"Delete from user_accounts where number != 4243;";
		db->Query(db->hStmt, deleteCommand);
		Sleep(1000);
	}

	return 0;
}

