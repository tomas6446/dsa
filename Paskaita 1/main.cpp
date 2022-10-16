#include <iostream>
#include <vector>

using namespace std;

int comp, swp;

void bubbleSort1(vector<int> &v)
{
    comp = 0;
    swp = 0;
    for (int i = 0; i < v.size() - 1; ++i)
    {
        for (int j = 0; j < v.size() - 1; ++j)
        {
            comp++;
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
                swp++;
            }
        }
    }
}

void bubbleSort2(vector<int> &v)
{
    comp = 0;
    swp = 0;
    for (int i = 0; i < v.size() - 1; ++i)
    {
        for (int j = 0; j < v.size() - 1 - i; ++j)
        {
            comp++;
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
                swp++;
            }
        }
    }
}

void bubbleSort3(vector<int> &v)
{
    comp = 0;
    swp = 0;
    for (int i = 0; i < v.size() - 1; ++i)
    {
        int changed = 0;
        for (int j = 0; j < v.size() - 1 - i; ++j)
        {
            comp++;
            if (v[j] > v[j + 1])
            {
                changed = 1;
                swap(v[j], v[j + 1]);
                swp++;
            }
        }
        if (changed == 0)
        {
            break;
        }
    }
}

int main()
{
    vector<int> v = {6, 2, 1, 4, 3, 5};
    bubbleSort1(v);
    printf("1. comp:%d\nswap:%d\n\n", comp, swp);

    v = {6, 2, 1, 4, 3, 5};
    bubbleSort2(v);
    printf("2. comp:%d\nswap:%d\n\n", comp, swp);

    v = {6, 2, 1, 4, 3, 5};
    bubbleSort3(v);
    printf("3. comp:%d\nswap:%d\n\n", comp, swp);
    return 0;
}
