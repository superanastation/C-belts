#include"database.h"
void Database::Print(ostream& os) const
{
	for (const auto& item : v_base) {
		os << item;
	}
}

void Database::Add(Date date, string event)
{
	if (set_base[date].count(event) == 0)
	{
		set_base[date].insert(event);
		v_base[date].push_back(event);
	}
		
}
pair<Date, string> Database::Last(Date date) const
{
	shared_ptr<Node> node;
	node = make_shared<DateComparisonNode>(Comparison::LessOrEqual, date);
	auto predicate = [node](const Date& date, const string& event) {
		return node->Evaluate(date, event);
	};
	auto it = v_base.rbegin();
	while (it != v_base.rend()) {
		
		if ((it->second).size()>0 && predicate(it->first, (it->second).back()))
		{
			return make_pair(it->first, (it->second).back());
		}	
		it++;
	}
	throw invalid_argument("");
}

map<Date, vector<string>> Database::FindIf(function<bool(Date, string)> func) const
{
	map<Date, vector<string>> res;
	for (const auto& item : v_base)
	{
		for (const auto& str : item.second)
		{
			if (func(item.first, str))
				res[item.first].push_back(str);
		}
	}
	return res;
}


int Database::RemoveIf(function<bool(Date, string)> func) 
{
	int res = 0;
	//map<Date, set<string>> found;
	//for (const auto& item : v_base)
	//{
	//	for (const auto& str : item.second)
	//	{
	//		if (func(item.first, str))
	//			found[item.first].insert(str);
	//	}
	//}
	//map<Date, vector<string>> data = FindIf(func);

	for (const auto& item : v_base)
	{
		auto it = stable_partition(v_base.at(item.first).begin(), v_base.at(item.first).end(), [item,func](string str) {
			return !func(item.first, str);
		});
		res += v_base.at(item.first).end() - it;
		for (auto it1 = it; it1 != v_base.at(item.first).end(); it1++) {
			set_base.at(item.first).erase(*it1);
			if (set_base.at(item.first).size() == 0)
				set_base.erase(item.first);
		}
		v_base.at(item.first).erase(it, v_base.at(item.first).end());
		//if (v_base.at(item.first).size() == 0)
		//	v_base.erase(item.first);
		//for (const auto& event : set_base.at(item.first))
		//{
		//	if (func(item.first, event))
		//		set_base.at(item.first).erase(event);
		//}
	}

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