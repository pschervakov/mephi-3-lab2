#ifndef LAB2_HASHTABLE
#define LAB2_HASHTABLE


#include <iostream>
#include "DynamicArray.h"
#include <string>
#include "IDictionary.h"

using namespace std;
using std::cout, std::cin, std::string;


template<class K, class V>
struct Pair {
    K key;
    V value;
};

template<class K, class V>
class HashTable : public IDictionary<K, V> {
private:
    struct HashTablePair {
        K key;
        V value;
        bool is_present;

        HashTablePair() : is_present(false) {};

        HashTablePair(K key, V value)
                : key(key), value(value), is_present(true) {};


    };

    int capacity;
    int size;
    const double coef = 0.7;
    DynamicArray<HashTablePair> data;

    int getHasH(K);

    void resize(int);
//    friend std::ostream& operator<<(std::ostream&, const IDictionary<K,V>&);

public:
    class HashTableIterator {
    private:
        int idx;
        int table_size;
        HashTable<K, V> *table;

    public:
        explicit HashTableIterator(HashTable<K, V> *table) {
            this->table = table;
            table_size = table->capacity;
            idx = 0;
        }

        bool hasNext() {
            for (int i = idx; i < table_size; ++i) {
                if (table->data[i].is_present) return true;
            }
            return false;

        }

        Pair<K, V> next() {
            while (table->data[idx].is_present != true) {
                if (idx >= table_size - 1) throw std::runtime_error("end of collection");
                ++idx;
            }
            Pair<K, V> pair = Pair<K, V>{.key=table->data[idx].key, .value=table->data[idx].value};
            ++idx;
            return pair;
        }


    };

    explicit HashTable(int);

    void add(K, V) override;

    void remove(K) override;

    int getCapacity() override;

    int getCount() override;

    V &get(K) override;

    bool find(K) override;

    string toString() override;

    HashTableIterator getIterator();

    bool operator==(IDictionary<K, V>  &) override;
    void print(ostream &strm) override;

};

template<class K, class V>
HashTable<K, V>::HashTable(int cap)
        : data(DynamicArray<HashTablePair>(cap)), capacity(cap), size(0) {}

template<class K, class V>
int HashTable<K, V>::getHasH(K key) {
    return sizeof(key) % capacity;
}

template<class K, class V>
void HashTable<K, V>::add(K key, V value) {
    if (size > int(capacity * coef)) {
        resize(size * 2);
    }

    int n = getHasH(key);
    int i = 0;
    while (i < capacity and data[n].is_present) {
        if (data[n].key == key) {
            break;
        }
        n = (n + 1) % capacity;
        ++i;
    }
    data[n] = HashTablePair(key, value);
    ++size;
}

template<class K, class V>
void HashTable<K, V>::remove(K key) {
    int n = getHasH(key);
    int i = 0;
    while (i < capacity) {
        if (data[n].key == key and data[n].is_present) {
            data[n].is_present = false;
            --size;
            return ;
        }
        n = (n + 1) % capacity;
        ++i;
    }
    throw std::runtime_error("element not found");
}


template<class K, class V>
V &HashTable<K, V>::get(K key) {
    int n = getHasH(key);
    int i = 0;
    while (i < capacity) {
        if (data[n].key == key and data[n].is_present) {
            return data[n].value;
        }
        n = (n + 1) % capacity;
        ++i;

    }
    throw std::runtime_error("element not found");
}

template<class K, class V>
bool HashTable<K, V>::find(K key) {
    try {
        this->get(key);
        return true;

    }
    catch (std::runtime_error &) {
        return false;
    }
}


template<class K, class V>
string HashTable<K, V>::toString() {
    string s;
    for (int i = 0; i < capacity; ++i) {
        if (data[i].is_present) {
//            s += std::to_string(data[i].key) + ":" + std::to_string(data[i].value) + " ";
            s += data[i].key + ":" + std::to_string(data[i].value) + " ";
        }
    }
    return s;
}

template<class K, class V>
void HashTable<K, V>::resize(int new_size) {
    data.resize(new_size);
    size = new_size;
}

template<class K, class V>
int HashTable<K, V>::getCapacity() {
    return capacity;
}

template<class K, class V>
int HashTable<K, V>::getCount() {
    return size;
}

template<class K, class V>
typename HashTable<K, V>::HashTableIterator HashTable<K, V>::getIterator() {
    return HashTable::HashTableIterator(this);
}

template<class K, class V>
bool HashTable<K, V>::operator==(IDictionary<K, V> &table) {
    if (this->size != table.getCount() or this->capacity != table.getCapacity()) return false;
    HashTable<K,V>::HashTableIterator iter = this->getIterator();
    for (; iter.hasNext();) {
        Pair<K, V> pair = iter.next();
        K key = pair.key;
        V value = pair.value;
        if (not table.find(key) or table.get(key) != this->get(key)) {
            return false;
        }
    }
    return true;
}

template<class K, class V>
void HashTable<K, V>::print(ostream &strm) {
    for (int i = 0; i < this->capacity; ++i){
        if (this->data[i].is_present) {
            strm << this->data[i].key <<":"<< this->data[i].value<<" ";
        }
    }
}


template<class K, class V>
std::ostream &operator<<(ostream &strm, IDictionary<K, V> &table ) {
    table.print(strm);
    return strm;
}



#endif //LAB2_HASHTABLE






