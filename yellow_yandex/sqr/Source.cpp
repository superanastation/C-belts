#include<utility>
#include<iostream>
#include<map>
#include<vector>

using namespace std;

template <typename Collection> Collection Sqr(const Collection& col);
template <typename T> vector<T> operator *(const vector<T>& left, const vector<T>& right);
template <typename First, typename Second> pair<First, Second> operator*(const pair<First, Second>& left, const pair<First, Second>& right);
template <typename Key, typename Value> map<Key, Value> operator*(const map<Key, Value>& left, const map<Key, Value>& right);

template <typename T> vector<T> operator*(const vector<T>& left, const vector<T>& right) {
	vector<T> res;
	for (auto& j : left) {
		res.push_back(j*j);
	}
	return res;
}
template <typename First, typename Second> pair<First, Second> operator*(const pair<First, Second>& left, const pair<First, Second>& right) {
	pair<First, Second> res;
	res.first = left.first*right.first;
	res.second = left.second*right.second;
	return res;
}
template <typename Key, typename Value> map<Key, Value> operator*(const map<Key, Value>& left, const map<Key, Value>& right) {
	map<Key, Value> res;
	for (const auto& item : left) {
		res[item.first] = item.second*item.second;
	}
	return res;
}

template <typename Collection> Collection Sqr(const Collection& col) {
	Collection res=col*col;
	return res;
}

//template <typename R> R Sqr(const R& num);
////template <typename T> vector<T> Sqr(const vector<T>& vec);
////template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);
////template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);
//
//template <typename R> R Sqr(const R& num) {
//	R res= num * num;
//	return res;
//}

//template <typename T> vector<T> Sqr(const vector<T>& vec) {
//	vector<T> res;
//	for (const auto& i : vec) {
//		res.push_back(Sqr(i));
//	}
//	return res;
//}
//
//template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p) {
//	pair<First, Second> res;
//	res.first = Sqr(p.first);
//	res.second = Sqr(p.second);
//	return res;
//}
//
//template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m) {
//	map<Key, Value> res;
//	for (const auto& item : m) {
//		res[(item.first)]=Sqr(item.second);
//	}
//	return res;
//}

int main() {
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}