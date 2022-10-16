
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "vector"
#include "iostream"

int minDistance(const int dist[], const bool shortPath[], int elem)
{
    int min = -1, x;
    for (int i = 0; i < elem; i++) {
        if (!shortPath[i] && dist[i] <= min) {
            min = dist[i], x = i;
        }
    }
    return x;
}

void dijkstra(int graph[ELEMENT_COUNT][ELEMENT_COUNT], int src, int elem)
{
    int distance[elem];
    bool shortestPath[elem];

    distance[elem] = {-1};
    shortestPath[elem] = {false};
    distance[src] = 0;

    for (int i = 0; i < elem - 1; i++) {
        int min = minDistance(distance, shortestPath, elem);
        shortestPath[min] = true;

        for (int j = 0; j < elem; j++) {
            if (!shortestPath[j] && distance[i] != -1 && graph[i][j] &&
                distance[i] + graph[i][j] < distance[j]) {
                distance[j] += graph[i][j];
            }
        }
    }
    for(int i =0; i < elem; i++) {
        std::cout << distance[i] << " ";
    }
    std::cout << std::endl;
}

#endif
