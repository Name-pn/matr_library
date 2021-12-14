#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

const int MATR_OUTPUT_CHARS = 4;

class matr_operations {
private:
	long long n, m;
	std::vector <std::vector<long double>> mas;

public:
	//������������
	matr_operations(void);
	matr_operations(long long m);
	matr_operations(long long m, long long n);

	//������ � ������
	inline long long lines(void);
	inline void set_lines(long long m);
	inline long long columns(void);
	inline void set_columns(long long n);
	inline long double at(long long i, long long j);

	//�������� � ��������
	matr_operations transpose(void); //����������������
	long long try_triangular_matr(void); //���������� ������� � ������������ ���� � ��������� ��������������� ���������
	long double determinant(void); //���������� ������������
	matr_operations inverse_matr(void); //��������� �������� �������

	//�������������� ��������
	matr_operations matr_minor(long long i, long long j); //��������� "��������" �������
	long double minor(long long i, long long j); //��������� ������

	//������������� ���������
	std::vector <long double> &operator [] (size_t i);
	friend std::istream& operator >> (std::istream& in, matr_operations& a);
	friend std::ostream& operator << (std::ostream& out, matr_operations a);
	friend matr_operations operator + (matr_operations a, matr_operations& b);
	friend matr_operations operator * (matr_operations a, long double k);
	friend matr_operations operator * (long double k, matr_operations a);
	friend matr_operations operator - (matr_operations a, matr_operations b);
	friend matr_operations operator * (matr_operations a, matr_operations b);
	
};

//�������� ������� start � ������� n
matr_operations pow(matr_operations, int);