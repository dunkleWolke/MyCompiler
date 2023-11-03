#include <iostream>
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include "Log.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "GRB.h"
#include "MFST.h"
#include "PolishNotation.h"
#include "Lexanaliz.h"
#include "Semantic.h"
#include "Generation.h"
using namespace std;
void wmain(int agrc, wchar_t* agrv[])
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(agrc, agrv);
		log = Log::getlog(parm.log);
		WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Log::WriteText(log, in);
		LT::LexTable lt = LT::Create();
		IT::IdTable it = IT::Create();
		LA::table(in, lt, it, log);
		Log::WriteLT(lt, log, it);

		Log::WriteLT_ALL(lt, log);
		Log::WriteIT_ALL(it, log);
		MFST::Mfst mfst(lt, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();
		mfst.printrules();

		PN::SearchEq(lt, it);
		Log::WritePN(lt, log, it);

		SA::Semantic(lt, it, log);

		Generation::Generation(lt, it, log, parm.out);

		In::Delete(in);
		LT::Delete(lt);
		IT::Delete(it);
		Log::Close(log);
		system("pause");

	}
	catch (Error::ERROR e)
	{
		if (e.id != 100)
			Log::WriteError(log, e);
		else
		{
			cout << "Ошибка " << e.id << "  " << e.message << endl
				<< "---------------------------------------------------\n";
			system("pause");
		}
	}
}