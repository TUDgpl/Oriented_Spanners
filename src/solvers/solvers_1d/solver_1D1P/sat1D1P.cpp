#include "sat1D1P.h"
using namespace std;
// binary search

/*
(i, i+2)
c1 or c2 or c3 or c4
c1: just (i, i+2)
c2: left (l,i+2), l < i
c3: right (i, r), r > i+2
c4: cut va:(l,i+1) and vb:(i+1, r), l < i and r > i+2
*/
void Sat1P::write_clauses_2(vector<pair<unsigned int, unsigned int>>& candidate_edges, int C, ofstream& outdata, RationalNumber test_v) {
    for (unsigned int i = 0; i < pVector.size() - 2; i++) {
        unsigned int j = i + 2;
        RationalNumber maxD = test_v * (pVector[j] - pVector[i]);
        // c1
        outdata << decode(j, i, 0, base) << " ";
        candidate_edges.push_back(pair<unsigned int, unsigned int>(j, i));
        // c2
        for (int l = i - 1; l >= 0; l--) {
            if (pVector[j] - pVector[l] <= maxD) {
                outdata << decode(j, l, 0, base)  << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(j, l));
            }
            else
                break;
        }
        // c3
        for (int r = j + 1; r < pVector.size(); r++) {
            if (pVector[r] - pVector[i] <= maxD) {
                outdata << decode(r, i, 0, base)  << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(r, i));
            }
            else
                break;
        }
        // c4
        vector<pair<unsigned int, unsigned int>> candidates_ende_pairs;
        int C_start = C;
        // collect all the c4s
        for (int l = i - 1; l >= 0; l--) {
            if (pVector[j] - pVector[l] > maxD) {
                break;
            }
            for (unsigned int r = j + 1; r < pVector.size(); r++) {
                if (pVector[r] - pVector[l] <= maxD) {
                    outdata << C << " ";
                    C++;
                    candidates_ende_pairs.push_back(
                        pair<unsigned int, unsigned int>(l, r));
                }
                else {
                    break;
                }
            }
        }
        outdata << "0" << std::endl;
        // add c4 clauses
        for (int index = 0; index < candidates_ende_pairs.size(); index++) {
            outdata << -C_start << " "
                << decode(i + 1, candidates_ende_pairs[index].first, 0, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                i + 1, candidates_ende_pairs[index].first));
            outdata << -C_start << " "
                << decode(candidates_ende_pairs[index].second, i + 1, 0, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                candidates_ende_pairs[index].second, i + 1));
            C_start++;
        }
    }
}

void Sat1P::write_solver_input(RationalNumber test_v) {
    ofstream outdata;
    int count = 0;
    outdata.open(instance_f.c_str());
    if (!outdata) {
        // file couldn't be opened
        cerr << instance_f << " Error: (write_solver_input) file could not be opened"
            << endl;
        exit(1);
    }
    outdata << "c  SAT for 1D 1PPB  " << instance_f << endl;
    outdata << std::setprecision(0);
    vector<pair<unsigned int, unsigned int>> edges;
    // Todo: write candidate clauses
    //  consider all pairs <i, i+2>
    // cut edge
    /*not v_S(c4) or v_1a or v2a --- put va and vb to the edge sets
      not v_S or v_1b or v2b
      for each c4, S++;
    */
    //// tuple(a,b,c) -----> edge (a,b) on page c
    int C =  pVector.size() * pVector.size() + 2;
    base = pVector.size();

    vector<pair<unsigned int, unsigned int>> candidate_edges;
    write_clauses_2(candidate_edges, C, outdata, test_v);

    // Todo: first write all candidate clauses (store all edges into a vector
    // edges)
    //       write conflict clauses of crossing edges
    // if edges x and y have crossing --> (not x1) or (not x2) or (not y0) or (not
    // y1)
    for (int i = 0; i < candidate_edges.size(); i++) {
        for (int j = i + 1; j < candidate_edges.size(); j++) {
            if (find_cross(candidate_edges[i], candidate_edges[j])) {
                outdata << -decode(candidate_edges[i].first, candidate_edges[i].second,
                    0, base)
                    << " "
                    << -decode(candidate_edges[j].first, candidate_edges[j].second,
                        0, base)
                    << " 0" << endl;
            }
        }
    }

    outdata << flush;
    outdata.close();
}
// Todo: check if it is a valid solution
//      check if it is crossing-free
//      compute the dilation (<= test_v)

