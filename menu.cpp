
#include "iostream"
#include "ThinArray.h"
#include "HashTable.h"
#include "string.h"
#include "DynamicArray.h"
#include "AlphabeticalIndex.h"
//
using std::cout, std::cin, std::endl, std::string;

void arrayMenu() {
    int size;
    cout << "enter array size" << endl;
    cin >> size;
    DynamicArray<int> arr = DynamicArray<int>(size);
    cout << "enter elements" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
    cout << ThinArray<int>(arr).toString();
    cout<<endl;

}

void alphaIndexMenu() {
    string s;
    int size=4;
    cout << "enter str size"<<endl;
    cin >> size;
    cout << "enter your string"<<endl;
    std::getline(std::cin, s);
    cout << alpha(s, size, "word")->toString();
    cout<<endl;
};

void chooseOption() {
    cout << "1. Array menu ";
    cout << "2. Alphabetical index ";
    cout<< "3. Exit";
    cout << endl;
}


int main() {
//    int choice;
//    while (true) {
//        chooseOption();
//        cin >> choice;
//        if (choice == 1) {
//            arrayMenu();
//        } else if (choice==2){
//            alphaIndexMenu();
//        } else break;
//    }
    int choice;
    cin>>choice;
    string s;
    std::getline(std::cin, s);
    cout<<s;

}