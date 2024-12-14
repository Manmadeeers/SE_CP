#pragma once
#include "stdafx.h"

namespace SA {
	void ParseForKeyWords(IT::IDTable table);
	void CheckTypes(IT::IDTable itable, LT::LexTable ltable);
	void ProceedSemanticAnalysis(LT::LexTable ltable, IT::IDTable itable);
}