#include "matr.h"

/**
 * \file
 * \brief Файл реализации.
 */

matr_operations::matr_operations(void) {
	n = 0;
	m = 0;
}

matr_operations::matr_operations(long long m) {
	try {
		if (m < 1)
			throw std::exception("Ошибка данных. Попытка определения некорректного размера матрицы\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	this->m = m;
	this->n = m;
	mas.resize(m);
	for (size_t i = 0; i < m; i++) {
		mas[i].resize(n);
	}
}

matr_operations::matr_operations(long long m, long long n) {
	try {
		if (m < 1 || n < 1)
			throw std::exception("Ошибка данных. Попытка определения некорректного размера матрицы\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	this->m = m;
	this->n = n;
	mas.resize(m);
	for (size_t i = 0; i < m; i++) {
		mas[i].resize(n);
	}
}

void matr_operations::read_matr (void){
	for (size_t i = 0; i < this->lines(); i++) {
		for (size_t j = 0; j < this->n; j++) {
			std::cin >> (*this)[i][j];
		}
	}
}

inline long long matr_operations::lines(void) {
	return(m);
}

inline void matr_operations::set_lines(long long m) {
	try {
		if (m < 1)
			throw std::exception("Ошибка данных. Попытка определения некорректного размера матрицы\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	this -> m = m;
	this->mas.resize(m);
	for (size_t i = 0; i < this->m; i++) {
		this->mas[i].resize(this->n);
	}

}

inline long long matr_operations::columns(void) {
	return(n);
}

inline void matr_operations::set_columns(long long n) {
	try {
		if (n < 1)
			throw std::exception("Ошибка данных. Попытка определения некорректного размера матрицы\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	this->n = n;
	for (size_t i = 0; i < this->m; i++) {
		this->mas[i].resize(this->n);
	}
}

inline long double matr_operations::at(long long i, long long j) {
	try {
		if (i < 0 || i > this->m-1 || j < 0 || j > this->n-1)
			throw std::exception("Логическая ошибка. Попытка обращения по некорректному индексу\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	return(mas[i][j]);
}

matr_operations matr_operations::transpose(void) {
	matr_operations b(m, n);
	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			b.mas[i][j] = mas[j][i];
		}
	}
	return (b);
}

std::vector <long double> & matr_operations::operator [] (size_t i) {
	try {
		if (i < 0 || i > this->m - 1)
			throw std::exception("Логическая ошибка. Попытка обращения по некорректному индексу\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	return(mas[i]);
}

std::istream& operator >> (std::istream& in, matr_operations& a) {
	if (a.m == 0 || a.n == 0) {
		in >> a.m >> a.n;
		a.mas.resize(a.m);
		for (size_t i = 0; i < a.m; i++) {
			a.mas[i].resize(a.n);
		}
	}
	for (size_t i = 0; i < a.m; i++) {
		for (size_t j = 0; j < a.n; j++) {
			in >> a.mas[i][j];
		}
	}
	return(in);
}

std::ostream& operator << (std::ostream& out, matr_operations a) {
	for (size_t i = 0; i < a.m; i++) {
		for (size_t j = 0; j < a.n; j++) {
			out << std::setw(MATR_OUTPUT_CHARS) << a.mas[i][j] << ' ';
		}
		out << '\n';
	}
	return(out);
}

matr_operations operator + (matr_operations a, matr_operations& b) {
	try {
		if (a.m != b.m || a.n != b.n || a.n == 0)
			throw std::exception("Логическая ошибка. Не корректные размерности операндов матриц");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	for (size_t i = 0; i < a.m; i++) {
		for (size_t j = 0; j < a.n; j++) {
			a.mas[i][j] += b.mas[i][j];
		}
	}
	return(a);
}

matr_operations operator * (matr_operations a, long double k) {
	try {
		if (a.n == 0 || a.m == 0)
			throw std::exception("Логическая ошибка. Не корректные размерности операндов матриц");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	for (size_t i = 0; i < a.m; i++) {
		for (size_t j = 0; j < a.n; j++) {
			a.mas[i][j] *= k;
		}
	}
	return(a);
}

matr_operations operator * (long double k, matr_operations a) {
	return(a * k);
}

matr_operations operator - (matr_operations a, matr_operations b) {
	b = b * -1;
	return(a + b);
}

static long double get_el(matr_operations a, matr_operations b, long long mi, long long mj) {
	long double el = 0;
	for (size_t i = 0; i < a.columns(); i++) {
		el += a[mi][i] * b[i][mj];
	}
	return(el);
}

matr_operations operator * (matr_operations a, matr_operations b) {
	if (a.columns() != b.lines())
		throw std::exception("Ошибка вводимых данных. Размерности матриц не допускают их перемножения");
	matr_operations c(a.lines(), b.columns());
	for (size_t i = 0; i < b.columns(); i++) {
		for (size_t j = 0; j < a.lines(); j++) {
			c.mas[i][j] = get_el(a, b, i, j);
		}
	}
	return(c);
}

matr_operations pow(matr_operations start, int n) {
	matr_operations t = start;
	for (size_t i = 0; i < n; i++) {
		t = t * start;
	}
	return t;
}

/// <summary>
/// Возвращает наименьший общий делитель a и b
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
long double gcd(long long a, long long b) {
	a = abs(a);
	b = abs(b);
	while (a * b != 0) {
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	return(a + b);
}

/// <summary>
/// Возвращает наименьшее общее кратное a и b
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
long double scm(long long a, long long b) {
	long long lgcd = gcd(a, b);
	if (lgcd)
		return(a * b / lgcd);
	else
		return 1;
}

/// <summary>
/// Возвращает наименьшее общее кратное массива a
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
long double line_gcd(std::vector <long double> a) {
	long long r = 1;
	if (a.size() > 1)
		r = gcd(a[0], a[1]);
	for (size_t i = 2; i < a.size(); i++) {
		r = gcd(r, a[i]);
	}
	if (r)
		return(r);
	else
		return(1);
}

/// <summary>
/// Функция, делящая элементы a на x
/// </summary>
/// <param name="a"></param>
/// <param name="x"></param>
void divide_vect(std::vector <long double> &a, long long x) {
	for (size_t i = 0; i < a.size(); i++) {
		a[i] /= x;
	}
}

/// Выносит общие множители строк матрицы a
long long red_smatr(matr_operations &a) {
	long long r = 1;
	long long gcd;
	for (size_t i = 0; i < a.lines(); i++) {
		gcd = line_gcd(a[i]);
		r *= gcd;
		divide_vect(a[i], gcd);
	}
	return(r);
}

/// Возвращает наименьшее общее кратное столбца i матрицы a
long long scm_column(matr_operations a, size_t i) {
	long long r = 1;
	long long lscm = 1;
	if (a.columns() - 1 > i && a[i][i] != 0 && a[i+1][i] != 0)
		lscm = scm(a[i][i], a[i + 1][i]);
	for (size_t j = i + 2; j < a.lines(); j++) {
		if (a[j][i] != 0)
			lscm = scm(lscm, a[j][i]);
	}
	return(lscm);
}

/// Приводит i столбец a к виду как в треугольной матрице
long long prepare_column(matr_operations &a, size_t i) {
	long long multiple = 1;
	long long lscm = scm_column(a, i);
	long long lm;
	for (size_t j = i + 1; j < a.lines(); j++) {
		if (a[j][i] != 0) {
			// lm = на сколько нужно умножить j строку, чтобы привести i элемент к одному числу
			lm = lscm / a[j][i];
			//Исключение
			if (lm != 0) {
				for (size_t k = i; k < a.columns(); k++) {
					a[j][k] *= lm;
				}
				multiple *= lm;
			}
		}
	}
	return multiple;
}

void dif_propor_line(matr_operations &a, size_t i, size_t j) {
	long long k;
	if (a[i][i] != 0)
		k = a[j][i] / a[i][i];
	else
		k = 1;
	for (size_t di = 0; di < a.columns(); di++) {
		a[j][di] -= a[i][di] * k;
	}
}

void clean_bottom(matr_operations &a, size_t i) {
	for (size_t j = i + 1; j < a.lines(); j++) {
		dif_propor_line(a, i, j);
	}
}

/// <summary>
/// Приводит i-элемент главной диагонали a к 1 путем его деления, возвращает число, на которое он делился или 1, если элемент равен 0
/// </summary>
/// <param name="a"></param>
/// <param name="i"></param>
/// <returns></returns>
long double try_to_one(matr_operations& a, size_t i) {
	if (a[i][i] != 0) {
		long double k = a[i][i];
		divide_vect(a[i], k);
		return(k);
	}
	else 
		return(1);
}

/// <summary>
/// Прибавляет к i-строке a j-строку a
/// </summary>
/// <param name="a"></param>
/// <param name="i"></param>
/// <param name="j"></param>
void sum_rows(matr_operations& a, int i, int j) {
	for (size_t k = 0; k < a.columns(); k++) {
		a[i][k] += a[j][k];
	}
}

/// <summary>
/// Убирает 0 в i элементе главной диагонали a путем прибавления строки снизу, если это возможно
/// </summary>
/// <param name="a"></param>
/// <param name="i"></param>
void try_change_zero(matr_operations &a, int i) {
	if (a[i][i] == 0) {
		for (size_t j = i + 1; j < a.lines(); j++) {
			if (a[j][i] != 0) {
				sum_rows(a, i, j);
			}
		}
	}
}

long long matr_operations::try_triangular_matr(void) {
	long long r = 1;
	r *= red_smatr(*this); // Вынос общих множителей строк
	long double del = 1;
	for (size_t i = 0; i < m; i++) {
		try_change_zero(*this, i); // Если в [i][i] ноль то попытаться его заменить
		del *= prepare_column(*this, i);
		clean_bottom(*this, i);
		r *= try_to_one(*this, i);
		if ((*this)[i][i] == 0)
			return 0;
	}
	return(r / del);
}

long double matr_operations::determinant(void) {
	if (n != m)
		throw std::exception("Ошибка данных. Попытка нахождения опеределителя не квадратной матрицы");
	if (n < 1 || m < 1)
		throw std::exception("Ошибка данных. Попытка нахождения опеределителя матрицы не корректной размерности");
	matr_operations temp = *this;
	long double k = temp.try_triangular_matr(); // Приведение матрицы к треугольному виду и получение множителя

 	return(k);
}

matr_operations matr_operations::matr_minor(long long i, long long j) {
	try {
		if (m != n || n < 2 || m < 2)
			throw std::exception("Ошибка данных. Попытка нахождения минорной матрицы при не корректной размерности исходной матрицы\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	matr_operations b(m - 1, n - 1);
	for (size_t li = 0; li < i; li++) {
		for (size_t lj = 0; lj < j; lj++) {
			b[li][lj] = mas[li][lj];
		}
		for (size_t lj = j + 1; lj < n; lj++) {
			b[li][lj - 1] = mas[li][lj];
		}
	}
	for (size_t li = i + 1; li < m; li++) {
		for (size_t lj = 0; lj < j; lj++) {
			b[li - 1][lj] = mas[li][lj];
		}
		for (size_t lj = j + 1; lj < n; lj++) {
			b[li - 1][lj - 1] = mas[li][lj];
		}
	}
	return(b);
}

long double matr_operations::minor(long long i, long long j) {
	try {
		if (m != n || n < 2 || m < 2)
			throw std::exception("Ошибка данных. Попытка нахождения минора матрицы не корректной размерности\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	matr_operations b(m - 1, n - 1); 
	b = this->matr_minor(i, j);
	return (b.determinant());
}

matr_operations matr_operations::inverse_matr(void) {
	long double det;
	try {
		det = this->determinant();
		if (det == 0)
			throw std::exception("Логическая ошибка. Попытка получения обратной матрицы при определителе равном нулю\n");
		if (n != m || m < 1 || n < 1)
			throw std::exception("Ошибка данных. Попытка нахождения опеределителя матрицы не корректной размерности\n");
	}
	catch (std::exception a) {
		std::cout << a.what();
		exit(-1);
	}
	matr_operations b(m, n);
	for (long long i = 0; i < m; i++) {
		for (long long j = 0; j < n; j++) {
			b[i][j] = ((i + j) % 2 ? -1 : 1) * this->minor(i, j);
		}
	}
	b = b.transpose();
	return(b*(1/det));
}
