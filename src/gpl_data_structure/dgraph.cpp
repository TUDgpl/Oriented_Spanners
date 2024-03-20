/*
 * graph.h
 *
 *  Created on: Sep 24, 2019
 *  Author: gpl
 *  Self-defined graph representation.
 *  Considering the extern algorithms we choose may be sensitive to the size of
 * verices, we use this way.
 *
 *
 * adapted 2021
 * remove the dynamic part
 * add vertex weights
 */
#include <cassert>
#include <cstdio>
#include <set>
#include <vector>
#include "dgraph.h"
using namespace std;


DGraph::DGraph(int n) {
    adList.reserve(n);
    for (int i = 0; i < n; i++) {
        adList.push_back(Node(i));
    }
}
void DGraph::addEdges(const vector<pair<unsigned int, unsigned int>>& edges) {
    for (int i = 0; i < edges.size(); i++) {
        addEdge(edges[i].first, edges[i].second);
    }
}
void DGraph::addEdge(unsigned int v1, unsigned int v2) {
    assert(v1 > v2 + 1);
    adList[v1].OutNeighborhood.insert(v2);
    adList[v2].InNeighborhood.insert(v1);
}
bool DGraph::containEdge(unsigned int v1, unsigned int v2) {
    assert(v1 > v2 + 1);
    return (adList[v1].OutNeighborhood.count(v2) != 0 &&
        adList[v2].InNeighborhood.count(v1) != 0);
}


RationalNumber DGraph::get_dilation(const vector<RationalNumber>& pVector) {
    size_t index_i = 0;
    size_t index_j = 0;
    RationalNumber tmax(1);
    size_t inD = 0;
    size_t outD = 0;
    size_t l = 0;
    size_t r = 0;
    int lar = -1;
    for (int i = 0; i < pVector.size() - 2; i++) {
        RationalNumber tmin(pVector.back() * 2000);
        assert(tmin > 0);
        int j = i + 2;
        // ONE COVER
        if (!adList[i].InNeighborhood.empty()) {
            l = i;
            r = *(adList[i].InNeighborhood.begin());
            tmin = min(tmin, (pVector[r] - pVector[l])/(pVector[j] - pVector[i]));
            assert(tmin > 0);
        }
        if (!adList[j].OutNeighborhood.empty()) {
            l = *(adList[j].OutNeighborhood.rbegin());
            r = j;
            tmin = min(tmin, (pVector[r] - pVector[l])/ (pVector[j] - pVector[i]));
            assert(tmin > 0);
        }
        // TWO FLIPS
        if (!adList[i + 1].OutNeighborhood.empty() &&
            !adList[i + 1].InNeighborhood.empty()) {
            l = *(adList[i + 1].OutNeighborhood.rbegin());
            r = *(adList[i + 1].InNeighborhood.begin());
            tmin = min(tmin, (pVector[r] - pVector[l])/ (pVector[j] - pVector[i]));
            assert(pVector[r] - pVector[l] > 0);
            assert(pVector[j] - pVector[i] > 0);
            assert(tmin > 0);
        }
        /*
        double  tmin_dijkstra = get_dilation_dijkstra(pVector, j, i);
        assert(abs(boost::rational_cast<double>(tmin) - tmin_dijkstra) <= epsilon);
        */
        //std::cout << "(" << i << "," << j << "), d: " << boost::rational_cast<double>(tmin) << std::endl;
        if (tmax <= tmin) {
            index_i = i;
            index_j = i + 2;
        }
        tmax = max(tmax, tmin);



    }
    for (int i = 0; i < pVector.size() - 3; i++) {
        RationalNumber tmin(pVector.back() * 2);
        assert(tmin > 0);
        int j = i + 3;
        // ONE COVER
        if (!adList[i].InNeighborhood.empty()) {
            l = i;
            for (auto itr = adList[i].InNeighborhood.begin();
                itr != adList[i].InNeighborhood.end(); itr++) {
                r = *(itr);
                if (r > i + 2) {
                    tmin = min(tmin, (pVector[r] - pVector[l])/(pVector[j] - pVector[i]));
                    break;
                }
            }
        }
        if (!adList[j].OutNeighborhood.empty()) {
            r = j;
            for (auto itr = adList[j].OutNeighborhood.rbegin();
                itr != adList[j].OutNeighborhood.rend(); itr++) {
                l = *(itr);
                if (l <= i) {
                    tmin = min(tmin, (pVector[r] - pVector[l])/(pVector[j] - pVector[i]));
                    break;
                }
            }
        }
        // TWO FLIPS- might have overlaps

        if (!adList[i + 1].OutNeighborhood.empty() &&
            !adList[i + 1].InNeighborhood.empty()) {
            l = *(adList[i + 1].OutNeighborhood.rbegin());
            r = *(adList[i + 1].InNeighborhood.begin());
            tmin = min(tmin, (pVector[r] - pVector[l])/(pVector[j] - pVector[i]));
        }
        if (!adList[i + 2].OutNeighborhood.empty() &&
            !adList[i + 2].InNeighborhood.empty()) {
            l = *(adList[i + 2].OutNeighborhood.rbegin());
            r = *(adList[i + 2].InNeighborhood.begin());
            tmin = min(tmin, (pVector[r] - pVector[l])/(pVector[j] - pVector[i]));
        }
        if (!adList[i + 2].OutNeighborhood.empty() &&
            !adList[i + 1].InNeighborhood.empty()) {
            l = *(adList[i + 2].OutNeighborhood.rbegin());
            r = *(adList[i + 1].InNeighborhood.begin());
            tmin = min(tmin, (pVector[r] - pVector[l] + pVector[i + 2] -pVector[i + 1])/
                (pVector[j] - pVector[i]));
        }
        /*
        double  tmin_dijkstra = get_dilation_dijkstra(pVector, j, i);
        assert(abs(boost::rational_cast<double>(tmin) - tmin_dijkstra) <= epsilon);
        */
        //std::cout << "(" << i << "," << j << "), d: " << boost::rational_cast<double>(tmin) << std::endl;
        if (tmax <= tmin) {
            index_i = i;
            index_j = i + 3;
        }
        tmax = max(tmax, tmin);
    }
    std::cout << "(" << index_i << "," << index_j << ")" << std::endl;
    return tmax;
};

