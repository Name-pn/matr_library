#pragma once

/**
 * \file
 * \brief Заголовочный файл библиотеки
 */

#ifndef MATR_OPERATIONS
#define MATR_OPERATIONS

#include <iostream>
#include <vector>
#include <iomanip>

const int MATR_OUTPUT_CHARS = 4;

/*
 * \brief Класс матрица, над которой определены алгебраические операции
 * 
 * Данный класс поддерживает такие операции как: сумма матриц, разность, произведение матрицы на матрицу и число, а также вычисление определителя
 * квадратной матрицы и получение обратной матрицы. Часть методов и перегрузок операторов в классе выполняют одно и тоже действие.
 */
class matr_operations {
private:
	long long n, m;
	std::vector <std::vector<long double>> mas;

public:
	/**
	 * \brief Конструктор пустой матрицы.
	 */
	matr_operations(void);
	/**
	 * \brief Конструктор квадратной матрицы.
	 * \param[in] m Размер квадратной матрицы
	 */
	matr_operations(long long m);
	/**
	 * \brief Конструктор произвольной матрицы.
	 * \param[in] m Число строк матрицы.
	 * \param[in] n Число столбцов матрицы.
	 */
	matr_operations(long long m, long long n);

	/**
	 * \brief Метод чтение матрицы со стандартного потока.
	 */
	void read_matr();

	//Работа с полями
	///\brief Метод, возвращающий число строк в матрице.
	inline long long lines(void);
	///\brief Метод, устанавливающий число строк в матрице.
	inline void set_lines(long long m);
	///\brief Метод, возвращающий число столбцов в матрице.
	inline long long columns(void);
	///\brief Метод, устанавливающий число столбцов в матрице.
	inline void set_columns(long long n);
	///\brief Метод получения элемента матрицы по индексам i и j.
	inline long double at(long long i, long long j);

	//Операции с матрицей
	/// Метод, возвращающий транспонированную матрицу
	matr_operations transpose(void); //Транспонирование
	/// Метод, приводящий матрицу к треугольному виду, если это возможно
	long long try_triangular_matr(void); //Приведения матрицы к треугольному виду и получение использованного множителя
	/// Метод, возвращающий детерминант матрицы.
	long double determinant(void);
	/// Метод, возвращающий матрицу обратную данной.
	matr_operations inverse_matr(void);

	/// Возвращает минор матрицы без i строки, j столбца
	matr_operations matr_minor(long long i, long long j); //Получение "минорной" матрицы
	// Возвращает определитель минора матрицы, полученного исключая i строку и j столбец
	long double minor(long long i, long long j); //Получение минора

	//Перегруженный операторы
	///Возвращает строку матрицы
	std::vector <long double> &operator [] (size_t i);
	///Чтение матрицы
	friend std::istream& operator >> (std::istream& in, matr_operations& a);
	/// <summary>
	/// Вывод матрицы
	/// </summary>
	/// <param name="out"></param>
	/// <param name="a"></param>
	/// <returns></returns>
	friend std::ostream& operator << (std::ostream& out, matr_operations a);
	/// <summary>
	/// Сложение матриц
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	friend matr_operations operator + (matr_operations a, matr_operations& b);
	/// <summary>
	/// Умножение матрицы на число
	/// </summary>
	/// <param name="a"></param>
	/// <param name="k"></param>
	/// <returns></returns>
	friend matr_operations operator * (matr_operations a, long double k);
	/// <summary>
	/// Умножение матрицы на число
	/// </summary>
	/// <param name="k"></param>
	/// <param name="a"></param>
	/// <returns></returns>
	friend matr_operations operator * (long double k, matr_operations a);
	/// <summary>
	/// Вычитание матрицы из матрицы
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	friend matr_operations operator - (matr_operations a, matr_operations b);
	/// <summary>
	///Умножение матриц
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	friend matr_operations operator * (matr_operations a, matr_operations b);
	
};

///Возводит матрицу start в степень n
matr_operations pow(matr_operations, int);

#endif
