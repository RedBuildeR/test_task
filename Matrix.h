#pragma once
#include<fstream>
#include<iostream>
#include <typeinfo>

template <typename T>
class Matrix
{
private:
	T** data;
	int n;

public:
	Matrix();
	Matrix(int n);
	void output(std::ostream& out);
	void input(std::istream& in);
	int size();
	T& at(int row, int col);
	Matrix<T>& operator=(const Matrix<T>& rhs);

};

template <typename T>
Matrix<T>::Matrix() {
	data = NULL;
	n = 0;
}

template <typename T>
Matrix<T>::Matrix(int n) {
	this->data = new T * [n];
	for (int i = 0; i < n; i++) {
		data[i] = new T[n];
	}
	this->n = n;
}


template <typename T>
void Matrix<T>::output(std::ostream& out) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			out << this->data[i][j] << ' ';
		}
		out << '\n';
	}
}

template<typename T>
void Matrix<T>::input(std::istream& in)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			in >> this->data[i][j];
		}
	}
}

template<typename T>
T& Matrix<T>::at(int row, int col) {
	return this->data[row][col];
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if (this->n != rhs.n) {
		for (int i = 0; i < n; i++) {
			delete[] this->data[i];
		}
		delete[] this->data;
		this->data = new T * [rhs.n];
		for (int i = 0; i < rhs.n; i++) {
			data[i] = new T[rhs.n];
		}
		this->n = rhs.n;
	}
	for (int i = 0; i < rhs.n; i++) {
		for (int j = 0; j < rhs.n; j++) {
			this->data[i][j] = rhs.data[i][j];
		}
	}
	return *this;
}

template <typename T>
int Matrix<T>::size() {
	return n;
}