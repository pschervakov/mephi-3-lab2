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

        Pair<K, V> next() {
            while (table->data[idx].is_present != true) {
                ++idx;
            }
            Pair<K, V> pair = Pair<K, V>{.key=table->data[idx].key, .value=table->data[idx].value};
            cout << table->data[idx].key << table->data[idx].value << "\n";
            ++idx;
            return pair;
        }


    };

    explicit HashTable(int);

    void add(K, V);

    void remove(K);

    int getCapacity();

    int getCount();

    V &get(K);

    bool find(K);

    string toString();

    HashTableIterator getIterator();


};

template<class K, class V>
HashTable<K, V>::HashTable(int cap)
        : data(DynamicArray<HashTablePair>(cap)), capacity(cap), size(0) {}

template<class K, class V>
int HashTable<K, V>::getHasH(K key) {
    return sizeof(key);
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
            throw runtime_error("element already exists");
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
            break;
        }
        n = (n + 1) % capacity;
        ++i;
    }
}


template<class K, class V>
V &HashTable<K, V>::get(K key) {
    int n = getHasH(key);
    int i = 0;
    bool flag = false;
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











