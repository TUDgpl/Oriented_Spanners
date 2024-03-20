#include "solver_1D.h"
#include <algorithm>
// read input form an IPE file
//write the input points into a standard DIMACS file
void Solver_1D::readIPE() {
	ifstream fp;
	fp.open(input_ipe_s, std::ios::in);
	if (!fp.is_open()) {
		std::cout << Input_file_s << std::endl;
		perror("read file fails");
		exit(EXIT_FAILURE);
	}

	string buff;
	string s = "pos";
	char const* digits = "0123456789";
	getline(fp, buff);
	while (!fp.eof()) {
		if (buff.find(s) != std::string::npos) {

			std::size_t const n = buff.find_first_of(digits);
			if (n != std::string::npos)
			{
				std::size_t const m = buff.find_first_not_of(digits, n);
				string number = buff.substr(n, m != std::string::npos ? m - n : m);
				pVector.push_back(atoR(strdup(number.c_str())));
			}
		}
		getline(fp, buff);
	}

	set(pVector.size());

	/*
	Input_file_s = "test.txt";
	readFile();
	*/

}



void Solver_1D::read_point(string s) {
	// if string is a floating number/ integer number
	int  n = std::count(s.begin(), s.end(), ' ');
	char* str = strdup(s.c_str());
	if (n == 1) {
		pVector.push_back(atoR(strtok(str, " ")));
	}
	else {
		int n = atoi(strtok(str, " "));
		int d = atoi(strtok(NULL, " "));
		assert(n >= 0);
		assert(d > 0);
		pVector.push_back(RationalNumber(n,d));
	}
	
};

void Solver_1D::set(size_t point_size) {
	pVector.reserve(point_size);
	solution = DGraph(point_size);
};




void Solver_1D::draw() {
	char file_str[400];
	strcpy(file_str, Result_folder_s.c_str());
	strcat(file_str, get_file_name_no_extension(Input_file_s).c_str());
	strcat(file_str, Algo_t.c_str());
	strcat(file_str, "_");
	strcat(file_str, BoolToString(short_edges_only_flag));
	strcat(file_str, "-");
	strcat(file_str, std::to_string(long_edge_length).c_str());
	strcat(file_str, "_");
	double range = 40.0 / boost::rational_cast<double>(pVector.back() - pVector[0]);
	//strcat(file_str, "solution.tex");
	//draw_tikz(range, file_str, "every node/.append style={draw, circle}");
	strcat(file_str, "solution.xml");
	draw_ipe( file_str);
}


void Solver_1D::print() {
	solution.print();
}
void Solver_1D::debug() {
	bool is_planar = is_planarity();
	assert(is_planar);
}