
#include "iostream"
#include "SparseArray.h"
#include "HashTable.h"
#include "string.h"
#include "DynamicArray.h"
#include "AlphabeticalIndex.h"
//
using namespace std;
using std::cout, std::cin, std::endl;

//void arrayMenu() {
//    int size;
//    cout << "enter array size" << endl;
//    cin >> size;
//    DynamicArray<int> arr = DynamicArray<int>(size);
//    cout << "enter elements" << endl;
//    for (int i = 0; i < size; ++i) {
//        cin >> arr[i];
//    }
//    SparseArray<int> a(arr);
//    cout<<a;
//    cout<<endl;
//
//}





int main(int argc, char * argv[]) {

    string s=argv[2];
    int size=std::atoi(argv[3]);
    string type=argv[4];
    cout << *alpha(s, size, type);

}