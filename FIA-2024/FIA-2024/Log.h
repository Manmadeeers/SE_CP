#pragma once
#include "stdafx.h"
#include "Error.h"

namespace LOG {
	struct Log {
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};
	static const Log INITLOG{ L"", NULL };
	Log getlog(wchar_t logfile[]);//form log structure
	void WriteLine(Log log, char* c, ...);
	void WriteLine_W(Log log, wchar_t* wc, ...);
	void WriteLog(Log log);
	void WriteParm(Log log, PARM::PARM Parm);
	void WriteIN(Log log, In::IN in);
	void WriteERROR(Log log, ERROR::Error error);
	void Close(Log log);
};
