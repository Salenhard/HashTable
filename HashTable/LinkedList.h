#pragma once
#include<iostream>
#include "Node.h"
using namespace std;
template <class T>
class LinkedList {
private:
	// указатели для доступа к началу и концу списка
	Node<T>* front, * rear;
	
	// используются для извлечения, вставки и удаления данных
	Node<T>* prevPtr, * currPtr;
	
	// число элементов в списке
	int size;

	// положение в списке. используется методом Reset
	int position;

	// закрытые методы для создания и удаления узлов
	Node<T>* GetNode(const T& item, Node<T>* ptrNext = NULL);
	void FreeNode(Node<T>* p);

	// копирует список L в текущий список
	void CopyList(const LinkedList<T>& L);

public:

	// констуктор
	LinkedList();
	LinkedList(const LinkedList<T>& L);

	// деструктор
	~LinkedList();

	// оператор присваивания
	LinkedList<T>& operator=(const LinkedList<T>& L);

	// проверка сотсояния списка
	int ListSize() const;
	int ListEmpty() const;

	// методы прохождения списка
	void Reset(int pos = 0);
	void Next();
	int EndOfList() const;
	int CurrentPosition() const;
	
	// методы вставки
	void InsertFront(const T& item);
	void InsertRear(const T& item);
	void InsertAt(const T& item);
	void InsertAfter(const T& item);

	// методы удаления
	T DeleteFront();
	void DeleteAt();

	// возвратить/изменить данные
	T& Data();

	// очистка списка
	void ClearList();
};

template <class T>
LinkedList<T>::LinkedList() : front{ NULL }, rear{ NULL }, prevPtr{ NULL },
currPtr{ NULL }, size{ 0 }, position{ -1 } {}

template <class T>
void LinkedList<T>::CopyList(const LinkedList<T>& L) {
	// p - указатель на L
	Node<T>* p = L.front;
	int pos;
	
	while (p != NULL) {
		InsertRear(p->data);
		p = p->NextNode();
	}

	if (position == -1)
		return;

	// переустановить prevPtr и currPtr в новом списке 
	prevPtr = NULL;
	currPtr = front;
	for (pos = 0; pos != position; pos++)
	{
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
	}
}

template<class T>
void LinkedList<T>::ClearList(void) {
	Node<T>* currPosition, * nextPosition;
	currPosition = front;
	while (currPosition != NULL)
	{
		nextPosition = currPosition->NextNode();
		FreeNode(currPosition);
		currPosition = nextPosition;
	}
	front = rear = NULL;
	prevPtr = currPtr = NULL;
	size = 0;
	position = -1;
}

template<class T>
void LinkedList<T>::Reset(int pos)
{
	int startPos;

	if (front == NULL)
		return;

	if (pos < 0 || pos >size - 1) {
		cerr << "Reset: Неверно задано положение: " << pos << endl;
		return;
	}

	if (pos == 0)
	{
		prevPtr = NULL;
		currPtr = front;
		position = 0;
	}
	else
	{
		currPtr = front->NextNode();
		prevPtr = front;
		startPos = 1;
		for (position = startPos; position != pos; position++) {
			prevPtr = currPtr;
			currPtr = currPtr->NextNode();
		}
	}
}

template<class T>
void LinkedList<T>::Next() {
	if (currPtr != NULL)
	{
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
		position++;
	}
}

template<class T>
T& LinkedList<T>::Data() {
	if (size == 0 || currPtr == NULL)
	{
		cerr << "Data: Неверная ссылка!" << endl;
		exit(1);
	}
	return currPtr->data;
}

template <class T>
void LinkedList<T>::InsertAt(const T& item) {
	Node<T>* newNode;
	if (prevPtr == NULL)
	{
		newNode = GetNode(item, front);
		front = newNode;
	}
	else
	{
		newNode = GetNode(item);
		prevPtr->InsertAfter(newNode);
	}
	if (prevPtr == rear) {
		rear = newNode;
		position = size;
	}
	currPtr = newNode;
	size++;
}

template <class T>
void LinkedList<T>::InsertFront(const T& item) {
	Node<T>* p = GetNode(item);
	if (front == NULL)
	{
		rear = p;
		currPtr = p;
		position = 1;
	}
	else {
		p->InsertAfter(front);	
	}
	front = p;
	size++;
}

template <class T>
void LinkedList<T>::InsertRear(const T& item) {
	Node<T>* p = GetNode(item);
	if (ListEmpty()) {
		front = p;
		rear = p;
		currPtr = p;
		position = 1;
		size = 1;
	}
	else
	{
		rear->InsertAfter(p);
		rear = NextNode();
		size++;
	}
}

template <class T>
void LinkedList<T>::InsertAfter(const T& item) {
	Node<T>* p = GetNode(item);
	Node<T>* tmp;
	if (ListEmpty())
	{
		cerr << "Ошибка вставки: лист пустой!";
		exit(1);
	}
	else {
		tmp = currPtr->NextNode();
		currPtr->InsertAfter(p);
		p->InsertAfter(tmp);
		size++;
	}
}

template <class T>
T LinkedList<T>::DeleteFront() {
	Node<T>* p;
	if (front == NULL) {
		cerr << "Ошибка удаления!" << endl;
		exit(1);
	}
	else
	{
		p = front;
		front = front->NextNode();
		FreeNode(p);
		size--;
	}
}

template <class T>
void LinkedList<T>::DeleteAt() {
	Node<T>* p;

	if (currPtr == NULL)
	{
		cerr << "Ошибка удаления!" << endl;
		exit(1);
	}
	if (prevPtr == NULL)
	{
		p = front;
		front = front->NextNode();
	}
	else
		p = prevPtr->DeleteAfter();
	if (p == rear)
	{
		rear = prevPtr;
		position--;
	}
	currPtr = p->NextNode();

	FreeNode(p);
	size--;
}

template <class T>
int LinkedList<T>::EndOfList() const{
	if (currPtr == rear)
		return 1;
	else 
		return 0;
}

template <class T>
int LinkedList<T>::CurrentPosition() const {
	return position;
}

template <class T>
int LinkedList<T>::ListSize() const {
	return size;
}

template <class T>
int LinkedList<T>::ListEmpty() const {
	return (int)(size == 0);
}

template <class T>
Node<T>* LinkedList<T>::GetNode(const T& item, Node<T>* ptrNext) {
	return new Node<T>(item, ptrNext);
}

template <class T>
void LinkedList<T>::FreeNode(Node<T>* p) {
	delete *p;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& L) {
	ClearList();
	if (L.ListEmpty())	
		this = LinkedList();
	else
	{
		L.currPtr = L.front;
		while (currPtr != rear)
		{
			InsertRear(L.currPtr);
			currPtr = currPtr->NextNode();
		}
	}
}

template <class T>
LinkedList<T>::~LinkedList() {
	ClearList();
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& L) {
	LinkedList(L);
}

