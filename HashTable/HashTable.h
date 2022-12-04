#pragma once
#include "Iterator.h"
#include "List.h"
#include "Array.h"
#include "LinkedList.h"
template<class T>
class HashTableIterator;

template <class T>
class HashTable : public List<T>
{
protected:
	// ����� ������; ������������� ������ �������
	int numBuckets;

	//���-������� ���� ������ ��������� �������
	Array<LinkedList<T>> buckets;

	// ��� ������� � ����� �������� ������
	// � �������� ���������� ��������� ���
	unsigned long(*hf)(T key);
	T* current;

public:
	// ����������� � �����������, �����������
	// ������ ������� � ���-�������
	HashTable(int nbucket, unsigned long hashf(T key);
	// ������ ��������� �������
	virtual void Insert(const T& key);
	virtual int Find(T& key);
	virtual void Delete(const T& key);
	virtual void ClearList(void);
	void Update(const T& key);

	//������������� ��������, ������� ������ �
	// ������-������

	friend class HashTableIterator<T>
};

