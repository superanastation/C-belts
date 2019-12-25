#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include <sstream>

using namespace std;

class Date {
public:
	Date(int y, int m, int d) {
		year = y;
		month = m;
		day = d;
	}
	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear())
		return lhs.GetYear() < rhs.GetYear();
	else if (lhs.GetMonth() != rhs.GetMonth())
		return lhs.GetMonth() < rhs.GetMonth();
	else
		return lhs.GetDay() < rhs.GetDay();
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		base[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event);
	int  DeleteDate(const Date& date);

	///* ??? */ Find(const Date& date) const;

	void Print() const;
private:
	map<Date, set<string>> base;
};

int main() {
	Database db;

	string command;
	while (getline(cin, command)) {
		if (command == "ADD") {
			string date, event;
			cin >> date >> event;
			istringstream iss(date);
			vector<string> str_y_m_d;
			vector<int> int_y_m_d;
			string input;
			int year_s = 1;
			if (iss.peek() == '-') {
				year_s = -1;
			}
			while (getline(iss,input,'-'))
			{
				if (!input.empty()) {
					str_y_m_d.push_back(input);
				}
			}
			if (str_y_m_d.size() != 3) {
				cout << "Wrong date format: " << date << endl;
			}
			else {
				for (auto num : str_y_m_d) {
					int temp = 0;
					stringstream geek(num);
					geek >> temp;
					int_y_m_d.push_back(temp);
				}
				if (int_y_m_d[0] == 0) {
					cout << "Wrong date format: " << date << endl;
				}
				else {
					int_y_m_d[0] *= year_s;
					if (int_y_m_d[1] <= 0 || int_y_m_d[1] >= 13) {
						cout << "Month value is invalid: " << int_y_m_d[1] << endl;
					}
					else
					{
						if (int_y_m_d[2] <= 0 || int_y_m_d[2] >= 31) {
							cout << "Day value is invalid: " << int_y_m_d[2] << endl; 
						}
						else {
							if (!event.empty()) {
								Date new_date = { int_y_m_d[0], int_y_m_d[1], int_y_m_d[2] };
								db.AddEvent(new_date, event);
							}
						}
					}
				}
			}
		}
	}

	return 0;
}