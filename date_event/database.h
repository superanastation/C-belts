#pragma once
#include<string>
#include"date.h"
#include<map>
#include<unordered_set>
#include"node.h"

using namespace std;

class Database
{
public:
	void Add(Date date, string event);

	void Print(ostream& os);

	string Last(Date date);

	//map<Date, set<string>> DateComparison(const DateComparisonNode& node);

	//map<Date, set<string>> EventComparison(const EventComparisonNode& node);

	template <typename T> map<Date, unordered_set<string>> FindIf(T& func)
	{
		map<Date, unordered_set<string>> res;
		for (const auto& item : base)
		{
			for (const auto& str:item.second)
			{
				if (func(item.first, str))
					res[item.first].insert(str);
			}
		}
		return res;
		//string type = condition->GetTypeNode();
		//if (type == "LogicalOperationNode") {
		//	shared_ptr<Node> condition->GetLeft();
		//	// тут надо что-то возможно рекурсивное придумать.
		//}
		//else
		//	if (type == "DateComparisonNode")
		//	{
		//		// return с соответствующей функцией
		//	}
		//	else
		//		if (type == "EventComparisonNode")
		//		{
		//			// return с соответствующей функцией
		//		}
	}

	template <typename T> int RemoveIf(T& func)		//	argument???
	{
		int res=0;

		for (const auto& item : base)
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
protected:
	map<Date, unordered_set<string>> base;
};

ostream& operator << (ostream& os, const pair<const Date, unordered_set<string>>& d_e)
{
	for (const auto& item : d_e.second)
	{
		os << d_e.first << " " << item;
	}
	return os;
}