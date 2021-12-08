﻿/***********************************************************************************\
*                    кафедра № 304 1 курс 1 семестр информатика						*
*-----------------------------------------------------------------------------------*
*	Project type : solution															*
*	Project name : lw2																*
*	File name    : main.cpp															*
*	Language     : c/c++															*
*	Programmers  : Плоцкий Б.А. Фальгаров А.А.										*
*	Created      :  15/11/21														*
*	Last revision:  16/11/21														*
*	Comment(s)   : Вариант № 6														*
*																					*
*	Файл исходных данных содержит значения величин M, GRN и элементов массива		*
*	vec[0],...,vec[7]. Написать, отладить и протестировать программу, выполняющую:	*
*		1. Чтение данных из файла.													*
*		2. Формирование нового массива newvec, первый элемент которого равен 		*
*	последнему элементу массива vec, второй - сумме двух последних элементов, 		*
*	третий - сумме трех последних элементов и т.д., кроме того, в newvec последними	*
*	элементами включаются значения GRN и сумма абсолютных значений первых M			*
*	элементов массива vec.															*
*		3. Суммирование всех элементов сформированного массива.						*
*		4. Печать сформированного массива и значения суммы.							*
*		5. Опроеделение положения в сформированном массиве наименьшего				*
*	положительного элемента, печать номера и значения этого элемента.				*
*		Программа должна быть параметризирована и обеспечивать входной контроль.	*
\***********************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
using namespace std;

/***************************************************************
*             О С Н О В Н А Я     П Р О Г Р А М М А            *
***************************************************************/

//  Описание главной функции
int main()
{
	// Установка кодовой страницы консоли
	setlocale(LC_ALL, "RUS");
	//SetConsoleOutputCP(65001);

	// Переменная для работы с файлом
	ifstream file;

	// Открытие файла
	file.open("tests/test1.txt");

	if (!file.is_open())
	{
		cout << "Файл не может быть открыт!\n";
		return 1;
	}// end if


	/*--------------------------------*/
	/*   Блок объявления переменных   */
	/*--------------------------------*/
	double vec[8] = {};		// Изначальный масив
	double sum;				// Сумма элементов       
	double newvec[11];		// Обработанный масив, согласно условию
	int indMin;				// Номер наименьшего положительного
							// элемента

	int M;					// Количество первых элементов,
							// абсолютную сумму которых нужно
							// вписать в sum

	int GRN;				// Значение, вписываемое в предпоследний
							// элемент обработанного масива

	int i;					// Счетчик для цикла ввода массива

	/*---------------------------------*/
	/*  Блок инициализации переменных  */
	/*---------------------------------*/
	indMin = 0;
	sum = 0;

	// Ввод M
	file >> M;

	/*---------------------------------*/
	/*     Проверка входных данных     */
	/*---------------------------------*/
	if (file.eof())
	{

	}
	if (file.fail())
	{
		cout << "M должна быть целым числом." << endl;
		return 2;
	}// end if
	if (!(M > 0))
	{
		cout << "M должна быть > 0." << endl;
		return 3;
	}// end if

	// Эхопечать
	cout << "Эхопечать\tM = " << M << endl;

	// Ввод GRN
	file >> GRN;

	// Эхопечать
	cout << "Эхопечать\tGRN = " << GRN << endl;

	/*---------------------------------*/
	/*     Проверка входных данных     */
	/*---------------------------------*/
	if (file.fail())
	{
		cout << "GRN должна быть числом." << endl;
		return 4;
	}// end if
	else
	{
		// Ввод элементов массива
		for (i = 0; i < 8 && !file.eof(); i++)
		{
			// Ввод элементов массива
			file >> vec[i];

			// Проверка входного символа
			if (file.fail())
			{
				cout << "Элемент массива должен быть числом." << endl;
				return 5;
			}// end if

			// Эхопечать
			cout << "Эхопечать\tvec[" << i << "] = " << vec[i] << endl;
		}// end for i

		// Вывод ошибки, если не достигли конца файла
		if (!file.eof())
		{
			cout << "\nЭлементов массива больше, чем 8.\n"
				<< "Остальные элементы не были введены." << endl;
		}// end if

		// Вывод ошибки, если элментов недостаточно
		if (i <= 7)
		{
			cout << "\nЭлементов массива меньше, чем 8.\n"
				<< "Дальнейшие рассчеты не возможны." << endl;
			return 6;
		}// end if
	}// end else

	// Присваивание последнего элемента из vec
	// первому элементу из newvec 
	newvec[0] = vec[7];

	// Формирование массива newvec
	for (i = 1; i <= 7; i++)
	{
		// Присваивание newvec[i] суммы предыдущего
		// элемента из newvec с vec[7 - i]
		newvec[i] = newvec[i - 1] + vec[7 - i];

		// Сумирование элементов, индексы которых меньше M
		if (i <= M)
		{
			sum += abs(vec[i - 1]);
		}// end if
	}// end for i

	// Второй с конца элемент newvec равен GRN
	newvec[8] = GRN;

	// Препоследний элемент newvec равен GRN
	newvec[9] = sum;

	// Обнуление суммы
	sum = 0;

	// Расчет суммы элементов newvec
	// Печать элементов массива
	cout << "\nВывод элементов массива:\n";
	for (i = 0; i < 10; i++)
	{
		sum += newvec[i];

		// Печат сформированного массива
		cout << "newvec[" << i << "] = " << newvec[i] << endl;

		// Поиск минимального индекса
		if (newvec[indMin] > newvec[i])
		{
			indMin = i;
		}// end if
	}// end for i

	// Вывод мин. индекса и минимального элемента 
	cout << "\nИндекс минимального элемента = " << indMin
		<< "\nМинимальный элемент = " << newvec[indMin]
		<< endl;

	return 0;
} // end main


/**********    End of main.cpp file   **********/