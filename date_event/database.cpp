#include"database.h"
void Database::Print(ostream& os) const
{
	for (const auto& item : base) {
		os << item;
	}
}

void Database::Add(Date date, string event)
{
	if (base[date].count(event)==0)
		base[date].insert(event);
}
pair<Date, string> Database::Last(Date date) const
{
	shared_ptr<Node> node;
	node = make_shared<DateComparisonNode>(Comparison::LessOrEqual, date);
	auto predicate = [node](const Date& date, const string& event) {
		return node->Evaluate(date, event);
	};
	auto it = base.rend();
	while (it != base.rbegin()) {
		it++;
		auto it_ev = (it->second).begin();
		if (predicate(it->first, (*it_ev)))
		{
			return make_pair(it->first, (*it_ev));
		}		
	}
	throw invalid_argument("");
}

map<Date, unordered_set<string>> Database::FindIf(function<bool(Date, string)> func) const
{
	map<Date, unordered_set<string>> res;
	for (const auto& item : base)
	{
		for (const auto& str : item.second)
		{
			if (func(item.first, str))
				res[item.first].insert(str);
		}
	}
	return res;
}


int Database::RemoveIf(function<bool(Date, string)> func) 
{
	int res = 0;

	map<Date, unordered_set<string>> data = FindIf(func);

	for (const auto& item : data)
	{
		for (const auto& str : item.second)
		{
			if (func(item.first, str))
			{
				res++;
				if (item.second.size() > 1)
					base.at(item.first).erase(str);
				else
					base.erase(item.first);
			}
		}
	}

	return res;
}

ostream& operator << (ostream& os, const pair<const Date, unordered_set<string>>& d_e)
{
	for (const auto& item : d_e.second)
	{
		os << d_e.first << " " << item << endl;
	}
	return os;
}

ostream& operator << (ostream& os, const pair<const Date, string>& d_e)
{
		os << d_e.first << " " << d_e.second << endl;
	return os;
}