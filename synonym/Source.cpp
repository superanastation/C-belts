#include<iostream>
#include<map>
#include<string>
#include<set>

using namespace std;

bool check_syn(const map<string, set<string>>& dict) {
	string word1, word2;
	cin >> word1 >> word2;
	if (dict.count(word1) != 0) {
		if ((dict.at(word1)).count(word2) != 0)
			return true;

	}
	return false;
}

int main() {
	int q;
	cin >> q;
	map<string, set<string>> dict;
	for (int i = 0; i < q; i++) {
		string command;
		cin >> command;
		if (command == "ADD") {
			string word1,word2;
			cin >> word1 >> word2;
			dict[word1].insert(word2);
			dict[word2].insert(word1);
		}
		else if (command == "COUNT") {
			string word;
			cin >> word;
			if (dict.count(word)!=0)
			{
				cout << (dict.at(word)).size() << endl;
			}
			else
			{
				cout << 0 << endl;
			}
			
		}
		else if (command == "CHECK") {
			bool res = check_syn(dict);
			if (res)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}
	return 0;
}