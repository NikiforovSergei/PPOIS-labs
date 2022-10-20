#pragma once

#define ERROR_THROW(id) Error::geterror(id);				 		// throw ERRPR_THROW(id)
#define ERROR_THROW_IN(id, l, c) Error::geterrorin(id, l, c);		// throw ERRPR_THROW_IN(id, строка, колонка)
#define ERROR_ENTRY(id, m) {id, m, {-1,-1}}							// элемент таблицы ошибок
#define ERROR_MAXSIZE_MESSAGE 200									// максимальаня длина сообщения об ошибке
#define ERROR_ENTRY_NODEF(id)		ERROR_ENTRY(-id, "Неопрделённая ошибка")	// 1 неопределенный элемент таблицы ошибок

#define ERROR_MAX_ENTRY 1000	// количество элементов в таблице ошибок

namespace Error
{
	struct ER	// тип исключения для throw ERROR_THROW | ERROR_THROW_IN и catch(ERROR)
	{
		int id;									// код ошибки
		char message[ERROR_MAXSIZE_MESSAGE];	// сообщение об ошибке
		struct IN								// расширение для ошибки при обработке входных данных
		{
			short line;							// номер строки (0, 1, 2, ...)
			short col;							// номер позиции в стркое (0, 1, 2, ...)
		} inext;
	};

	ER geterror(int id);							// сформировать ERROR для ERROR_THROW
	ER geterrorin(int id, int line, int col);	// сформировать ERROR для ERROR_THROW_IN
}