#pragma once
using namespace std;
#include <cmath>
#include "solver_1D.h"
#include "miscellaneous.h"
#include <list>
#include "dgraph.h"
#include <set>


class Solver_1D1P:public Solver_1D{
public:
	Solver_1D1P() {};
	void output(RationalNumber od) override;
	void outputMeasures() override;
	virtual void say_hello() { printf("Run Solver_1D1P"); };
	void draw_tikz(double range, std::string path, std::string optional_parameters) override;
	void draw_ipe(std::string path) override;
	bool is_planarity() override;

private:
};