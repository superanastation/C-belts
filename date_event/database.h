#pragma once
#include<string>
#include"date.h"
#include<map>
#include<set>
#include"node.h"

using namespace std;

class Database
{
public:
	void Add(Date date, string event);

	void Print(ostream& os); // fix: надо определить оператор вывода для пары дата-событие

	template <typename T> map<Date, set<string>> FindIf(T& func)
	{
		string type = condition->GetTypeNode();
		if (type == "LogicalOperationNode") {
			shared_ptr<Node> condition->GetLeft();
			// тут надо что-то возможно рекурсивное придумать.
		}
		else
			if (type == "DateComparisonNode")
			{
				// return с соответствующей функцией
			}
			else
				if (type == "EventComparisonNode")
				{
					// return с соответствующей функцией
				}
	}

	template <typename T> int RemoveIf(T& func)		//	argument???
	{
		//
		Date d;
		string str;
		condition;
		func(d, str);
		// сначала разобрать условие, если не нужно удалить всю базу, то использовать FindIf
		// 
		map<Date, set<string>> to_del = FindIf(func);
		int size = to_del.size(); // тут скорее всего не верно, нужно посчитать именно количество удаляемых event-ов
		// удаление наверное в цикле
		base.erase()

		return size;
		
	}
protected:
	map<Date, set<string>> base;
};