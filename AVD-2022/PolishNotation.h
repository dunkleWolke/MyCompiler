#pragma once
#include "IT.h"
#include "LT.h"
#include <iostream>
#include <stack>

namespace PN
{
	void SearchEq(LT::LexTable& LexT, IT::IdTable& IdT);
	bool PolishNotation(int lexpos, LT::LexTable& LexT, IT::IdTable& IdT);
	int ArifmPriorities(char symb);
}