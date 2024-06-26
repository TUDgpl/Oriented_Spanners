#include "miscellaneous.h"
jsonM measures;
string Result_folder_s;
string Algo_t;
string input_ipe_s;
string Input_file_s;
string Input_file_name;
double W;
double H;
bool short_edges_only_flag = false;
int long_edge_length = 6;
double epsilon = 0.000000000000001;

#ifdef _WIN32
std::string sat_solver_PATH = "D:/glucose-4.1-win-x64/glucose.exe";
std::string tmp_dictionary = "D:/GIT/OriSpanner/tmp";
#endif

#ifdef linux
std::string sat_solver_PATH = "./glucose-simp";
std::string tmp_dictionary = "scratch";
#endif



void printArgs(int argc, char* argv[]) {
	std::cout << argc-1 <<" arguments:" << std::endl;
	if (argc > 1)
	{
		std::copy(argv + 1, argv + argc, std::ostream_iterator<const char*>(std::cout, "\n"));
	}
}
void parseInitOptions(int argc, char* argv[]) {
	//printArgs(argc, argv);
	cxxopts::Options options("OriSpanner", "Test");
	options.add_options()
		("a,algorithm", "Algorithm Option", cxxopts::value<std::string>())
		("h,help", "Print usage")
		("d", "dictionary", cxxopts::value<std::string>()->default_value("D:/GIT/OriSpannerP/solutions/"))
		("i,ipe", "ipe input file", cxxopts::value<std::string>())
		("f,filename", "input file", cxxopts::value<std::string>())
		("l,length", "edge length limit", cxxopts::value<int>()->default_value("6"))
		("s,short", "short edge only", cxxopts::value<bool>()->default_value("false"))
		("p", "path", cxxopts::value<std::string>())
		("t", "tmp", cxxopts::value<std::string>())

		;
	options.allow_unrecognised_options();
	auto result = options.parse(argc, argv);
	if (result.count("help"))
	{
		printInitUsage();
		exit(0);
	}
	if (result.count("short")) {
		short_edges_only_flag = true;
		long_edge_length = result["l"].as<int>();
	}

	if (result.count("filename")) {
		Input_file_s = strdup(result["filename"].as<std::string>().c_str());
		Input_file_name = get_file_name(Input_file_s);
		string outFile(Input_file_s);
		std::string key = "/";
		std::size_t found = outFile.rfind(key);
		outFile = outFile.substr(found + 1);
		measures.addElement("info", "file", outFile);
	}
	else {
		if (result.count("ipe")) {
			input_ipe_s = strdup(result["ipe"].as<std::string>().c_str());
			Input_file_name = get_file_name(input_ipe_s);
			string outFile(input_ipe_s);
			std::string key = "/";
			std::size_t found = outFile.rfind(key);
			outFile = outFile.substr(found + 1);
			measures.addElement("info", "file", outFile);
		}
		else {
			std::cerr << "Input file missing" << std::endl;
			printInitUsage();
			exit(0);
		}
	}
	if (result.count("path")) {
		sat_solver_PATH = result["p"].as<std::string>();
	
	
	
	}
	if (result.count("tmp")) {
		tmp_dictionary= result["t"].as<std::string>();
	}
	
	Result_folder_s = result["d"].as<std::string>();
	if(Input_file_s.find("uniform") != std::string::npos) Result_folder_s += "1D/Uniform/";
	if (Input_file_s.find("exp") != std::string::npos) Result_folder_s += "1D/Exp/";
	if (Input_file_s.find("mixed") != std::string::npos) Result_folder_s += "1D/Mixed/";
	if (Input_file_s.find("unit") != std::string::npos) Result_folder_s += "1D/Unit/";

	if (result.count("algorithm")) {
		Algo_t = result["algorithm"].as<std::string>();
		measures.addElement("info", "algo_type", Algo_t);
	}
};
/*print the manual of the program*/
void printInitUsage() {
	cout << "\n--------oriSpanner, a orinted spanner solver by " << GREEN << "" << RESET << " -----------------\n";
	//printf("\nauthor: Guangping Li\n");
	printf("\n-------------------Usage--------------------------------------------------------\n");
	printf("./oriSpanner  -f <instance> [options]\n");
	printf("\n-------------------Options------------------------------------------------------\n");
	printf("   --help, -h : output this help\n");
	printf("   --algorithm, -a : algorithm in use (see options below)\n");
	printf("   --dictionary, -d : solution folder\n");
	printf("   --ipe, -i : ipe drawing input file\n");
	printf("   --short, -s : get optimal solutions with only short edge-distance edges, in combination with the flag -l\n");
	printf("   --length, -l : only using short edge distance edges (pi, pj) where j -i < l\n");
	printf("   --path, -p : SAT solver bin path\n");
	printf("   --tmp, -t : temp folder to store temperary DIMAS files generated by SAT solvers\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("\n-------------------algorithm options------------------------------------------------------\n");
	printf("   sat1 : exact sat-model based solver to find an optimal 1-PPB using Glucose SAT solver \n");
	printf("   sat : exact sat-model based solver to find an optimal 2-PPB using Glucose SAT solver \n");
	printf("   greedy: a greedy algorithm to find an optimal 1-PPB by selecting the shortes edges\n");
	printf("   dp: a dynamic programming algorithm to find an optimal 1-PPB \n");
	
	printf("   *More details see the paper \"Oriented Spanners\" <https://arxiv.org/abs/2306.17097>\n");
	printf("---------------------------------------------------------------------------------\n");
}

void outputMeasure(const char* append) {
	string outFile(Input_file_name);
	string appendix;
	appendix += "_";
	appendix += Algo_t;
	appendix += "_";
	appendix += BoolToString(short_edges_only_flag);
	appendix += "_";
	appendix += std::to_string(long_edge_length);
	appendix += append;
	measures.output(Result_folder_s.c_str(), appendix.c_str(), outFile.c_str());
};

bool find_cross(const Arc_1D& a1, const Arc_1D& a2)
{
	int s1 = min(a1.s, a1.t);
	int s2 = min(a2.s, a2.t);
	int t1 = max(a1.s, a1.t);
	int t2 = max(a2.s, a2.t);
	if (a1.s < a2.s) return (a1.t < a2.t && a1.t > a2.s);
	else {
		if (a1.s > a2.s) return (a2.t < a1.t && a2.t > a1.s);
	}
	return false;
}

bool find_cross(unsigned int s1, unsigned int t1, unsigned int s2, unsigned int t2)
{
	s1 = min(s1, t1);
	s2 = min(s2, t2);
	t1 = max(s1, t1);
	t2 = max(s2, t2);
	if (s1 < s2) return (t1 < t2 && t1 > s2);
	else {
		if (s1 > s2) return (t2 < t1 && t2 > s1);
	}
	return false;
}

// edge (a,b) on page c
tuple<int, int, int> encode(unsigned int i, unsigned int base) {
	unsigned int a = i % base;
	unsigned int b = (i / base) % base;
	unsigned int c = i / (base * base);
	tuple<unsigned int, unsigned int, unsigned int> index{ a, b, c };
	return index;
}


void tools_debug() {
	unsigned int base = 10;
	unsigned int a = 189;
	tuple<unsigned int, unsigned int, unsigned int> index = encode(a, base);
	assert(get<0>(index) == 9);
	assert(get<1>(index) == 8);
	assert(get<2>(index) == 1);
	assert(decode(index, base) == a);
}

bool find_cross(const pair<unsigned int, unsigned int>& a1,
	const pair<unsigned int, unsigned int>& a2) {
	if (a1.first < a2.first)
		return (a1.second < a2.second && a2.second < a1.first);
	else {
		if (a1.first > a2.first)
			return (a2.second < a1.second && a1.second < a2.first);
	}
	return false;
}

// check if one page is planar
bool is_planar(const vector<pair<unsigned int, unsigned int>>& page_0) {
	for (int i = 0; i < page_0.size(); i++) {
		for (int j = i + 1; j < page_0.size(); j++) {
			if (find_cross(page_0[i], page_0[j])) return false;
		}
	}
	return true;
}

