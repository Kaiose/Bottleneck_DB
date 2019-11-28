#pragma once
#include "stdafx.h"



template <typename T>
class Singleton {

protected:
	Singleton() = default;

public:


	static T& getInstance() {

		static T instance;

		return instance;
	}

};



class ThreadManager : public Singleton<ThreadManager> {

	friend Singleton;
	vector<thread*> queue;
	
	ThreadManager() {
		
	}

	~ThreadManager() {
		
		vector<thread*>::iterator it;

		while (!queue.empty()) {
			it = queue.begin();

			for (; it != queue.end();) {
				if ((*it)->joinable()) {
					(*it)->join();
					it = queue.erase(it);
				}
				else
					it++;
			}
		}

	}
public:
	typedef void func(SQLHSTMT hStmt);


	void push(func work, SQLHSTMT hStmt) {
		queue.emplace_back(new thread(work,hStmt));
	}

	
	


};




