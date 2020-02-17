#pragma once
#include"date.h"
#include"condition_parser.h"

//������ string ���� ����� ����������� ������� enum 

class Node {
public:

	Node(string type) : type_(type){}

	string GetTypeNode();

	bool Evaluate(const Date& date, const string& event);	// ���� �� ����� �������� ������������� �� ������ ������� ������ ����. ������ ������ ������ � ���� ���������

protected:
	string type_;
};

class EmptyNode :public Node
{
public:
	EmptyNode() :
		Node("EmptyNode"){}
};

class LogicalOperationNode : public Node
{
public:

	LogicalOperationNode(LogicalOperation l_op, shared_ptr<Node> node_left, shared_ptr<Node> node_right):
		Node("LogicalOperationNode"),l_op_(l_op),node_left_(node_left),node_right_(node_right){}

	shared_ptr<Node> GetLeft();

	shared_ptr<Node> GetRight();

	LogicalOperation GetOp();

protected:
	LogicalOperation l_op_;
	shared_ptr<Node> node_left_;
	shared_ptr<Node> node_right_;

};

class DateComparisonNode : public Node
{
public:

	DateComparisonNode(Comparison cmp, Date date):
		Node("DateComparisonNode"), cmp_(cmp), date_(date){}

protected:
	Comparison cmp_;
	Date date_;
};

class EventComparisonNode : public Node
{
public:

	EventComparisonNode(Comparison cmp, string event):
		Node("EventComparisonNode"), cmp_(cmp), event_(event){}

protected:
	Comparison cmp_;
	string event_;
};