#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
	map<T, int> element_count;
	auto it = remove_if(elements.begin(), elements.end(), [&element_count](T element) mutable {
		++element_count[element];
		return element_count[element] > 1;
	});
	elements.erase(it, elements.end());

	//vector<T> copy = elements;
	//auto it = begin(elements);
	//while (it != end(elements)) {
	//	auto j_it = it+1;
	//	auto new_end = remove_if(j_it, end(elements), [](T& item) {
	//		return item == it;
	//	});
	//	elements.erase(new_end, end(elements));
	//	//while (j_it != end(elements))
	//	//{
	//	//	if (*it == *j_it) {
	//	//		elements.erase(j_it);
	//	//		RemoveDuplicates(elements);
	//	//		break;
	//	//	}
	//	//	else
	//	//		++j_it;
	//	//}
	//	++it;
	//}
	//for (int i = 0; i < elements.size(); i++) {
	//	for (int j = i++; j < elements.size(); j++) {
	//		if (elements[i] == elements[j]) {
	//			elements.erase(j);
	//			RemoveDuplicates(elements);
	//			break;
	//		}
	//	}
	//}
	//return;
}

int main() {
	vector<int> v1 = { 6, 4, 7, 6, 4, 4, 0, 1 };
	RemoveDuplicates(v1);
	for (int x : v1) {
		cout << x << " ";
	}
	cout << endl;

	vector<string> v2 = { "C", "C++", "C++", "C", "C++" };
	RemoveDuplicates(v2);
	for (const string& s : v2) {
		cout << s << " ";
	}
	cout << endl;
	return 0;
}