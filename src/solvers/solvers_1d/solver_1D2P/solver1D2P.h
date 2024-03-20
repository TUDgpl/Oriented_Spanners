#pragma once
using namespace std;
#include <cmath>
#include "solver_1D.h"
#include "miscellaneous.h"
#include <list>
#include "dgraph.h"
#include <set>


class Solver_1D2P :public Solver_1D {
public:
	Solver_1D2P() {};
	virtual void say_hello() { printf("Run Solver_1D2P"); };

	void output(RationalNumber od) override;
	void outputMeasures() override;


	void draw_tikz(double range, std::string path, std::string optional_parameters) override;
	void draw_ipe(std::string path) override;
	bool is_planarity() override;
	vector<unsigned int> solution_indices;
	vector<pair<unsigned int, unsigned int>> page_0;
	vector<pair<unsigned int, unsigned int>> page_1;
	unsigned int base = 0;
	void set_pages();
	RationalNumber teo_g = 2;
	void set(size_t point_size) override;
};