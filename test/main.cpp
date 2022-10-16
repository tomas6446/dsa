
#include <string>
#include <iostream>
#include <cmath>
#include "vector"

#include "List.h"
#include "Tree.h"
#include "Table.h"

using namespace std;

int main() {
    Tree<int> tree({5, 8, 7, 9, 1, 3, 4, 2, 6});
    tree.print();
    return 0;
}
