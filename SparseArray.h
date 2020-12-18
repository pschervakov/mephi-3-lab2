#include <iostream>
#include "string"
#include "HashTable.h"
#include "IDictionary.h"
#include "DynamicArray.h"


class SparseArrayException : public std::exception {
private:
    std::string error;

public:
    SparseArrayException(std::string error)
            : error(error) {}

    string getError() { return error; }
};


template<typename T>
class SparseArray {
private:
    IDictionary<int, T> *dict;
    int size;
public:
    SparseArray(DynamicArray<T> arr);

    T get(int);

    T &getRef(int);

    void set(int, T);

    void append(T);

    int getSize();


};

template<typename T>
SparseArray<T>::SparseArray(DynamicArray<T> arr) {
    size = arr.get_size();
    dict = new HashTable<T, int>(size * 2);
    for (int i = 0; i < size; ++i) {
        if (arr[i] != 0) {
            dict->add(i, arr[i]);
        }
    }

}

template<typename T>
T SparseArray<T>::get(int key) {
    if (key < 0 or key > size) throw SparseArrayException("index out of range");
    if (dict->find(key)) {
        return dict->at(key);
    } else {
        return 0;
    }
}
template<typename T>
T &SparseArray<T>::getRef(int key) {
    if (key < 0 or key > size) throw SparseArrayException("index out of range");
    if (dict->find(key)) {
        return dict->at(key);
    } else {
        throw SparseArrayException("zero elements can't be returned as references");
    }
}


template<typename T>
void SparseArray<T>::set(int key, T value) {
    if (value!=0){
        dict->add(key,value);
    } else if (dict->find(key)) dict->remove(key);
}



template<typename T>
void SparseArray<T>::append(T value) {
    if (value != 0) {
        dict->add(size, value);
    }
    size += 1;
}

template<typename T>
int SparseArray<T>::getSize() {
    return this->size;
}



template<class T>
std::ostream &operator<<(ostream &strm, SparseArray<T> &arr) {
    for (int i = 0; i < arr.getSize(); ++i) {
        strm << arr.get(i) << " ";
    }
    return strm;
}

