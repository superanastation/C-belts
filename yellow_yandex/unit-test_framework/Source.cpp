#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
	const string& hint)
{
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u
			<< " hint: " << hint << endl;
		throw runtime_error(os.str());
	}
}

inline void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (runtime_error& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
	}
	void ChangeLastName(int year, const string& last_name) {
	}
	string GetFullName(int year) {
	}
};

void TestChangeLastName() {
	Person test;
	AssertEqual(test.GetFullName(6) , "Incognito", "test.GetFullName(6)==Incognito");
	test.ChangeLastName(3, "last1");
	AssertEqual(test.GetFullName(0) , "Incognito", "test.GetFullName(0)==Incognito");
	AssertEqual(test.GetFullName(3) , "last1 with unknown first name", "test.GetFullName(3) == last1 with unknown first name");
	AssertEqual(test.GetFullName(10) ,"last1 with unknown first name", "test.GetFullName(10) == last1 with unknown first name");
	test.ChangeLastName(1, "last2");
	AssertEqual(test.GetFullName(0) , "Incognito", "test.GetFullName(0)==Incognito last2");
	AssertEqual(test.GetFullName(1) , "last2 with unknown first name", "test.GetFullName(1) == last2 with unknown first name");
	AssertEqual(test.GetFullName(2) , "last2 with unknown first name", "test.GetFullName(2) == last2 with unknown first name");
	AssertEqual(test.GetFullName(3) , "last1 with unknown first name", "test.GetFullName(3) == last1 with unknown first name last 2");
	AssertEqual(test.GetFullName(10) , "last1 with unknown first name", "test.GetFullName(10) == last1 with unknown first name last 2");
	test.ChangeLastName(5, "last3");
	AssertEqual(test.GetFullName(0) , "Incognito", "test.GetFullName(0)==Incognito last3");
	AssertEqual(test.GetFullName(1) , "last2 with unknown first name", "test.GetFullName(1) == last2 with unknown first name last3");
	AssertEqual(test.GetFullName(2) , "last2 with unknown first name", "test.GetFullName(2) == last2 with unknown first name last3");
	AssertEqual(test.GetFullName(3) , "last1 with unknown first name", "test.GetFullName(3) == last1 with unknown first name last3");
	AssertEqual(test.GetFullName(5) , "last3 with unknown first name", "test.GetFullName(3) == last3 with unknown first name last3");
	AssertEqual(test.GetFullName(10) , "last3 with unknown first name", "test.GetFullName(10) == last3 with unknown first name last3");
	test.ChangeLastName(3, "last5");
	AssertEqual(test.GetFullName(0) , "Incognito", "test.GetFullName(0)==Incognito last5");
	AssertEqual(test.GetFullName(3), "last1 with unknown first name", "test.GetFullName(3) == last1 with unknown first name last5");
	AssertEqual(test.GetFullName(10) ,"last3 with unknown first name", "test.GetFullName(10) == last3 with unknown first name last5");
	AssertEqual(test.GetFullName(1) , "last2 with unknown first name", "test.GetFullName(1) == last2 with unknown first name last5");
	Assert(test.GetFullName(4) == "last1 with unknown first name", "test.GetFullName(4) == last1 with unknown first name");
}

