#include<iostream>
#include<string>
#include<deque>
#include<stack>
#include<sstream>

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
	stack<PartExp> deq;

	if (N > 0)
	{
		for (int i = 0; i < N; i++) {
			char op;
			int r_num;
			cin >> op >> r_num;
			PartExp in = { op,r_num };
			deq.push(in);
		}
		ostringstream s_out;
		auto it = deq.top();
		bool pre_priority = false;
		for (int i = 0; i < N; i++) {
			auto last = deq.top();
			deq.pop();
			auto pre_last = deq.top();
			if ((pre_last.operation == '+' || pre_last.operation == '-') && (last.operation == '*' || last.operation == '/'))
			{

			}
		}
		/*for (int i = 0; i < N; i++) {
			cout << "(";
		}
		cout << to_string(num) << ") ";
		for (int i = 0; i < N - 1; i++) {
			cout << deq.at(i).operation << " " << to_string(deq.at(i).number) << ") ";
		}
		cout << deq.at(N - 1).operation << " " << to_string(deq.at(N - 1).number);*/
	}
	else {
		out = to_string(num);
		cout << out << endl;
	}
	return 0;
}