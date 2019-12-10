#include <iostream>
using namespace std;

class Rational {
public:
	Rational() {
		num = 0;
		den = 1;
	}

	Rational(int numerator, int denominator) {
		if (numerator == 0) {
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

private:
	int num;
	int den;
};

int main() {
	{
		Rational r1(4, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			cout << "4/6 != 2/3" << endl;
			return 1;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			cout << "2/3 + 4/3 != 2" << endl;
			return 2;
		}
	}

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}