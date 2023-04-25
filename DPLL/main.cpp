#include "file_operator.h"
#include "dpll.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	clock_t start = clock();
	Question q;
	Solves s;
	string tmp;
	cin >> tmp;
	cin >> tmp >> q.var_num >> q.clause_num;
	q.clause.resize(q.clause_num);
	int i = 0;
	while (i < q.clause_num) {			
		int t;
		cin >> t;
		q.clause[i].push_back(t);
		if (t == 0) {
			++i;
		}
	}
	//allSolves(q, s);
	//randSolves(q, s);
	set<vector<int>> r = randSolves(q, s, 10);

	clock_t end = clock();
	cout << "time : " << ((double)end - start) / CLOCKS_PER_SEC << "s\n";
	for (int i = 0; i < s.solve.size(); ++i) {
		for (int j = 0; j < s.solve[i].size(); ++j) {
			cout << (s.solve[i][j] > 0 ? j + 1 : -j - 1) << " ";
		}
		cout << endl;
	}
	cout << "solve_num : " << s.solve.size() << endl;
	return 0;
}
