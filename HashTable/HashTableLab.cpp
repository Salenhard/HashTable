#include <iostream>
#include <fstream>
#include "HashTable.h"
#include "HashTableIterator.h"
using namespace std;
struct NameRecord
{
	string name;
	int count;
	NameRecord() {
		name = "";
		count = 0;
	}
	int operator ==(const NameRecord& rhs) {
		return name == rhs.name;
	}
};


unsigned long hash1(NameRecord elem)
{
	unsigned long hashval = 0;
	for (int i = 0; i < elem.name.length(); i++)
		hashval = (hashval << 3) + elem.name[i];
	return hashval;
};



int main()
 {
	ifstream fin;
	NameRecord rec;
	string token;
	HashTable<NameRecord> HF(101, hash1);
	setlocale(0, "ru");
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

	for (hiter.Reset(); !hiter.EndOfList(); hiter.Next()) {
		rec = hiter.Data();
		cout << rec.name << ": " << rec.count << endl;
	}
}


