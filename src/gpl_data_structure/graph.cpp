#include "graph.h"

size_t Graph::get_edges_size()
{
    size_t eSize = 0;
    for (unsigned int i = 0; i < adList.size(); i++) {
        eSize += adList[i].InNeighborhood.size();
    }
    return eSize / 2;
}
Graph::Graph() {}


Graph::Graph(int n) {
    adList.reserve(n);
    for (int i = 0; i < n; i++) {
        adList.push_back(Node(i));
    }
}




size_t Graph::get_vertices_size() {
    return adList.size();
}

void Graph::addEdge(unsigned int v1, unsigned int v2) {
    assert(v1 < adList.size());
    assert(v2 < adList.size());
    adList[v1].OutNeighborhood.insert(v2);
    adList[v2].InNeighborhood.insert(v1);
};

void Graph::removeEdge(unsigned int v1, unsigned int v2) {
    assert(v1 < adList.size());
    assert(v2 < adList.size());
    adList[v1].OutNeighborhood.erase(v2);
    adList[v2].InNeighborhood.erase(v1);

}

bool Graph::containEdge(unsigned int v1, unsigned int v2) {
    assert(v1 < adList.size());
    assert(v2 < adList.size());
    return (adList[v1].OutNeighborhood.count(v2) != 0 && adList[v2].InNeighborhood.count(v1) != 0);
};


// print adjecency list

void Graph::print() {
    size_t eSize = 0;
    for (unsigned int i = 0; i <adList.size(); i++) {
        eSize += adList[i].InNeighborhood.size();
    }
    for (unsigned int i = 0; i <adList.size(); ++i) {
        cout << i << ": " << endl;
        cout << "in: ";
        for (auto itr = adList[i].InNeighborhood.begin(); itr != adList[i].InNeighborhood.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
        cout << "out: ";
        for (auto itr = adList[i].OutNeighborhood.begin(); itr != adList[i].OutNeighborhood.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
};


void Graph::output() {

    size_t eSize = 0;
    for (unsigned int i = 0; i <adList.size(); i++) {
        eSize += adList[i].InNeighborhood.size();
    }
    for (unsigned int i = 0; i <adList.size(); ++i) {
        cout << i << ": " << endl;
        cout << "in: ";
        for (auto itr = adList[i].InNeighborhood.begin(); itr != adList[i].InNeighborhood.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
        cout << "out: ";
        for (auto itr = adList[i].OutNeighborhood.begin(); itr != adList[i].OutNeighborhood.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
}


// check vertexID<< numV
// check if no edge bidirected 

void Graph::debug() {
    set<unsigned int>::iterator it;
    for (unsigned int i = 0; i <adList.size(); i++) {
        it = adList[i].InNeighborhood.begin();
        while (it != adList[i].InNeighborhood.end()) {
            assert(!containEdge(i, *it));
            //index < numV
            assert(*it <= adList.size());
            it++;
        }
        it = adList[i].OutNeighborhood.begin();
        while (it != adList[i].OutNeighborhood.end()) {
            //undirected graph (u,v)->(v,u)
            assert(!containEdge(*it, i));
            //index < numV
            assert(*it <= adList.size());
            it++;
        }
    }
};

bool Graph::is_planarity() {
    std::set<unsigned int>::iterator it;
    std::set<unsigned int>::iterator iv;
    for (unsigned int i = 0; i < adList.size(); i++) {
        it = adList[i].InNeighborhood.begin();
        while (it != adList[i].InNeighborhood.end()) {
            for (unsigned int j = i + 1; j < adList.size(); j++) {
                iv = adList[j].InNeighborhood.begin();
                while (iv != adList[j].InNeighborhood.end()) {
                    if (find_cross(*it, i, *iv, j)) return false;
                    iv++;
                }
            }
            it++;
        }
    }

    return true;
};