#include <iostream>
#include "string"
#include "hash_table.h"
#include "IDictionary.h"
#include "DynamicArray.h"

template<typename T>
class ThinArray {
private:
    IDictionary<int, T> *dict;
    int size;
public:
    ThinArray(DynamicArray<T> arr);

    T &get(int);

    T set(int, T);

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
T &ThinArray<T>::get(int key) {
    if (dict->find(key)) {
        return dict->get(key);
    } else {
        return 0;
    }
}

template<typename T>
T ThinArray<T>::set(int key, T value) {
    if (value==0){
        if (dict->find(key)){
            dict->remove(key);
        }
    } else{
        dict->add(key,value);
    }
}


