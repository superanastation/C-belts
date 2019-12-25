#include <iostream>
#include<sstream>
#include <map>
#include <set>
#include <vector>
#include<cmath>
using namespace std;
class Rational {
public:
	Rational() {
		num = 0;
		den = 1;
	}

	Rational(int numerator, int denominator) {
		if (denominator == 0) {
			throw invalid_argument("Invalid argument");//runtime_error()
		}
		else if (numerator == 0 ) {
			num = numerator;
			den = 1;
		}
		else {
			int a = abs(numerator);
			int b = abs(denominator);
			while (a > 0 && b > 0) {
				if (a > b)
					a = a % b;
				else
				{
					b = b % a;
				}
			}
			int dev = a + b;
			num = numerator / dev;
			den = denominator / dev;
			if (den < 0) {
				den *= (-1);
				num *= (-1);
			}
		}	
	}

	int Numerator() const {
		return num;
	}

	int Denominator() const {
		return den;
	}

	bool operator ==(const Rational& right) const{
		return (this->num == right.num && this->den == right.den);
	}
	Rational operator +(const Rational& right) const{
		int new_num = this->num*right.den + right.num*this->den;
		int new_den = this->den*right.den;
		return Rational(new_num, new_den);
	}
	Rational operator -(const Rational& right) const {
		int new_num = this->num*right.den - right.num*this->den;
		int new_den = this->den*right.den;
		return Rational(new_num, new_den);
	}
	Rational operator *(const Rational& right) const {
		int new_num = this->num*right.num;
		int new_den = this->den*right.den;
		return Rational(new_num, new_den);
	}
	Rational operator /(const Rational& right) const {
		if (right.Numerator() == 0) {
			throw domain_error("Division by zero");
		}
		int new_num = this->num*right.den;
		int new_den = this->den*right.num;
		return Rational(new_num, new_den);
	}
	bool operator <(const Rational& right) const {
		if (this->den == right.den)
			return this->num < right.num;
		else {
			return this->num*right.den < this->den*right.num;
		}
	}

private:
	int num;
	int den;
};
istream& operator >>(istream& stream, Rational& new_r) {
	int num, den;
	char check,op;
	if (stream.tellg()!=-1) {
		stream >> num;
		stream >> check;
		stream >> den;
		if (check == '/')
			new_r = Rational(num, den);
	}
	

	return stream;
}
ostream& operator << (ostream& str, const Rational& val) {
	str << val.Numerator() << '/' << val.Denominator();
	return str;
}
void run(const string& input_str) {
	Rational temp1, temp2;
	char op;
	istringstream input(input_str);
	input >> temp1 >> op >> temp2;
	if (op == '+') {
		Rational res = temp1 + temp2;
		cout << res;
	}
	else if (op == '-') {
		Rational res = temp1 - temp2;
		cout << res;
	}
	else if (op == '*') {
		Rational res = temp1 * temp2;
		cout << res;
	}
	else if (op == '/') {
		Rational res = temp1 / temp2;
		cout << res;
	}
}
int main() {
	try {
		string in_r1,in_op,in_r2;
		cin >> in_r1>>in_op>>in_r2;
		run(in_r1+" "+in_op + " " + in_r2);
	}
	catch (exception& ex) {
		cout << ex.what();
	}
	
	return 0;
}