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
	"Неверный размер массива", "Ошибка выделения памяти", "Неверный индекс: "
};
template <class T>
class Array
{
private: 
	// динамически выделяемый список размером size
	T* alist;
	int size;

	// метод обработки ошибок
	void Error(ErrorType error, int badIndex = 0) const {
		std::cerr << "Ошибка" << errorMsg[error];
		exit(1);
	}

public:
	// конструкторы и деструктор
	Array(int sz = 50);
	Array(const Array<T>& A);
	~Array(void);

	// присваивание, индексация и преобразование указателя
	Array<T>& operator= (const Array<T>& rhs);
	T& operator[](int i);
	operator T* (void) const;

	// операции с размером массива
	int ListSize(void) const;	// читать size
	void Resize(int sz;)		// обновлять size
};

template<class T>
inline Array<T>::Array(int sz) {
	// проверка на наличие параметра неверного размера
	if (sz <= 0)
		Error(invalidArraySize);
	// присваивание размера и выделение памяти
	size = sz;
	alist = new T[size];
	// убеждаемся в том, что система выделяет необходимую память,
	if (alist == NULL)
		Error(memoryAllocationError);
}

// деструтор
template<class T>
Array<T>::~Array(void)
{
	delete[] alist;
}
// конструктор копирования
template <class T>
Array<T>::Array(const Array<T>& X) {
	// получить размер объекта и присовить текущему объекту
	int n = X.size;
	size = n;
	alist = new T[n]; // динамически созданный массив
	if (alist == NULL)
		Error(memoryAllocationError);
	T* srcptr = X.alist; // адрес начала X.alist
	T* destptr = alist;	 // адрес начала alist
	while (n--) // копировать список
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
	// возвращает адресс закрытого массива в текущем объекте
	return alist;
}

template <class T>
void Array<T>::Resize(int sz) {
	// проверка нового размера массива
	if (sz <= 0)
		Error(invalidArraySize);
	// ничего не делать, если размер не изменился
	if (sz == size)
		return;
	// запросить память для нового массива и проверить ответ системы
	T* newlist = new T[sz];
	if (newlist == NULL)
		Error(memoryAllocationError);
	// объявить n и инициализировать значение sz или size
	int n = (sz <= size) ? sz : size;
	T* srcptr = X.alist; // адрес начала X.alist
	T* destptr = alist;	 // адрес начала alist
	while (n--)			// копировать список
		*destptr++ = *srcptr++;

	// удалить старый список
	delete[] alist;
	
	// переустановить alist, чтобы он указывал на newlist
	// и обновить член класса size
	alist = newlist;
	size = sz;
}
template<class T>
int Array<T>::ListSize() const{
	return size;
}