void TestChangeFirstName() {
	Person test;
	test.ChangeFirstName(3, "first1");
	AssertEqual(test.GetFullName(0) , "Incognito", "test after add firstname 1");
	AssertEqual(test.GetFullName(3) , "first1 with unknown last name", "test GetFullName(3) == first1");
	AssertEqual(test.GetFullName(10) , "first1 with unknown last name", "test GetFullName(10) == first1");
	test.ChangeFirstName(10, "first10");
	AssertEqual(test.GetFullName(0) , "Incognito", "test after add firstname 2");
	AssertEqual(test.GetFullName(3) , "first1 with unknown last name", "test GetFullName(3) == first1 after add firstname 2");
	AssertEqual(test.GetFullName(10) ,"first10 with unknown last name", "test GetFullName(10) == first10");
	AssertEqual(test.GetFullName(7) , "first1 with unknown last name", "test GetFullName(7) == first1");
	AssertEqual(test.GetFullName(70) ,"first10 with unknown last name", "test GetFullName(70) == first10");
	test.ChangeFirstName(5, "first5");
	AssertEqual(test.GetFullName(0) , "Incognito", "test after add firstname 3");
	AssertEqual(test.GetFullName(3) , "first1 with unknown last name", "test GetFullName(3) == first1 after add firstname 3");
	AssertEqual(test.GetFullName(10) , "first10 with unknown last name", "test GetFullName(10) == first10 test after add firstname 3");
	AssertEqual(test.GetFullName(7) , "first5 with unknown last name", "test GetFullName(7) == first5");
	AssertEqual(test.GetFullName(70) ,"first10 with unknown last name", "test GetFullName(70) == first10 test after add firstname 3");
	AssertEqual(test.GetFullName(4) , "first1 with unknown last name", " getfullname(4) test after add firstname 3");
	AssertEqual(test.GetFullName(5) , "first5 with unknown last name", "test GetFullName(5) == first5");
	test.ChangeFirstName(10, "first100");
	AssertEqual(test.GetFullName(10), "first10 with unknown last name", "test GetFullName(10) == first10 test after add firstname 100 trying change first name second time in a year");
	AssertEqual(test.GetFullName(7), "first5 with unknown last name", "test GetFullName(7) == first1 test after add firstname 100");
	AssertEqual(test.GetFullName(70) , "first10 with unknown last name", "test GetFullName(70) == first10 test after add firstname 100");
}

void TestFullName1() {
	Person test;
	test.ChangeFirstName(3, "first3");
	test.ChangeLastName(5, "last5");
	AssertEqual(test.GetFullName(1), "Incognito", "test after adding fullname1");
	AssertEqual(test.GetFullName(3), "first3 with unknown last name", "test.GetFullName(3),first3 with unknown last name");
	AssertEqual(test.GetFullName(4), "first3 with unknown last name", "test.GetFullName(3),first3 with unknown last name 2");
	AssertEqual(test.GetFullName(5), "first3 last5", "test.GetFullName(5)");
	AssertEqual(test.GetFullName(15), "first3 last5", "test.GetFullName(15)");
	test.ChangeLastName(3, "last3");
	AssertEqual(test.GetFullName(3), "first3 last3", "test.GetFullName(3),first3 last3");
	AssertEqual(test.GetFullName(4), "first3 last3", "test.GetFullName(3),first3 last3 2");
	AssertEqual(test.GetFullName(5), "first3 last5", "test.GetFullName(5) last3");
	test.ChangeFirstName(5, "first5");
	AssertEqual(test.GetFullName(3), "first3 last3", "test.GetFullName(3), first3 last3 first5");
	AssertEqual(test.GetFullName(6), "first5 last5", "test test.GetFullName(6)");
}

void TestFullName2() {
	Person test1;
	Person test2;
	AssertEqual(test2.GetFullName(50) , "Incognito", "test2.GetFullName(50)");
	AssertEqual(test1.GetFullName(50) , "Incognito", "test1.GetFullName(50)");
	test1.ChangeFirstName(8, "1first8");
	AssertEqual(test2.GetFullName(8) , "Incognito", "test2.GetFullName(8)");
	test2.ChangeLastName(4, "test2last4");
	AssertEqual(test1.GetFullName(1), "Incognito", "test1.GetFullName(1)");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestChangeLastName, "TestChangeLastName");
	runner.RunTest(TestChangeFirstName, "TestChangeFirstName");
	runner.RunTest(TestFullName1, "TestFullName1");
	runner.RunTest(TestFullName2, "TestFullName2");
	return 0;
}