int DGraph::minDistance(const vector<RationalNumber>& pVector, const vector<double>& dist,
    const vector<bool>& processed) {
    // Initialize min value
    double min = 2 * boost::rational_cast<double>(pVector.back());
    int min_index = -1;

    for (int v = 0; v < pVector.size(); v++)
        if (processed[v] == false && dist[v] <= min) min = dist[v], min_index = v;

    return min_index;
}
double DGraph::get_shortest_path_complete(const vector<RationalNumber>& pVector, size_t s,
    size_t t) {
    if (s > t) swap(s, t);
    if (t > s + 1) return 2 * boost::rational_cast<double>((pVector[t] - pVector[s]));
    // searching for the nearst point
    else {
        double prev = -2* boost::rational_cast<double>(pVector.back());
        double suss = 2 * boost::rational_cast<double>(pVector.back());
        if (s > 0) prev = boost::rational_cast<double>(pVector[s - 1]);
        if (t < pVector.size() - 1) suss = boost::rational_cast<double>(pVector[t + 1]);
        double dis = boost::rational_cast<double>(pVector[s]) - prev;
        if (dis > suss - boost::rational_cast<double>(pVector[t])) dis = suss - boost::rational_cast<double>(pVector[t]);
        assert(boost::rational_cast<double>(pVector[t] - pVector[s]) + dis > 0);
        return 2 * (boost::rational_cast<double>(pVector[t] - pVector[s]) + dis);
    }
}

