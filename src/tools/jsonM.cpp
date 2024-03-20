/*
 * json.cpp
 *
 *  Created on: July 9, 2021
 *      Author: gpl
 */
#include "jsonM.h"
using namespace std;
void hello() {
	cout << "Hello CMake." << endl;
}

void jsonM::print() {
	std::cout << jObject;
};
void jsonM::addElement(std::string key, std::string value) {
	if (jObject.find(key) != jObject.end()) {
		if (jObject[key].is_array()) {
			jObject[key].push_back(value);
		}
		else {
			auto oldValue = jObject[key];
			jObject[key] = { oldValue,value };
		}
	}
	else jObject[key] = value;
}


void jsonM::addElement(std::string key, jsonM value) {
	if (jObject.find(key) != jObject.end()) {
		if (jObject[key].is_array()) {
			jObject[key].push_back(value.jObject);
		}
		else {
			auto oldValue = jObject[key];
			jObject[key] = { oldValue,value.jObject };
		}
	}
	else jObject[key] = value.jObject;
}




void jsonM::addElement(std::string key1, std::string key2, std::string value) {
	if (jObject.find(key1) != jObject.end()) {
		auto& item = jObject[key1];
		if (item.find(key2) != item.end()) {
			if (item[key2].is_array()) {
				item[key2].push_back(value);
			}
			else {
				auto oldValue = item[key2];
				item[key2] = { oldValue,value };
			}
		}
		else {
			jObject[key1][key2] = value;
		}
	}
	else {
		jObject[key1][key2] = value;
	}
}


void jsonM::addElement(std::string key1, std::string key2, jsonM value) {
	if (jObject.find(key1) != jObject.end()) {
		auto& item = jObject[key1];
		if (item.find(key2) != item.end()) {
			if (item[key2].is_array()) {
				item[key2].push_back(value.jObject);
			}
			else {
				auto oldValue = item[key2];
				item[key2] = { oldValue,value.jObject };
			}
		}
		else {
			jObject[key1][key2] = value.jObject;
		}
	}
	else {
		jObject[key1][key2] = value.jObject;
	}
}
void jsonM::debug() {
}
void jsonM::output(const char* outfolder, const char* appendix, const char* outFile) {
	std::ofstream ofs;
	std::string s = std::string(outfolder) + "/" + outFile;
	s += appendix;
	try {
		ofs.open(s, std::fstream::out);
	}
	catch (std::ofstream::failure& e) {
		std::cerr << "Exception opening file: " << std::strerror(errno) << "\n";
	}
	ofs << jObject;
	cout << jObject;
	ofs.close();
}
