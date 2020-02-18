#include"node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event)
{
	return true;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& l_op, const shared_ptr<Node>& node_left, const shared_ptr<Node>& node_right) :
	l_op_(l_op), node_left_(node_left), node_right_(node_right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event)
{
	bool res_left=node_left_->Evaluate(date, event);
	bool res_right = node_right_->Evaluate(date, event);
	if (l_op_ == LogicalOperation::And)
		return res_left && res_right;
	else
		return res_left || res_right;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) :
	cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event)
{
	switch (cmp_)
	{
	case Comparison::Equal :
		return date == date_;
	case Comparison::Greater:
		return date > date_;
	case Comparison::GreaterOrEqual:
		return date >= date_;
	case Comparison::Less:
		return date < date_;
	case Comparison::LessOrEqual:
		return date <= date_;
	default:
		return date != date_;
		break;
	}
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) :
	cmp_(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event)
{
	switch (cmp_)
	{
	case Comparison::Equal:
		return event == event_;
	case Comparison::Greater:
		return event > event_;
	case Comparison::GreaterOrEqual:
		return event >= event_;
	case Comparison::Less:
		return event < event_;
	case Comparison::LessOrEqual:
		return event <= event_;
	default:
		return event != event_;

	}
}