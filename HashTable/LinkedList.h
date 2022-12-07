#pragma once

#include <iostream>
#include <stdlib.h>
#include "Node.h"

using namespace std;

template <class T>
class LinkedList
{
	template <class> friend class SeqListIterator;		//  friend class - ������

private:
	// ��������� ��� ������� � ������ � ����� ������ 
	Node<T>* front, * rear;
	// ������������ ��� ����������, ������� � �������� ������
	Node<T>* prevPtr, * currPtr;
	// ����� ��������� � ������ 
	int size;
	// ��������� � ������. ������������ ������� Reset 
	int position;

	// �������� ����
	Node<T>* GetNode(const T& item, Node<T>* ptrNext = NULL);
	// ������� ����
	void FreeNode(Node<T>* pl);
	// �������� ������ L � ������� ������ 
	void CopyList(const LinkedList<T>& L);
	
public:	
	// ����������� 
	LinkedList();
	// ����������� 
	LinkedList(const LinkedList<T>& L);
	// ���������� 
	~LinkedList();

	// �������� ��������� ������ 
	int ListSize() const;
	// �������� �� �������
	int ListEmpty() const;

	// ������������ position � ��������� pos
	void Reset(int pos = 0);
	// ������� � ����. ����
	void Next();
	// ��������, ����� �� �� ����� ������
	bool EndOfList() const;
	// ������� position
	int CurrentPosition() const;

	// �������� �������
	void InsertFront(const T& item);
	// �������� � �����
	void InsertRear(const T& item);
	// �������� �� �����-�� �������
	void InsertAt(const T& item);
	void InsertAfter(const T& item);

	// ������ �������� 
	T DeleteFront();
	// �������� ������-�� ��������
	void DeleteAt();

	// ����������/�������� ������ 
	T& Data();
	// ������� ������ 
	void ClearList();
	LinkedList<T>& operator = (const LinkedList<T>& L);
};

/*----------���������� ���� �����----------*/

template <class T>
Node<T>* LinkedList<T>::GetNode(const T& item, Node<T>* ptrNext) {
	Node<T>* temp = new Node<T>(item, ptrNext);
	return temp;
};


template <class T>
void LinkedList<T>::FreeNode(Node<T>* pl) {
	delete pl;
};


template <class T>
void LinkedList<T>::CopyList(const LinkedList<T>& L) {
	// � - ��������� �� L
	Node<T>* p = L.front;
	int pos;
	// ��������� ������ ������� �� L � ����� �������� ������� 
	while (p != NULL) {
		InsertRear(p->data);
		p = p->NextNode();
	}

	// �����, ���� ������ ������
	if (position == -1)
		return;

	// n������������� prevPtr � currPtr � ����� ������
	prevPtr = NULL;
	currPtr = front;
	for (pos = 0; pos != position; pos++) {
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
	}
};


template <class T>
LinkedList<T>::LinkedList() {
	front = NULL;
	rear = NULL;
	prevPtr = NULL;
	currPtr = NULL;
	size = 0;
	position = 0;
};


template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& L) {
	CopyList(L);
};


template <class T>
LinkedList<T>::~LinkedList(void) {
	delete front;
	delete rear;
};


// �������� ������������
template <class T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T>& L) {
	CopyList(L);	//�������� ������ �� ��������
	return *this;	//���������� ���� ������
};


template <class T>
int LinkedList<T>::ListSize(void) const {
	return size;
};


template <class T>
int LinkedList<T>::ListEmpty(void) const {
	return size == 0;
};


template <class T>
void LinkedList<T>::Reset(int pos) {
	int startPos;
	// ���� ������ ������, ����� 
	if (front == NULL)
		return;
	// ���� ��������� ������ �� �����, ��������� ���������
	if (pos < 0 || pos > size - 1)
	{
		cerr << "Reset: ������� ������ ���������: " << pos << std::endl;
		return;
	}
	// ���������� �������� n���������� � pos
	if (pos == 0) {
		// ������� � ������ ������
		prevPtr = NULL;
		currPtr = front;
		position = 0;
	}
	else
		// n������������� currPtr, prevPtr, � startPos 
	{
		currPtr = front->NextNode();
		prevPtr = front;
		startPos = 1;
		// ������������� ������ �� pos 
		for (position = startPos; position != pos; position++) {
			// ����������� ��� ��������� ����������� ������
			prevPtr = currPtr;
			currPtr = currPtr->NextNode();
		}
	}
};


template <class T>
void LinkedList<T>::Next(void) {
	// �����, ���� ����� ������ ��� // ������ ������ 
	if (currPtr != NULL) {
		// n������������� ��� ��������� �� ���� ���� ������
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
		position++;
	}
};


template <class T>
bool LinkedList<T>::EndOfList() const {
	return (position == size);
};


template <class T>
int LinkedList<T>::CurrentPosition(void) const {
	return position;
};


