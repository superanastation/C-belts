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
		if (numerator == 0 || denominator==0) {
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
	////istringstream& operator >>(istringstream& stream,Rational& new_r) {
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

private:
	int num;
	int den;
};
istream& operator >>(istream& stream, Rational& new_r) {
	int num, den;
	char check;
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
	//cout << val.p << '/' << val.q << endl;
	return str;
}
int main() {

	{
		const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
			return 1;
		}

		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}


	cout << "OK" << endl;
	return 0;
}