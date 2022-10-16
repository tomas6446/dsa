#include <gtest/gtest.h>

#include <vector>
#include "../src/Array.h"

bool eval(std::vector<int> a, ADT::Tree<int> b) {
    if (a.size() != b.getSize()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void print(std::vector<int> a, ADT::Tree<int> b) {
    for (int x: a) {
        std::cout << x << " ";
    }
    std::cout << std::endl<< std::endl;
    b.print();
}

TEST(ArrayTest, addLast) {
    srand(time(nullptr));

    int i = 0;
    int N = 100;
    std::vector<int> testVector;
    ADT::Tree<int> testArray;

    while (i < N) {
        int r = rand() % 10;
        testVector.push_back(r);
        testArray.addLast(r);
        EXPECT_EQ(true, eval(testVector, testArray));
        i++;
    }
}

TEST(ArrayTest, addFirst) {
    srand(time(nullptr));

    int i = 0;
    int N = 100;
    std::vector<int> testVector;
    ADT::Tree<int> testArray;

    while (i < N) {
        int r = rand() % 10;
        testVector.insert(testVector.begin(), r);
        testArray.addFirst(r);
        EXPECT_EQ(true, eval(testVector, testArray));
        i++;
    }
}


TEST(ArrayTest, addPos) {
    srand(time(nullptr));

    int i = 0;
    int N = 100;
    std::vector<int> testVector;
    ADT::Tree<int> testArray;

    while (i < N) {
        int r = rand() % 10;
        testVector.insert(testVector.begin() + i, r);
        testArray.add(i, r);
        EXPECT_EQ(true, eval(testVector, testArray));
        i++;
    }
}


TEST(ArrayTest, removePos) {
    srand(time(nullptr));

    std::vector<int> testVector;
    ADT::Tree<int> testArray;

    int i = 0;
    int N = 100;
    while (i < N) {
        testVector.insert(testVector.begin() + i, i);
        testArray.add(i, i);
        i++;
    }

    int j = 0;
    while (j < N) {
        testArray.remove(0);
        testVector.erase(testVector.begin());

        EXPECT_EQ(true, eval(testVector, testArray));
        j++;
    }
}

TEST(ArrayTest, removeFirst) {
    srand(time(nullptr));

    std::vector<int> testVector;
    ADT::Tree<int> testArray;

    int i = 0;
    int N = 100;
    while (i < N) {
        testVector.insert(testVector.begin() + i, i);
        testArray.add(i, i);
        i++;
    }

    int j = 0;
    while (j < N) {
        testArray.removeFirst();
        testVector.erase(testVector.begin());

        EXPECT_EQ(true, eval(testVector, testArray));
        j++;
    }
}

TEST(ArrayTest, removeLast) {
    srand(time(nullptr));

    std::vector<int> testVector;
    ADT::Tree<int> testArray;

    int i = 0;
    int N = 100;
    while (i < N) {
        testVector.insert(testVector.begin() + i, i);
        testArray.add(i, i);
        i++;
    }

    int j = 0;
    while (j < N) {
        testArray.removeLast();
        testVector.pop_back();

        EXPECT_EQ(true, eval(testVector, testArray));
        j++;
    }
}

TEST(ArrayTest, get) {
    srand(time(nullptr));

    std::vector<int> testVector;
    ADT::Tree<int> testArray;

    int i = 0;
    int N = 100;
    while (i < N) {
        testVector.insert(testVector.begin() + i, i);
        testArray.add(i, i);
        i++;
    }

    int j = 0;
    while (j < N) {
        EXPECT_EQ(true, testVector[j] == testArray.get(j));
        j++;
    }
}

TEST(ArrayTest, size) {
    srand(time(nullptr));

    std::vector<int> testVector;
    ADT::Tree<int> testArray;

    int i = 0;
    int N = 100;
    while (i < N) {
        testVector.insert(testVector.begin() + i, i);
        testArray.add(i, i);
        i++;
    }
    EXPECT_EQ(true, testVector.size() == testArray.getSize());
}

