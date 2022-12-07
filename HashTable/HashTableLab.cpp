#include <iostream>
#include <fstream>
#include "HashTable.h"
#include "HashTableIterator.h"
using namespace std;
struct NameRecord
{
	string name;
	int count;
};

unsigned long hash(NameRecord elem)
{
	unsigned long hashval = 0;
	for (int i = 0; i < elem.name.length(); i++)
		hashval = (hashval << 3) + elem.name[i];
	return hashval;
};

unsigned long hash1(NameRecord elem) {
	return 1;
}

int main()
{
	ifstream fin;
	NameRecord rec;
	string token;
	HashTable<NameRecord> HF(101, hash1);
	fin.open("strings.dat", ios::in | ios::_Nocreate);
	if (!fin) {
		cerr << "Невозможно открыть \"strings.dat\"!" << endl;
		exit(1);
	}

	while (fin>>rec.name)
	{
		if (HF.Find(rec)) {
			rec.count += 1;
			HF.Update(rec);
		}
		else
		{
			rec.count = 1;
			HF.Insert(rec);
		}
	}
	HashTableIterator<NameRecord> hiter(HF);

	for(hiter.Reset(); !hiter.EndOfList(); hiter.Next()){
		rec = hiter.Data();
		cout << rec.name << ": " << rec.count << endl;
	}
}


