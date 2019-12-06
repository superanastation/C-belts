#include<iostream>
#include<map>
#include<string>
#include<set>

using namespace std;

int count_syn(const map<string, set<string>>& dict, const string& word) {
	//int num_syn = 0;
	set<string> syn;
	if (dict.count(word) != 0) {
		syn.insert(begin(dict.at(word)), end(dict.at(word)));

	}
	{
		for (auto item : dict) {
			if (item.second.count(word) != 0)
				syn.insert(item.first);
		}					
	}
	
	return syn.size();

}

bool check_syn(const map<string, set<string>>& dict) {
	string word1, word2;
	cin >> word1 >> word2;
	if (dict.count(word1) != 0) {
		if ((dict.at(word1)).count(word2) != 0)
			return true;

	}
	if (dict.count(word2) != 0)
	{
		if ((dict.at(word2)).count(word1) != 0)
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
		}
		else if (command == "COUNT") {
			string word;
			cin >> word;
			int num = count_syn(dict, word);
			cout << num << endl;
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