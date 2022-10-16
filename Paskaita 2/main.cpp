#include <iostream>

int mod = 0, watch = 0;

typedef struct Paprastas
{
    int n = 1;
    int *dArray = new int[n];

    int get(int index)
    {
        return dArray[index];
    }

    int size()
    {
        return n;
    }

    void add(int index, int value)
    {
        index > n ? n = index : n++;
        dArray = (int *) realloc(dArray, n * sizeof(int));

        for (int i = n; i >= index; i--)
        {
            dArray[i] = dArray[i - 1];
            watch++;
        }

        dArray[index] = value;
        mod++;
    }

    void del(int index)
    {
        for (int i = index; i < n; i++)
        {
            dArray[i] = dArray[i + 1];
            watch++;
        }
        n--;
    }
} Paprastas;

typedef struct Skeletas
{
    int n = 1;
    int *dArray = new int[n];
    int *dArrayDes = new int[n]; // array for describing dArray with bits

    int get(int index)
    {
        return dArray[index];
    }

    int size()
    {
        return n;
    }

    void add(int index, int value)
    {
        index > n ? n = index : n++;
        dArray = (int *) realloc(dArray, n * sizeof(int));
        dArrayDes = (int *) realloc(dArrayDes, n * sizeof(int));

        for (int i = n; i >= index; i--)
        {
            dArray[i] = dArray[i - 1];
            watch++;
            dArrayDes[i] = dArrayDes[i - 1];
            watch++;
        }

        dArray[index] = value;
        mod++;
        dArrayDes[index] = 1;
        mod++;
    }

    void del(int index)
    {
        dArrayDes[index] = 0;
    }

    void balance()
    {
        for (int i = 1; i < n; i++)
        {
            if (dArrayDes[i] == 0)
            {
                for (int j = i; j < n; j++)
                {
                    dArrayDes[j] = dArrayDes[j + 1];
                    watch++;
                    dArray[j] = dArray[j + 1];
                    watch++;
                }
                n--;
                i--;
            }
        }
    }
} Skeletas;

typedef struct Nenuoseklus
{
    int n = 1;
    int *dArray = new int[n];
    int *dIndexArray = new int[n]; // array to store indexes of dArray

    int get(int index)
    {
        return dArray[dIndexArray[index]];
    }

    int size()
    {
        return n;
    }

    void add(int index, int value)
    {
        index > n ? n = index : n++;
        dArray = (int *) realloc(dArray, n * sizeof(int));
        dIndexArray = (int *) realloc(dArray, n * sizeof(int));

        dIndexArray[n] = index;
        mod++;
        dArray[dIndexArray[n]] = value;
        mod++;
    }

    void del(int index)
    {
        for (int i = index; i < n; i++)
        {
            dIndexArray[i] = dIndexArray[i + 1];
            watch++;
        }
        n--;
    }
} Nenuoseklus;

int main()
{
    Paprastas ar;

    ar.add(1, 4);
    ar.add(1, 5);
    ar.get(2);
    ar.add(2, 3);
    ar.del(1);
    ar.add(1, 6);
    ar.del(1);
    ar.size();
    ar.get(1);

    for (int i = 1; i < ar.size(); i++)
    {
        std::cout << ar.get(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Modifikaciju:" << mod << " Perziuru:" << watch << std::endl;
    mod = 0;
    watch = 0;
    //_________________________________

    Skeletas sk;

    sk.add(1, 4);
    sk.add(1, 5);
    sk.get(2);
    sk.add(2, 3);
    sk.del(1);
    sk.add(1, 6);
    sk.del(1);
    sk.size();
    sk.get(1);

    sk.balance();
    for (int i = 1; i < sk.size(); i++)
    {
        std::cout << sk.get(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Modifikaciju:" << mod << " Perziuru:" << watch << std::endl;
    mod = 0;
    watch = 0;
    //_________________________________

    Nenuoseklus nen;

    nen.add(1, 4);
    nen.add(1, 5);
    nen.get(2);
    nen.add(2, 3);
    nen.del(1);
    nen.add(1, 6);
    nen.del(1);
    nen.size();
    nen.get(1);

    for (int i = 1; i < sk.size(); i++)
    {
        std::cout << sk.get(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Modifikaciju:" << mod << " Perziuru:" << watch << std::endl;
    mod = 0;
    watch = 0;
    return 0;
}
