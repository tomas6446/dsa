#include <iostream>

#define PI 3.1415926535897932384650288
#define SERIES 11

using namespace std;

int fact(int n)
{
    return ((n >= 1) ? n * fact(n - 1) : 1);
}

float findRoot(float number)
{
    float error = 0.0000001;
    float cnumber = number; // define the precision of your result
    while ((cnumber - number / cnumber) > error) // loop until precision satisfied
    {
        cnumber = (cnumber + number / cnumber) / 2;
    }
    return cnumber;
}

float findPower(float value, int power)
{
    if (power == 0)
    {
        return 1;
    }
    else if (power == 1)
    {
        return value;
    }
    else if (power < 0)
    {
        if (value == 0)
        {
            return -0;
        }
        else
        {
            return 1 / (value * findPower(value, (-power) - 1));
        }
    }

    return value * findPower(value, power - 1);
}

float findSinus(int degree)
{
    float rad = ((float) (degree % 360) * (float) PI) / 180;
    float sin = 0;

    // taylor series
    for (int i = 0; i < SERIES; i++)
    {
        // Y = X - X^3/ 3! + X^5/ 5! - ... + (-1)^(n+1) * X^(2*n-1)/ (2n-1)!
        sin += findPower(-1, i) * findPower(rad, 2 * i + 1) / (float) fact(2 * i + 1);
    }
    return sin;
}

int findLogn(int n, int base)
{
    return (n > base - 1) ? 1 + findLogn(n / base, base) : 0; // recursion until n is smaller than base -1
}

int main()
{
    std::cout << "Root of 2: " << findRoot(2) << std::endl;
    std::cout << "Sinus of 122: " << findSinus(122) << std::endl;
    std::cout << "Log base 2 of 4: " << findLogn(4, 2) << std::endl;

    return 0;
}