#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "LT.h"
#include "Error.h"
#include "IT.h"
namespace Log
{
	struct LOG
	{
		wchar_t* logfile;
		std::ofstream* stream;

		LOG()
		{
			this->logfile = new wchar_t[PARM_MAX_SIZE];
			this->stream = new std::ofstream;
		}
	};
	void WriteLT_ALL(LT::LexTable lt, LOG log);
	void WriteIT_ALL(IT::IdTable it, LOG log);
	void WriteLT(LT::LexTable lt, LOG log, IT::IdTable it);
	void WritePN(LT::LexTable lt, LOG log, IT::IdTable it);
	static LOG INITLOG;
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, const char* c, ...);
	void WriteLine(LOG log, const wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void WriteError(LOG log, Error::ERROR error);
	void WriteText(Log::LOG log, In::IN in);
	void Close(LOG log);
}