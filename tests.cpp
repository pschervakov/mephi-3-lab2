#include "gtest/gtest.h"
#include "string"
#include "HashTable.h"
#include "IDictionary.h"
#include "ThinArray.h"
#include "DynamicArray.h"
#include "AlphabeticalIndex.h"

using namespace std;
//using std::string;

bool isEqual(DynamicArray<int> arr, ThinArray<int> thin_arr) {
    if (arr.get_size() != thin_arr.getSize()) {
        return false;
    } else {
        for (int i = 0; i < arr.get_size(); ++i) {
            if (arr[i] != thin_arr.get(i)) {
                return false;
            }
        }
    }
    return true;
}

class TestTable : public ::testing::Test {
public:
    void SetUp() {
        table = new HashTable<int, int>(cap);
        int *arr = new int[size];
        createArray(arr);
        for (int i = 0; i < size; ++i) {
            table->add(arr[i], rand() % 100);
        }
        std::cout << table->toString();

    }


    void createArray(int *a) {
        srand(time(0));
        for (int i = 0; i < size; ++i) {
            a[i] = i;
        }
        for (int i = 0; i < size; ++i) {
            int ran = rand() % size;
            int temp = a[i];
            a[i] = a[ran];
            a[ran] = temp;

        }

    }


    int cap = 100;
    int size = 50;
    HashTable<int, int> *table;
};

class TestAlpha : public ::testing::Test {
public:
    void SetUp() {
        int size = 3;
        string s = "abc de fgh ijklm nop qrst uvwx yz abcd efgh ijk lmno pqr stuvwxyz";
        int a[20] = {1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6};
        string b[20];
        for (int p = 0, i = 0, q = 0; p != std::string::npos; p = q, ++i)
            b[i] = s.substr(p + (p != 0), (q = s.find(' ', p + 1)) - p - (p != 0));
        dict = new HashTable<string, int>(100);
        for (int i = 0; i < 14; ++i) {
            dict->add(b[i], a[i]);
        }
        dict2 = alpha(s, 3, "word");
    }

    IDictionary<string, int> *dict2;
    IDictionary<string, int> *dict;
};


class TestThinArray : public ::testing::Test {
public:
    void SetUp() {
        arr = new DynamicArray<int>(100);
        srand(time(0));
        for (int i = 0; i < arr->get_size(); ++i) {
            int idx = rand() % arr->get_size();
            (*arr)[idx] = rand() % 1000;
        }
        thin_arr = new ThinArray<int>(*arr);
    }


    DynamicArray<int> *arr;
    ThinArray<int> *thin_arr;
};

TEST_F(TestTable, add) {
    table->add(101, 5);
    EXPECT_EQ(table->get(101), 5);
}

TEST_F(TestTable, add_exists) {
    table->add(101, 5);
    table->add(101, 6);
    EXPECT_EQ(table->get(101), 6);
}

TEST_F(TestTable, remove) {
    table->add(102, 5);
    table->remove(102);
    EXPECT_THROW(table->get(102), runtime_error);
}

TEST_F(TestTable, size) {
    table->add(103, 8);
    EXPECT_EQ(table->getCount(), 51);
}


TEST_F(TestThinArray, convert) {
    EXPECT_TRUE(isEqual(*arr, *thin_arr));
}

TEST_F(TestThinArray, get) {
    EXPECT_EQ(thin_arr->get(3), arr->get(3));
}


TEST_F(TestAlpha, word) {
    EXPECT_TRUE((*dict2) == (*dict));
}