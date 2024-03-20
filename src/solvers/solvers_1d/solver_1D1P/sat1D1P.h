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
#include "solver1D1P.h"
#include "dgraph.h"
// binary search


class Sat1P :public Solver_1D1P {
public:
    RationalNumber solve() override;
    const string Input_file_s;
    int base;

protected:
    vector<RationalNumber> get_candidate();
    bool sat_solve(bool only_short, RationalNumber test_v);
    bool read_solution(RationalNumber test_v);
    void write_solver_input(RationalNumber test_v);
private:
    string instance_f;
    string solution_f;
    void write_clauses_2(vector<pair<unsigned int, unsigned int>>& candidate_edges,
        int C, ofstream& outdata, RationalNumber test_v);
    void verify(const vector<unsigned int>& solution_indices, RationalNumber test_v);
};