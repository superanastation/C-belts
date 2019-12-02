#include<string>
#include<iostream>
#include<vector>

using namespace std;

void make_full(int num_d, vector<vector<string>>& routine) {
	for (int i = 0; i < num_d+1; i++) {
		vector<string> temp(0);
		routine.push_back(temp);
	}
}

void query(int n) {
	vector<vector<string>> routine;
	vector<int> year = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int k = 0;//номер текущего мес€ца
	make_full(31, routine);
	for (int i = 0; i < n; i++) {
		string command;
		cin >> command;
		int num;
		string deal;
		if (command == "ADD") {
			cin >> num >> deal;
			routine[num].push_back(deal);
		}
		else if (command == "DUMP") {
			cin >> num;
			cout << routine[num].size() << ' ';
			for (int j = 0; j < routine[num].size(); j++) {
				cout << routine[num][j] << ' ';
			}
			cout << endl;
		}
		else if (command == "NEXT") {
			vector<vector<string>> temp;
			k+=1;
			if (k > 11) {
				k =0;
			}
			make_full(year[k], temp);
			if (temp.size() >= routine.size()) {
				for (int j = 0; j < routine.size(); j++) {
					temp[j] = routine[j];
				}
			}
			else {
				for (int j = 0; j < routine.size(); j++) {
					if (j < temp.size()) {
						temp[j] = routine[j];
					}
					else {
						(temp[temp.size() - 1]).insert(end(temp[temp.size() - 1]),begin(routine[j]), end(routine[j]));
					}
				}
			}
			//routine.clear();
			routine = temp;
		}
			
	}

}
int main() {
	int n;
	cin >> n;
	query(n);
	return 0;
}