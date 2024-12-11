#include "stdafx.h"
namespace ERROR
{
	// 0 - 99 - системные ошибки/system erors
	// 100 - 109 - ошибки параметров//parameter erors
	// 110 - 119 - ошибки открытия и чтения файлов/file open and read erors

    Error errors[ERROR_MAX_ENTRY] = //list of errors
    {
		ERROR_ENTRY(0, "Inapropriate error code"),
		ERROR_ENTRY(1, "System error"),
		ERROR_ENTRY(2,"Not enough parametres set"),
		ERROR_ENTRY_NODEF(3),
		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),
		ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),

		//lexem and identifier table errors
		ERROR_ENTRY(60, "Lexem Table:failed to add a new element. Table overflow  or impossible size"),
		ERROR_ENTRY(61, "Lexem Table:failed to get an element by index.Table subscript out of range or less then possible"),
		ERROR_ENTRY_NODEF(62),
		ERROR_ENTRY(63, "Lexem Table:failed to open a stream to print the table"),
		ERROR_ENTRY_NODEF(64),
		ERROR_ENTRY(65, "ID Table:Id's name is longer then alowed length"),
		ERROR_ENTRY(66, "ID Tbale:failed to add a new element.Table overflow"),
		ERROR_ENTRY(67, "ID Table:failed to get an element by index.Table subscript out of range or less then possible"),
		ERROR_ENTRY(68,"ID Table:failed to create an ID Table. Size is more then allowed"),
		ERROR_ENTRY_NODEF(69),
		ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),

		//lecsical analyzer erors
		ERROR_ENTRY(90, "Lexical analyser: word was not determined"),
		ERROR_ENTRY(91, "Lexical analyser: string literal is longer then possible"),
		ERROR_ENTRY(92, "Lexical analyser: string literal was not determined"),
		ERROR_ENTRY(93, "Lexical analyser: identifier was not determined"),
		ERROR_ENTRY(94, "Lexical analyser: more then one main function found"),
		ERROR_ENTRY(95, "Lexical analyser: function was determined more than once"),
		ERROR_ENTRY(96, "Lexical analyser: variable was declared more than once"),
		ERROR_ENTRY(97, "Lexical analyser: unknown variable"),
		ERROR_ENTRY(98,"Lexical analyser: punktuation mistakes"),
		ERROR_ENTRY_NODEF(98),
		ERROR_ENTRY_NODEF(99),

		//
		ERROR_ENTRY(100, " -in must have a parametr"),
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Incoming parametr length is more than possible"),
		ERROR_ENTRY(105, "File length limit is reached"),
		ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Source code file opening error (-in)"),
		ERROR_ENTRY(111, "Inapropprite symbol in a source code file (-in)"),
		ERROR_ENTRY(112, "Failed to create log file (-log)"),
		ERROR_ENTRY(113, "Failed to create out file (-out)"),
		ERROR_ENTRY(114,"Log file creation impossible"),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),
		ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY_NODEF100(200),

		ERROR_ENTRY_NODEF100(300),

		ERROR_ENTRY_NODEF100(400),

		ERROR_ENTRY_NODEF100(500),

		//syntax analyser errors
		ERROR_ENTRY(600,"Incorrect program structure"),
		ERROR_ENTRY(601,"Incorrect identifier, ley word usage or punktuation"),
		ERROR_ENTRY(602,"Incorrect expression"),
		ERROR_ENTRY(603,"Incorrect expression as function parametres"),
		ERROR_ENTRY(604,"Incorrect function parametres"),
		ERROR_ENTRY(605,"Incorrect math function or operator or it's usage"),
		ERROR_ENTRY(606,"Incorrect loop exit condition"),
		ERROR_ENTRY(607,"Incorrect parametres in function that doesn't take any"),

		ERROR_ENTRY_NODEF100(700),

		ERROR_ENTRY_NODEF100(800)
		
    };

	Error geterror(int id) //function for common general errors
	{
		if (id < 1 || id >= ERROR_MAX_ENTRY) {//if there is an unexpected error
			return errors[0];//throw an error for an unexpected error
		}
		return errors[id];//if an eror in expected throw an eror suitable for a situation
	}
	Error geterrorin(int id, int line = -1, int col = -1, unsigned char* FailedText = (unsigned char*)"")//function to throw a specified error
	{
		if (id < 1 || id >= ERROR_MAX_ENTRY) {
			return errors[0];
		}
		//specify an error and column where an error is ocured
		errors[id].err_spec.col = col;
		errors[id].err_spec.line = line;
		errors[id].err_spec.FailedText = FailedText;
		return errors[id];
	}
}

