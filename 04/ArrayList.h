#ifndef ARRAYLIST_H
#define ARRAYLIST_H


class ArrayList
{
private:

    int size = 10;
    int *data = new int[size];


public:

    ArrayList()
    {
        size = 10;
    }

    ArrayList(int size)
    {
        this->size = size;
        data = new int[size];
    }

    ~ArrayList()
    {
        delete[] data;
    }

    int getValue(int index)
    {
        if (index < size)
        {
            return data[index];
        }
        else
        {
            return 0;
        }
    }

    void printArray()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void addData(int key, int index)
    {
        data[index] = key;
    }

    void deleteData(int key)
    {
        int pos;

        for (int i = 0; i < size; i++)
        {
            if (data[i] == key)
            {
                pos = i;
            }
        }

        if (pos < 0 || pos > size)
        {
            for (int i = pos - 1; i < size; i++)
            {
                data[i] = data[i + 1];
            }
        }
        size--;
    }

    bool searchData(int key)
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i] == key)
            {
                return true;
            }
        }
        return false;
    }
};

#endif
