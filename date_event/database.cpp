#include"database.h"
void Database::Print(ostream& os)
{
	for (const auto& item : base) {
		os << item;
	}
}

void Database::Add(Date date, string event)
{
	base[date].insert(event);
}
string Database::Last(Date date)
{
	shared_ptr<Node> node;
	node = make_shared<DateComparisonNode>(Comparison::LessOrEqual, date);
	auto predicate = [node](const Date& date, const string& event) {
		return node->Evaluate(date, event);
	};

	const auto entries = FindIf(predicate);
	if (entries.size() == 0)
		throw invalid_argument("");
	else
	{
		auto it = entries.end()--;
		return *(it->second.end()--);
	}
}