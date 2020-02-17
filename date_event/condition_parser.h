#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

// В общем случае вызврашает LogicalOperationNode
shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

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