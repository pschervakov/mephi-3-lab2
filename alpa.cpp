//
// Created by philip on 11/21/20.
//
#include <iostream>
#include "string"
#include "hash_table.h"
#include "IDictionary.h"
#include "DynamicArray.h"

using namespace std;

int strSize(int i, int size) {
    if (i == 1) return size / 2;
    else if (i % 10 == 0) return 3 * size / 4;
    else return size;
}

int charsToStr(int bw, int size, DynamicArray<string> a) {
    int ii = 0;
    int jj = bw;
    while (ii - 1 <= size) {
        ii += a[jj].length() + 1;
        cout << ii << " " << size << "\n";
        if (ii - 1 <= size) {
            ++jj;
        }
    }
    cout << "\n";
    return jj - bw;
}

IDictionary<string, int> *alpha(string s, int SIZE, string size_type) {
    IDictionary<string, int> *dict = new HashTable<string, int>(100);
    DynamicArray<string> a(100);
    for (int p = 0, i = 0, q = 0; p != std::string::npos; p = q, ++i)
        a.set(i, s.substr(p + (p != 0), (q = s.find(' ', p + 1)) - p - (p != 0)));

    int size;
    int i = 1;
    int bw = 0;
    bool flag = true;
    while (flag) {
        if (size_type == "word") {
            size = strSize(i, SIZE);
        } else if (size_type=="letter") {
            size = strSize(i, charsToStr(bw, SIZE, a));
        }
        for (int j = bw; j < size + bw; ++j) {
            if (j >= a.get_count()) {
                flag = false;
                break;
            }
            dict->add(a[j], i);
        }
        bw += size;
        ++i;
    }
    return dict;
}

int main() {
    //    std::getline(std::cin, s);
    int size = 5;
    string s = "sdf f qwe trt rty ty c jk";
    cout << alpha(s, size, "letter")->toString();


}