#include "miscellaneous_exaction.h"
// write back file
void writeFile(){




}
// 

// hhelp-methods (cut// fix)
void exact(int argc, char* argv[]) {
	parseInitOptions(argc, argv);
	Sat2P S;
	S.readFile();
	RationalNumber best(2, 1);
	RationalNumber best_short(2, 1);
	int test_len = 4;
	// only using edge length < test_len
	bool conter_found = S.conjecture_check(best, best_short, test_len);
	if (conter_found) {
		printf("counterexample for edge length limit %i ,(%f, %f)", test_len, boost::rational_cast<double>(best), boost::rational_cast<double>(best_short));
	}
	else {
		assert(best == best_short);
		printf("%f, SHORT", boost::rational_cast<double>(best));
	}
};







void long_edge_test(int argc, char* argv[]) {
	parseInitOptions(argc, argv);
	Sat2P S;
	S.readFile();
	RationalNumber best(2, 1);
	RationalNumber best_short(2, 1);
	int test_len = 4;
	// only using edge length < test_len
	bool conter_found = S.conjecture_check(best, best_short, test_len);
	if (conter_found) {
		printf("counterexample for edge length limit %i ,(%f, %f)", test_len, boost::rational_cast<double>(best), boost::rational_cast<double>(best_short));
	}
	else {
		assert(best == best_short);
		printf("%f, SHORT", boost::rational_cast<double>(best));
	}
};
