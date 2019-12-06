#include<string>
#include<map>
#include<iostream>

using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		story[year].first = first_name;
		// добавить факт изменения имени на first_name в год year
	}
	void ChangeLastName(int year, const string& last_name) {
		story[year].second = last_name;
		// добавить факт изменения фамилии на last_name в год year
	}
	string GetFullName(int year) {
		//story.count(begin(story), end(story));
		if (story.size() > 0) {
			string ans;
			string first_name;
			string last_name;
			bool is_first_change = true;
			int found_year;
			for (const auto& change : story) {				
				if (is_first_change) {
					if (change.first>year)
						return "Incognito";
					else {
						found_year = change.first;
						is_first_change = false;
					}
				}					
				else{
					if (change.first <= year)
						found_year = change.first;
					else
						break;
				}
			}
			for (const auto& change : story) {
				if (change.first > found_year)
					break;
				else {
					if (change.second.first.size() != 0)
						first_name = change.second.first;
					if (change.second.second.size() != 0)
						last_name = change.second.second;
				}
			}
			if (first_name.size() == 0)
				return last_name + " with unknown first name";
			else if (last_name.size() == 0)
				return first_name + " with unknown last name";
			else
				return first_name + ' ' + last_name;

		}
		else
			return "Incognito";
		



		//if (story.count(year) == 0) {
		//	return "Incognito";
		//}
		//else if ((story[year]).first.size() == 0) {
		//	return (story[year]).second + " with unknown first name";
		//}
		//else if ((story[year]).second.size() == 0) {
		//	return  (story[year]).first + " with unknown last name";
		//}
		//else
		//{
		//	string ans = (story[year]).first + ' ' + (story[year]).second;
		//	return ans;
		//}
		// получить имя и фамилию по состоянию на конец года year
	}
private:
	map<int, pair<string, string>> story;
	//vector<string> FirstName;
	//vector<string> LastName;
	//int year;
	// приватные поля
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}
	return 0;
}