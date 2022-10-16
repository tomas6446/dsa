#include "Tree.h"
#include "Table.h"
#include "List.h"

int main() {
    Tree<int> tree({1, 2, 3, 4, 5, 6});
    tree.print();

    Table<int> table({1, 2, 3, 4, 5, 6});
    table.print();

    List<int> list({1, 2, 3, 4, 5, 6});
    list.print();
    return 0;
}
