#pragma once
#include "stdafx.h"
#define PARM_IN		L"-in:"					// source code file extenction
#define PARM_OUT	L"-out:"				// object code file extenction
#define PARM_LOG	L"-log:"				// log file extenction

#define PARM_MAX_SIZE	300					// max parametr length

#define PARM_OUT_DEFAULT_EXT L".out"		// object file default
#define PARM_LOG_DEFAULT_EXT L".log"		// log default

namespace PARM
{
	struct PARM {
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
	};

	PARM getparm(int argc, _TCHAR* ragv[]);//form PARM structure based on main function parametres
};