#include <gtest/gtest.h>
#include <vector>
#include "../src/data.h"
#include "iomanip"
#include <chrono>

using namespace std;

vector<pair<std::string, std::string>> testValues{
        {"40",                            "2"},
        {"0.000000313123213",             "120"},
        {"0.3123213123123",               "4234234234.313123213"},
        {"0.000304607",                   "6"},
        {"4234234234.313123213",          "0.3123213123123"},
        {"0.017453",                      "1"},
        {"1.313123213",                   "0.3123123123123123123123123123213123123"},
        {"1",                             "1001"},
        {"55.53",                         "55.555"},
        {"0",                             "1"},
        {"0.017453",                      "0.017453"},
        {"0.034906",                      "0.017453"},
        {"-123.123",                      "222.222"},
        {"123.123",                       "-222.222"},
        {"2",                             "5"},
        {"0",                             "1"},
        {"534323132131312.3123213123123", "4234234234.313123213"},
};

TEST(DataTests, isSmaller) {
    int counter = 1;
    for (auto test: testValues) {
        std::cout << "Test number " << counter << ": " << std::endl;
        Big a(test.first);
        Big b(test.second);
        std::cout << "Expected " << (stod(test.first) < stod(test.second)) << " got " << (a < b) << std::endl;
        EXPECT_EQ(true, a < b);
        counter++;
    }
    std::cout << std::endl;
}

TEST(DataTests, AdditionTest) {
    int counter = 1;
    for (auto test: testValues) {
        std::cout << "Test number " << counter << ": " << std::endl;
        Big res(to_string(stod(test.first) + stod(test.second)));
        Big a(test.first);
        Big b(test.second);
        std::cout << "Expected " << stod(test.first) + stod(test.second) << " got " << (a + b).getValue() << std::endl;
        EXPECT_EQ(true, res == a + b);
        counter++;
    }
    std::cout << std::endl;
}

TEST(DataTests, SubtractionTest) {
    int counter = 1;
    for (auto test: testValues) {
        std::cout << "Test number " << counter << ": " << std::endl;
        Big res(to_string(stod(test.first) - stod(test.second)));
        Big a(test.first);
        Big b(test.second);
        std::cout << "Expected " << stod(test.first) - stod(test.second) << " got " << (a - b).getValue() << std::endl;
        EXPECT_EQ(true, res == a - b);
        counter++;
    }
    std::cout << std::endl;
}

TEST(DataTests, MultiplicationTest) {
    int counter = 1;
    for (auto test: testValues) {
        std::cout << "Test number " << counter << ": " << std::endl;
        Big res(to_string(stod(test.first) * stod(test.second)));
        Big a(test.first);
        Big b(test.second);
        std::cout << "Expected " << stod(test.first) * stod(test.second) << " got " << (a * b).getValue() << std::endl;
        EXPECT_EQ(true, res == a * b);
        counter++;
    }
    std::cout << std::endl;
}

TEST(DataTests, DivisionTest) {
    int counter = 1;
    for (auto test: testValues) {
        std::cout << "Test number " << counter << ": " << std::endl;
        Big res(to_string(stod(test.first) / stod(test.second)));
        Big a(test.first);
        Big b(test.second);
        std::cout << "Expected " << stod(test.first) << " / " << stod(test.second) << " = " << stod(test.first) / stod(test.second)
                  << " got " << (a / b).getValue() << std::endl;
        counter++;
    }
    EXPECT_EQ(true, false);
    std::cout << std::endl;
}

#include "../src/test.cpp"

TEST(DataTests, FunctionTests) {
    int N = 40, i = 1;

    auto opStart = std::chrono::high_resolution_clock::now();
    auto opFinish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedSeconds;

    opStart = std::chrono::high_resolution_clock::now();
    while (i < N) {
        string output;

        cout << setw(5) << right << "[" << i << "]" << setw(50) << right
             << (output = toStr(myFactorial(i))) << setw(75) << right;
        cout << (output = toStr(myPrime(convert(to_string(i))))) << setw(100) << right;
        cout << (output = toStr(myPow(i, i))) << setw(100) << right;
        cout << (output = toStr(myLog(i))) << setw(75) << right;
        //cout << (output = toStr(myPi(i))) << setw(75) << right;
        //cout << (output = toStr(mySqrt(i))) << setw(75) << right;
        //cout << (output = toStr(mySin(i))) << setw(100) << right;
        myType *data = new myType[N];
        for (int x = 0; x < N; ++x) {
            data[x] = convert(to_string(x + 1));
        }
        cout << myFind(data, N, Big(to_string(i))) << setw(75) << right;
        cout << (output = toStr(myAvg(data, i))) << setw(75) << right << endl;
        delete[] data;

        i++;
    }
    opFinish = std::chrono::high_resolution_clock::now();
    elapsedSeconds = opFinish - opStart;
    std::cout << endl << "elapsed seconds: " << elapsedSeconds.count() << std::endl;

    EXPECT_EQ(true, false);
}



