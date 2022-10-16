#include <gtest/gtest.h>
#include "../src/test2.cpp"

using namespace std;


void print(intTree Int, doubleTree Double, stringTree String) {
    cout << "INT---------" << endl;
    Int.print();
    cout << "DOUBLE---------" << endl;
    Double.print();
    cout << "STRING---------" << endl;
    String.print();
    cout << endl;
}

std::vector<string> str{"tomas", "igor", "barbim", "maksashov", "repkin", "kozakas", "namu", "darbas", "Tree", "Table",
                        "tomas", "igor", "barbim", "maksashov", "repkin", "kozakas", "namu", "darbas", "Tree", "Table",
                        "tomas", "igor", "barbim", "maksashov", "repkin", "kozakas", "namu", "darbas", "Tree", "Table",
                        "tomas", "igor", "barbim", "maksashov", "repkin", "kozakas", "namu", "darbas", "Tree", "Table",};
Container container;

int N = 20;

TEST(Tree, pushElement) {
//    srand(time(nullptr));
    for (int i = 0; i < N; i++) {
        container.add(i, {i, "s", (double) (i)});
        //notify(OPCODE::INS, container[i]);
    }

    createIndex(DATATYPE::INT, container);
    createIndex(DATATYPE::STR, container);
    createIndex(DATATYPE::DBL, container);

    print(Int, Double, String);
}

TEST(Tree, findElement) {
    cout << "Trying to find int values" << endl;
    for (int i = 0; i < N; i++) {
        cout << "[" << i << "] ";
        cout << Int.search(i) << endl;
    }
    cout << endl;

    cout << "Trying to find string values" << endl;
    for (int i = 0; i < N; i++) {
        cout << "[" << "s" << "] ";
        cout << String.search("s") << endl;
    }
    cout << endl;

    cout << "Trying to find double values" << endl;
    for (int i = 0; i < N; i++) {
        cout << "[" << i << "] ";
        cout << Double.search(i) << endl;
    }
    cout << endl;
}

TEST(Tree, removeAllElements) {
    for(int i = 0; i < N; i++) {
        notify(OPCODE::DEL, container[0]);
        container.remove(0);
    }
    print(Int, Double, String);
}