#include "stdafx.h"
#include "Log.h"

namespace LOG {
	Log getlog(wchar_t logfile[]) {

		Log log_to_return;

		log_to_return.stream = new ofstream;//form a new stream using ofstream
		log_to_return.stream->open(logfile);//open file with a certain name

		if (!log_to_return.stream->is_open()) {
			throw ERROR_THROW(112);
		}
		wcscpy_s(log_to_return.logfile, logfile);//copy filename to the Log structure


		return log_to_return;
	}

	void WriteLine(Log log, char* c, ...) {
		char** pointer = &c;
		while (*pointer != "") {
			*log.stream << *pointer;
			*pointer++;
		}
		*log.stream << endl;
	}

	void WriteLine_W(Log log, wchar_t* wc, ...) {
		wchar_t** pc = &wc;
		char l[1024] = "";
		char f[1024] = "";
		while (*pc != L"")
		{
			wcstombs_s(0, l, *pc, IN_MAX_LEN_TEXT);
			strcat_s(f, l);
			pc++;
		}
		*log.stream << f;
	}
	void WriteLog(Log log) {
		char date[100];
		tm local;
		time_t currentTime;
		currentTime = time(NULL);
		localtime_s(&local, &currentTime);
		strftime(date, 100, "%d.%m.%Y %H:%M:%S", &local);
		*log.stream << "---------- Protocol ---------- Date: " << date << endl;
	}

	void WriteParm(Log log, PARM::PARM Parm) {
		*log.stream << "----------Parametres----------" << endl;
		char buffer[PARM_MAX_SIZE];
		size_t tsize = 0;
		wcstombs_s(&tsize, buffer, Parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << buffer << endl;
		wcstombs_s(&tsize, buffer, Parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << buffer << endl;
		wcstombs_s(&tsize, buffer, Parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << buffer << endl;
	}

	void WriteIN(Log log, In::IN in) {
		*log.stream << "----------Entered info----------" << endl;
		*log.stream << in.text << endl;
		*log.stream << "Total amount of symbols: " << in.size << endl;
		*log.stream << "Total amount of ignored symbols: " << in.ignore << endl;
		*log.stream << "Total amount of lines: " << in.lines << endl;
		//testing an array of words
		for (int i = 0; i < in.words_size; i++) {
			*log.stream << in.words[i] << endl;
		}
	}



	void WriteERROR(Log log, ERROR::Error error) {
		*log.stream << "----------Errors----------" << endl;
		*log.stream << "Error " << error.id << " " << error.message << endl;
		if (error.err_spec.line != -1) {
			*log.stream << "Error " << error.id << " " << error.message << " occured in line " << error.err_spec.line << " column" << error.err_spec.col << endl;
		}
	}

	void Close(Log log) {
		log.stream->close();
		delete log.stream;
	}
};