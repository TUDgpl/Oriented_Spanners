/*
 * miscellaneous.h 
 * OriSpanner
 *  Created on: Sep 15, 2013
 *      Author: gpl
 */

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include<vector>
#include<cassert>
#include <boost/heap/priority_queue.hpp>
#include <set>

#include <boost/rational.hpp>







#include "cxxopts.hpp"
#include "jsonM.h"

extern std::string sat_solver_PATH;
extern std::string tmp_dictionary;



using namespace std;
extern jsonM measures;
extern string Result_folder_s;
extern string input_ipe_s;
extern string Input_file_s;
extern string Input_file_name;
extern string Algo_t;
extern double W;
extern double H;
extern double epsilon;
extern bool short_edges_only_flag;
extern int long_edge_length;


void hello();





//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

typedef boost::rational<long long> RationalNumber;

void printArgs(int argc, char* argv[]);
void parseInitOptions(int argc, char* argv[]);
void outputMeasure(const char* append);
void printInitUsage();







bool find_cross(unsigned int s1, unsigned int t1, unsigned int s2, unsigned int t2);

inline string get_file_name(const std::string& file) {
	const std::size_t found = file.find_last_of("/\\");
	return  file.substr(found + 1);
}


inline string get_file_name_no_extension(const std::string& file) {
	string file_name = get_file_name(file);
	const std::size_t found = file_name.find_last_of(".");
	return  file_name.substr(0, found );

}

//+++++++++++++++++++++++++ 1D +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// edge (a,b) on page c
tuple<int, int, int> encode(unsigned int i, unsigned int base);
inline unsigned int decode(
	const tuple<unsigned int, unsigned int, unsigned int>& index,
	unsigned int base) {
	assert(get<2>(index) == 0 or get<2>(index) == 1);
	return get<0>(index) + get<1>(index) * base + get<2>(index) * (base * base);
}

inline unsigned int decode(unsigned int a, unsigned int b, unsigned int c,
	unsigned int base) {
	assert(c == 0 or c == 1);
	return a + b * base + c * (base * base);
}

void tools_debug();

bool find_cross(const pair<unsigned int, unsigned int>& a1,
	const pair<unsigned int, unsigned int>& a2);
// check if one page is planar
bool is_planar(const vector<pair<unsigned int, unsigned int>>& page_0);


//----------------------1D---------------------------------------------------
inline int gcd(int a, int b)
{
    while (b != a)
    {
        if (a < b)
            b -= a;
        else
            a -= b;
    }
    return a;
}

inline RationalNumber atoR(char* str) {
    int n = atoi(strtok(str, "."));
    char* f = strtok(NULL, ".");
    int d = 0;
    if (f != NULL) {
        d = strlen(f);
        if (d >= 16) {
        perror("To large denominator, please use the rational numbers");
        exit(EXIT_FAILURE);
        }
        n = n * pow(10, d) + atoi(f);
    }
    return RationalNumber(n, (int)pow(10, d));
}

