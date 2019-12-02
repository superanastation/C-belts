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
	int k = 1;//номер текущего мес€ца
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
			cout << routine[num].size() << ' ';;
			for (int j = 0; j < routine[num].size(); j++) {
				cout << routine[num][j] << ' ';
			}
			cout << endl;
		}
		else if (command == "NEXT") {
			vector<vector<string>> temp;
			k+=1;
			if (k > 11) {
				k %= 11;
			}				
			if (k == 2)
				make_full(28,temp);
			else if (k%2==1)
				make_full(31, temp);
			else
				make_full(30, temp);
			if (temp.size() >= routine.size()) {
				for (int j = 0; j < routine.size(); j++) {
					temp[j] = routine[j];
				}
			}
			else {
				//temp.insert(end(temp), begin(routine), end(routine));
				for (int j = 0; j < routine.size(); j++) {
					if (j < temp.size()) {
						temp[j] = routine[j];
					}
					else {
						/*for (int m = 0; m < routine[j].size(); m++) {
							temp[temp.size() - 1][temp[j].size() - 1 + m] = routine[j][m];
						}*/
						(temp[temp.size() - 1]).insert(end(temp[temp.size() - 1]),begin(routine[j]), end(routine[j]));
						//(temp[temp.size()-1]).push_back(routine[j]);
						//temp.insert(end(temp), begin(routine), end(routine));
						//(temp.end()).push_back(routine[j]);
					}
				}
			}
			routine.clear();
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