#include "stdafx.h"
#include "Out.h"
namespace OUT {

	Out getout(wchar_t outfile[]) {

		Out out_to_return;

		out_to_return.stream = new ofstream;//opening a new stream
		out_to_return.stream->open(outfile);

		if (!out_to_return.stream->is_open()) {//check if it's possible to open/create file
			throw ERROR_THROW(113);
		}

		wcscpy_s(out_to_return.outfile, outfile);//write info down to the structure


		return out_to_return;
	}

	void WriteOUT(In::IN in, wchar_t outfile[]) {
		ofstream file_out(outfile);

		if (!file_out.is_open()) {
			throw ERROR_THROW(113);
		}

		file_out << in.text << endl;

		file_out.close();
	}

	void WriteERROR(ERROR::Error error, Out out) {
		//*out.stream << in.text << endl;
		*out.stream << "Error " << error.id << " " << error.message << endl;
		if (error.err_spec.line != -1) {
			*out.stream << "Error " << error.id << " " << error.message << " occured in line " << error.err_spec.line << " column " << error.err_spec.col << endl
				<< " Text: " << error.err_spec.FailedText << endl;
		}


	}


	void Close(Out out) {
		out.stream->close();
		delete out.stream;
	}
};