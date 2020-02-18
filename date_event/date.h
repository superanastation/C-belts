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
ostream& operator << (ostream& os, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
//ostream& operator << (ostream& os, const Date& date) 
//{
//	os << setfill('0') << setw(4) << date.GetYear() << "-" << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
//	return os;
//}
//
//bool operator<(const Date& lhs, const Date& rhs) {
//	if (lhs.GetYear() != rhs.GetYear())
//		return lhs.GetYear() < rhs.GetYear();
//	else if (lhs.GetMonth() != rhs.GetMonth())
//		return lhs.GetMonth() < rhs.GetMonth();
//	else
//		return lhs.GetDay() < rhs.GetDay();
//}
//
//bool operator==(const Date& lhs, const Date& rhs) {
//	if (lhs.GetYear() == rhs.GetYear())
//	{
//		if (lhs.GetMonth() == rhs.GetMonth())
//		{
//			return lhs.GetDay() == rhs.GetDay();
//		}
//	}
//	return false;
//}
//
//bool operator>(const Date& lhs, const Date& rhs) {
//	return !(lhs < rhs) && !(lhs == rhs);
//}
//
//bool operator>=(const Date& lhs, const Date& rhs) {
//	return !(lhs < rhs);
//}
//
//bool operator<=(const Date& lhs, const Date& rhs) {
//	return (lhs < rhs) || (lhs == rhs);
//}
//
//bool operator!=(const Date& lhs, const Date& rhs) {
//	return !(lhs == rhs);
//}