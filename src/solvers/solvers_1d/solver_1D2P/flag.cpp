#include "sat1D2P.h"
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
void Sat2P:: write_clauses_2(vector<pair<unsigned int, unsigned int>>& candidate_edges, int C, ofstream& outdata, RationalNumber test_v) {
    for (unsigned int i = 0; i < pVector.size() - 2; i++) {
        unsigned int j = i + 2;
        RationalNumber maxD = test_v * (pVector[j] - pVector[i]);
        assert(maxD.numerator() > 0);
        assert(maxD.denominator() > 0);
        // c1
        outdata << decode(j, i, 0, base) << " " << decode(j, i, 1, base) << " ";
        candidate_edges.push_back(pair<unsigned int, unsigned int>(j, i));
        // c2
        for (int l = i - 1; l >= 0; l--) {
            if (pVector[j] - pVector[l] <= maxD) {
                outdata << decode(j, l, 0, base) << " " << decode(j, l, 1, base) << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(j, l));
            }
            else
                break;
        }
        // c3
        for (int r = j + 1; r < pVector.size(); r++) {
            if (pVector[r] - pVector[i] <= maxD) {
                outdata << decode(r, i, 0, base) << " " << decode(r, i, 1, base) << " ";
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
                << " "
                << decode(i + 1, candidates_ende_pairs[index].first, 1, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                i + 1, candidates_ende_pairs[index].first));
            outdata << -C_start << " "
                << decode(candidates_ende_pairs[index].second, i + 1, 0, base)
                << " "
                << decode(candidates_ende_pairs[index].second, i + 1, 1, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                candidates_ende_pairs[index].second, i + 1));
            C_start++;
        }
    }
}

