#include "gtest/gtest.h"
#include "string"
#include "hash_table.h"
#include "IDictionary.h"

using namespace std;
class TestTable : public ::testing::Test {
public:
    void SetUp() {
        table=new HashTable<int,int>(cap);
        int *arr = new int[size];
        createArray(arr);
        for (int i = 0; i < size; ++i) {
            table->add(arr[i], rand() % 100);
        }
        std::cout<<table->toString();
    }


    void createArray(int *a) {
        srand(time(0));
        for (int i = 0; i < size; ++i) {
            a[i] = i;
        }
        for (int i=0;i<size;++i){
            int ran=rand() % size;
            int temp=a[i];
            a[i]=a[ran];
            a[ran]=temp;

        }

    }


    int cap = 100;
    int size = 50;
    HashTable<int, int> *table;
};

TEST_F(TestTable, set) {
    table->add(101, 5);
    EXPECT_EQ(table->get(101), 5);
}

TEST_F(TestTable, remove) {
    table->add(102, 5);
    table->remove(102);
    EXPECT_THROW(table->get(102), runtime_error);
}

TEST_F(TestTable, size) {
    table->add(103,8);
    EXPECT_EQ(table->getCount(),51);
}
