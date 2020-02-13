#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <memory>

using namespace std;

class Human {
public:
	Human(const string& name,const string& profi) : 
		Name(name),Profession(profi){}

	string getName() {
		return Name;
	}

	string getProfession()
	{
		return Profession;
	}

	void Do(deque<string>& do_smth) {
		do_smth.push_front(" ");
		do_smth.push_front(Name);
		do_smth.push_front(": ");
		do_smth.push_front(Profession);

		for (const string& str : do_smth) {
			cout << str;
		}
		cout << endl;
	}

	virtual void Walk(string destination) {
		deque<string> do_smth;
		do_smth.push_back(" walks to: ");
		do_smth.push_back(destination);
		Do(do_smth);
	}

	virtual void Check(shared_ptr<Human> h) {}

protected:
	const string Name;
	const string Profession;
};

class Student : public Human{
public:

	Student(const string& name,const string& favouriteSong): 
		Human(name,"Student"), FavouriteSong(favouriteSong) {}

	void Learn() {
		deque<string> do_smth;
		do_smth.push_back(" learns");
		Do(do_smth);
	}

	void Walk(string destination) override
	{
		deque<string> do_smth;
		do_smth.push_back(" walks to: ");
		do_smth.push_back(destination);
		Do(do_smth);
		SingSong();
	}

	void SingSong() {
		deque<string> do_smth;
		do_smth.push_back(" sings a song: ");
		do_smth.push_back(FavouriteSong);
		Do(do_smth);
	}

protected:
	const string FavouriteSong;
};


class Teacher:public Human {
public:

	Teacher(const string& name,const string& subject): 
		Human(name,"Teacher"),Subject(subject) {}

	void Teach() {
		deque<string> do_smth;
		do_smth.push_back(" teaches: ");
		do_smth.push_back(Subject);
		Do(do_smth);
	}

protected:
	string Subject;
};


class Policeman: public Human {
public:
	Policeman(const string& name) :
		Human(name, "Policeman") {}

	void Check(shared_ptr<Human> h) override
	{
		deque<string> do_smth;
		do_smth.push_back(" checks ");
		do_smth.push_back((*h).getProfession());
		do_smth.push_back(". ");
		do_smth.push_back((*h).getProfession());
		do_smth.push_back("'s name is: ");
		do_smth.push_back((*h).getName());
		Do(do_smth);
	}

};


void VisitPlaces(shared_ptr<Human> h, vector<string> places) {
	for (auto p : places) {
		(*h).Walk(p);
	}
}


int main() {

	shared_ptr<Human> s;
	shared_ptr<Human> t;
	shared_ptr<Human> p;

	p = make_shared<Policeman>("Bob");
	s = make_shared<Student>("Ann", "We will rock you");
	t = make_shared<Teacher>("Jim", "Math");

	VisitPlaces(t, { "Moscow", "London" });
	(*p).Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}