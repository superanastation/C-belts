#include <iostream>
#include<sstream>
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
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
		}
	}

	cout << "OK" << endl;
	return 0;
}