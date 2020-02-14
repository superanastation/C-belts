#pragma once
#include<string>
#include"date.h"
#include<map>
#include<set>

using namespace std;

class Database
{
public:
	void Add(Date date, string event);
	void Print(ostream& os);
protected:
	map<Date, set<string>> base;
};