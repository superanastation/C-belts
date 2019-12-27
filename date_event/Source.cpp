#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include <sstream>
#include<iomanip>

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
bool operator==(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() == rhs.GetDay();
		}
	}
	else
		return false;
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		base[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {
		for (auto& item : base) {
			if (date == item.first) {
				return (item.second.erase(event) == 1);
			}
		}
		return false;
	}
	int  DeleteDate(const Date& date) {
		int num=0;
		for (auto& item : base) {
			if (date == item.first) {
				num = item.second.size();
				base.erase(date);
				break;
			}
		}
		return num;
	}

	set<string> Find(const Date& date) const {
		set<string> empty;
		for (const auto& item : base) {
			if (date == item.first) {
				return item.second;
			}
		}
		return empty;
	}

	void Print() const {
		for (const auto& item : base) {
			for (const auto& even : item.second) {				
				cout << setfill('0') << setw(4) << item.first.GetYear() << "-" << setw(2) << item.first.GetMonth() << "-" << setw(2) << item.first.GetDay() << " " << even << endl;
			}
		}
	}
private:
	map<Date, set<string>> base;
};
Date is_format(const string& date) {
	int count = 0;
	//for (const auto& item : date) {
	//	if (!isdigit(item) && item != '-' && item != '+') {
	//		string mistake = "Wrong date format: " + date;
	//		throw runtime_error(mistake);
	//	}
	//	else if (item == '-' && count <= 5){
	//		count++;
	//	}
	//	if (count > 5) {
	//		string mistake = "Wrong date format: " + date;
	//		throw runtime_error(mistake);
	//	}
	//}
	istringstream iss(date);
	int year, month, day;
	//char def1,def2;
	if (!isdigit(iss.peek()) && iss.peek() != '-' && iss.peek() != '+') {
		string mistake = "Wrong date format: " + date;
		throw runtime_error(mistake);
	}
	iss >> year;// >> def1;
	int one = 1;
	if (iss.peek() == '-') {
		iss.ignore(1);
		if (iss.peek() == '-' || iss.peek() == '+')
		{
			if (iss.peek()=='-')
				one = -1;
			iss.ignore(1);
		}
		if (!isdigit(iss.peek())) {
			string mistake = "Wrong date format: " + date;
			throw runtime_error(mistake);
		}
	}
	else {
		string mistake = "Wrong date format: " + date;
		throw runtime_error(mistake);
	}
	iss >> month;
	month *= one;
	one = 1;
	if (iss.peek() == '-') {
		iss.ignore(1);
		if (iss.peek() == '-' || iss.peek() == '+')
		{
			if (iss.peek() == '-')
				one = -1;
			iss.ignore(1);
		}
		if (!isdigit(iss.peek())) {
			string mistake = "Wrong date format: " + date;
			throw runtime_error(mistake);
		}
	}
	else {
		string mistake = "Wrong date format: " + date;
		throw runtime_error(mistake);
	}
	iss>>day;
	day *= one;
	if (iss.peek() != EOF) {
		string mistake = "Wrong date format: " + date;
		throw runtime_error(mistake);
	}	
	if (year>9999) {
		string mistake = "Wrong date format: " + date;
		throw runtime_error(mistake);
	}
	else if (month <= 0 || month >= 13) {
		string mistake = "Month value is invalid: " + to_string(month);
		throw runtime_error(mistake);
	}
	else if (day <= 0 || day >= 32) {
		string mistake = "Day value is invalid: " + to_string(day);
		throw runtime_error(mistake);
	}
	else 
		return Date(year,month,day);
}
void Add(Database& db,string date, string event){

		Date new_date = is_format(date);
		db.AddEvent(new_date, event);
}
int main() {
	
	try {
		Database db;
		string command;
		while (getline(cin, command)) {
			istringstream iss(command);
			string input;
			vector<string> str_in;
			while (getline(iss, input, ' '))
			{
				if (!input.empty()) {
					str_in.push_back(input);
				}
			}			
			if (str_in.size() != 0) {
				command = str_in[0];
				if (command == "Add") {
					if (str_in.size() == 3) {
						string date = str_in[1];
						string event = str_in[2];
						Add(db, date, event);
					}					
				}
				else if (command == "Find") {
					string date = str_in[1];
					Date norm_date = is_format(date);
					set<string> found = db.Find(norm_date);
					if (!found.empty()) {
						for (const auto& item : found) {
							cout << item << endl;
						}
					}
				}
				else if (command == "Del") {
					string date = str_in[1];
					Date norm_date = is_format(date);
					if (str_in.size() == 3) {
						string event = str_in[2];
						if (db.DeleteEvent(norm_date, event)) {
							cout << "Deleted successfully" << endl;
						}
						else
							cout << "Event not found" << endl;
					}
					else {
						int num = db.DeleteDate(norm_date);
						cout << "Deleted " << to_string(num) << " events" << endl;
					}
				}
				else if (command == "Print") {
					db.Print();
				}
				else {
					string mistake = "Unknown command: " + command;
					throw runtime_error(mistake);
				}
			}				
		}
	}	
	catch (exception &ex) {
		cout << ex.what() << endl;
	}
	return 0;
}