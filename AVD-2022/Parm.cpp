#include "Parm.h"
#include "Error.h"
#include <string>
#include <fstream>
using namespace std;
namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		bool in = 0, out = 0, log = 0;
		PARM e;
		for (int i = 1; i < argc; ++i)
		{
			*argv = argv[i];
			if (wcslen(*argv) > PARM_MAX_SIZE) throw ERROR_THROW(104)
				int size = wcslen(*argv);

			if (wcsstr(*argv, PARM_IN))
			{
				in = true;
				wchar_t* a = *argv + (wchar_t)4;
				wcsncpy_s(e.in, a, wcslen(a));
				ofstream file1(e.in, ios_base::in);
				if (!file1.is_open()) throw ERROR_THROW(100);
				file1.close();
			}
			if (wcsstr(*argv, PARM_OUT))
			{
				out = true;
				wchar_t* a = *argv + (wchar_t)5;
				wcsncpy_s(e.out, a, wcslen(a));
			}
			if (wcsstr(*argv, PARM_LOG))
			{
				log = true;
				wchar_t* a = *argv + (wchar_t)5;
				wcsncpy_s(e.log, a, wcslen(a));
			}
		}
		if (!in) throw ERROR_THROW(100);
		*argv = argv[1];
		if (!out)
		{
			wchar_t* a = *argv + (wchar_t)4;
			wcsncpy_s(e.out, a, wcslen(a));
			wcscat_s(e.out, PARM_OUT_DEFAULT_EXT);
		}
		if (!log)
		{
			wchar_t* a = *argv + (wchar_t)4;
			wcsncpy_s(e.log, a, wcslen(a));
			wcscat_s(e.log, PARM_LOG_DEFAULT_EXT);
		}
		return e;
	}
}