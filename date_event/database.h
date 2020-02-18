#pragma once
#include<string>
#include"date.h"
#include<map>
#include<unordered_set>
#include"node.h"
#include<functional>

using namespace std;

class Database
{
public:
	void Add(Date date, string event);

	void Print(ostream& os) const;

	string Last(Date date) const;

	map<Date, unordered_set<string>> FindIf(function<bool(Date, string)> func) const
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
	}

	int RemoveIf(function<bool(Date, string)> func)
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

ostream& operator << (ostream& os, const pair<const Date, unordered_set<string>>& d_e);