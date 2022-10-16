#include <utility>

#include "data.h"

Big::Big(const Big &b) {
    this->value = b.value;
    this->nat = b.nat;
    this->real = b.real;
    this->isNegative = b.isNegative;
}

Big::Big(const std::string &val) {
    setValue(val);
}

Big::Big() = default;

Big::~Big() = default;


Big Big::operator+(Big b) {
    Big result;
    pushZeros(real, b.real);

    if (!isNegative && b.isNegative) {
        isNegative = false;
        b.isNegative = false;

        return *this - b;
    } else if (isNegative && !b.isNegative) {
        isNegative = false;
        b.isNegative = false;

        return b - *this;
    }

    long long commaPos = b.real.size();

    nat = combine(nat, real);
    b.nat = combine(b.nat, b.real);
    result.nat = Addition(nat, b.nat);

    for (long long s = commaPos - 1; s >= 0; s--) {
        result.real.push_back(result.nat.back());
        result.nat.pop_back();
    }
    std::reverse(result.real.begin(), result.real.end());

    result.nat = RemoveZeros(result.nat);
    return result;
}

Big Big::operator-(Big b) {
    Big result;
    pushZeros(real, b.real);

    if (!isNegative && b.isNegative) {
        b.isNegative = false;
        return *this + b;
    } else if (isNegative && !b.isNegative) {
        isNegative = false;
        result = *this + b;
        result.setNegative();
        return result;
    }

    long long commaPos = b.real.size();

    nat = combine(nat, real);
    b.nat = combine(b.nat, b.real);

    if (*this < b) {
        if (!isNegative && !b.isNegative) {
            result.isNegative = true;
        } else if (isNegative && b.isNegative) {
            result.isNegative = false;
        }
        result.nat = Subtraction(b.nat, nat);
    } else if (*this > b) {
        if (!isNegative && !b.isNegative) {
            result.isNegative = false;
        } else if (isNegative && !b.isNegative) {
            result.isNegative = true;
        }
        result.nat = Subtraction(nat, b.nat);
    } else {
        result.nat = {0};
    }

    for (long long s = commaPos - 1; s >= 0; s--) {
        result.real.push_back(result.nat.back());
        result.nat.pop_back();
    }
    std::reverse(result.real.begin(), result.real.end());

    result.nat = RemoveZeros(result.nat);
    return result;
}

Big Big::operator*(Big b) {
    Big result;

    // add minus sign if one of the numbers is negative
    if ((isNegative && !b.isNegative) || (!isNegative && b.isNegative)) {
        result.isNegative = true;
    } else if (isNegative && b.isNegative) {
        result.isNegative = false;
    }

    long long commaPos = (b.real.size() + real.size());

    nat = combine(nat, real);
    b.nat = combine(b.nat, b.real);

    result.nat = Multiply(nat, b.nat);
    for (long long s = commaPos - 1; s >= 0; s--) {
        result.real.push_back(result.nat.back());
        result.nat.pop_back();
    }
    std::reverse(result.real.begin(), result.real.end());

    result.nat = RemoveZeros(result.nat);
    return result;
}

Big Big::operator/(Big b) {
    Big result;
    long long commaPos = 0;

    if (b.nat[0] == 1 && b.nat.size() == 1) {
        return *this;
    } else if (b.nat[0] == 0 && b.real.empty() && b.nat.size() == 1) {
        //throw std::logic_error("Dividing by zero exception");
    } else if (*this == b) {
        return Big("1");
    }

    pushZeros(real, b
            .real);

    nat = combine(nat, real);
    b.
            nat = combine(b.nat, b.real);
    result.
            nat = Division(nat, b.nat, commaPos);

    for (
            long long s = result.nat.size() - 1;
            s >=
            commaPos;
            s--) {
        result.real.
                push_back(result
                                  .nat[s]);
        result.nat.

                pop_back();

    }
    std::reverse(result
                         .real.

            begin(), result

                         .real.

            end()

    );

    while (result.nat[0] == 0 && result.nat.

            size()

                                 > 1) {
        result.nat.
                erase(result
                              .nat.

                begin()

        );
    }

    return
            result;
}

Big Big::operator%(Big b) {
    Big result;

    result.nat = Remainder(nat, b.nat);

    return result;
}

Big Big::operator++() {
    *this = *this + Big("1");
    return *this;
}

Big Big::operator++(int) {
    return ++*this;
}

Big Big::operator--() {
    *this = *this - Big("1");
    return *this;
}

Big Big::operator+=(const Big &adt) {
    *this = *this + adt;
    return *this;
}

Big Big::operator-=(const Big &adt) {
    *this = *this - adt;
    return *this;
}

Big Big::operator*=(const Big &adt) {
    *this = *this * adt;
    return *this;
}

Big Big::operator/=(const Big &adt) {
    *this = *this / adt;
    return *this;
}

Big Big::operator%=(const Big &adt) {
    *this = *this % adt;
    return *this;
}

std::ostream &operator<<(std::ostream &os, Big &b) {
    return os << b.getValue();
}

char Big::operator[](int index) {
    value = getValue();
    return value[index];
}

bool Big::operator<=(Big b) {
    return (*this < b) || (*this == b);
}

bool Big::operator>=(Big b) {
    return (*this > b) || (*this == b);
}

bool Big::operator<(Big b) {
    std::vector<int> x(nat), y(b.nat);
    pushZeros(real, b.real);

    x.insert(x.end(), real.begin(), real.end());
    y.insert(y.end(), b.real.begin(), b.real.end());
    return isSmaller(x, y);
}

bool Big::operator>(Big b) {
    std::vector<int> x(nat), y(b.nat);
    pushZeros(real, b.real);

    x.insert(x.end(), real.begin(), real.end());
    y.insert(y.end(), b.real.begin(), b.real.end());
    while (x[0] == 0 && x.size() > 1) {
        x.erase(x.begin());
    }
    while (y[0] == 0 && y.size() > 1) {
        y.erase(y.begin());
    }

    return !isSmaller(x, y);
}

bool Big::operator==(Big b) {
    std::vector<int> x(nat), y(b.nat);
    pushZeros(real, b.real);

    x.insert(x.end(), real.begin(), real.end());
    y.insert(y.end(), b.real.begin(), b.real.end());
    while (x[0] == 0 && x.size() > 1) {
        x.erase(x.begin());
    }
    while (b[0] == 0 && y.size() > 1) {
        y.erase(y.begin());
    }

    return isEqual(x, y);
}

bool Big::operator!=(Big b) {
    return !(*this == b);
}

Big &Big::operator=(std::string val) {
    setValue(std::move(val));
    return *this;
}

Big &Big::operator=(std::vector<int> val) {
    std::string temp = toString(val);
    setValue(temp);
    return *this;
}

Big &Big::operator=(const Big &b) {
    if (this == &b) {
        return *this;
    }
    value = b.value;
    nat = b.nat;
    real = b.real;
    isNegative = b.isNegative;

    return *this;
}
