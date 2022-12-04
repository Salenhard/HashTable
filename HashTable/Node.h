#pragma once
template <typename T>
class Node							// ��������� ����� ���� ������
{
private:
	Node* next;						// ��������� �� ����. ����

public:
	T data;							// ������ ���� ������
	// �����������
	Node(const T& item, Node<T>* ptrnext = NULL);

	// ������ ����������� ������
	void InsertAfter(Node<T>* p);
	Node<T>* DeleteAfter();
	
	// ��������� ������ ���������� ����
	Node<T>* NextNode() const;
};

template <class T>
Node<T>::Node(const T& item, Node<T>* ptrnext) : data{ item }, next{ ptrenext } {};

// ���������� �������� ���� next
template <class T>
Node<T>* Node<T>::NextNode() const {
	return next;
}

// �������� ���� p ����� �������� ���� 
template <class T>
void Node<T>::InsertAfter(Node<T>* p) {
	// p ��������� �� ��������� �� ������� ����
	// � ������� ���� - �� p.
	p->next = next;
	next = p;
}

// ������� ����, ��������� �� �������, � ���������� ��� �����
template <class T>
Node<T>* Node<T>::DeleteAfter()
{
	// ��������� ����� ���������� ����
	Node<T>* tempPtr = next;

	// ���� ��� ���������� ����, ���������� NULL
	if (next == NULL)
		return NULL;

	// ������� ���� ��������� �� ����, ��������� �� tempPtr.
	next = tempPtr->next;
	
	// ���������� ��������� �� ����������� ����
	return tempPtr;
}