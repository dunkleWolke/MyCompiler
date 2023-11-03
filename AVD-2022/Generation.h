#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"

#define SEM_GREAT ">"
#define SEM_LESS "<"
#define SEM_EQUAL "=="
#define SEM_GREATEQUAL ">="
#define SEM_LESSEQUAL "<="
#define SEM_NOTEQUAL "!="

namespace Generation
{
	void Generation(LT::LexTable& t, IT::IdTable& idif, Log::LOG log, wchar_t outfile[]);
}