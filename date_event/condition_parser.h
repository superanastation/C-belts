#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

string ParseEvent(istream& is);

void TestEmptyNode();
void TestDbAdd();
void TestDbFind();
void TestDbLast();
void TestDbRemoveIf();
void TestInsertionOrder();
void TestsMyCustom();
void TestDatabase();