#pragma once
#include "stdafx.h"
#include "Error.h"
namespace OUT {
	struct Out {
		wchar_t outfile[PARM_MAX_SIZE];//out fle parametr
		std::ofstream* stream;
	};
	static const Out INITOUT{ L"", NULL };//initialize Out
	Out getout(wchar_t outfile[]);//create an Out structure
	void WriteOUT(In::IN in, wchar_t outfile[]);//write info down to Out file
	void WriteERROR(ERROR::Error error, Out out);
	void Close(Out out);//close .out files
};