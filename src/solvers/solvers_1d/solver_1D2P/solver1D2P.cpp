#include "solver1D2P.h"
// Todo: check if it is a valid solution
//      check if it is crossing-free
//      compute the dilation (<= test_v)

//// tuple(a,b,c) -----> edge (a,b) on page c


void Solver_1D2P::outputMeasures() {
    std::cout << "Hello world" << std::endl;
    // page 0
    for (auto i : page_0) {
        measures.addElement("page_0", std::to_string(i.first), std::to_string(i.second));
    }
    //page 1
    for (auto i : page_1) {
        measures.addElement("page_1", std::to_string(i.first), std::to_string(i.second));
    }
}

void Solver_1D2P::output(RationalNumber od) {
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

    // page 0
    ofs <<  "Page_0: " << endl;
    for (auto i : page_0) {
        ofs <<"("<< std::to_string(i.first)<<", " << std::to_string(i.second) << ")" << endl;
    }
    //page 1
    ofs << "Page_1: " << endl;
    for (auto i : page_1) {
        ofs << "(" << std::to_string(i.first) << ", " << std::to_string(i.second) << ")" << endl;
    }
    ofs.close();
}

bool Solver_1D2P::is_planarity() {
    // planarity check
    return (is_planar(page_0) && is_planar(page_1));
}

void Solver_1D2P::draw_tikz(double range, std::string path, std::string optional_parameters) {
    uint64_t num_nodes = pVector.size();
    std::ofstream o(path);

    // Enviroment
    o << "\\documentclass{standalone}" << std::endl;
    o << "\\usepackage{tikz}" << std::endl;
    o << "\\begin{document}" << std::endl;
    o << "\\begin{tikzpicture}[";
    o << optional_parameters;
    o << "]" << std::endl;


    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (int i = 0; i < num_nodes; ++i) {
        o << "\\node[minimum size=1mm] at (" << range * boost::rational_cast<double>(pVector[i]) << "," << 0 << ") (" << i << ") {} ;" << std::endl;
    }

    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)


    // page 0
    for (auto i :page_0) {
            o << "\\draw (" << i.first << ") edge";
            o << "[bend right]";
            o << " (" << i.second << ");" << std::endl;
    }
    //page 1
    for (auto i : page_1) {
        o << "\\draw (" << i.first << ") edge";
        o << "[bend left]";
        o << " (" << i.second << ");" << std::endl;
    }

      
    for (int i = 0; i < num_nodes - 1; ++i) {
        o << "\\draw (" << i << ") edge";
        o << " (" << i + 1 << ");" << std::endl;
    }
    // END of File
    o << "  \\end{tikzpicture}\n";
    o << "  \\end{document}\n";

    o.close();
};

void Solver_1D2P::draw_ipe(std::string path) {
    int y = 300;
    double y_scale = 1;
    std::ofstream o(path);

    // Find extreme coords of the graph (if you use CGAL you can use inbuild functions instead)

    double xmin =0;
    double xmax = boost::rational_cast<double>(pVector.back());
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

/*
    <ipeselection pos = "20.1445 300.135">
        < path layer = "edges" stroke = "black">
        16 300 m
        576 300 l
        h
        < / path>
        <use layer = "points" name = "mark/disk(sx)" pos = "21.045 300" size = "normal" stroke = "black" / >
        < / ipeselection>
*/


    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)
    o << "<path layer=\"edges\" stroke=\"black\" pen=\"normal\">\n";
    o << fixed << ((xmin - xmin) * 560 / scale + 16) << " "
        << y << " m\n";
    o << fixed << ((xmax - xmin) * 560 / scale + 16)
        << " " <<y << " l\n";
    o << "h\n</path>\n";

    /*
    for (RationalNumber p : pVector)
    {
        o << fixed << "<use layer=\"points\" name=\"mark/disk(sx)\" pos=\"" << ((boost::rational_cast<double>(p) - xmin) * 560 / scale + 16) << " " << (y) << "\" size=\"normal\" stroke=\"black\"/>\n";
    }

    RationalNumber a = pVector[2];
    RationalNumber b = pVector[8];

    bool above = false;

    o << "<path layer = \"points\" stroke = \"black\">" << endl;
    o << fixed << ((boost::rational_cast<double>(above ? a : b) - xmin) * 560 / scale + 16) << " " << y << " m" << endl;
    o << fixed << (((boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale) << " 0 0 ";
    o << fixed << ((-(boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale) << " ";
    o << fixed << ((boost::rational_cast<double>(a) + (boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale + 16) << " " << (y) << " ";
    o << fixed << ((boost::rational_cast<double>(above ? b : a) - xmin) * 560 / scale + 16) << " " << y << " a" << endl;
    o << "</path>" << endl;


    */



    // page 0
        for (auto i : page_0) {
            RationalNumber a = pVector[i.first];
            RationalNumber b = pVector[i.second];
            bool above = true;
            o << "<path layer = \"points\" stroke = \"black\">" << endl;
            o << fixed << ((boost::rational_cast<double>(above ? a : b) - xmin) * 560 / scale + 16) << " " << y << " m" << endl;
            o << fixed << (((boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale) << " 0 0 ";
            o << fixed << ((-(boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale) << " ";
            o << fixed << ((boost::rational_cast<double>(a) + (boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale + 16) << " " << (y) << " ";
            o << fixed << ((boost::rational_cast<double>(above ? b : a) - xmin) * 560 / scale + 16) << " " << y << " a" << endl;
            o << "</path>" << endl;
        }
    //page 1
    for (auto i : page_1) {
        RationalNumber a = pVector[i.first];
        RationalNumber b = pVector[i.second];
        bool above = false;
        o << "<path layer = \"points\" stroke = \"black\">" << endl;
        o << fixed << ((boost::rational_cast<double>(above ? a : b) - xmin) * 560 / scale + 16) << " " << y << " m" << endl;
        o << fixed << (((boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale) << " 0 0 ";
        o << fixed << ((-(boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale) << " ";
        o << fixed << ((boost::rational_cast<double>(a) + (boost::rational_cast<double>(b) - boost::rational_cast<double>(a)) / 2 - xmin) * 560 / scale + 16) << " " << (y) << " ";
        o << fixed << ((boost::rational_cast<double>(above ? b : a) - xmin) * 560 / scale + 16) << " " << y << " a" << endl;
        o << "</path>" << endl;
    }

 

    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (RationalNumber p : pVector)
    {
        o <<fixed<< "<use layer=\"points\" name=\"mark/disk(sx)\" pos=\"" << ((boost::rational_cast<double>(p) - xmin) * 560 / scale + 16) << " " << y<< "\" size=\"normal\" stroke=\"black\"/>";
    }

    o << fixed << "</page>\n";
    o << fixed << "</ipe>\n";

    o.close();
}



void Solver_1D2P::set_pages() {
    page_0.clear();
    page_1.clear();
    for (int i = 0; i < solution_indices.size(); i++) {
        tuple<unsigned int, unsigned int, unsigned int> index =
            encode(solution_indices[i], base);
        if (get<2>(index) == 0) {
            page_0.push_back(
                pair<unsigned int, unsigned int>(get<0>(index), get<1>(index)));
        }
        else {
            assert(get<2>(index) == 1);
            page_1.push_back(
                pair<unsigned int, unsigned int>(get<0>(index), get<1>(index)));
        }
    }
    solution = DGraph(pVector.size());
    solution.addEdges(page_0);
    solution.addEdges(page_1);
    solution.get_longest_edge(pVector);
}

void Solver_1D2P::set(size_t point_size) {
    base = point_size;
}

