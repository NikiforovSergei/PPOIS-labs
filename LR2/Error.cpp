#include "Header.h"

namespace Error
{
	ER error[ERROR_MAX_ENTRY] =	// Таблица ошибок
	{
		ERROR_ENTRY(0, "Некорректный ввод\n"),
		ERROR_ENTRY(1, "Функция Bool должна иметь 1 аргумент\n"),
		ERROR_ENTRY(2, "Пустой ввод\n"),
		ERROR_ENTRY(3, "Некорректный ввод скобок\n"),
		ERROR_ENTRY(4, "Знаки операций не могут быть внутри множества\n"),
		ERROR_ENTRY(5, "Элементы не могут являться операндами\n"),
		ERROR_ENTRY(6, "Запятая не является оператором\n")
	};

	ER geterror(int id) {
		ER e;								// Объявляем переменную е структуры ERROR
		if (id < 0 || id > ERROR_MAX_ENTRY)		// Проверяем диапазон
			e = error[0];						// Если ошибка выходит за диапазон
		else
			e = error[id];	// Если входит в диапазон
		return e;
	}

	ER geterrorin(int id, int line = -1, int col = -1) {
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
