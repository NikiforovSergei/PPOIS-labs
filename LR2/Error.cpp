#include "Error.h"

namespace Error
{
	ER error[ERROR_MAX_ENTRY] =	// Таблица ошибок
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки\n"),
		ERROR_ENTRY(1, "Системный сбой\n"),
		ERROR_ENTRY(2, "Неверный размер имени\n"),  
		ERROR_ENTRY(3, "Введенное имя не соответсвует правилам\n"),
		ERROR_ENTRY(4, "Имя первого множества такое же, как и у второго множества\n"),
		ERROR_ENTRY(5, "Недопустимый символ кодировки\n"),
		ERROR_ENTRY(6, "Элемент присутсвует в множестве\n"),
		ERROR_ENTRY(7, "Некорректный ввод\n"),
		ERROR_ENTRY(8, "Такого имени нет\n"),
		ERROR_ENTRY(9, "Такой операции не существует\n"),
		ERROR_ENTRY(10, "Функция Boolean не должна содержать два аргумента\n"),
	};

	ER geterror(int id){
		ER e;								// Объявляем переменную е структуры ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)		// Проверяем диапазон
			e = error[0];						// Если ошибка выходит за диапазон
		else
			e = error[id];	// Если входит в диапазон
		return e;
	}

	ER geterrorin(int id, int line = -1, int col = -1){
		ER e;								// Объявляем переменную е структуры ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)		// Снова проверяем диапазон
			e = error[0];						// Не входит
		else									// Входит
		{
			e = error[id];						// Записываем ошибку
			e.inext.line = line;				// Определяем строку
			e.inext.col = col;					// Определяем позицию
		}
		return e;
	}

};
