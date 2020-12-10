#include <iostream>
#include "string"
#include "HashTable.h"
#include "IDictionary.h"
#include "DynamicArray.h"

template<typename T>
class ThinArray {
private:
    IDictionary<int, T> *dict;
    int size;
public:
    ThinArray(DynamicArray<T> arr);

    T get(int);

    void set(int, T);

    void append(T);

    int getSize();

    string toString();

};

template<typename T>
ThinArray<T>::ThinArray(DynamicArray<T> arr) {
    size = arr.get_size();
    dict = new HashTable<T, int>(size * 2);
    for (int i = 0; i < size; ++i) {
        if (arr[i] != 0) {
            dict->add(i, arr[i]);
        }
    }

}

template<typename T>
T ThinArray<T>::get(int key) {
    if (dict->find(key)) {
        return dict->get(key);
    } else {
        return 0;
    }
}

template<typename T>
void ThinArray<T>::set(int key, T value) {
    if (dict->find(key)) {
        dict->remove(key);
        if (value != 0) {
            dict->add(key, value);
        }
    } else {
        dict->add(key, value);
    }
}


template<typename T>
string ThinArray<T>::toString() {
    string s;
    for (int i = 0; i < size; ++i) {
        s += std::to_string(this->get(i)) + ' ';
    }
    return s;
}

template<typename T>
void ThinArray<T>::append(T value) {
    if (value != 0) {
        dict->add(size, value);
    }
    size += 1;
}

template<typename T>
int ThinArray<T>::getSize() {
    return this->size;
}


