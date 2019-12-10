#include <iostream>
#include<sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;
//while (a > 0 && b > 0) {
//	if (a > b)
//		a = a % b;
//	else
//	{
//		b = b % a;
//	}
//}
//cout << a + b;
class Rational {
public:
	Rational() {
		num = 0;
		den = 1;
	}

	Rational(int numerator, int denominator) {
		if (numerator == 0 || denominator==0) {
			num = numerator;
			den = 1;
		}
		else {
			int a = numerator;
			int b = denominator;
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

<<<<<<< HEAD
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
	//istringstream& operator >>(istringstream& stream,Rational& new_r) {
	//	stream >> this->num;
	//	stream.ignore(1);
	//	stream >> this->den;
	//	return stream;
	//}
	//ostringstream& operator <<(ostringstream& stream) {
	//	stream << this->num;
	//	stream << '/';
	//	stream << this->den;
	//	return stream;
	//}
=======
>>>>>>> parent of 76e4c36... = + -
private:
	int num;
	int den;
};
istream& operator >>(istream& stream, Rational& new_r) {
	int num, den;
	char check;
	stream >> num;
	stream >> check;
	stream >> den;
	if (check=='/')
		new_r = Rational(num,den);
	return stream;
}
ostream& operator << (ostream& str, const Rational& val) {
	str << val.Numerator() << '/' << val.Denominator();
	//cout << val.p << '/' << val.q << endl;
	return str;
}
int main() {
	{
<<<<<<< HEAD
		const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
=======
		const Rational r(3, 10);
		if (r.Numerator() != 3 || r.Denominator() != 10) {
			cout << "Rational(3, 10) != 3/10" << endl;
>>>>>>> parent of 76e4c36... = + -
			return 1;
		}

<<<<<<< HEAD
		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
=======
	{
		const Rational r(8, 12);
		if (r.Numerator() != 2 || r.Denominator() != 3) {
			cout << "Rational(8, 12) != 2/3" << endl;
>>>>>>> parent of 76e4c36... = + -
			return 2;
		}
	}

	{
<<<<<<< HEAD
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
=======
		const Rational r(-4, 6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			cout << "Rational(-4, 6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(4, -6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			cout << "Rational(4, -6) != -2/3" << endl;
>>>>>>> parent of 76e4c36... = + -
			return 3;
		}
	}

	{
		const Rational r(0, 15);
		if (r.Numerator() != 0 || r.Denominator() != 1) {
			cout << "Rational(0, 15) != 0/1" << endl;
			return 4;
		}
	}

	{
		const Rational defaultConstructed;
		if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
			cout << "Rational() != 0/1" << endl;
			return 5;
		}
	}

	cout << "OK" << endl;
	return 0;
}