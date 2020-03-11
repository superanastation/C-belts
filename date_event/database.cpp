#include"database.h"
void Database::Print(ostream& os) const
{
	for (const auto& item : v_base) {
		os << item;
	}
}

void Database::Add(const Date& date,const string& event)
{
	if (set_base[date].insert(event).second)
	{
		v_base[date].push_back(event);
	}
		
}
pair<Date, string> Database::Last(Date date) const
{
	auto it=v_base.upper_bound(date);
	if (it != v_base.begin())
	{
		it--;
		
	}
	else
	{
		if (it->first != date);
		throw invalid_argument("");
	}
	return make_pair(it->first, (it->second).back());
	//shared_ptr<Node> node;
	//node = make_shared<DateComparisonNode>(Comparison::LessOrEqual, date);
	//auto predicate = [node](const Date& date, const string& event) {
	//	return node->Evaluate(date, event);
	//};
	//auto it = v_base.rbegin();
	//while (it != v_base.rend()) {
	//	
	//	if ((it->second).size()>0 && predicate(it->first, (it->second).back()))
	//	{
	//		return make_pair(it->first, (it->second).back());
	//	}	
	//	it++;
	//}
	//throw invalid_argument("");
}

// проблема в том, что здесь будет количество найдённых по размеру мапы, а она равна количеству дат, а надо количество найденных событий
vector<pair<Date,string>> Database::FindIf(function<bool(Date, string)> func) const
{
	vector<pair<Date, string>> res;
	for (const auto& item : v_base)
	{
		for (const auto& str : item.second)
		{
			if (func(item.first, str))
				res.push_back(make_pair(item.first, str));
		}
	}
	return res;
}


int Database::RemoveIf(function<bool(Date, string)> func) 
{
	int res = 0;

	//vector<pair<Date, string>> found = FindIf(func);
	//res = found.size();
	//for (const auto& item : found)
	//{
	//	auto it = stable_partition(v_base.at(item.first).begin(), v_base.at(item.first).end(), [item, func](string str) {
	//		return !func(item.first, str);
	//	});
	//	for (auto it1 = it; it1 != v_base.at(item.first).end(); it1++) {
	//		set_base.at(item.first).erase(*it1);
	//		if (set_base.at(item.first).size() == 0)
	//			set_base.erase(item.first);
	//	}
	//	v_base.at(item.first).erase(it, v_base.at(item.first).end());
	//	if (v_base.at(item.first).size() == 0)
	//		v_base.erase(item.first);
	//}
	//for (const auto& item : v_base)
	//{
	//	auto it = stable_partition(v_base.at(item.first).begin(), v_base.at(item.first).end(), [item,func](string str) {
	//		return !func(item.first, str);
	//	});
	//	res += v_base.at(item.first).end() - it;
	//	for (auto it1 = it; it1 != v_base.at(item.first).end(); it1++) {
	//		set_base.at(item.first).erase(*it1);
	//		if (set_base.at(item.first).size() == 0)
	//			set_base.erase(item.first);
	//	}
	//	v_base.at(item.first).erase(it, v_base.at(item.first).end());
	//	//if (v_base.at(item.first).size() == 0)
	//	//	v_base.erase(item.first);
	//}

	auto iterator = v_base.begin();

	while (iterator != v_base.end())
	{
		auto it = stable_partition(v_base.at(iterator->first).begin(), v_base.at(iterator->first).end(), [iterator, func](string str) {
			return !func(iterator->first, str);
		});
		res += v_base.at(iterator->first).end() - it;
		for (auto it1 = it; it1 != v_base.at(iterator->first).end(); it1++) {
			set_base.at(iterator->first).erase(*it1);
			if (set_base.at(iterator->first).size() == 0)
				set_base.erase(iterator->first);
		}
		v_base.at(iterator->first).erase(it, v_base.at(iterator->first).end());
		if (v_base.at(iterator->first).size() == 0)
			iterator = v_base.erase(iterator);
		else
			iterator++;
	}
	//for (auto iterator = v_base.begin(); iterator != v_base.end(); iterator++)
	//{
	//	auto it = stable_partition(v_base.at(iterator->first).begin(), v_base.at(iterator->first).end(), [iterator, func](string str) {
	//		return !func(iterator->first, str);
	//	});
	//	res += v_base.at(iterator->first).end() - it;
	//	for (auto it1 = it; it1 != v_base.at(iterator->first).end(); it1++) {
	//		set_base.at(iterator->first).erase(*it1);
	//		if (set_base.at(iterator->first).size() == 0)
	//			set_base.erase(iterator->first);
	//	}
	//	v_base.at(iterator->first).erase(it, v_base.at(iterator->first).end());
	//	if (v_base.at(iterator->first).size() == 0)
	//		iterator=v_base.erase(iterator);
	//}

	return res;
}

ostream& operator << (ostream& os, const pair<const Date, vector<string>>& d_e)
{
	for (const auto& item : d_e.second)
	{
		os << d_e.first << " " << item << endl;
	}
	return os;
}

ostream& operator << (ostream& os, const pair<const Date, string>& d_e)
{
	os << d_e.first << " " << d_e.second;// << endl;
	return os;
}

ostream& operator << (ostream& os, const vector<pair<const Date, string>>& d_e)
{
	for (const auto& item : d_e)
	{
		os << item;
	}
	return os;
}