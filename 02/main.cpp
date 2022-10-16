#include <iostream>
#include <string>
#include<bits/stdc++.h>

typedef struct big
{
    std::string number;

    void swapNumbers(std::string &n2)
    {
        if (number.length() > n2.length())
        {
            swap(number, n2);
        } // swap numbers if n1 is bigger than n2
    }

    std::string operator-(big n2)
    {
        std::string originalN1 = number;
        std::string originalN2 = n2.number;

        swapNumbers(n2.number);

        int sum;
        int digitDiff = n2.number.length() - number.length(); //     digitDiff - how many digits n2 is bigger than n1
        std::string result;

        for (int i = number.length() - 1; i >= 0; i--)
        {
            //  convert n1.number and n2.number to integer then sum them and add how many dozens to add
            sum = (n2.number[i + digitDiff] - '0') - (number[i] - '0'); //   n2.number[i + digitDiff] means last index of n2
            //  convert to string again
            if (sum < 0)
            {
                result.push_back((10 + sum % 10) + '0'); // sum is negative then current number is 10 + sum
                n2.number[i + digitDiff - 1] = ((n2.number[i + digitDiff - 1] - '0') - 1) + '0'; // sum is negative then next number - 1
            }
            else
            {
                result.push_back(sum % 10 + '0');
            }
        }
        if (result[0] == '0')
        {
            result = '0';
        }
        for (int i = digitDiff - 1; i >= 0; i--)
        {
            result.push_back((n2.number[i] - '0') + '0');
        }
        if (originalN1.length() < originalN2.length())
        {
            result.push_back('-');
        }
        reverse(result.begin(), result.end());

        number = originalN1;
        n2.number = originalN2;

        return result;
    }

    std::string operator+(big n2)
    {
        std::string originalN1 = number;
        std::string originalN2 = n2.number;

        swapNumbers(n2.number);

        int dozenCount = 0, sum;
        int digitDiff = n2.number.length() - number.length(); //     digitDiff - how many digits n2 is bigger than n1
        std::string result;

        for (int i = number.length() - 1; i >= 0; i--)
        {
            //  convert n1.number and n2.number to integer then sum them and add how many dozens to add
            sum = (number[i] - '0') + (n2.number[i + digitDiff] - '0') + dozenCount; //   n2.number[i + digitDiff] means last index of n2
            //  convert to string again
            result.push_back(sum % 10 + '0');
            dozenCount = sum / 10;
        }
        for (int i = digitDiff - 1; i >= 0; i--)
        {
            sum = ((n2.number[i] - '0') + dozenCount);
            result.push_back(sum % 10 + '0');
            dozenCount = sum / 10;
        }
        if (dozenCount) // Add remaining dozen
        {
            result.push_back(dozenCount + '0');
        }
        reverse(result.begin(), result.end());

        number = originalN1;
        n2.number = originalN2;

        return result;
    }
} big;

int main()
{
    big n1, n2;

    std::cout << "1: ";
    std::cin >> n1.number;
    std::cout << "2: ";
    std::cin >> n2.number;

    std::cout << n1.number << " + " << n2.number << " = " << n1.operator+(n2) << std::endl;
    std::cout << n1.number << " - " << n2.number << " = " << n1.operator-(n2) << std::endl;

    return 0;
}
