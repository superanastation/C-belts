#pragma once

#include<sstream>
#include<vector>
#include<iomanip>

using namespace std;

class Date
{
public:
	Date(int d, int m, int y) :
		year(y), month(m), day(d){}

	int GetYear() const
	{
		return year;
	}

	int GetMonth() const
	{
		return month;
	}

	int GetDay() const
	{
		return day;
	}

	
protected:
	int year, month, day;
}; 

ostream& operator << (ostream& os, const Date& date) 
{
	os << setfill('0') << setw(4) << date.GetYear() << "-" << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
	return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear())
		return lhs.GetYear() < rhs.GetYear();
	else if (lhs.GetMonth() != rhs.GetMonth())
		return lhs.GetMonth() < rhs.GetMonth();
	else
		return lhs.GetDay() < rhs.GetDay();
}

bool operator==(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear())
	{
		if (lhs.GetMonth() == rhs.GetMonth())
		{
			return lhs.GetDay() == rhs.GetDay();
		}
	}
	return false;
}

bool operator>(const Date& lhs, const Date& rhs) {
	return !(lhs < rhs) && !(lhs == rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return !(lhs < rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}