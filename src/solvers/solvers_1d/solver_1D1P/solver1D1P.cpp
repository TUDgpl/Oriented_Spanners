#include "solver1D1P.h"



 void Arc_1D::print() const{
	cout << "Arc (" << s << ", " << t << "), " << l << std::endl;
}

void Arc_1D::debug(vector<RationalNumber>& pVector) {
	assert(pVector.size() > t);
	assert(pVector.size() > s);
	assert(abs(pVector[t] - pVector[s]) == l);

}

void Solver_1D1P::outputMeasures() {
    for (unsigned int i = 0; i < pVector.size(); ++i) {
        for (auto itr = solution.adList[i].OutNeighborhood.begin(); itr != solution.adList[i].OutNeighborhood.end(); ++itr) {
            measures.addElement("solution", std::to_string(i), std::to_string(*itr));
        }
    }
}

void Solver_1D1P::output(RationalNumber od) {
    char file_str[400];
    strcpy(file_str, Result_folder_s.c_str());
    strcat(file_str, get_file_name_no_extension(Input_file_s).c_str());
    strcat(file_str, Algo_t.c_str());
    strcat(file_str, "_");
    strcat(file_str, BoolToString(short_edges_only_flag));
    strcat(file_str, "_");
    strcat(file_str, std::to_string(long_edge_length).c_str());
    strcat(file_str, "_");
    strcat(file_str, "solution.txt");

    std::ofstream ofs;
    std::string s(file_str);
    try {
        ofs.open(s, std::fstream::out);
    }
    catch (std::ofstream::failure& e) {
        std::cerr << "Exception opening file: " << std::strerror(errno) << "\n";
    }
    ifstream src;
    ofstream dst;
    src.open(Input_file_s, std::fstream::in);
    ofs << src.rdbuf();
    src.close();
    ofs << "d " << od << endl;
    for (unsigned int i = 0; i < pVector.size(); ++i) {
        ofs << i << ": " << endl;
        ofs << "in: ";
        for (auto itr = solution.adList[i].InNeighborhood.begin(); itr != solution.adList[i].InNeighborhood.end(); ++itr) {
            ofs << *itr << " ";
        }
        ofs << endl;
        ofs << "out: ";
        for (auto itr = solution.adList[i].OutNeighborhood.begin(); itr != solution.adList[i].OutNeighborhood.end(); ++itr) {
            ofs << *itr << " ";
        }
        ofs << endl;
    }
    ofs.close();
}


bool Solver_1D1P::is_planarity() {
	std::set<unsigned int>::iterator it;
	std::set<unsigned int>::iterator iv;
	for (unsigned int i = 0; i < solution.adList.size(); i++) {
		it = solution.adList[i].InNeighborhood.begin();
		while (it != solution.adList[i].InNeighborhood.end()) {
			for (unsigned int j = i + 1; j < solution.adList.size(); j++) {
				iv = solution.adList[j].InNeighborhood.begin();
				while (iv != solution.adList[j].InNeighborhood.end()) {
					if (find_cross(*it, i, *iv, j)) return false;
					iv++;
				}
			}
			it++;
		}
	}

	return true;
};


void Solver_1D1P::draw_tikz(double range, std::string path,  std::string optional_parameters = "every node/.append style={draw, circle}, rotate = 90")
{
    uint64_t num_nodes = pVector.size();
    std::ofstream o(path);

    // Enviroment
    o << "\\documentclass{article}" << std::endl;
    o << "\\usepackage{tikz}" << std::endl;
    o << "\\begin{document}" << std::endl;
    o << "\\begin{tikzpicture}[";
    o << optional_parameters;
    o << "]" << std::endl;


    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (int i = 0; i < num_nodes; ++i) {
        o << "\\node[] at (" << range * boost::rational_cast<double>(pVector[i])<< "," << 0 << ") (" << i << ") {} ;" << std::endl;
    }

    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)
    for (int i = 0; i < num_nodes; ++i) {
        for (auto j: solution.adList[i].OutNeighborhood) {
            o << "\\draw (" << i << ") edge";
                o << "[bend right]";
            o << " (" << j << ");" << std::endl;
        }
    }
    for (int i = 0; i < num_nodes-1; ++i) {
        o << "\\draw (" << i << ") edge";
        o << " (" << i+1 << ");" << std::endl;
    }
        // END of File
        o << "  \\end{tikzpicture}\n";
        o << "  \\end{document}\n";

    o.close();
}

