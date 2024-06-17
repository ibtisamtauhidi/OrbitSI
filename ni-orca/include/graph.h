#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Graph {
    std::vector<int> vertex_labels;
    std::vector<int> vertex_degrees;
    std::vector<std::vector<int>> adjacency_list;
};

Graph readGraph(const char* file_name);
void formatVF3(Graph graph);
void preProcess(Graph graph);
void printGraph(Graph graph);

#endif /* GRAPH_H */

