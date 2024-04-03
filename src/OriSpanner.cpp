// OriSpanner.cpp : Defines the entry point for the application.
//
#include "OriSpanner.h"
#include <filesystem>
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
template <typename SolverT>
void solve() {
	SolverT solver = new SolverT() ;
	solver.set();
	solver.solve();
};
/*
int main(int argc, char* argv[]) {
	parseInitOptions(argc, argv);
	Sat2P S;
	if (Input_file_s.empty()) S.readIPE();
	else S.readFile();
	//S.print();
	// set solver
	if (true) {
		RationalNumber od = S.solve();
		S.debug();
		S.output(od);
		measures.addElement("info", "solver", "DP");
		measures.addElement("performance", "dilation", to_string(boost::rational_cast<double>(od)));
		S.outputMeasures();
		outputMeasure("dp.json");
		S.draw();
	}
}
*/
template <typename Solver_T>
void test_solver(){
	Solver_T S;
	if (Input_file_s.empty()) S.readIPE();
	else S.readFile();
	//S.print();
	// set solver
	if (true) {
		RationalNumber od = S.solve();
		S.debug();
		S.output(od);
		measures.addElement("info", "solver", Algo_t);
		measures.addElement("performance", "dilation", to_string(od));
		S.outputMeasures();
		outputMeasure(".json");
		S.draw();
	}
}

int main(int argc, char* argv[]) {
	parseInitOptions(argc, argv);
	if (Algo_t.compare("dp") == 0)
	{
		test_solver<DP>();
		return 0;
	}
	if (Algo_t.compare("sat") == 0)
	{
		test_solver<Sat2P>();
		return 0;
	}
	if (Algo_t.compare("sat1") == 0)
	{
		test_solver<Sat1P>();
		return 0;
	}
	cerr << " Error: algorithm type "<<Algo_t << " can not be recognized " << endl;
	printInitUsage();
	exit(1);
	return -1;
}


/*
int main(int argc, char* argv[]) {
for (const auto& dirEntry : recursive_directory_iterator(myPath))
	 std::cout << dirEntry << std::endl;




}
*/