inline string to_string(RationalNumber const& test_v) {
    return to_string(test_v.numerator()) + "_" + to_string(test_v.denominator());

}
/*
class RationalNumber
{
public:

    int numerator_;
    int denominator_;

    void reduce()
    {
        int tempGcd = gcd(numerator_, denominator_);

        numerator_ = numerator_ / tempGcd;
        denominator_ = denominator_ / tempGcd;
    }

    RationalNumber()
    {
        numerator_ = 0;
        denominator_ = 1;
    }
    RationalNumber(int a)
    {
        numerator_ = a;
        denominator_ = 1;
    }
    RationalNumber(int a, int b)
    {
        numerator_ = a;
        denominator_ = b;
    }
    RationalNumber(const RationalNumber& other)
    {
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
    }
    RationalNumber& operator=(RationalNumber const& other) {
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
        return *this;
    }

    RationalNumber& operator=(int other) {
        numerator_ = other;
        denominator_ = 1;
        return *this;
    }

    ~RationalNumber() {}

    float to_float() const
    {
        float tempNumerator = this->numerator_;
        float tempDenominator = this->denominator_;
        return tempNumerator / tempDenominator;
    };

    RationalNumber invert() const
    {
        RationalNumber resultInvert(denominator_, numerator_);
        return resultInvert;
    };

};

inline RationalNumber atoR(char* str) {
    int n = atoi(strtok(str, "."));
    char* f= strtok(NULL, ".");
    int d = 1;
    if (f != NULL) {
        d = strlen(f);
        n = n * pow(10, d) + atoi(f);
    }
    return RationalNumber(n,d);
}
inline bool operator <(RationalNumber const& lhs, RationalNumber const& other) {
    if (other.numerator_ == INT_MAX) return true;
    return(lhs.numerator_ * other.denominator_ < other.numerator_ * lhs.denominator_);

}

inline bool operator >(int other, RationalNumber const& rhs) {
    return(other * rhs.denominator_ > rhs.numerator_);

}

inline bool operator >(RationalNumber const& rhs, int other) {
    return(rhs.numerator_ > other * rhs.denominator_);

}
inline bool operator >=(RationalNumber const& lhs, RationalNumber const& rhs) {
    return(lhs.numerator_ * rhs.denominator_ >= rhs.numerator_ * lhs.denominator_);

}

inline bool operator <(int other, RationalNumber const& rhs) {
    return(rhs.numerator_ > other * rhs.denominator_);

}

inline bool operator <=(int other, RationalNumber const& rhs) {
    return(other * rhs.denominator_ <= rhs.numerator_);

}

inline RationalNumber operator +(RationalNumber const& lhs, const RationalNumber& rhs)
{
    int tempNum = lhs.numerator_;
    int tempDenum = lhs.denominator_;
    int n = (tempNum * rhs.denominator_) + (rhs.numerator_ * tempDenum);
    int d = tempDenum * rhs.denominator_;
    RationalNumber a(n, d);
    a.reduce();
    return a;
};


inline RationalNumber operator -(RationalNumber const& lhs, const RationalNumber& rhs)
{
    int tempNum = lhs.numerator_;
    int tempDenum = lhs.denominator_;
    int n = (tempNum * rhs.denominator_) - (rhs.numerator_ * tempDenum);
    int d = tempDenum * rhs.denominator_;
    RationalNumber a(n,d);
    a.reduce();
    return a;
};


inline RationalNumber operator /(RationalNumber const& lhs, const RationalNumber& rhs)
{
    RationalNumber a(lhs.numerator_ * rhs.denominator_, lhs.denominator_ * rhs.numerator_);
    a.reduce();
    return a;
};


inline RationalNumber operator *(RationalNumber const& lhs, const RationalNumber& rhs)
{
    RationalNumber a(lhs.numerator_ * rhs.numerator_, lhs.denominator_ * rhs.denominator_);
    a.reduce();
    return a;
};

inline RationalNumber operator *(RationalNumber const& lhs, unsigned int other) {
    RationalNumber a(lhs.numerator_ * other, lhs.denominator_);
    a.reduce();
    return a;

}
inline RationalNumber operator -(RationalNumber const& lhs, double other) {
    RationalNumber a(lhs.numerator_ * other, lhs.denominator_);
    a.reduce();
    return a;

}

inline bool operator <=(RationalNumber const& lhs, RationalNumber const& other) {
    return(lhs.numerator_ * other.denominator_ <= other.numerator_ * lhs.denominator_);

}

inline bool operator >(RationalNumber const& lhs, RationalNumber const& other) {
    return(lhs.numerator_ * other.denominator_ > other.numerator_ * lhs.denominator_);

}

inline RationalNumber min(RationalNumber const& lhs, RationalNumber const& other) {
    if (lhs <= other) return lhs;
    return other;

}
inline RationalNumber abs(RationalNumber const&  other) {
    RationalNumber a(abs(other.numerator_ ),abs(other.denominator_));
    return a;

}

inline RationalNumber max(RationalNumber const& lhs, RationalNumber const& other) {
    if (lhs <= other) return other;
    return lhs;

}
inline string to_string(RationalNumber const& test_v) {
    return to_string(test_v.numerator_) + "_" + to_string(test_v.denominator_);

}


inline bool operator ==(RationalNumber const& lhs, RationalNumber const& other) {
    return(lhs.numerator_ * other.denominator_ == other.numerator_ * lhs.denominator_);

}

inline bool operator ==(RationalNumber const& lhs, int other) {
    if (other == INT_MAX) {
        cout << (lhs.numerator_ == INT_MAX);
        cout << (lhs.denominator_ == 1);
        return (lhs.numerator_ == INT_MAX && lhs.denominator_ == 1);
    }
    return(lhs.numerator_ == other * lhs.denominator_);

}

*/
struct Arc_1D {
    // s: source index 
    // t: target index
    //l: length
    Arc_1D() { s = 0;  t = 0; l = 0; };
    Arc_1D(unsigned int source, unsigned int target, RationalNumber len) {
        s = source;
        t = target;
        l = len;
    }
    void print() const;
    void debug(vector<RationalNumber>& points);

    unsigned s;
    unsigned t;
    RationalNumber l;
};

bool find_cross(const Arc_1D& a1, const Arc_1D& a2);

inline const char* const BoolToString(bool b)
{
    return b ? "true" : "false";
}
