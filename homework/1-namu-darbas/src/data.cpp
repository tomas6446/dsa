#include "data.h"

// store value in vector
std::vector<int> Big::storeInVector(std::string val) {
    unsigned int a = 0;
    std::vector<int> arr;
    if (val.empty()) {
        return {0};
    }
    while (a != val.length()) {
        arr.push_back(val[a] - '0');
        a++;
    }
    return arr;
}

// combine two vector into one
std::vector<int> Big::combine(std::vector<int> &a, std::vector<int> &b) {
    a.insert(a.end(), b.begin(), b.end());
    b.clear();
    return a;
}

void Big::setValue(std::string val) {
    value = std::move(val);

    // erase minus from value stores in class, switch isNegative to true, to tag negative numbers
    if (value[0] == '-') {
        value.erase(value.begin());
        isNegative = true;
    }

    // store value into 2 separate vectors for natural and real parts of number
    if (value.find('.') == std::string::npos) {
        nat = storeInVector(value);
    } else {
        nat = storeInVector(value.substr(0, value.find('.')));
        real = storeInVector(value.substr(value.find('.') + 1, value.length() - 1));
    }
}

// convert vector to string
std::string Big::toString(std::vector<int> a) {
    std::string res;
    for (auto x: a) {
        res += std::to_string(x);
    }
    return res;
}

// convert vector to value
std::string Big::convertToValue(Big &b) {
    std::string val;
    for (auto n: b.nat) {
        val += std::to_string(n);
    }
    if (!b.real.empty()) {
        val += '.';
        for (auto r: b.real) {
            val += std::to_string(r);
        }
    } else {
        if (b.nat[0] == 0 && b.nat.size() == 1) {
            return val;
        }
        val += ".0";
    }
    if (b.isNegative) {
        val = '-' + val;
    }
    return val;
}

std::string Big::getValue() {
    while (!real.empty() && real[real.size() - 1] == 0) {
        real.pop_back();
    }
    value = convertToValue(*this);
    return value;
}

void Big::setNegative() {
    isNegative = true;
}

void Big::clear() {
    value.clear();
    nat.clear();
    real.clear();
    isNegative = false;
}

std::vector<int> Big::RemoveZeros(std::vector<int> a) {
    std::string zeros, z;
    if (!a.empty()) {
        if (equal(a.begin() + 1, a.end(), a.begin()) && a[0]== 0) {
            a.clear();
            a.push_back(0);
            return a;
        } else {
            for (unsigned long long i = 0; i < a.size(); ++i) {
                zeros += std::to_string(a[i]);
            }
            zeros.erase(0, zeros.find_first_not_of('0'));
            a.clear();
            for (unsigned long long i = 0; i < zeros.size(); ++i) {
                a.push_back(stoi(z = zeros[i]));
            }
            return a;
        }
    }
    return a;
};

bool Big::isSmaller(std::vector<int> a, std::vector<int> b) {
    if (a.empty() || b.empty()) {
        return false;
    }
    if (a.size() < b.size() && a[0] != 0 && b[0] != 0) {
        return true;
    } else if (a.size() > b.size() && a[0] != 0 && b[0] != 0) {
        return false;
    }
    for (unsigned long long i = 0; i < a.size(); i++) {
        if (a[i] < b[i]) {
            return true;
        } else if (a[i] > b[i]) {
            return false;
        }
    }
    return false;
}

bool Big::isEqual(std::vector<int> a, std::vector<int> b) {
    return (a == b);
}

/* Column division */
std::vector<int> Big::Division(std::vector<int> a, std::vector<int> b, long long &commaPos) {
    std::vector<int> result;
    Big dividend, divisor, quotient;

    // remove zeros on left from one vector, add it to the other, collect zeros removed
    int zero = 0;
    if (a[0] == 0 && a[1] == 0) {
        for (unsigned int i = 0; i < a.size() - 1; i++) {
            b.push_back(0);
        }
    }
    while (a[0] == 0 && a.size() > 1) {
        a.erase(a.begin());
        zero++;
    }
    while (b[0] == 0 && b.size() > 1) {
        b.erase(b.begin());
    }

    // find comma position by subtracting two number sizes
    int commaShift = 0;
    if(a.size() > 2) {
        commaShift = (a.size() > b.size() ? a.size() - b.size() : 0);
    }
    // indx represents digits which will be added to the dividend after every subtraction
    int indx = a.size() > b.size() ? b.size() : -1;

    dividend.nat.insert(dividend.nat.end(), a.begin(), a.end() - commaShift);
    divisor = b;

    long long multiplyCount;
    bool addComma = true;

    while (true) {
        // start from multiplying quotient by one to find to the dividend number
        multiplyCount = 1;
        quotient.nat = divisor.nat;

        // find nearest quotient
        while (quotient <= dividend) {
            quotient = divisor * Big(std::to_string(++multiplyCount));
        }
        quotient -= divisor;
        multiplyCount -= 1;

        // subtract dividend and quotient
        dividend -= quotient;

        // push result to the result vector
        result.push_back(multiplyCount);

        // add comma after first subtraction + comma shift
        if (addComma) {
            commaPos = result.size() + commaShift;
            addComma = false;
        }

        // check if dividend is already 0 and does not need to be
        if (dividend.nat.size() == 1 && dividend.nat.back() == 0) {
            break;
        }
        // add digits to the dividend of the original dividend number
        if (indx != -1 && indx < (int)a.size()) {
            // add original digits
            if (dividend.nat[0] == 0 && dividend.nat.size() == 1) {
                dividend.nat[0] = a[indx];
            } else {
                dividend.nat.push_back(a[indx]);
            }
            indx++;
        } else {
            // push zeros if indx is out of range of original dividend
            dividend.nat.push_back(0);
        }
        // precision of the result
        if (result.size() >= 51) {
            break;
        }
    }
    return result;
}