template<typename T>
void LinkedList<T>::InsertFront(const T& item) {
	Node<T>* newNode; //����� ����
	newNode = GetNode(item, front); //������� � ���� �������� � ����� ������
	front = newNode; //��������� �� ����� ����
	currPtr = front; //��������� ������� ���������
	position = 0; //��������� �������
	size++; //����������� ������
}


template<typename T>
void LinkedList<T>::InsertRear(const T& item) {
	Node<T>* newNode; //����� ����
	this->currPtr = this->front;
	this->position = 0;
	//���� ������ ����, �������� item � ������
	if (this->currPtr == NULL)
		this->InsertFront(item);
	else {
		//����� ���� � ������� ����������
		while (this->currPtr->NextNode() != NULL)
			this->currPtr = this->currPtr->NextNode();
		// ������� ���� � �������� � ����� ������ (����� currPtr)
		newNode = this->GetNode(item, this->rear);
		this->currPtr->InsertAfter(newNode);
		this->size++;
	}
}


template <class T>
void LinkedList<T>::InsertAt(const T& item) {
	Node<T>* newNode;
	// ��� ������: ������� � ������ ��� ������ ������
	if (prevPtr == NULL) {
		// ������� � ������ ������. n������� ����� ���� � ������ ������ 
		newNode = GetNode(item, front);
		front = newNode;
	}
	else {
		// ������� ������ ������. �������� ���� ����� prevPtr
		newNode = GetNode(item);
		prevPtr->InsertAfter(newNode);
	}

	// ��� prevPtr == rear, ����� ������� � ������ ������ 
	// ��� � ����� ��������� ������; ��������� rear � positio�
	if (prevPtr == rear) {
		rear = newNode;
		position = size;
	}
	// �������� currPtr � ��������� size
	currPtr = newNode;
	size++;
};


template<typename T>
void LinkedList<T>::InsertAfter(const T& item) {
	Node<T>* newNode; //����� ����
	if (this->front == NULL) { //���� ������ ����
		//��������� ��� � ������
		newNode = this->getNode(item, this->front);
		this->front = newNode;
	}
	else {
		if (this->currPtr == this->rear) { //���� ��� ��������� ����
			//��������� � ����� ������
			newNode = this->getNode(item, this->rear);
			this->prev_ptr->insAfter(newNode);
		}
		else {
			//��������� ����� ��������
			newNode = this->getNode(item, currPtr->nextNode());
			this->currPtr->insAfter(newNode);
		}
	}
	this->next(); //������� �������
	this->size++;
}


template <class T>
T LinkedList<T>::DeleteFront() {					// TODO
	Node<T>* p;
	T tmp = NULL;

	// ������, ���� ������ ������ ��� ����� ������
	if (currPtr == NULL) {
		cerr << "������ ��������!" << std::endl;
		exit(1);
	}

	if (front != nullptr)
	{
		p = front;
		front = front->NextNode();
		tmp = p->data;
	}

	FreeNode(p);
	return tmp;
};


template <class T>
void LinkedList<T>::DeleteAt(void) {
	Node<T>* p;
	// ������, ���� ������ ������ ��� ����� ������
	if (currPtr == NULL) {
		cerr << "������ ��������!" << std::endl;
		exit(1);
	}

	// ������� ����� ������ � ������ � ������ ������
	if (prevPtr == NULL) {
		// ��������� ����� ������, �� �� ��������� ���. ���� ��� - ��������� ����, ��������� front �������� NULL 
		p = front;
		front = front->NextNode();
	}
	else {
		// �� ��������� ���������� ���� ����� prevPtr, ��������� ����� 
		p = prevPtr->DeleteAfter();
	}

	// ���� ����� ������, ����� ������ ������ � prevPtr, // � position �����w����� �� 1 
	if (p == rear) {
		rear = prevPtr;
		position--;
	}

	// ���������� currPtr �� ��������� ��������� ����. ���� � - ��������� ���� � ������, currPtr ���������� ������ NULL 
	currPtr = p->NextNode();
	// ���������� ���� � ��������� �������� size
	FreeNode(p);
	size--;
};


template <class T>
T& LinkedList<T>::Data(void) {
	// ������, ���� ������ ������ ��� ����������� ���������
	if (size == 0 || currPtr == NULL) {
		cerr << "Data: �������� ������!" << std::endl;
		exit(1);
	}
	return currPtr->data;
};


template <class T>
void LinkedList<T>::ClearList() {
	Node<T>* currPosition, * nextPosition;
	currPosition = front;
	while (currPosition != NULL) {
		// �������� ����� ���������� ���� � ������� �������
		nextPosition = currPosition->NextNode();
		FreeNode(currPosition);
		currPosition = nextPosition; // ������� � ���������� ���� 
	}
	front = rear = NULL;
	prevPtr = currPtr = NULL;
	size = 0;
	position = -1;
};