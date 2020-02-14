#pragma once

#include<sstream>
#include<vector>

using namespace std;

class Date
{
public:
	Date(int d, int m, int y) :
		year(y), month(m), day(d){}

	ostream& operator << (ostream& os);
protected:
	int year, month, day;
};