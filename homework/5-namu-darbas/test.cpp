#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>
#include <vector>


// other includes and definitions

/* YOUR CODE HERE */

using namespace std;


// throw the following class if function is not implemented
class NotImplementedException {
};

// final result
int result;

// output				
vector<int> output;

int isSafe(int v, int **graph, vector<int> path, int pos) {
    if (graph[path[pos - 1]][v] != 0) {
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool findCycle(int **graph, int pos, vector<int> path, bool *visited, int size) {
    if (pos != size) {
        for (int v = 0; v < size; v++) {
            if (isSafe(v, graph, path, pos) && !visited[v]) {
                path.push_back(v);
                visited[v] = true;
                findCycle(graph, pos + 1, path, visited, size);
                visited[v] = false;
                path.pop_back();
            }
        }
    } else {
        if (graph[path[path.size() - 1]][path[0]] != 0) {
            path.push_back(0);
            output = path;
            path.pop_back();
            return true;
        }
        return false;
    }
}

void hamiltonianCycle(int **input, int size) {
    // result: set to size if hamiltonian cycle exists, and to 0 otherwise
    // output: node indices (starting at 0) in the hamiltonian cycle;
    // if many cycles are present, output should be such that it represents
    // the largest multidigital number among those possible
    // heuristic: the longer the cycle, the better

    std::vector<int> path;
    path.push_back(0);
    bool visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }
    visited[0] = true;

    if (!findCycle(input, 1, path, visited, size)) {
        result = size;
    } else {
        result = 0;
    }
}

void largestClique(int **input, int size) {
    // result: set to the size of the largest clique
    // output: node indices (starting at 0) in the largest clique in a descending order;
    // if many such cliques are present, output should be such that it represents
    // the largest multidigital number among those possible
    // heuristic: the larger the clique, the better
    /* YOUR CODE HERE */
    throw NotImplementedException();
}

void dominatingSet(int **input, int size) {
    // result: set to the size of the minimum dominating set
    // output: node indices (starting at 0) in the minimum dominating set in a descending order;
    // if many such sets are present, output should be such that it represents
    // the largest multidigital number among those possible
    // heuristic: the smaller the set, the better
    /* YOUR CODE HERE */
    throw NotImplementedException();
}

void independentSet(int **input, int size) {
    // result: set to the size of the maximum independent set
    // output: node indices (starting at 0) in the maximum independent set in a descending order;
    // if many such sets are present, output should be such that it represents
    // the largest multidigital number among those possible
    // heuristic: the larger the set, the better
    /* YOUR CODE HERE */
    throw NotImplementedException();
}

void vertexCover(int **input, int size) {
    // result: set to the size of the minimum vertex cover
    // output: node indices (starting at 0) in the minimum vertex cover in a descending order;
    // if many such covers are present, output should be such that it represents
    // the largest multidigital number among those possible
    // heuristic: the smaller the cover, the better
    /* YOUR CODE HERE */
    throw NotImplementedException();
}

void longestPath(int **input, int size) {
    // result: set to the length of the longest output
    // output: node indices (starting at 0) in the longest output;
    // if many such paths are present, output should be such that it represents
    // the largest multidigital number among those possible
    // heuristic: the longer the output, the better
    /* YOUR CODE HERE */
    throw NotImplementedException();
}

void intersectionNumber(int **input, int size) {
    // result: set to the intersection number (edge clique cover number)
    // output: clique sizes that cover the graph, in a descending order
    // heuristic: the smaller the number, the better
    /* YOUR CODE HERE */
    throw NotImplementedException();
}

void vertexColoring(int **input, int size) {
    // result: set to the chromatic number
    // output: numbers of vertices colored in each color, in a descending order;
    // if many such colorings are possible, output should be such that it represents
    // the largest multidigital number among those possible
    // heuristic: the smaller the number, the better
    /* YOUR CODE HERE */
    throw NotImplementedException();
}

void edgeColoring(int **input, int size) {
    // result: set to the chromatic index
    // output: numbers of edges colored in each color, in a descending order;
    // if many such colorings are possible, output should be such that it represents
    // the largest multidigital number among those possible
    // heuristic: the smaller the index, the better
    /* YOUR CODE HERE */
    throw NotImplementedException();
}


/* DO NOT MODIFY CODE BELOW */

int main() {
    try {
        int x = -1;
        while (1) {
            cin >> x;
            if (x == 0) {
                break;
            } else {
                int n;
                cin >> n;
                int **input = new int *[n];
                for (int i = 0; i < n; ++i) {
                    input[i] = new int[n];
                }
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        cin >> input[i][j];
                    }
                }
                switch (x) {
                    case 1:
                        hamiltonianCycle(input, n);
                        break;
                    case 2:
                        largestClique(input, n);
                        break;
                    case 3:
                        dominatingSet(input, n);
                        break;
                    case 4:
                        independentSet(input, n);
                        break;
                    case 5:
                        vertexCover(input, n);
                        break;
                    case 6:
                        longestPath(input, n);
                        break;
                    case 7:
                        intersectionNumber(input, n);
                        break;
                    case 8:
                        vertexColoring(input, n);
                        break;
                    case 9:
                        edgeColoring(input, n);
                        break;
                }

                for (int i = 0; i < n; ++i) {
                    delete[] input[i];
                }
                delete[] input;

            }
        }
    } catch (NotImplementedException &e) {
        return 2018;
    } catch (...) {
        return -1;
    }
    return 0;
}
