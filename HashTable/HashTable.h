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
	// число болков; предаставл€ют размер таблицы
	int numBuckets;

	//хеш-таблица есть массив св€занных списков
	Array<LinkedList<T>> buckets;

	// хеш функци€ и адрес элемента данных
	// к которому обращались последний раз
	unsigned long(*hf)(T key);
	T* current;

public:
	// конструктор с параметрами, включающими
	// размер табоицы и хеш-функцию
	HashTable(int nbucket, unsigned long hashf(T key);
	// методы обработки списков
	virtual void Insert(const T& key);
	virtual int Find(T& key);
	virtual void Delete(const T& key);
	virtual void ClearList(void);
	void Update(const T& key);

	//дружественный итератор, имеющий доступ к
	// данным-членам

	friend class HashTableIterator<T>
};

