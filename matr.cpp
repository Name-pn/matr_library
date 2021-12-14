#include "matr.h"

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
			b.mas[i][j] = mas[m - i - 1][n - j - 1];
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

long double scm(long long a, long long b) {
	long long lgcd = gcd(a, b);
	if (lgcd)
		return(a * b / lgcd);
	else
		return 1;
}

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

void divide_vect(std::vector <long double> &a, long long x) {
	for (size_t i = 0; i < a.size(); i++) {
		a[i] /= x;
	}
}

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

long long prepare_column(matr_operations &a, size_t i) {
	long long multiple = 1;
	long long lscm = scm_column(a, i);
	long long lm;
	for (size_t j = i + 1; j < a.lines(); j++) {
		if (a[j][i] != 0) {
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

long double try_to_one(matr_operations& a, size_t i) {
	if (a[i][i] != 0) {
		long double k = a[i][i];
		divide_vect(a[i], k);
		return(k);
	}
	else 
		return(1);
}

long long matr_operations::try_triangular_matr(void) {
	long long r = 1;
	r *= red_smatr(*this);
	for (size_t i = 0; i < m - 1; i++) {
		r /= prepare_column(*this, i);
		clean_bottom(*this, i);
		r *= try_to_one(*this, i);
	}
	return(r);
}

long double matr_operations::determinant(void) {
	if (n != m)
		throw std::exception("Ошибка данных. Попытка нахождения опеределителя не квадратной матрицы");
	if (n < 1 || m < 1)
		throw std::exception("Ошибка данных. Попытка нахождения опеределителя матрицы не корректной размерности");
	long double k = this->try_triangular_matr();
	long double det = 1;
	for (size_t i = 0; i < (*this).n; i++) {
		det *= (*this)[i][i];
	}
 	return(det);
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
