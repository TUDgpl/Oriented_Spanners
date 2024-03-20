#pragma once
#include <assert.h>
#pragma once
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <cassert>
#include <iomanip>
#include <iostream>
#include <istream>
#include <set>
#include <string>
#include <vector>
#include "solver1D2P.h"
#include "dgraph.h"
// binary search


class Sat2P :public Solver_1D2P {
public:
    RationalNumber solve() override;
    int base;
    bool conjecture_check( RationalNumber& best, RationalNumber& best_short, int test_len);
protected:
    vector<RationalNumber> get_candidate();
    RationalNumber sat_solve( bool only_short, RationalNumber test_v, int test_len);
    RationalNumber read_solution(bool only_short, RationalNumber test_v);
    void write_solver_input(bool only_short, RationalNumber test_v, int test_len);
private:
    string instance_f;
    string solution_f;
    void write_clauses_2(vector<pair<unsigned int, unsigned int>>& candidate_edges,
        int C, ofstream& outdata,  RationalNumber test_v);
    void write_clauses_3(vector<pair<unsigned int, unsigned int>>& candidate_edges,
        int C, ofstream& outdata, RationalNumber test_v);
    void sat_debug(RationalNumber test_v);


};