void Sat2P::write_clauses_3(vector<pair<unsigned int, unsigned int>>& candidate_edges,
    int C, ofstream& outdata, RationalNumber test_v) {
    //  consider all pairs <i, i+3>
    /*
    c1 or c2 or c3 or c41 or c42 or c43
    c1: just (i, i+3)
    c2: left (l,i+3), l < i
    c3: right (i, r), r > i+3
    c41: cut va:(l,i+1) and vb:(i+1, r), l < i and r > i+2
    c42: cut va:(l,i+2) and vb:(i+2, r), l < i+1 and r > i+3
    c43: cut va:(l,i+2) and vb:(i+1, r), l < i+1 and r > i+2
    */
    for (unsigned int i = 0; i < pVector.size() - 3; i++) {
        unsigned j = i + 3;
        RationalNumber maxD = test_v * (pVector[j] - pVector[i]);
        // c1
        outdata << decode(j, i, 0, base) << " " << decode(j, i, 1, base) << " ";
        candidate_edges.push_back(pair<unsigned int, unsigned int>(j, i));
        // c2
        for (int l = i - 1; l >= 0; l--) {
            if (pVector[j] - pVector[l] <= maxD) {
                outdata << decode(j, l, 0, base) << " " << decode(j, l, 1, base) << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(j, l));
            }
            else
                break;
        }
        // c3
        for (int r = j + 1; r < pVector.size(); r++) {
            if (pVector[r] - pVector[i] <= maxD) {
                outdata << decode(r, i, 0, base) << " " << decode(r, i, 1, base) << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(r, i));
            }
            else
                break;
        }
        // c4
        vector<bool> candidates_ende_pairs_valid_c43;
        vector<pair<unsigned int, unsigned int>> candidates_ende_pairs;
        int C_start = C;
        for (int l = i; l >= 0; l--) {
            if (pVector[j] - pVector[l] > maxD) break;
            for (unsigned int r = j; r < pVector.size(); r++) {
                if (pVector[r] - pVector[l] <= maxD) {
                    // for c41
                    if (l < i) {
                        outdata << C << " ";
                        C++;
                    }
                    // for c42
                    if (r > j) {
                        outdata << C << " ";
                        C++;
                    }
                    candidates_ende_pairs.push_back(
                        pair<unsigned int, unsigned int>(l, r));
                    // for c43
                    if (pVector[r] - pVector[l] + pVector[i + 2] - pVector[i + 1] <=
                        maxD) {
                        candidates_ende_pairs_valid_c43.push_back(true);
                        outdata << C << " ";
                        C++;
                    }
                    else {
                        candidates_ende_pairs_valid_c43.push_back(false);
                    }
                }
                else {
                    break;
                }
            }
        }
        outdata << "0" << std::endl;
        // add c4 clauses
        for (int index = 0; index < candidates_ende_pairs.size(); index++) {
            // c41
            if (candidates_ende_pairs[index].first < i) {
                outdata << -C_start << " "
                    << decode(i + 1, candidates_ende_pairs[index].first, 0, base)
                    << " "
                    << decode(i + 1, candidates_ende_pairs[index].first, 1, base)
                    << " 0" << endl;
                candidate_edges.push_back(pair<unsigned int, unsigned int>(
                    i + 1, candidates_ende_pairs[index].first));
                outdata << -C_start << " "
                    << decode(candidates_ende_pairs[index].second, i + 1, 0, base)
                    << " "
                    << decode(candidates_ende_pairs[index].second, i + 1, 1, base)
                    << " 0" << endl;
                candidate_edges.push_back(pair<unsigned int, unsigned int>(
                    candidates_ende_pairs[index].second, i + 1));
                C_start++;
            }
            // c42
            if (candidates_ende_pairs[index].second > j) {
                outdata << -C_start << " "
                    << decode(i + 2, candidates_ende_pairs[index].first, 0, base)
                    << " "
                    << decode(i + 2, candidates_ende_pairs[index].first, 1, base)
                    << " 0" << endl;
                candidate_edges.push_back(pair<unsigned int, unsigned int>(
                    i + 2, candidates_ende_pairs[index].first));
                outdata << -C_start << " "
                    << decode(candidates_ende_pairs[index].second, i + 2, 0, base)
                    << " "
                    << decode(candidates_ende_pairs[index].second, i + 2, 1, base)
                    << " 0" << endl;
                candidate_edges.push_back(pair<unsigned int, unsigned int>(
                    candidates_ende_pairs[index].second, i + 2));
                C_start++;
            }
            // c3
            if (candidates_ende_pairs_valid_c43[index] == true) {
                outdata << -C_start << " "
                    << decode(i + 2, candidates_ende_pairs[index].first, 0, base)
                    << " "
                    << decode(i + 2, candidates_ende_pairs[index].first, 1, base)
                    << " 0" << endl;
                candidate_edges.push_back(pair<unsigned int, unsigned int>(
                    i + 2, candidates_ende_pairs[index].first));

                outdata << -C_start << " "
                    << decode(candidates_ende_pairs[index].second, i + 1, 0, base)
                    << " "
                    << decode(candidates_ende_pairs[index].second, i + 1, 1, base)
                    << " 0" << endl;

                candidate_edges.push_back(pair<unsigned int, unsigned int>(
                    candidates_ende_pairs[index].second, i + 1));
                C_start++;
            }
        }
    }
}
void Sat2P::write_solver_input(bool only_short, RationalNumber test_v, int test_len) {
    ofstream outdata;
    int count = 0;
    assert(test_v.numerator() > 0);
    assert(test_v.denominator() > 0);
    string filename = tmp_dictionary + "/" + Input_file_name + +"_" +
        to_string(test_v) + "_DIMACS.txt";

    if (only_short)
        filename = tmp_dictionary + "/" + Input_file_name + +"_" + to_string(test_v) +
        "_DIMACS_short.txt";

    outdata.open(filename.c_str());
    if (!outdata) {
        // file couldn't be opened
        cerr << filename << " Error: (write_solver_input) file could not be opened"
            << endl;
        exit(1);
    }
    outdata << "c  SAT for 1D 1PPB  " << filename << endl;
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
    int C = 2 * pVector.size() * pVector.size() + 2;
    base = pVector.size();

    vector<pair<unsigned int, unsigned int>> candidate_edges;
    write_clauses_2( candidate_edges,  C, outdata, test_v);
    write_clauses_3(candidate_edges, C, outdata, test_v);

    // Todo: first write all candidate clauses (store all edges into a vector
    // edges)
    //       write conflict clauses of crossing edges
    // if edges x and y have crossing --> (not x1) or (not x2) or (not y0) or (not
    // y1)
    for (int i = 0; i < candidate_edges.size(); i++) {
        for (int j = i + 1; j < candidate_edges.size(); j++) {
            if (find_cross(candidate_edges[i], candidate_edges[j])) {
                outdata << -(int)decode(candidate_edges[i].first, candidate_edges[i].second,
                    0, base)
                    << " "
                    << -(int)decode(candidate_edges[j].first, candidate_edges[j].second,
                        0, base)
                    << " 0" << endl;

                outdata << -(int)decode(candidate_edges[i].first, candidate_edges[i].second,
                    1, base)
                    << " "
                    << -(int)decode(candidate_edges[j].first, candidate_edges[j].second,
                        1, base)
                    << " 0" << endl;
            }
        }
    }
    // if only short is allowed, deactivate all long edges
    if (only_short) {
        for (int i = 0; i < candidate_edges.size(); i++) {
            if (candidate_edges[i].first - candidate_edges[i].second >= test_len) {
                outdata << -(int)decode(candidate_edges[i].first, candidate_edges[i].second,
                    0, base) << " 0" << endl;
                outdata << -(int)decode(candidate_edges[i].first, candidate_edges[i].second,
                    1, base) << " 0" << endl;
            }
        }
    }

    outdata << flush;
    outdata.close();
}

