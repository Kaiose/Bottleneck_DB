#include "stdafx.h"
#include "Database.h"



Database::Database(SQLWCHAR* odbc_name, SQLWCHAR* odbc_id, SQLWCHAR* odbc_pw) : attribute_count(1) {
	memcpy(ODBC_NAME, odbc_name, sizeof(SQLWCHAR) * PARAMETER_LEN);
	memcpy(ODBC_ID, odbc_id, sizeof(SQLWCHAR) * PARAMETER_LEN);
	memcpy(ODBC_PW, odbc_pw, sizeof(SQLWCHAR) * PARAMETER_LEN);
}

bool Database::Connect() {
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) {
		cout << "SQL Handel Allocate Failed \n";
		return false;
	}

	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS) {
		cout <<"SQL Set Env Attr Failed \n";
		return false;
	}

	// 연결핸들을 설정한다.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
		cout << "SQL Handel Allocate Failed \n";
		return false;
	}


	// 데이터에 연결한다.
	if (SQLConnect(hDbc, ODBC_NAME, SQL_NTS, ODBC_ID, SQL_NTS, ODBC_PW, SQL_NTS) != SQL_SUCCESS) {
		cout << "SQL Handle Connect Failed \n";
		return false;
	}

	// 명령문핸들을 할당한다.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
		cout << "SQL Handel Allocate Failed \n";
		return false;
	}

	return true;

}



bool Database::Disconnect() {

	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	return true;
}


bool Database::Query() {

	wchar_t command[100] = { 0, };

	wcin.getline(command, 100);
	int ret = SQLExecDirect(hStmt, (SQLWCHAR*)command, SQL_NTS);
	
	
	if (ret != SQL_SUCCESS) {
		cout << "Query Failed \n";
		if (hStmt) SQLCloseCursor(hStmt);
		return false;
	}
	return true;

}

bool Database::Query(SQLHSTMT hStmt,wchar_t* command) {


	int ret = SQLExecDirect(hStmt, (SQLWCHAR*)command, SQL_NTS);

	if (ret != SQL_SUCCESS) {
		cout << "Query Failed \n";
		if (hStmt) SQLCloseCursor(hStmt);
		return false;
	}
	return true;

}

void Database::Select() {
	
	if (Query() == false) cout << "Select Query Failed\n"; return;
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		unordered_map<int, Attribute*>::iterator it = attri_map.begin();
		for (; it != attri_map.end(); it++)
			it->second->print();
		cout << "\n";
	}
	if (hStmt) SQLCloseCursor(hStmt);

}


void Database::Insert(SQLHSTMT hStmt) {
	LARGE_INTEGER cicles; 
	QueryPerformanceCounter(&cicles); 
	srand(cicles.QuadPart);
	//	Source https ://www.physicsforums.com/threads/srand-seed-microsecs.303949/

	int value = rand();
	//"Insert into user_accounts values(id, "name", password)"
	
	wchar_t command[100] = { 0, };
	wsprintfW(command, L"insert into user_accounts values(%d,\"%dtest\",1234);", value, value);

	if (Query(hStmt,command) == false) cout << "Insert Query Failed\n"; return;
	

	if (hStmt) SQLCloseCursor(hStmt);
}

void Database::Delete() {
	if (Query() == false) cout << "Delete Query Failed\n"; return;

	if (hStmt) SQLCloseCursor(hStmt);

}


void Database::Bind_Attribute(const char* attribute_name, int type) {
	
	Attribute* node = nullptr;
	switch (type) {
	case SQL_CHAR:
		node = new Attribute_CHAR();
		SQLBindCol(hStmt, attribute_count++, SQL_CHAR, ((Attribute_CHAR*)node)->value, sizeof(char)* PARAMETER_LEN, &node->len);
		break;
	case SQL_INTEGER:
		node = new Attribute_INT();
		SQLBindCol(hStmt, attribute_count++, SQL_INTEGER, &(((Attribute_INT*)node)->value), sizeof(int), &node->len);
		break;
	case SQL_SMALLINT:
		break;
	case SQL_DOUBLE:
		break;
	case SQL_FLOAT:
		break;
	}
	if(node != nullptr)
		attri_map.insert(make_pair(attribute_count, node));

}


