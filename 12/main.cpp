#include <fstream>
#include <algorithm>
#include <iomanip>
#include "vector"
#include "iostream"
#include "Hash.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int lev(std::string a, std::string b, int m, int n)
{
    return m == 0 ? n : n == 0 ? m : a[m - 1] == b[n - 1] ?
                                     lev(a, b, m - 1, n - 1) : 1 + min(min(lev(a, b, m, n - 1),
                                                                           lev(a, b, m - 1, n)), lev(a, b, m - 1, n - 1));

}

std::string toLower(std::string word)
{
    for (char i: word) {
        if (isupper(i)) {
            word = tolower(i);
        }
    }
    return word;
}

void read(Hash *vocab, const std::string &fileName)
{
    std::ifstream file(fileName, ios::in);

    std::string word;
    if (file.is_open()) {
        while (file >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), []
                    (char c) { return !std::isalpha(c); }), word.end());

            vocab->insertItem(toLower(word));
        }
    }
    file.close();
}

void vocAdd(const std::string &word)
{
    std::ofstream file("vocabulary.txt", ios::app);
    file << word << std::endl;
    file.close();
}

std::string findNearest(Hash *vocab, const std::string &notFound)
{
    std::string nearest;

    list<std::string> voc = vocab->getTable(notFound[0] - 97);
    int minLev = (int) notFound.length(), l;
    for (auto &v: voc) {
        l = lev(notFound, v, (int) notFound.length(), (int) v.length());
        if (l <= minLev && l != 0) {
            minLev = l;
            nearest = v;
        }
    }

    std::cout << minLev << " ";
    return nearest;
}


int main()
{
    Hash *vocab = new Hash(26);
    Hash *text = new Hash(26);
    Hash *notFound = new Hash(26);
    new Hash(26);

    read(text, "text.txt");
    read(vocab, "vocabulary.txt");

    int count = 0;

    std::cout << "Words with misstakes:" << std::endl;
    // capacity - alphabet char count
    for (int i = 0; i < text->getCapacity(); i++) {
        list<std::string> vocTable = vocab->getTable(i);
        list<std::string> textTable = text->getTable(i);

        if (vocTable.empty() || textTable.empty()) {
            continue;
        }
        for (auto &itText: textTable) {
            for (auto &itVoc: vocTable) {
                int l = lev(itText, itVoc, (int) itText.length(), (int) itVoc.length());
                if (l < 3 && l > 0) { // to find similiar word with max 2 letter difference
                    std::cout << fixed << setw(5)
                              << right << count++ << ": [ " << itText << " ]"
                              << setw(10 - (int) itText.length())
                              << right << "[ " << itVoc << " ]"
                              << setw(5) << right << " := ";
                    std::cout << lev(itText, itVoc, (int) itText.length(), (int) itVoc.length()) << std::endl;
                }
                else {
                    notFound->insertItem(itText);
                }
            }
        }
    }

    std::cout << "Not found in vocabulary words" << std::endl;
    count = 0;
    char choice;
    for (int i = 0; i < notFound->getCapacity(); i++) {
        list<std::string> notFoundTable = vocab->getTable(i);
        for (auto &f: notFoundTable) {
            std::cout << count++ << ": ";
            std::cout << f << " [ nearest diff: " << findNearest(vocab, f) << " ] " << std::endl;
            std::cout << "[ADD] Y/N: ";
            cin >> choice;

            switch (choice) {
                case 'Y':
                    vocAdd(f);
                    break;
                case 'y':
                    vocAdd(f);
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}

