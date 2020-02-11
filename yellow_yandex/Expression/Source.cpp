#include<iostream>
#include<string>

using namespace std;

int main() {
	string out;
	int num;
	cin >> num;
	int N;
	cin >> N;
	out = to_string(num);
	if (N > 0)
	{
		//out = "(" + out + ")";
		char pre_op = '*';
		for (int i = 0; i < N; i++) {
			char op;
			int r_num;
			cin >> op >> r_num;
			if ((pre_op == '+' || pre_op == '-') && (op == '*' || op == '/'))
			{
				out = "(" + out + ")" + " " + op + " " + to_string(r_num);
			}
			else
				out = out + " " + op + " " + to_string(r_num);
			pre_op = op;
			//if (i != N - 1)
			//	out = "(" + out + ")";
		}
	}
	
	cout << out << endl;
	return 0;
}