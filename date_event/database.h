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

	void Print(ostream& os); // fix: ���� ���������� �������� ������ ��� ���� ����-�������

	template <typename T> map<Date, set<string>> FindIf(T& func)
	{
		string type = condition->GetTypeNode();
		if (type == "LogicalOperationNode") {
			shared_ptr<Node> condition->GetLeft();
			// ��� ���� ���-�� �������� ����������� ���������.
		}
		else
			if (type == "DateComparisonNode")
			{
				// return � ��������������� ��������
			}
			else
				if (type == "EventComparisonNode")
				{
					// return � ��������������� ��������
				}
	}

	template <typename T> int RemoveIf(T& func)		//	argument???
	{
		//
		Date d;
		string str;
		condition;
		func(d, str);
		// ������� ��������� �������, ���� �� ����� ������� ��� ����, �� ������������ FindIf
		// 
		map<Date, set<string>> to_del = FindIf(func);
		int size = to_del.size(); // ��� ������ ����� �� �����, ����� ��������� ������ ���������� ��������� event-��
		// �������� �������� � �����
		base.erase()

		return size;
		
	}
protected:
	map<Date, set<string>> base;
};