RationalNumber Sat2P::read_solution(bool only_short, RationalNumber test_v) {
    string file_d =
        tmp_dictionary + "/" + Input_file_name + +"_" + to_string(test_v);
    string solution_d = file_d + "_DIMACS_solution.txt";
    if (only_short) solution_d = file_d + "_DIMACS_solution_short.txt";
    ifstream solution_file;
    solution_file.open(solution_d.c_str());
    if (!solution_file) {
        // file couldn't be opened
        cerr << "Error: solution file could not be opened" << endl;
        cerr << "Error:" << solution_d << endl;
        exit(1);
    }
    string line;
    char head;
    int i;
    getline(solution_file, line);
    if (!line.compare("UNSAT")) {
        // 's' and 't' are equal.
        return -1;
    }
    solution_indices.clear();
    char* str = line.data();
    const char s[2] = " ";
    char* token = strtok(str, s);
    int index_MAX = pVector.size() * pVector.size() + (pVector.size() - 1) * pVector.size() + (pVector.size() - 1);
    int index = 0;
    while (token != NULL && index < index_MAX) {
        i = atoi(token);
        index++;
        if (i > 0) {
            // Todo: how to know if it is satisfiing and how to encode the index as
            // tripe
            solution_indices.push_back(i);
        }
        token = strtok(NULL, s);
    }
    solution_file.close();
    if (remove(solution_d.c_str()) != 0)
        perror("Error deleting solution file");
    
    set_pages();
    RationalNumber od = solution.get_dilation(pVector);
    std::cout << "get dilation: " << od << std::endl;
    return od;
};

RationalNumber Sat2P::sat_solve(bool only_short, RationalNumber test_v, int test_len) {
    // remove the datas
    string file_d =
        tmp_dictionary + "/" + Input_file_name + +"_" + to_string(test_v);
    write_solver_input(only_short, test_v, test_len);
    string o = sat_solver_PATH + file_d + "_DIMACS.txt " + file_d +
        "_DIMACS_solution.txt" + "> NUL 2>&1";
    if (only_short) o = sat_solver_PATH + file_d + "_DIMACS_short.txt " + file_d +
        "_DIMACS_solution_short.txt" + "> NUL 2>&1";
    int success = system(o.c_str());
    string instance_f = file_d + "_DIMACS.txt";
    if (only_short)instance_f = file_d + "_DIMACS_short.txt";
  
    if (remove(instance_f.c_str()) != 0)
      perror("Error deleting instance file");
  
  return read_solution(only_short, test_v);
}
vector<RationalNumber> Sat2P::get_candidate() {
    std::set<RationalNumber> candidate_ods;
    for (int i = 0; i < pVector.size() - 2; i++) {
        // consider all pairs <i, i+2>
        int j = i + 2;
        RationalNumber sp = pVector[j] - pVector[i];
        for (int k = 0; k <= i; k++) {
            for (int m = j; m < pVector.size(); m++) {
                RationalNumber sc = pVector[m] - pVector[k];
                RationalNumber q = sc / sp;
                assert(q.numerator() > 0 && q.denominator() > 0);
                if (sc / sp <= teo_g) candidate_ods.insert(sc / sp);
            }
        }
    }
    for (int i = 0; i < pVector.size() - 3; i++) {
        // consider all pairs <i, i+3>
        int j = i + 3;
        RationalNumber sp = pVector[j] - pVector[i];
        RationalNumber rp = pVector[i + 2] - pVector[i + 1];
        for (int k = 0; k <= i; k++) {
            for (int m = j; m < pVector.size(); m++) {
                RationalNumber sc = pVector[m] - pVector[k];
                if (sc / sp <= teo_g) {
                    RationalNumber q = sc / sp;
                    assert(q.numerator() > 0 && q.denominator() > 0);
                    candidate_ods.insert(sc / sp);
                }
                if ((sc + rp) / sp <= teo_g) {
                    RationalNumber q = (sc + rp) / sp;
                    assert(q.numerator() > 0 && q.denominator() > 0);
                    candidate_ods.insert((sc + rp) / sp);
                }
            }
        }
    }
    vector<RationalNumber> vc(candidate_ods.begin(), candidate_ods.end());
    return vc;
}


