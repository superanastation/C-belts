#pragma once

#include<sstream>
#include<vector>
#include<iomanip>

using namespace std;

class Date
{
public:
	Date(int y, int m, int d);

	int GetYear() const;

	int GetMonth() const;

	int GetDay() const;

	
protected:
	int year, month, day;
}; 

Date ParseDate(istream& iss);

ostream& operator << (ostream& os, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);