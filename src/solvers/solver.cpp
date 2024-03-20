#include "solver.h"


void Solver::readFile() {
	//cout<< "in readFile"<<endl;
	ifstream fp;
	//fp.open("Debug/instance.cnf",std::ios::in);
	fp.open(Input_file_s, std::ios::in);
	if (!fp.is_open() ) {
		std::cout << std::filesystem::current_path() << std::endl;
		std::cout << Input_file_s << std::endl;
		perror("read file fails");
		exit(EXIT_FAILURE);
	}
	string buff;
	char head;
	getline(fp, buff);
	getline(fp, buff);
	while (!fp.eof()) {
		if (buff.empty()) continue;
		head = buff.at(0);
		if (head == 'p') {
			break;
		}
		getline(fp, buff);
	}
	//std::cout<< buff<< std::endl;
	// Parse the p line
	char* str = strdup(buff.c_str());
	const char s[2] = " ";
	strtok(str, s);
	W = atof(strtok(NULL, s));
	H = atof(strtok(NULL, s));
	unsigned int i = 0;
	while (!fp.eof()) {
		getline(fp, buff);
		if (buff.empty()) continue;
		read_point(buff);
		i++;
	}
	set(i);
};
