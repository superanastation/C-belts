#include<iostream>
#include<string>
#include<deque>

using namespace std;

struct PartExp {
	char operation;
	int number;
};

int main() {
	string out;
	int num;
	cin >> num;
	int N;
	cin >> N;
	deque<string> deq_str;

	if (N > 0)
	{
		string pre_op = "*";// '*';
		deq_str.push_back(to_string(num));
		for (int i = 0; i < N; i++) {
			string op;
			int r_num;
			cin >> op >> r_num;
			if ((pre_op == "+" || pre_op == "-") && (op == "*" || op == "/"))
			{
				deq_str.push_front("(");
				deq_str.push_back(")");
			}
			deq_str.push_back(" ");
			deq_str.push_back(op);
			deq_str.push_back(" ");
			deq_str.push_back(to_string(r_num));

			pre_op = op;
		}
		for (const auto& item : deq_str)
		{
			cout << item;
		}
	}
	else {
		out = to_string(num);
		cout << out << endl;
	}
	return 0;
}