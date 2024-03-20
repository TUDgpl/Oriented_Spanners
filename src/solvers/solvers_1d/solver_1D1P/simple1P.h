# pragma once
#include <queue>
#include "solver.h"
#include "solver1D1P.h"
#include <set>
#include "dgraph.h"
// greedy approach, with garantee 5
//<key, value>
struct Arc_greater
{
	bool operator()(Arc_1D const& a1, Arc_1D const& a2) const
	{
		return a1.l > a2.l;
	}
};

class DList : public std::set<int> {
public:
    int inorderPredecessor(int key)
    {
        set<int>::iterator it;
        it = find(key); // get iterator of key
        if (it == end()) {
            printf("alart 1");
            exit(-1);
        }
        // If iterator is at first position
        // Then, it doesn't have predecessor
        if (it == begin()) {
            return -1;
        }

        --it; // get previous element
        return *it;
    }

    int inorderSuccessor(int key)
    {
        set<int>::iterator it;
        it = find(key); // get iterator of key
        if (it == end()) {
            printf("alart 2");
            exit(-1);
        }
        ++it; // get next element

        // Iterator points to NULL (Element does
        // not exist)
        if (it == end())
        {
            return -1;
        }
        return *it;
    }
};

class Simple :public Solver_1D1P{
public:
	void say_hello() { printf("Run Simple"); };

    RationalNumber solve() override;
private:
	boost::heap::priority_queue<Arc_1D, boost::heap::compare<Arc_greater>> T;
    RationalNumber teo_g = RationalNumber(5);
};