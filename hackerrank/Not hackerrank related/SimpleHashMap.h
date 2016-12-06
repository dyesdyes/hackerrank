
#define NULL 0


struct SimpleHashEntry {
public:
	SimpleHashEntry(int k, int v) : key(k), value(v){
	}

	int getKey(){return key;}
	int getValue(){return value;}

private:
	int key;
	int value;
};


/* 
	Super simple implementation of a hash table
	The hash function is supra simple and works only on int, there will be many collisions
	Fixed size
	Collisions are handled via open adressing
*/
class SimpleHashMap {

	SimpleHashMap(){
		values = new SimpleHashEntry*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; ++i){
			values[i] = NULL;
		}
	}

	~SimpleHashMap(){
		// Note that the respnsability to delete the object is not ours, we just remove the entry from the table
		for (int i = 0; i < TABLE_SIZE; ++i){
			values[i] = NULL;
		}
		delete[] values;
	}

	int at(int key){
		int actualIndex = findIndex(key);
		return actualIndex != -1 ? values[actualIndex]->getValue() : actualIndex;
	}

	void insert(SimpleHashEntry* entry){
		if (!entry)
			return;

		int hash = hashFunction(entry->getKey());
		int counter = 0;
		while(values[hash] != NULL  && counter++ < TABLE_SIZE){
			hash = (hash + 1) % TABLE_SIZE;
		}
		if (!values[hash]){
			values[hash] = entry;
		}
	}

	// Note that the respnsability to delete the object is not ours, we just remove the entry from the table
	void erase(int key){
		int actualIndex = findIndex(key);
		if (actualIndex != -1){
			values[actualIndex] = NULL;
		}
	}

private:

	int findIndex(int key){
		int hash = hashFunction(key);
		int counter = 0;
		while(values[hash] != NULL && values[hash]->getKey != key && counter++ < TABLE_SIZE){
			hash = (hash + 1) % TABLE_SIZE;
		}
		if (counter >= TABLE_SIZE) // then table is full...
			return -1;
		return values[hash] ? values[hash]->getKey() : -1;
	}

	int hashFunction(int key){
		return key % TABLE_SIZE;
	}

	SimpleHashEntry** values;

	const int TABLE_SIZE = 256;
};