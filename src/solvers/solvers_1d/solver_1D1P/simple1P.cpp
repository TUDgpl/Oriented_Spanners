#include "simple1P.h"
RationalNumber Simple::solve() {
	DList L;
	for (int i = 0; i < pVector.size(); i++) 
	{
		L.insert(i);
	}

	// set initial priority queue
	int i = 0;
	for (int i = 0; i < pVector.size()-2; i++) {
		T.push(Arc_1D(i+2, i, pVector[i + 2]- pVector[i]));
	}
	Arc_1D Cover_min;
	while (!T.empty()) {
		Cover_min = T.top();
		T.pop();
		// get predecessor and successor
		DList::iterator prev = L.find(Cover_min.s);
		DList::iterator suss = L.find(Cover_min.t);
		if (suss != L.end() && prev != L.end()) {
			L.erase(*(next(suss,1)));
			solution.addEdge(Cover_min.s, Cover_min.t);
			DList::iterator suss_s = std::prev(suss,1);
			DList::iterator prev_v = std::next(prev,1);
			//add (i+1,i-2)
			if(suss_s != L.end()) T.push(Arc_1D( *prev, *suss_s, pVector[*prev]- pVector[*suss_s]));
			//add (i+2,i-1)
			if (prev_v != L.end()) T.push(Arc_1D(*prev_v, *suss, pVector[*prev_v]-pVector[*suss]));
		}
	}
	assert(is_planarity() == true);
	RationalNumber od = solution.get_dilation(pVector);
	assert(od <= teo_g);
	printf("Simple solved with %f", boost::rational_cast<double>(od) );
	return od;
}
