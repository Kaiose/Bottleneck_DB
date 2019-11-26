#pragma once
#include "stdafx.h"
#include <sql.h>
#include <sqlext.h>

#define PARAMETER_LEN 30

class Attribute{
public:
	SQLLEN len;


	virtual void print() = 0;
};


class Attribute_CHAR : public Attribute{
public:

	char value[PARAMETER_LEN];
	SQLLEN len;

	Attribute_CHAR() {
	}

	void print() {
		cout << value << " ";
	}
};


class Attribute_INT : public Attribute {
public:
	int value;

	Attribute_INT() { }

	void print() {
		cout << value << " ";
	}
};






class Database {
	
	int id;
	char name[20];
	char password[20];
	SQLLEN idLen, nameLen, passwordLen;
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;

	SQLWCHAR ODBC_NAME[PARAMETER_LEN];
	SQLWCHAR ODBC_ID[PARAMETER_LEN];
	SQLWCHAR ODBC_PW[PARAMETER_LEN];
	
	int attribute_count;

	unordered_map<int, Attribute*> attri_map;

public:

	Database(SQLWCHAR* odbc_name, SQLWCHAR* odbc_id, SQLWCHAR* odbc_pw);


	bool Connect();
	bool Disconnect();
	
	void Query();
	
	void AttributeBind();
	void Bind_Attribute(const char* attribute_name, int type);


private:

};