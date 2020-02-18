#include"date.h"

Date::Date(int y, int m, int d) :
	year(y), month(m), day(d) {}

int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

Date ParseDate(istream& iss) {
	int year, month, day;
	char def1, def2;
	iss >> year >> def1 >> month >> def2 >> day;
	return Date(year, month, day);
}

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