#pragma once
#include"date.h"
#include<memory>
//#include"condition_parser.h"

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation {
	Or,
	And,
};

class Node {
public:
	Node() {};
	virtual bool Evaluate(const Date& date, const string& event)=0;	
};

class EmptyNode :public Node
{
public:

	bool Evaluate(const Date& date, const string& event) override;
};

class LogicalOperationNode : public Node
{
public:

	LogicalOperationNode(const LogicalOperation& l_op, const shared_ptr<Node>& node_left, const shared_ptr<Node>& node_right);

	bool Evaluate(const Date& date, const string& event) override;

protected:
	LogicalOperation l_op_;
	shared_ptr<Node> node_left_;
	shared_ptr<Node> node_right_;

};

class DateComparisonNode : public Node
{
public:

	DateComparisonNode(const Comparison& cmp, const Date& date);

	bool Evaluate(const Date& date, const string& event) override;

protected:
	Comparison cmp_;
	Date date_;
};

class EventComparisonNode : public Node
{
public:

	EventComparisonNode(const Comparison& cmp, const string& event);

	bool Evaluate(const Date& date, const string& event) override;

protected:
	Comparison cmp_;
	string event_;
};