/* Remainder by finding quotient using multiplication and subtraction */
std::vector<int> Big::Remainder(std::vector<int> a, std::vector<int> b) {
    Big remainder;
    Big dividend, divisor, mult;
    dividend.nat = a;
    divisor.nat = b;

    long long multiplyCount = 1;
    mult = divisor;

    while (mult <= dividend) {
        mult = divisor * Big(std::to_string(++multiplyCount));
    }
    mult -= divisor;
    remainder = dividend - mult;

    return remainder.nat;
}

std::vector<int> Big::pushZerosLeft(std::vector<int> a, std::vector<int> b) {
    long long diff = a.size() - b.size();
    for (long long i = 0; i < diff; ++i) {
        b.insert(b.begin(), 0);
    }
    return b;
}

std::vector<int> Big::Subtraction(std::vector<int> a, std::vector<int> b) {
    std::vector<int> difference;

    if (a.size() == 1 && b.size() == 1 && a[0] == 0 && b[0] == 0) {
        return a;
    }
    if (a.size() < b.size() || (a.size() == b.size() && (a[0] < b[0]))) {
        std::vector<int> temp;
        for (unsigned long long i = 0; i < a.size(); ++i) {
            temp.push_back(a[i]);
        }
        a.clear();
        for (unsigned long long i = 0; i < b.size(); ++i) {
            a.push_back(b[i]);
        }
        b.clear();
        for (unsigned long long i = 0; i < temp.size(); ++i) {
            b.push_back(temp[i]);
        }
    }
    if (a.size() > b.size()) {
        b = pushZerosLeft(a, b);
    } else if (b.size() > a.size()) {
        a = pushZerosLeft(b, a);
    }
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    // subtract a from b
    for (unsigned long long i = 0; i < a.size(); ++i) {
        if (a[i] < b[i]) {
            a[i + 1] -= 1;
            a[i] += 10;
        }
        difference.push_back(a[i] - b[i]);
    }
    std::reverse(difference.begin(), difference.end());
    return difference;
}

std::vector<int> Big::Addition(std::vector<int> a, std::vector<int> b) {
    std::vector<int> sum;
    std::vector<int> carry;
    int initialSum, temp;

    std::string helper, h2, h3;

    // add zeros from left
    if (a.size() > b.size()) {
        b = pushZerosLeft(a, b);
    } else if (b.size() > a.size()) {
        a = pushZerosLeft(b, a);
    }
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    for (unsigned long long i = 0; i < a.size(); ++i) {
        // sum numbers from vector
        initialSum = a[i] + b[i];
        if (i > 0) {
            initialSum = initialSum + carry[i-1];
        }
        // find carry
        temp = 0;
        if (initialSum > 9) {
            helper = std::to_string(initialSum);
            temp = stoi(h2 = helper[0]);
            initialSum = stoi(h3 = helper[1]);
        }
        // add sum into vector
        sum.push_back(initialSum);
        carry.push_back(temp);
    }
    sum.push_back(temp);
    std::reverse(sum.begin(), sum.end());
    return sum;
}

/* Multiply using brute force pen and paper algorithm*/
std::vector<int> Big::Multiply(std::vector<int> a, std::vector<int> b) {
    std::vector<int> solution, carry, ret;
    std::vector<std::vector<int>> sum;
    int prod, temp;
    std::string helper, h2, h3;

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    for (unsigned long long i = 0; i < b.size(); ++i) {
        for (unsigned long long j = 0; j < a.size(); ++j) {
            // multiply, add carry
            prod = a.at(j) == 0 && b.at(i) == 0 ? 0 : a.at(j) * b.at(i);
            if (j > 0) {
                prod = prod + carry.at(j - 1);
            }
            temp = 0;
            if (prod > 9) {
                helper = std::to_string(prod);
                temp = stoi(h2 = helper[0]);
                prod = stoi(h3 = helper[1]);
            }
            // add solution to vector
            solution.push_back(prod);
            // push_back carry
            carry.push_back(temp);
        }
        solution.push_back(temp);
        std::reverse(solution.begin(), solution.end());
        // pad right zeros
        for (unsigned long long k = 0; k < i; ++k) {
            solution.push_back(0);
        }
        sum.push_back(solution);
        // clear solution and carry
        solution.clear();
        carry.clear();
    }
    // sum solution
    for (unsigned long long i = 1; i < sum.size(); ++i) {
        sum.at(0) = (Addition(sum.at(0), sum.at(i)));
    }
    for (unsigned long long i = 0; i < sum.at(0).size(); ++i) {
        ret.push_back(sum.at(0).at(i));
    }
    return ret;
}

/* pushes zeros to equal out number digit amount */
void Big::pushZeros(std::vector<int> &a, std::vector<int> &b) {
    int diff;
    if (a.empty() || b.empty()) {
        return;
    }
    if (a.size() < b.size()) {
        diff = b.size() - a.size();
        for (int i = 0; i < diff; i++) {
            a.push_back(0);
        }
    } else if (a.size() > b.size()) {
        diff = a.size() - b.size();
        for (int i = 0; i < diff; i++) {
            b.push_back(0);
        }
    }
}
