#include <string>
#include <iostream>
#include <utility>
#include "data.h"


// other includes and definitions

/* YOUR CODE HERE */

using namespace std;

// define your datatype here
typedef Big myType;

// convert from string to myType
myType convert(string s) {
    return myType(s);
}

// convert from myType to string
string toStr(myType m) {
    return m.getValue();
}

// compute a factorial
myType myFactorial(int n);

// finds the next prime, bigger than n
myType myPrime(myType n);

// finds d to the power of (positive) p
myType myPow(double d, int p);

// finds (natural) logarithm of d
myType myLog(double d);

// finds sinus of d
myType mySin(double d);

// finds square root of d
myType mySqrt(double d);

// finds a value of PI with n digits of precision (zeroes afterwards)
myType myPi(int n);

// computes an average of n valus in an array
myType myAvg(myType *data, int n);

// search for a value in an array of n numbers and return an index
int myFind(myType *data, int n, myType value);

// sorts data in an array of n numbers by (optimized) bubble sort algorithm
void mySort(myType *data, int n);

myType myFactorial(int n) {
    myType result("1"), fact(std::to_string(n));
    for (int i = n - 1; i >= 1; i--) {
        result *= fact;
        fact = Big(std::to_string(i));
    }
    if (n == 0) {
        result.clear();
        result.setValue("0");
    }
    return result;
} // apskaičiuoja skaičiaus n faktorialą

bool isPrime(myType n) {
    for (myType i("2"); i < n; i++) {
        if (n % i == myType("0")) {
            return false;
        }
    }
    return true;
}

myType myPrime(myType n) {
    while (true) {
        n++;
        if (isPrime(n)) {
            return n;
        }
    }
}// randa mažiausią (sekantį) pirminį skaičių, didesnį už n

myType myPow(double d, int p) {

    myType constant(to_string(d)), result(to_string(d));
    if (d < 0) {
        constant.setNegative();
        result.setNegative();
    }
    if (p == 0) {
        return myType("1");
    }
    for (int i = 0; i < p - 1; ++i) {
        result *= constant;
    }
    return result;
}// randa reikšmę, gautą skaičių d pakėlus (teigiamu) laipsniu p

myType myLog(double d) {
    return ((d > 1) ? myType("1") + myLog(d / 2) : myType("0")); // recursion until d is smaller than base 1
}// randa (natūralų) skaičiaus d logaritmą

myType mySin(double d) {
    float rad = (float) (((int) d % 360) * 3.14159265359) / 180;
    myType sin("0");

    // taylor series
    for (int i = 0; i < 7; i++) {
        sin += myPow(-1, i) * myPow(rad, 2 * i + 1) / myFactorial(2 * i + 1);
    }
    return sin;
} // randa skaičiaus d sinusą

myType mySqrt(double d) {
    myType error("0.00001"); //define the precision of your result
    myType sqrt(to_string(d));
    myType num(to_string(d));

    while ((sqrt - num / sqrt) > error) //loop until precision satisfied
    {
        sqrt = (sqrt + num / sqrt) / myType("2");
    }
    return sqrt;
}

myType myPi(int n) {
    myType partialSeries("0");
    for (int i = 0; i < n; i++) {
        myType t(to_string(i));

        if (t % myType("2") == myType("0")) {
            partialSeries += myType("1") / (myType("2") * t + myType("1"));
        } else {
            partialSeries -= myType("1.0") / (myType("1") * t + myType("1"));
        }
    }
    myType series = myType("4.0") * partialSeries;

    return series;
}


myType myAvg(myType *data, int n) {
    myType avrg("0");
    for (int i = 0; i < n; i++) {
        avrg += data[i];
    }
    avrg /= myType(to_string(n));
    return avrg;
}

int myFind(myType *data, int n, myType value) {
    for (int i = 0; i < n; i++) {
        if (data[i] == value) {
            return i;
        }
    }
    return 0;
}


int partition(myType data[], int low, int high) {
    myType pivot = data[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (data[j] < pivot) {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return (i + 1);
}

void quickSort(myType data[], int low, int high) {
    if (low < high) {
        int pi = partition(data, low, high);
        quickSort(data, low, pi - 1);
        quickSort(data, pi + 1, high);
    }
}

void mySort(myType *data, int n) {
    quickSort(data, 0, n - 1);
}


/* DO NOT MODIFY CODE BELOW */
int main1() {
    while (1) {
        int x = -1;
        cin >> x;
        if (x == 0)
            break;
        string s;
        double d;
        int n;
        myType *data = NULL;
        string output;
        switch (x) {
            case 1:
                cin >> n;
                cout << (output = toStr(myFactorial(n))) << endl;
                break;
            case 2:
                cin >> s;
                cout << (output = toStr(myPrime(convert(s)))) << endl;
                break;
            case 3:
                int p;
                cin >> d >> p;
                cout << (output = toStr(myPow(d, p))) << endl;
                break;
            case 4:
                cin >> d;
                cout << (output = toStr(myLog(d))) << endl;
                break;
            case 5:
                cin >> d;
                cout << (output = toStr(mySin(d))) << endl;
                break;
            case 6:
                cin >> d;
                cout << (output = toStr(mySqrt(d))) << endl;
                break;
            case 7:
                cin >> n;
                cout << (output = toStr(myPi(n))) << endl;
                break;
            case 8:
                cin >> n;
                data = new myType[n];
                for (int i = 0; i < n; ++i) {
                    string s;
                    cin >> s;
                    data[i] = convert(s);
                }
                cout << (output = toStr(myAvg(data, n))) << endl;
                delete[] data;
                break;
            case 9:
                cin >> n;
                data = new myType[n];
                for (int i = 0; i < n; ++i) {
                    string s;
                    cin >> s;
                    data[i] = convert(s);
                }
                cin >> s;
                int f;
                cout << (f = myFind(data, n, convert(s))) << endl;
                delete[] data;
                break;
            case 10:
                cin >> n;
                data = new myType[n];
                for (int i = 0; i < n; ++i) {
                    string s;
                    cin >> s;
                    data[i] = convert(s);
                }
                mySort(data, n);
                for (int i = 0; i < n; ++i) {
                    cout << (output = toStr(data[i])) << endl;
                }
                delete[] data;
                break;
        }
    }
    return 0;
}