RationalNumber Sat2P::solve() {
    vector<RationalNumber> candidate_ods = get_candidate();
    int l = 0;
    int r = candidate_ods.size() - 1;
    RationalNumber best_od = 2;
    while (r >= l) {
        int mid = l + (r - l) / 2;
        assert(candidate_ods[mid].numerator() > 0);
        assert(candidate_ods[mid].denominator() > 0);
        RationalNumber found_od = sat_solve(short_edges_only_flag, candidate_ods[mid], long_edge_length);
        if (found_od > 0) {
            r = mid - 1;
            best_od = candidate_ods[mid];
        }
        else {
            l = mid + 1;
        }
    }
    assert(best_od <= teo_g);
    printf("Sat2P solved with %lld, %lld", best_od.numerator(),best_od.denominator());
    set_pages();
    return best_od;
}

void Sat2P::sat_debug(RationalNumber test_v) {
    RationalNumber od = solution.get_dilation(pVector);
    assert(od <= test_v);
}

// test if it requires long edges.
bool Sat2P::conjecture_check( RationalNumber& best, RationalNumber& best_short, int test_len) {
    vector<RationalNumber> candidate_ods = get_candidate();
    int l = 0;
    int r = candidate_ods.size() - 1;
    int mid = 0;
    while (r >= l) {
        mid = l + (r - l) / 2;
        if (candidate_ods[mid] >= best) {
            r = mid - 1;
            continue;
        }
        RationalNumber found = sat_solve(false, candidate_ods[mid], test_len);
        assert(found < best);
        bool found_value = false;
        if (found > 0) {
            for (int i = 0; i < candidate_ods.size(); i++) {
                if (candidate_ods[i] == found) {
                    found_value = true;
                }
            }
            assert(found_value);
        }
        //check if "found" can be computed
        //  
        if (found > 0) {
            RationalNumber checked_found = sat_solve(false, found, test_len);
            if (checked_found <= 0) {
                std::cout <<"check the files: "<< to_string(found)
                    <<" "<< to_string(candidate_ods[mid]) << std::endl;
            }
            assert(checked_found > 0);
        }
        assert(found < 0 || found_value);
        cout<< "best dilation <=" << to_string(candidate_ods[mid]) <<": " << to_string(found) << endl;
        if (found > 0) {
            best = found;
            RationalNumber found_short = sat_solve(true, found, test_len);
            bool found_value_short = false;
            for (int i = 0; i < candidate_ods.size(); i++) {
                if (candidate_ods[i] == found) found_value_short = true;
            }
            assert(found_short < 0 || found_value_short);
            cout << "short best dilation <=" << to_string(found) << ": " << to_string(found_short) << endl;
            if (found_short < 0) {
                cout<<"This is a conter - example with "<< to_string(candidate_ods[mid])<< endl;
                return true;
            }
            else {
                best = min(best, found_short);
                best_short = min(best_short, found_short);
            }
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    assert(best == best_short);
    return false;
}
