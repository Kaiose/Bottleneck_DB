// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include "targetver.h"


#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <unordered_map>
#include <atomic>
#include <thread>
#include <Windows.h>
#include <queue>
#include <sql.h>
#include <fstream>
#include <ostream>

using namespace std;
typedef void func(SQLHSTMT hStmt);

#include "Database.h"
#include "ThreadManager.h"



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
