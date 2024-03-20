#pragma once
#include <set>
#include <iostream>
#include<fstream>
#include <unordered_set>
#include <numeric>
#include <string.h>
#include <stdlib.h>
#include "miscellaneous.h"
using namespace std;

struct Node {
    Node(size_t i) { index = i; };
    size_t index;
    set<unsigned int> InNeighborhood;
    set<unsigned int> OutNeighborhood;
};


class Graph {
public:
    vector<Node> adList;
    Graph();
    Graph(int n);
    virtual void addEdge(unsigned int source, unsigned int target);
    virtual bool containEdge(unsigned int source, unsigned int target);
    void removeEdge(unsigned int source, unsigned int target);

    size_t get_edges_size();
    size_t get_vertices_size();
    void print();
    void debug();
    void output();
protected:
    bool is_planarity();
};