//// tuple(a,b,c) -----> edge (a,b) on page c
void Sat1P::verify(const vector<unsigned int>& solution_indices, RationalNumber test_v) {
    vector<pair<unsigned int, unsigned int>> page_0;
    unsigned int base = pVector.size();
    for (int i = 0; i < solution_indices.size(); i++) {
        tuple<unsigned int, unsigned int, unsigned int> index =
            encode(solution_indices[i], base);
        if (get<2>(index) == 0) {
            page_0.push_back(
                pair<unsigned int, unsigned int>(get<0>(index), get<1>(index)));
        }
    }
    // planarity check
    assert(is_planar(page_0));
    // compute dilation and check if it is <= test_v
    // set up the graph
    solution = DGraph(pVector.size());
    solution.addEdges(page_0);
    RationalNumber od = solution.get_dilation(pVector);
    assert(od <= test_v);
}
bool Sat1P::read_solution(RationalNumber test_v) {
    vector<unsigned int> solution_indices;
    ifstream solution_file;
    solution_file.open(solution_f.c_str());
    if (!solution_file) {
        // file couldn't be opened
        cerr << "Error: solution file could not be opened" << endl;
        cerr << "Error:" << solution_f << endl;
        exit(1);
    }
    string line;
    char head;
    int i;
    getline(solution_file, line);
    if (!line.compare("UNSAT")) {
        // 's' and 't' are equal.
        return false;
    }
    char* str = strdup(line.c_str());
    const char s[2] = " ";
    char* token = strtok(str, s);
    while (token != NULL) {
        i = atoi(token);
        if (i > 0) {
            // Todo: how to know if it is satisfiing and how to encode the index as
            // tripe
            solution_indices.push_back(i);
        }
        token = strtok(NULL, s);
    }
    solution_file.close();
    verify(solution_indices, test_v);
    return true;
};


bool Sat1P::sat_solve(bool only_short, RationalNumber test_v) {
    // remove the datas
    write_solver_input(test_v);
    string o = sat_solver_PATH + " "+ instance_f + " " +solution_f + "> NUL 2>&1";;
    int success = system(o.c_str());
    return read_solution(test_v);
}
vector<RationalNumber> Sat1P::get_candidate() {
    std::set<RationalNumber> candidate_ods;
    for (int i = 0; i < pVector.size() - 2; i++) {
        // consider all pairs <i, i+2>
        int j = i + 2;
        RationalNumber sp = pVector[j] - pVector[i];
        for (int k = 0; k <= i; k++) {
            for (int m = j; m < pVector.size(); m++) {
                RationalNumber sc = pVector[m] - pVector[k];
                if (sc / sp <= teo_g) candidate_ods.insert(sc / sp);
            }
        }
    }
    vector<RationalNumber> vc(candidate_ods.begin(), candidate_ods.end());
    return vc;
}


RationalNumber Sat1P::solve() {
    vector<RationalNumber> candidate_ods = get_candidate();
    int l = 0;
    int r = candidate_ods.size() - 1;
    RationalNumber best_od = teo_g;
    while (r >= l) {
        int mid = l + (r - l) / 2;
        string file_d = tmp_dictionary + "/" + Input_file_name + "_" + to_string(candidate_ods[mid]);
        if (short_edges_only_flag) {
            file_d += "_short_" + to_string(long_edge_length);
        }
        instance_f = file_d + "_sat1_DIMACS.txt";
        solution_f = file_d + "_sat1_DIMACS_solution.txt";

        bool found = sat_solve( false, candidate_ods[mid]);
        if (found) {
            best_od = candidate_ods[mid];
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    assert(best_od <= teo_g);
    printf("Sat1P solved with dilation %lld, %lld. \n", best_od.numerator(),best_od.denominator());
    return best_od;
}


