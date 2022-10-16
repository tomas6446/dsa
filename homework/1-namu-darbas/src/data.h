
#ifndef ADT_H
#define ADT_H

#include "iostream"
#include <algorithm>
#include <utility>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

class Big {
private:
    std::string value;
    std::vector<int> nat;
    std::vector<int> real;
    bool isNegative = false;

    std::vector<int> RemoveZeros(std::vector<int>);

    std::vector<int> storeInVector(std::string);

    std::vector<int> Addition(std::vector<int>, std::vector<int>);

    std::vector<int> Subtraction(std::vector<int>, std::vector<int>);

    std::vector<int> Multiply(std::vector<int>, std::vector<int>);

    std::vector<int> Division(std::vector<int>, std::vector<int>, long long &);

    std::vector<int> Remainder(std::vector<int>, std::vector<int>);

    std::vector<int> combine(std::vector<int> &a, std::vector<int> &b);

    std::string convertToValue(Big &);

    std::string toString(std::vector<int> a);

    bool isSmaller(std::vector<int>, std::vector<int>);

    bool isEqual(std::vector<int>, std::vector<int>);

    void pushZeros(std::vector<int> &, std::vector<int> &);

    std::vector<int> pushZerosLeft(std::vector<int> a, std::vector<int> b);

public:
    Big();

    explicit Big(const std::string &);

    Big(const Big &);

    ~Big();

    void clear();

    std::string getValue();

    void setValue(std::string val);

    void setNegative();

    bool operator<(Big);

    bool operator<=(Big);

    bool operator>(Big);

    bool operator>=(Big);

    bool operator==(Big);

    bool operator!=(Big);

    Big &operator=(const Big &b);

    Big &operator=(std::string);

    Big &operator=(std::vector<int> val);

    Big operator--();

    Big operator++();

    Big operator++(int);

    Big operator*(Big);

    Big operator-(Big);

    Big operator+(Big);

    Big operator/(Big);

    Big operator%(Big);

    Big operator+=(const Big &);

    Big operator-=(const Big &);

    Big operator/=(const Big &);

    Big operator%=(const Big &);

    Big operator*=(const Big &);

    char operator[](int);

    friend std::ostream &operator<<(std::ostream &, Big &);
};

#endif