double DGraph::get_dilation_dijkstra(const vector<RationalNumber>& pVector, size_t src, size_t target) {
    size_t V = pVector.size();
    vector<double> dist;
    vector<bool> processed;
    double MAX = boost::rational_cast<double>(pVector.back()) * 2;
    assert(MAX > 0);
    for (int i = 0; i < V; i++) {
        dist.push_back(MAX);
        processed.push_back(false);
    }
    dist[src] = 0;
    for (int count = 0; count < V; count++) {
        int u = minDistance(pVector, dist, processed);
        processed[u] = true;
        for (size_t v = 0; v < V; v++) {
            assert(boost::rational_cast<double>(abs(pVector[u] - pVector[v])) >= 0);
            assert(dist[u] + boost::rational_cast<double>(abs(pVector[u] - pVector[v])) >= 0);
            if (!processed[v] && (adList[u].OutNeighborhood.count(v) || u < v) &&
                dist[u] != MAX &&
                dist[u] + boost::rational_cast<double>(abs(pVector[u] - pVector[v])) <
                dist[v]) {
                dist[v] = dist[u] + boost::rational_cast<double>(abs(pVector[u] - pVector[v]));
            }
        }
    }
    double od = 0;
   
    // coumpute od
    od = (dist[target] + boost::rational_cast<double>((pVector[src] - pVector[target]))) /
        get_shortest_path_complete(pVector, src, target);
    assert(od <= boost::rational_cast<double>(pVector[V - 1] - pVector[0] + 1));

    assert (od- 1 >-epsilon);
    // assert(tmax <= pVector[end_index]- pVector[start_index] + 1);
    return od;
}

double DGraph::get_dilation_dijkstra(const vector<RationalNumber>& pVector, size_t src) {
    size_t V = pVector.size();
    double tmax = 1;
    double od = 0;
    for (int i = 0; i < src; i++) {
        // coumpute od
        od = get_dilation_dijkstra(pVector, src, i);
        assert(od <= boost::rational_cast<double>(pVector[V - 1] - pVector[0] + 1));
        tmax = max(tmax, od);
    }
    assert(tmax >= 1);
    // assert(tmax <= pVector[end_index]- pVector[start_index] + 1);
    return tmax;
}

double DGraph::get_dilation_dijkstra(const vector<RationalNumber>& pVector) {
    double tmax = 0;
    double od = 0;
    for (int i = 0; i < pVector.size(); i++) {
        od = get_dilation_dijkstra(pVector, i);
        tmax = std::max(tmax, od);
    }
    return tmax;
}

void DGraph::draw_tikz(double range, std::string path, const vector<RationalNumber>& pVector, std::string optional_parameters = "every node / .append style = { draw, circle }, rotate = 90")
{
    uint64_t num_nodes = pVector.size();
    std::ofstream o(path);

    // Enviroment

    o << "\\documentclass{article}"<<endl;
    o << "\\usepackage{tikz}" << endl;
    o << "\\begin{document}" << endl;
    o << "\\begin{tikzpicture}[";
    o << optional_parameters;
    o << "]" << std::endl;


    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (int i = 0; i < num_nodes; ++i) {
        o << "\\node[] at (" << boost::rational_cast<double>(pVector[i])/range << "," << 0 << ") (" << i << ") {} ;" << std::endl;
    }
                    
    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)
    for (int i = 0; i < num_nodes; ++i) {
        for (auto& itr:  adList[i].OutNeighborhood) {
            o << "\\draw (" << i << ") edge";
            o << "[bend right]";
            o << " (" << itr << ");" << std::endl;
        }
    }
    for (int i = 0; i < num_nodes-1; ++i) {
        o << "\\draw (" << i << ") edge";
        o << " (" << i+1 << ");" << std::endl;
    }
    // END of File
    o << "  \\end{tikzpicture}\n";
    o << "  \\end{document}\n";
    o.close();
}


void DGraph::get_longest_edge(const vector<RationalNumber>& pVector) {
    uint64_t num_nodes = pVector.size();
    size_t max_len = 1;
    int index_s = -1;
    int index_t = -1;
    for (int i = 0; i < num_nodes; ++i) {
        for (auto& itr : adList[i].OutNeighborhood) {
            int dis = itr - i;
            size_t l = std::abs(dis);
            if (l > max_len) {
                max_len = l;
                index_s = i;
                index_t = itr;
            }
        }
    }
    std::cout << "The longest edge: (" << index_s << ", " << index_t <<") with length: "<< max_len<< std::endl;
};
