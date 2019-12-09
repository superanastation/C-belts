#include <map>
#include <string>
#include <iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
// ���� ��� ����������, ���������� ������ ������
string FindNameByYear(const map<int, string>& names, int year) {
	string name;  // ���������� ��� ����������

	// ���������� ��� ������� �� ����������� ����� �������, �� ���� � ��������������� �������
	for (const auto& item : names) {
		// ���� ��������� ��� �� ������ �������, ��������� ���
		if (item.first <= year) {
			name = item.second;
		}
		else {
			// ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������
			break;
		}
	}

	return name;
}

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		last_names[year] = last_name;
	}
	string GetFullName(int year) {
		// �������� ��� � ������� �� ��������� �� ��� year
		const string first_name = FindNameByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year);

		// ���� � ���, � ������� ����������
		if (first_name.empty() && last_name.empty()) {
			return "Incognito";

			// ���� ���������� ������ ���
		}
		else if (first_name.empty()) {
			return last_name + " with unknown first name";

			// ���� ���������� ������ �������
		}
		else if (last_name.empty()) {
			return first_name + " with unknown last name";

			// ���� �������� � ���, � �������
		}
		else {
			return first_name + " " + last_name;
		}
	}
	string GetFullNameWithHistory(int year) {
		string current_name= FindNameByYear(first_names, year);
		string current_last= FindNameByYear(last_names, year);
		vector<string> past_fn;
		vector<string> temp;
		set<string> names;
		for (const auto& item : first_names) {
			// ���� ��������� ��� �� ������ �������, ��������� ���
			if (item.first <= year) {
				 {//if (names.count(item.second) == 0)
					temp.push_back(item.second);
				}
			}
			else {
				// ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������
				break;
			}
		}
		//���������� ������
		bool first = true;
		for (int i = temp.size() - 1; i >= 0;i--) {
			if (first && temp[i] != current_name) {
				past_fn.push_back(temp[i]);
				names.insert(temp[i]);
				first = false;
			}
			else if (!first && names.count(temp[i]) == 0) {
				past_fn.push_back(temp[i]);
				names.insert(temp[i]);
			}
		}
		first = false;
		temp.clear();
		names.clear();
		//
		vector<string> past_ln;
		for (const auto& item : last_names) {
			// ���� ��������� ��� �� ������ �������, ��������� ���
			if (item.first <= year) {
				{//if (names.count(item.second) == 0) 
					temp.push_back(item.second);
				}
			}
			else {
				// ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������
				break;
			}
		}

		first = true;
		for (int i = temp.size() - 1; i >= 0; i--) {
			if (first && temp[i] != current_last) {
				past_ln.push_back(temp[i]);
				names.insert(temp[i]);
				first = false;
			}
			else if (!first && names.count(temp[i]) == 0) {
				past_ln.push_back(temp[i]);
				names.insert(temp[i]);
			}
		}
		first = false;
		//---ANSWER
		if (current_name.empty() && current_last.empty())
			return "Incognito";
		string ans;
		if (!current_name.empty()) {
			ans = current_name; +" ";
			if (past_fn.size() != 0) {
				ans += "(";
				for (int i = 0; i < past_fn.size()-1; i++) {
					ans += (past_fn[i] + ", ");
				}
				ans += (past_fn[past_fn.size() - 1] + ") ");
			}
		}
			
		if (!current_last.empty()) {
			ans += current_last + " ";
			if (past_ln.size() != 0) {
				ans += "(";
				for (int i = 0; i < past_ln.size()-1; i++) {
					ans += (past_ln[i] + ", ");
				}
				ans += (past_ln[past_ln.size() - 1] + ") ");
			}
		}
		if (current_last.empty())
			return ans + "with unknown last name";
		
		if (current_name.empty())
			return ans + "with unknown first name";
		return ans;
		// �������� ��� ����� � ������� �� ��������� �� ����� ���� year
	}
private:
	map<int, string> first_names;
	map<int, string> last_names;
};


//int main() {
//	Person person;
//
//	person.ChangeFirstName(1965, "Polina");
//	person.ChangeLastName(1967, "Sergeeva");
//	for (int year : {1900, 1965, 1990}) {
//		cout << person.GetFullNameWithHistory(year) << endl;
//	}
//
//	person.ChangeFirstName(1970, "Appolinaria");
//	for (int year : {1969, 1970}) {
//		cout << person.GetFullNameWithHistory(year) << endl;
//	}
//
//	person.ChangeLastName(1968, "Volkova");
//	for (int year : {1969, 1970}) {
//		cout << person.GetFullNameWithHistory(year) << endl;
//	}
//
//	person.ChangeFirstName(1990, "Polina");
//	person.ChangeLastName(1990, "Volkova-Sergeeva");
//	cout << person.GetFullNameWithHistory(1990) << endl;
//
//	person.ChangeFirstName(1966, "Pauline");
//	cout << person.GetFullNameWithHistory(1966) << endl;
//
//	person.ChangeLastName(1960, "Sergeeva");
//	for (int year : {1960, 1967}) {
//		cout << person.GetFullNameWithHistory(year) << endl;
//	}
//
//	person.ChangeLastName(1961, "Ivanova");
//	cout << person.GetFullNameWithHistory(1967) << endl;
//
//	return 0;
//}