#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include "Error.h"

namespace SA
{
	bool Semantic(LT::LexTable& Lextable, IT::IdTable& idtable, Log::LOG& log);
}