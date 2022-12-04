#pragma once
#include <iostream>
#ifndef NULL
const int NULL = 0;
#endif // !NUll

enum ErrorType
{
	invalidArraySize, memoryAllocationError, indexOutOfRange
};
const char* errorMsg[] = {
	"�������� ������ �������", "������ ��������� ������", "�������� ������: "
};
template <class T>
class Array
{
private: 
	// ����������� ���������� ������ �������� size
	T* alist;
	int size;

	// ����� ��������� ������
	void Error(ErrorType error, int badIndex = 0) const {
		std::cerr << "������" << errorMsg[error];
		exit(1);
	}

public:
	// ������������ � ����������
	Array(int sz = 50);
	Array(const Array<T>& A);
	~Array(void);

	// ������������, ���������� � �������������� ���������
	Array<T>& operator= (const Array<T>& rhs);
	T& operator[](int i);
	operator T* (void) const;

	// �������� � �������� �������
	int ListSize(void) const;	// ������ size
	void Resize(int sz;)		// ��������� size
};

template<class T>
inline Array<T>::Array(int sz) {
	// �������� �� ������� ��������� ��������� �������
	if (sz <= 0)
		Error(invalidArraySize);
	// ������������ ������� � ��������� ������
	size = sz;
	alist = new T[size];
	// ���������� � ���, ��� ������� �������� ����������� ������,
	if (alist == NULL)
		Error(memoryAllocationError);
}

// ���������
template<class T>
Array<T>::~Array(void)
{
	delete[] alist;
}
// ����������� �����������
template <class T>
Array<T>::Array(const Array<T>& X) {
	// �������� ������ ������� � ��������� �������� �������
	int n = X.size;
	size = n;
	alist = new T[n]; // ����������� ��������� ������
	if (alist == NULL)
		Error(memoryAllocationError);
	T* srcptr = X.alist; // ����� ������ X.alist
	T* destptr = alist;	 // ����� ������ alist
	while (n--) // ���������� ������
		*destptr++ = *srcptr++;
}
template <class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs) {
	return Array(rhs);
}

template <class T>
T& Array<T>::operator[](int i) {
	if (i < size && i >= 0)
		return alist[i];
	else
		Error(indexOutOfRange);
}

template <class T>
Array<T>:: operator T* () const {
	// ���������� ������ ��������� ������� � ������� �������
	return alist;
}

template <class T>
void Array<T>::Resize(int sz) {
	// �������� ������ ������� �������
	if (sz <= 0)
		Error(invalidArraySize);
	// ������ �� ������, ���� ������ �� ���������
	if (sz == size)
		return;
	// ��������� ������ ��� ������ ������� � ��������� ����� �������
	T* newlist = new T[sz];
	if (newlist == NULL)
		Error(memoryAllocationError);
	// �������� n � ���������������� �������� sz ��� size
	int n = (sz <= size) ? sz : size;
	T* srcptr = X.alist; // ����� ������ X.alist
	T* destptr = alist;	 // ����� ������ alist
	while (n--)			// ���������� ������
		*destptr++ = *srcptr++;

	// ������� ������ ������
	delete[] alist;
	
	// �������������� alist, ����� �� �������� �� newlist
	// � �������� ���� ������ size
	alist = newlist;
	size = sz;
}
template<class T>
int Array<T>::ListSize() const{
	return size;
}