void Solver_1D1P::draw_ipe(std::string path){
    int y = 300;
    double y_scale = 1;
    std::ofstream o(path);

    // Find extreme coords of the graph (if you use CGAL you can use inbuild functions instead)

    double xmin = 0, xmax = 0;
    for (RationalNumber p : pVector)
    {
        xmin = std::min(xmin, boost::rational_cast<double>(p));
        xmax = std::max(xmax, boost::rational_cast<double>(p));
    }
    float scale = xmax - xmin;

    // Header of the IPE File
    o << "<?xml version=\"1.0\"?>\n";
    o << "<!DOCTYPE ipe SYSTEM \"ipe.dtd\">\n";
    o << "<ipe version=\"70218\" creator=\"Ipe 7.2.24\">\n";
    o << "<info created=\"D:20221020151441\" modified=\"D:20221020151441\"/>\n";
    o << "<ipestyle name=\"basic\">\n";
    o << "<symbol name=\"mark/disk(sx)\" transformations=\"translations\">\n";
    o << "<path fill=\"sym-stroke\">\n";
    o << "0.6 0 0 0.6 0 0 e\n";
    o << "</path>\n";
    o << "</symbol>\n";
    o << "<anglesize name=\"22.5 deg\" value=\"22.5\"/>\n";
    o << "<anglesize name=\"30 deg\" value=\"30\"/>\n";
    o << "<anglesize name=\"45 deg\" value=\"45\"/>\n";
    o << "<anglesize name=\"60 deg\" value=\"60\"/>\n";
    o << "<anglesize name=\"90 deg\" value=\"90\"/>\n";
    o << "<arrowsize name=\"large\" value=\"10\"/>\n";
    o << "<arrowsize name=\"small\" value=\"5\"/>\n";
    o << "<arrowsize name=\"tiny\" value=\"3\"/>\n";

    // If you want extra colors add here, see following lines for options
    o << "<color name=\"blue\" value=\"0 0 1\"/>\n";
    o << "<color name=\"gray\" value=\"0.745\"/>\n";
    o << "<color name=\"green\" value=\"0 1 0\"/>\n";
    o << "<color name=\"red\" value=\"1 0 0\"/>\n";
    o << "<color name=\"yellow\" value=\"1 1 0\"/>\n";

    // Choices for thickness of lines
    o << "<pen name=\"normal\" value=\"1\"/>\n";
    o << "<pen name=\"fat\" value=\"1.2\"/>\n";
    o << "<pen name=\"heavier\" value=\"0.8\"/>\n";
    o << "<pen name=\"ultrafat\" value=\"2\"/>\n";

    o << "<gridsize name=\"16 pts (~6 mm)\" value=\"16\"/>\n";
    o << "<gridsize name=\"32 pts (~12 mm)\" value=\"32\"/>\n";
    o << "<gridsize name=\"4 pts\" value=\"4\"/>\n";
    o << "<gridsize name=\"8 pts (~3 mm)\" value=\"8\"/>\n";
    o << "<opacity name=\"10%\" value=\"0.1\"/>\n";
    o << "<opacity name=\"25%\" value=\"0.25\"/>\n";
    o << "<opacity name=\"50%\" value=\"0.5\"/>\n";
    o << "<opacity name=\"75%\" value=\"0.75\"/>\n";
    o << "<symbolsize name=\"large\" value=\"5\"/>\n";
    o << "<symbolsize name=\"small\" value=\"2\"/>\n";
    o << "<symbolsize name=\"tiny\" value=\"1.1\"/>\n";
    o << "<textsize name=\"huge\" value=\"\\huge\"/>\n";
    o << "<textsize name=\"large\" value=\"\\large\"/>\n";
    o << "<textsize name=\"small\" value=\"\\small\"/>\n";
    o << "<textsize name=\"tiny\" value=\"\tiny\"/>\n";
    o << "<tiling name=\"falling\" angle=\"-60\" step=\"4\" width=\"1\"/>\n";
    o << "<tiling name=\"rising\" angle=\"30\" step=\"4\" width=\"1\"/>\n";
    o << "</ipestyle>\n";
    o << "<page>\n";
    o << "<layer name=\"edges\"/>\n";
    o << "<layer name=\"points\"/>\n";
    o << "<view layers=\"edges points\" active=\"points\"/>\n";

    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)
    o << "<path layer=\"edges\" stroke=\"black\" pen=\"normal\">\n";
    o << fixed << ((xmin - xmin) * 560 / scale + 16) << " "
        << y << " m\n";
    o << fixed << ((xmax - xmin) * 560 / scale + 16)
        << " " << y << " l\n";
    o << "h\n</path>\n";

    for (int i = 0; i < pVector.size(); ++i) {
        for (auto j : solution.adList[i].OutNeighborhood) {
            RationalNumber a = pVector[i];
            RationalNumber b = pVector[j];
            bool above = false;
            o << "<path layer = \"points\" stroke = \"black\">" << endl;
            o << fixed << ((boost::rational_cast<double>(above ? a : b) - xmin) * 560 / scale + 16) << " " << y << " m" << endl;
            o << fixed << (((boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale) << " 0 0 ";
            o << fixed << ((-(boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale) << " ";
            o << fixed << ((boost::rational_cast<double>(a) + (boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale + 16) << " " << (y) << " ";
            o << fixed << ((boost::rational_cast<double>(above ? b : a) - xmin) * 560 / scale + 16) << " " << y << " a" << endl;
            o << "</path>" << endl;
        }
    }




    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (RationalNumber p : pVector)
    {
        o << fixed << "<use layer=\"points\" name=\"mark/disk(sx)\" pos=\"" << ((boost::rational_cast<double>(p) - xmin) * 560 / scale + 16) << " " << y << "\" size=\"normal\" stroke=\"black\"/>";
    }

    o << fixed << "</page>\n";
    o << fixed << "</ipe>\n";

    o.close();
}
