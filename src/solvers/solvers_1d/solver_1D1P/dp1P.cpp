#include "dp1P.h"
RationalNumber DP::solve() {
	//initialize
	valid = vector < vector<vector<vector<bool>>>>(pVector.size(),
		vector<vector<vector<bool>>>(pVector.size(),
			vector<vector<bool>>(pVector.size(), vector<bool>(pVector.size(), false)
			)));


	back_tracing = vector < vector<vector<vector<tuple<int, int, int>>>>>(pVector.size(),
		vector<vector<vector<tuple<int, int, int>>>>(pVector.size(),
			vector<vector<tuple<int, int, int>>>(pVector.size(), vector<tuple<int, int, int>>(pVector.size(), tuple<int, int, int>(-2, -2, -2))
			)));

	odV = vector < vector<vector<vector<RationalNumber>>>>(pVector.size(),
		vector<vector<vector<RationalNumber>>>(pVector.size(),
			vector<vector<RationalNumber>>(pVector.size(), vector<RationalNumber>(pVector.size(), 2000 * pVector.back())
			)));


	for (int s = 2; s < pVector.size(); s++) {
		for (int l = 0; l < pVector.size() - s; l++) {
			int r = l + s;
			for (int lp = l + 2; lp <= r; lp++) {
				for (int rp = l; rp < r - 1; rp++) {
					//std::cout << "(" << l << ", " << lp << ", " << rp << ", " << r << ") " << std::endl;
					if (lp == r && rp == l && r == l + 2) {
						valid[l][lp][rp][r] = true;

						odV[l][lp][rp][r] = RationalNumber(1);
						// mark it as an end point of the back-tracing
						back_tracing[l][lp][rp][r] = tuple<int, int, int>(-1, -1, -1);
						continue;
					}
					if (lp <r && rp > l && lp > rp) {
						//std::cout << "case x" << std::endl;
						valid[l][lp][rp][r] = false;
						continue;
					}
					if (lp < r && rp == l) {
						//std::cout << "case xi" << std::endl;
						int krmin = -1;
						RationalNumber minOdil = 2000 * pVector.back();
						for (int kr = l; kr <= r - 3; kr++) {
							assert(valid[l][lp][kr][r - 1] || (lp <r - 1 && kr > l && lp > kr) || (lp == r - 1 && kr == l && r - 1 != l + 2));
							if (valid[l][lp][kr][r - 1]) {
								RationalNumber tempOdil = max(odV[l][lp][kr][r - 1], (pVector[r] - pVector[l]) / (pVector[r] - pVector[r - 2]));
								//assert(tempOdil == oE[l][lp][kr][r - 1].get_dilation(pVector));
								if (tempOdil < minOdil) {
									minOdil = tempOdil;
									krmin = kr;
								}
							}
						};
						odV[l][lp][rp][r] = minOdil;
						//odV[l][lp][rp][r] = oE[l][lp][rp][r].get_dilation(pVector);
						assert(odV[l][lp][rp][r] == minOdil);
						valid[l][lp][rp][r] = true;
						back_tracing[l][lp][rp][r] = tuple<int, int, int>(-3, -1, krmin);
						continue;
					}

					if (lp == r && rp > l) {
						//std::cout << "case xii" << std::endl;
						int klmin = -1;
						RationalNumber minOdil = 2000 * pVector.back();
						RationalNumber tempOdil;
						for (int kl = l + 3; kl <= r; kl++) {
							assert(valid[l + 1][kl][rp][r] || (kl < r && rp > l + 1 && kl > rp) || (kl == r && rp == l + 1 && r != l + 3));
							if (valid[l + 1][kl][rp][r]) {
								tempOdil = max(odV[l + 1][kl][rp][r], (pVector[r] - pVector[l]) / (pVector[l + 2] - pVector[l]));
								//tempOdil = oE[l + 1][kl][rp][r].get_dilation(pVector);
								//assert(tempOdil == max(odV[l + 1][kl][rp][r], (pVector[r] - pVector[l]) / (pVector[l + 2] - pVector[l])));
								if (tempOdil < minOdil) {
									minOdil = tempOdil;
									klmin = kl;
								}
							}
						};
						valid[l][lp][rp][r] = true;
						odV[l][lp][rp][r] = minOdil;
						//odV[l][lp][rp][r] = oE[l][lp][rp][r].get_dilation(pVector);
						//assert(odV[l][lp][rp][r] == minOdil);
						back_tracing[l][lp][rp][r] = tuple<int, int, int>(-4, klmin, -1);
						continue;
					}

					if (lp < r && rp > l && lp <= rp) {
						//std::cout << "case xiii" << std::endl;
						int klmin = -1;
						int krmin = -1;
						int kmin = -1;
						RationalNumber minOdil = 2000 * pVector.back();
						RationalNumber tempOdil;
						for (int k = max(l + 2, lp); k <= min(r - 2, rp); k++) {
							for (int kr = l; kr <= k - 2; kr++) {
								for (int kl = k + 2; kl <= r; kl++) {
									assert(valid[l][lp][kr][k] == true || (lp < k && kr > l && lp > kr) || (lp == k && kr == l && k != l + 2));
									assert(valid[k][kl][rp][r] == true || (kl < r && rp > k && kl > rp) || (kl == r && rp == k && r != k + 2));
									if (valid[l][lp][kr][k] && valid[k][kl][rp][r]) {
										tempOdil = max({ odV[l][lp][kr][k], odV[k][kl][rp][r], (pVector[kl] - pVector[kr]) / (pVector[k + 1] - pVector[k - 1]) });
										//DGraph t = oE[l][lp][kr][k];
										//t.merge(oE[k][kl][rp][r]);
										//t.addEdge(r, l);

										//tempOdil = t.get_dilation(pVector);
										//assert(tempOdil == max({ odV[l][lp][kr][k], odV[k][kl][rp][r], (pVector[kl] - pVector[kr]) / (pVector[k + 1] - pVector[k - 1]) }));
										if (tempOdil < minOdil) {
											minOdil = tempOdil;
											klmin = kl;
											kmin = k;
											krmin = kr;
										}
									}
								}

							}

						}
						valid[l][lp][rp][r] = true;
						odV[l][lp][rp][r] = minOdil;
						back_tracing[l][lp][rp][r] = tuple<int, int, int>(kmin, klmin, krmin);
						continue;
					}
				}
			}
		}
	}
	int lpmin = -1;
	int rpmin = -1;
	RationalNumber minOdil = 2000 * pVector.back();
	RationalNumber tempOdil;
	for (int lp = 2; lp < pVector.size(); lp++) {
		for (int rp = 0; rp < pVector.size() - 2; rp++) {
			assert(valid[0][lp][rp][pVector.size() - 1] == true || (lp < pVector.size() - 1 && rp > 0 && lp > rp) || (lp == pVector.size() - 1 && rp == 0));
			if (valid[0][lp][rp][pVector.size() - 1] == true) {
				tempOdil = odV[0][lp][rp][pVector.size() - 1];
				//tempOdil = oE[0][lp][rp][pVector.size() - 1].get_dilation(pVector);
				if (tempOdil < minOdil) {
					minOdil = tempOdil;
					lpmin = lp;
					rpmin = rp;
				}
			}
		}
	}
	assert(odV[0][lpmin][rpmin][pVector.size() - 1] == minOdil);

	//get the final solution by  back tracing
	back_trace(0, lpmin, rpmin, pVector.size() - 1);
	//assert(gg.get_edges_size() == solution_g.get_edges_size());
	//assert(gg.get_dilation_dijkstra(pVector) == solution_g.get_dilation_dijkstra(pVector));
	RationalNumber od = solution.get_dilation(pVector);
	double od_dij = solution.get_dilation_dijkstra(pVector);
	double diff = abs(boost::rational_cast<double>(od) - od_dij);
	assert(diff <= epsilon );
	assert(abs(boost::rational_cast<double>(od - odV[0][lpmin][rpmin][pVector.size() - 1])) <= epsilon);
	printf("DP  solved with %lld, %lld",odV[0][lpmin][rpmin][pVector.size() - 1].numerator(), odV[0][lpmin][rpmin][pVector.size() - 1].denominator());
	return odV[0][lpmin][rpmin][pVector.size() - 1];

};



void DP::back_trace(int l, int lp, int rp, int r) {
	solution.addEdge(r, l);
	int k = get<0>(back_tracing[l][lp][rp][r]);
	int kl = get<1>(back_tracing[l][lp][rp][r]);
	int kr = get<2>(back_tracing[l][lp][rp][r]);
	if (k == -2) assert(false);
	if (k == -3) {
		assert(kl == -1);
		back_trace(l, lp, kr, r - 1);
		return;
	}
	if (k == -4) {
		assert(kr == -1);
		back_trace( l + 1, kl, rp, r);
		return;
	}
	if (k > 0) {
		assert(kl > k);
		assert(kr < k);
		assert(kr >= 0);
		back_trace(l, lp, kr, k);
		back_trace(k, kl, rp, r);
		return;
	}
	return;

}